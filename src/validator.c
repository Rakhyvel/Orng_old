#include "validator.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./main.h"
#include "./position.h"
#include <assert.h>
#include <string.h>

static const List* functions = NULL;
static const List* globalVars = NULL;
static const List* enums = NULL;
static const List* depenGraph = NULL;
static const List* strings = NULL;
static const List* verbatims = NULL;
static const Map* includes = NULL;
static const SymbolNode* mainFunction = NULL;
static List* types;

bool looseOnConsts = false;

static const ASTNode* mainFunctionType;
static ASTNode* getType(ASTNode* node, bool intermediate, bool reassigning);
static ASTNode* expandTypeIdent(ASTNode* type, bool reassigning);
void validateAST(ASTNode* node);
void inferTypes(SymbolNode* var);

static void typeMismatchError(struct position pos, ASTNode* expectedType, ASTNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType);
    AST_TypeRepr(actualStr, actualType);
    error(pos, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

static void typeMismatchError2(struct position pos, struct position pos2, ASTNode* expectedType, ASTNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType);
    AST_TypeRepr(actualStr, actualType);
    error2(pos, pos2, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

static void incompatibleTypesError(struct position pos, ASTNode* leftType, ASTNode* rightType)
{
    char leftStr[255];
    char rightStr[255];
    AST_TypeRepr(leftStr, leftType);
    AST_TypeRepr(rightStr, rightType);
    error(pos, "incompatible types: %s and %s", leftStr, rightStr);
}

static void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName)
{
    if (pos2.start_line != 0) {
        error2(pos1, pos2, "symbol '%s' is undefined or not allowed through restriction", symbolName);
    } else {
        error(pos1, "symbol '%s' is undefined", symbolName);
    }
}

/*
* Takes in a dot chain and returns the symbol refered to by the dot chain
* WARNING: Check returns! may be null (undefined) or -1 (restricted)
*/
static SymbolNode* getDotSymbol(ASTNode* type)
{
    ASTNode* left = List_Begin(type->children)->data;
    ASTNode* newLeft = left;
    ASTNode* right = List_Begin(type->children)->next->data;
    SymbolNode* leftSymbol = NULL;

    // new left needs to eventually resolve to a parameter list
    bool resolved = false;
    while (!resolved) {
        // Find symbol, if it's a variable, newLeft is its type
        if (!newLeft) {
            resolved = true;
        } else if (newLeft->astType == AST_IDENT) {
            leftSymbol = Symbol_Find(newLeft->data, type->scope);
            ASTNode* prevNewLeftType = newLeft;
            if (leftSymbol == 0 || leftSymbol == -1) {
                newLeft = NULL;
                resolved = true;
            } else {
                if (leftSymbol->type->astType == AST_UNDEF) {
                    inferTypes(leftSymbol);
                }

                if (leftSymbol->symbolType == SYMBOL_VARIABLE) {
                    newLeft = expandTypeIdent(leftSymbol->type, true);
                    resolved = false;
                } else if (leftSymbol->symbolType == SYMBOL_MODULE) {
                    newLeft = leftSymbol->def;
                    resolved = false;
                } else {
                    resolved = true;
                }
            }
        }
        // Get symbol of left, if it's a variable, get its type
        else if (newLeft->astType == AST_DOT) {
            leftSymbol = getDotSymbol(newLeft);
            if (leftSymbol->symbolType == SYMBOL_VARIABLE) {
                newLeft = leftSymbol->type;
                resolved = false;
            } else {
                resolved = true;
            }
        }
        // Resolved, will iterate through paramlist
        else if (newLeft->astType == AST_PARAMLIST || newLeft->astType == AST_ARRAY) {
            resolved = true;
        }
        // newLeft is in the first child
        else if (newLeft->astType == AST_ADDR || newLeft->astType == AST_DEREF || newLeft->astType == AST_PAREN) {
            newLeft = List_Get(newLeft->children, 0);
            resolved = false;
        }
        // newLeft is in the second child
        else if (newLeft->astType == AST_CAST) {
            newLeft = List_Get(newLeft->children, 1);
            resolved = false;
        }
        // newLeft is in the first child's type
        else if (newLeft->astType == AST_INDEX) {
            ASTNode* arrayType = getType(List_Get(newLeft->children, 0), false, false);
            if (arrayType->astType == AST_ADDR) {
                arrayType = List_Get(arrayType->children, 0);
            }
            if (arrayType->astType != AST_ARRAY) {
                error(type->pos, "indexing on a non-array type");
            }
            ASTNode* dataDefine = List_Get(arrayType->children, 1);
            SymbolNode* dataSymbol = dataDefine->data;
            ASTNode* dataAddrType = dataSymbol->type;
            newLeft = List_Get(dataAddrType->children, 0);
            resolved = false;
        } else if (newLeft->astType == AST_EXTERN) {
            SymbolNode* var = newLeft->data;
            newLeft = var->def;
            resolved = false;
        }
        // newLeft is the type of the array data
        else if (newLeft->astType == AST_ARRAY) {
            ASTNode* define = List_Get(newLeft->children, 1);
            SymbolNode* var = define->data;
            if (var->symbolType == SYMBOL_VARIABLE) {
                newLeft = var->type;
                resolved = false;
            } else {
                leftSymbol = var;
                resolved = true;
            }
        } else if (newLeft->astType == AST_CALL) {
            newLeft = getType(newLeft, false, false);
            resolved = false;
        } else { // unreachable, likely not an L value
            error(left->pos, "left side of dot expression is not an l value");
            return NULL;
        }
    }

    SymbolNode* rightSymbol = NULL;
    if (!newLeft) {
        error(left->pos, "left side could not be resolved to a container");
    } else if (newLeft->astType == AST_PARAMLIST || newLeft->astType == AST_ARRAY) {
        // Search paramlists' defines for a symbol that matches
        ListElem* elem = List_Begin(newLeft->children);
        for (; rightSymbol == NULL && elem != List_End(newLeft->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* attr = define->data;
            if (!strcmp(attr->name, right->data)) {
                rightSymbol = attr;
                break;
            }
        }
        if (rightSymbol == NULL) {
            error(type->pos, "identifier '%s' not a member of parameterlist", right->data);
        }
    } else { // ERROR! NOT A PARAMLIST!
        // Search symbol for a symbol that matches
        rightSymbol = Map_Get(leftSymbol->children, right->data);
        if (rightSymbol == NULL) {
            if (newLeft->astType == AST_IDENT) {
                error(type->pos, "symbol '%s' is not a member of '%s'", right->data, newLeft->data);
            } else {
                error(type->pos, "symbol '%s' is not a member of expression", right->data);
            }
        } else if (!rightSymbol->isPublic) {
            error(type->pos, "cannot access non-public member '%s'", right->data);
        }
    }
    type->data = rightSymbol;
    return rightSymbol;
}

static void validateLValue(ASTNode* node)
{
    switch (node->astType) {
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        if (var->type->isConst) {
            error(node->pos, "symbol '%s' is constant", var->name);
        }
        break;
    }
    case AST_PAREN: {
        ASTNode* child = List_Get(node->children, 0);
        validateLValue(child);
        break;
    }
    case AST_INDEX: {
        ASTNode* child = List_Get(node->children, 0);
        validateLValue(child);
        ASTNode* childType = getType(child, false, false);
        if (childType->astType != AST_ARRAY && childType->astType != AST_ADDR) {
            ASSERT(0);
        }
        if (childType->astType == AST_ADDR) {
            childType = List_Get(childType->children, 0);
        }
        ASTNode* dataDefine = List_Get(childType->children, 1);
        SymbolNode* dataSymbol = dataDefine->data;
        ASTNode* dataAddrType = dataSymbol->type;
        ASTNode* dataType = List_Get(dataAddrType->children, 0);
        if (dataType->isConst) {
            error(node->pos, "array data type is constant");
        }
        break;
    }
    case AST_DEREF: {
        ASTNode* child = List_Get(node->children, 0);
        if (child->astType != AST_ADDROF) {
            validateLValue(child);
        }
        ASTNode* childType = getType(child, false, false);
        if (childType->astType != AST_ADDR) {
            ASSERT(0);
        }
        ASTNode* underlyingType = List_Get(childType->children, 0);

        if (underlyingType->isConst) {
            error(node->pos, "address expression is constant");
        }
        break;
    }
    case AST_DOT: {
        SymbolNode* var = getDotSymbol(node);
        if (var == 0 || var == 1) {
            error(node->pos, "dot expression does not resolve to a symbol");
        } else if (var->type->isConst) {
            error(node->pos, "symbol '%s' is constant", var->name);
        }
        break;
    }
    default:
        error(node->pos, "left side of assignment is not assignable");
    }
}

static ASTNode* resolveDotTypes(ASTNode* node, bool reassigning)
{
    if (node->astType == AST_DOT) {
        SymbolNode* dotSymbol = getDotSymbol(node);
        if (dotSymbol == 0 || dotSymbol == -1) {
            error(node->pos, "dot expression doesn't resolve to a symbol");
        }
        if (reassigning && dotSymbol->isExtern) {
            return AST_Create(AST_EXTERN, dotSymbol, dotSymbol, dotSymbol->pos, false);
        } else {
            return dotSymbol->def;
        }
    } else {
        return node;
    }
}

/*
* Takes in a type and expands type identifiers, and resolves dot types
* 
* if reassigning, don't expand extern types further
* else, expand extern types further
*/
static ASTNode* expandTypeIdent(ASTNode* type, bool reassigning)
{
    int loopCounter = 0;
    ASTNode* expanded = type;
    while (expanded->astType == AST_IDENT) {
        SymbolNode* var = Symbol_Find(expanded->data, expanded->scope);
        if (var != 0 && var != -1) {
            if (var->symbolType != SYMBOL_TYPE && var->symbolType != SYMBOL_ENUM) {
                ASTNode* varType = getType(var->def, false, false);
                if (varType->astType != AST_IDENT || strcmp(varType->data, "Type")) {
                    error2(type->pos, var->pos, "symbol '%s' is not a type", var->name);
                }
            }
            if (var->symbolType == SYMBOL_ENUM) {
                expanded = AST_Create(AST_ENUM, var, type->scope, type->pos, false);
            } else {
                if (reassigning && var->isExtern) {
                    expanded = AST_Create(AST_EXTERN, var, type->scope, type->pos, false);
                    break;
                } else {
                    expanded = var->def;
                }
            }
        } else if (!strcmp(expanded->data, "String")) {
            expanded = STRING_TYPE;
        } else if (!strcmp(expanded->data, "Module") && !expanded->isConst) {
            printf("Found one\n");
        } else {
            break;
        }
        if (loopCounter > 255) {
            error(type->pos, "exceeded type cycle limit");
        }
        loopCounter++;
    }
    if (expanded->astType == AST_ADDR) {
        ASTNode* oldType = List_Get(expanded->children, 0);
        expanded->children->head.next->data = expandTypeIdent(oldType, reassigning);
    } else if (expanded->astType == AST_PARAMLIST || expanded->astType == AST_ARRAY) {
        ListElem* elem = List_Begin(expanded->children);
        for (; elem != List_End(expanded->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* symbol = define->data;
            Validator_Validate(symbol);
        }
    } else if (expanded->astType == AST_PROCEDURE || expanded->astType == AST_FUNCTION) {
        ListElem* params = List_Begin(expanded->children);
        ListElem* rets = params->next;
        params->data = expandTypeIdent(params->data, true);
        rets->data = expandTypeIdent(rets->data, true);
    } else if (expanded->astType == AST_C_ARRAY) {
        ListElem* dataType = List_Begin(expanded->children);
        dataType->data = expandTypeIdent(dataType->data, true);
    }
    if (expanded->astType == AST_EXTERN && !reassigning) {
        SymbolNode* externVar = expanded->data;
        if (externVar->def->astType != AST_UNDEF) { // Extern symbols don't need a def, if they do, expand else leave as an extern
            expanded = expandTypeIdent(externVar->def, reassigning);
        }
    }

    while (expanded->astType == AST_DOT) {
        expanded = resolveDotTypes(expanded, reassigning);
    }

    return expanded;
}

void collectType(ASTNode* type)
{
    ListElem* elem = List_Begin(types);
    bool withinList = false;
    for (; elem != List_End(types); elem = elem->next) {
        ASTNode* otherType = elem->data;
        if (typesAreEquivalent(otherType, type)) {
            withinList = true;
            break;
        }
    }
    if (!withinList) {
        List_Append(types, type);
    }
}

/*
* Assumes that all subnodes have already been validated
* 
* @param intermediate	In the case of a dot chain with two or more dots, whether or not the this node is not the head dot in the dot chain
* @param reassigning	when reassigning, do not expand 
*/
static ASTNode* getType(ASTNode* node, bool intermediate, bool reassigning)
{
    ASSERT(node != NULL);
    //ASSERT(node->isValid);
    if (node->type != NULL && reassigning) {
        return node->type;
    }
    ASTNode* type = NULL;

    switch (node->astType) {
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        if (var == 0) {
            restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->data);
        } else if (var == -1) {
            restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->data);
        }
        if (var->type->astType == AST_UNDEF) {
            inferTypes(var);
        }
        type = expandTypeIdent(var->type, reassigning);
        break;
    }
    case AST_CALL: {
        ASTNode* call = List_Get(node->children, 0);
        ASTNode* functionType = getType(call, false, reassigning);
        ASTNode* functionReturn = List_Get(functionType->children, 1);
        type = expandTypeIdent(functionReturn, reassigning);
        break;
    }
    case AST_INT: {
        type = INT32_TYPE;
        break;
    }
    case AST_STRING: {
        type = CONST_STRING_TYPE;
        break;
    }
    case AST_CHAR: {
        type = CONST_CHAR_TYPE;
        break;
    }
    case AST_REAL: {
        type = REAL32_TYPE;
        break;
    }
    case AST_NEG: {
        type = INT32_TYPE;
        break;
    }
    case AST_ADD:
    case AST_SUBTRACT:
    case AST_MULTIPLY:
    case AST_DIVIDE:
    case AST_MODULUS:
    case AST_PAREN:
    case AST_BIT_OR:
    case AST_BIT_XOR:
    case AST_BIT_AND:
    case AST_LSHIFT:
    case AST_RSHIFT:
    case AST_BIT_NOT:
    case AST_ASSIGN:
    case AST_ADD_ASSIGN:
    case AST_SUB_ASSIGN:
    case AST_MULT_ASSIGN:
    case AST_DIV_ASSIGN:
    case AST_MOD_ASSIGN:
    case AST_AND_ASSIGN:
    case AST_OR_ASSIGN:
    case AST_XOR_ASSIGN:
    case AST_LSHIFT_ASSIGN:
    case AST_RSHIFT_ASSIGN:
    case AST_NAMED_ARG:
    case AST_RETURN: { // TODO: Maybe add a more nuanced system?
        ASTNode* left = List_Get(node->children, 0);
        type = getType(left, false, reassigning);
        break;
    }
    case AST_DEREF: {
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* addr = getType(left, false, reassigning);
        type = List_Get(addr->children, 0);
        break;
    }
    case AST_ADDROF: {
        ASTNode* innerType = getType(List_Get(node->children, 0), false, reassigning);
        ASTNode* addrType = AST_Create(AST_ADDR, 0, node->scope, (Position) { 0, 0, 0, 0 }, true);
        List_Append(addrType->children, innerType);
        type = addrType;
        break;
    }
    case AST_INDEX: {
        ASTNode* arrType = getType(List_Get(node->children, 0), false, reassigning);
        if (arrType->astType == AST_ARRAY) {
            ASTNode* define = List_Get(arrType->children, 1);
            SymbolNode* arrSymbol = define->data;
            type = expandTypeIdent(List_Get(arrSymbol->type->children, 0), reassigning);
        } else if (arrType->astType == AST_ADDR) {
            ASTNode* innerType = List_Get(arrType->children, 0);
            if (innerType->astType == AST_ARRAY) {
                ASTNode* define = List_Get(innerType->children, 1);
                SymbolNode* arrSymbol = define->data;
                type = expandTypeIdent(List_Get(arrSymbol->type->children, 0), reassigning);
            } else {
                type = expandTypeIdent(List_Get(arrType->children, 0), reassigning);
            }
        }
        break;
    }
    case AST_NULL: {
        ASTNode* voidPtr = AST_Create(AST_VOID, 0, node->scope, (Position) { 0, 0, 0, 0 }, true);
        ASTNode* addrType = AST_Create(AST_ADDR, 0, node->scope, (Position) { 0, 0, 0, 0 }, true);
        List_Append(addrType->children, voidPtr);
        type = addrType;
        break;
    }
    case AST_SIZEOF: {
        type = INT32_TYPE;
        break;
    }
    case AST_NOT:
    case AST_OR:
    case AST_AND:
    case AST_NEQ:
    case AST_EQ:
    case AST_GTR:
    case AST_GTE:
    case AST_LSR:
    case AST_LTE:
    case AST_TRUE:
    case AST_FALSE: {
        type = CONST_BOOL_TYPE;
        break;
    }
    case AST_IFELSE: {
        ASTNode* body = List_Begin(node->children)->next->data;
        ASTNode* elseBody = List_Begin(node->children)->next->next->data;
        ASTNode* bodyType = getType(body, false, false);
        ASTNode* elseBodyType = getType(elseBody, false, false);
        if (typesAreEquivalent(bodyType, elseBodyType)) {
            type = elseBodyType;
        } else if (typesAreEquivalent(elseBodyType, bodyType)) {
            type = bodyType;
        } else {
            type = UNDEF_TYPE;
        }
        break;
    }
    case AST_BLOCK:
    case AST_FOR:
    case AST_CASE: {
        ASTNode* lastNode = List_Get(node->children, node->children->size - 1);
        if (lastNode != NULL) {
            type = getType(lastNode, false, false);
        } else {
            type = UNDEF_TYPE;
		}
        break;
    }
    case AST_SWITCH: {
        if (node->children->size < 1) {
            type = UNDEF_TYPE;
            break;
        } else {
            ASTNode* firstCase = List_Get(node->children, 1);
            ASTNode* firstCaseType = getType(firstCase, false, false);
            type = firstCaseType;
            for (ListElem* elem = List_Begin(node->children)->next; elem != List_End(node->children); elem = elem->next) {
                ASTNode* caseNode = elem->data;
                ASTNode* caseNodeType = getType(caseNode, false, false);
                if (!typesAreEquivalent(firstCaseType, caseNodeType) || !typesAreEquivalent(caseNodeType, firstCaseType)) {
                    type = UNDEF_TYPE;
                    break;
                }
            }
            break;
        }
    }
    case AST_ARGLIST:
    case AST_UNDEF:
    case AST_DEFINE:
    case AST_IF:
    case AST_FREE:
    case AST_DEFER:
    case AST_BREAK:
    case AST_CONTINUE: {
        type = UNDEF_TYPE;
        break;
    }
    case AST_CAST: {
        type = List_Get(node->children, 1);
        break;
    }
    case AST_DOT: {
        ASTNode* left = List_Begin(node->children)->data;
        ASTNode* right = List_Begin(node->children)->next->data;
        ASTNode* leftType = getType(left, left->astType != AST_DOT, reassigning); // need to know the type of the left side of dot
        leftType = expandTypeIdent(resolveDotTypes(leftType, false), reassigning);
        ASTNode* paramlist = NULL;

        bool resolved = false;
        if (leftType->astType == AST_IDENT && (!strcmp(leftType->data, "Module") || !strcmp(leftType->data, "Package") || !strcmp(leftType->data, "Enum"))) {
            SymbolNode* leftSymbol = NULL;
            if (left->astType == AST_IDENT) {
                leftSymbol = Symbol_Find(left->data, left->scope);
            } else if (left->astType == AST_DOT) {
                leftSymbol = getDotSymbol(left);
            } else {
                ASSERT(0);
            }
            if (leftSymbol->def->astType == AST_PARAMLIST || leftSymbol->def->astType == AST_VOID) {
                paramlist = leftSymbol->def;
            } else if (leftSymbol->def->astType == AST_DOT) {
                SymbolNode* dotSymbol = getDotSymbol(leftSymbol->def);
                paramlist = dotSymbol->def;
            } else {
                error(leftSymbol->pos, "leftSymbol def ast type was %s, is that right?", AST_GetString(leftSymbol->def->astType));
            }
        } else if (leftType->astType == AST_IDENT && !strcmp(leftType->data, "Type")) {
            SymbolNode* leftSymbol = NULL;
            if (left->astType == AST_IDENT) {
                leftSymbol = Symbol_Find(left->data, left->scope);
            } else if (left->astType == AST_DOT) {
                leftSymbol = getDotSymbol(left);
            } else {
                ASSERT(0);
            }
            paramlist = leftSymbol->def;
        } else if (leftType->astType == AST_ADDR) {
            paramlist = expandTypeIdent((ASTNode*)List_Get(leftType->children, 0), reassigning);
        } else if (leftType->astType == AST_PARAMLIST || leftType->astType == AST_ARRAY) {
            paramlist = leftType;
        } else if (leftType->astType == AST_EXTERN) {
            SymbolNode* leftSymbol = leftType->data;
            paramlist = leftSymbol->def;
        } else {
            error(left->pos, "left side of dot must be container");
        }
        if (paramlist->astType == AST_EXTERN) {
            SymbolNode* var = paramlist->data;
            paramlist = var->def;
        }

        if (paramlist->astType == AST_ADDR) { // done to weed out dots on double addresses, does this work?
            error(left->pos, "left side of dot must be container");
        }

        ListElem* elem = List_Begin(paramlist->children);
        SymbolNode* attr = NULL;
        for (; type == NULL && elem != List_End(paramlist->children); elem = elem->next) {
            ASTNode* define = elem->data;
            attr = define->data;
            if (!strcmp(attr->name, right->data)) {
                ASTNode* retval = expandTypeIdent(attr->type, reassigning);
                if (leftType->astType == AST_IDENT && !strcmp(leftType->data, "Type") && !retval->isConst) {
                    error(node->pos, "type access is not a constant");
                }
                if (intermediate && retval->astType == AST_IDENT && (!strcmp(retval->data, "Module") || !strcmp(retval->data, "Package"))) {
                    type = attr->def;
                    break;
                } else {
                    type = retval;
                    break;
                }
            }
        }
        if (type == NULL) {
            if (left->astType == AST_IDENT) {
                error(node->pos, "symbol '%s' is not a member of '%s'", right->data, left->data);
            } else {
                error(node->pos, "symbol '%s' is not a member of left-side expression", right->data);
            }
        } else if (!attr->isPublic) {
            error(node->pos, "cannot access non-public member '%s'", right->data);
        }
        break;
    }
    case AST_VOID: {
        type = node;
        break;
    }
    case AST_ENUM:
    case AST_PARAMLIST:
    case AST_FUNCTION:
    case AST_PROCEDURE:
    case AST_ADDR:
    case AST_ARRAY: {
        type = TYPE_TYPE;
        break;
    }
    case AST_ARRAY_LITERAL: {
        ASTNode* firstElem = List_Begin(node->children)->data;
        ASTNode* firstType = getType(firstElem, false, reassigning);
        type = createArrayTypeNode(firstType, node->children->size, true);
        type->isConst = true;
        break;
    }
    case AST_NEW: {
        ASTNode* newType = List_Get(node->children, 0);
        ASTNode* addr = AST_Create(AST_ADDR, NULL, node->scope, node->pos, false);
        List_Append(addr->children, newType);
        type = addr;
        break;
    }
    default:
        error(node->pos, "unimplemented type inference for AST Node %s", AST_GetString(node->astType));
    }

    node->type = type;
    collectType(type);
    return type;
}

static int scalarTypeType(ASTNode* node)
{
    if (node->astType == AST_ENUM) {
        return 0;
    } else if (node->astType != AST_IDENT) {
        return -1;
    } else {
        if (!strcmp(node->data, "Int8")) {
            return 0;
        } else if (!strcmp(node->data, "Int16")) {
            return 0;
        } else if (!strcmp(node->data, "Int32") || !strcmp(node->data, "Int")) {
            return 0;
        } else if (!strcmp(node->data, "Int64")) {
            return 0;
        } else if (!strcmp(node->data, "Real32") || !strcmp(node->data, "Real")) {
            return 1;
        } else if (!strcmp(node->data, "Real64")) {
            return 1;
        } else {
            return -1;
        }
    }
}

// a is subset of b
// returns -1 if N/A, 0 if applicable and incompatible, and 1 if applicable and compatible
static int typesAreCompatible(ASTNode* a, ASTNode* b)
{
    int aIntType = scalarTypeType(a);
    int bIntType = scalarTypeType(b);
    if (aIntType < 0 || bIntType < 0) {
        return -1;
    } else {
        if (a->astType != AST_ENUM && b->astType == AST_ENUM || a->astType == AST_ENUM && b->astType == AST_ENUM) {
            return -1;
        } else {
            return aIntType <= bIntType;
        }
    }
}

/*
checks whether A <= B, that is "is A a subtype of B"
Note that there is no subtype polymorphism other than Int <: Enum and T <: :T
All other types are distinct
*/
bool typesAreEquivalent(ASTNode* a, ASTNode* b)
{
    ASTNode* aExpand = expandTypeIdent(a, true);
    ASTNode* bExpand = expandTypeIdent(b, true);

    if (aExpand->astType == AST_EXTERN) {
        SymbolNode* var = aExpand->data;
        if (var->def->astType == AST_UNDEF) {
            return true;
        } else {
            aExpand = var->def;
        }
    }
    if (bExpand->astType == AST_EXTERN) {
        SymbolNode* var = bExpand->data;
        if (var->def->astType == AST_UNDEF) {
            return true;
        } else {
            bExpand = var->def;
        }
    }

    if (aExpand->visited && bExpand->visited) {
        return true;
    }

    // check if a < b (a is compatible with b)
    int compatiblility = typesAreCompatible(aExpand, bExpand);
    if (compatiblility != -1) {
        return compatiblility;
    }
    if (bExpand->astType == AST_IDENT && !strcmp(bExpand->data, "Module") && aExpand->astType == AST_IDENT && !strcmp(aExpand->data, "Type")) {
        return true;
    }
    if (bExpand->astType == AST_IDENT && !strcmp(bExpand->data, "Package")) {
        return true;
    }
    if (!looseOnConsts && bExpand->isConst && !aExpand->isConst) {
        return false;
    }

    bool retval = true;
    if (aExpand->astType != bExpand->astType && !(bExpand->astType == AST_PROCEDURE && aExpand == AST_FUNCTION)) {
        if (aExpand->astType == AST_C_ARRAY) {
            ASTNode* dataType = List_Get(aExpand->children, 0);
            retval = typesAreCompatible(dataType, bExpand);
        } else if (bExpand->astType == AST_C_ARRAY) {
            ASTNode* dataType = List_Get(bExpand->children, 0);
            retval = typesAreCompatible(aExpand, dataType);
        } else {
            retval = false;
        }
    } else if (aExpand->children->size != bExpand->children->size) {
        retval = false;
    } else {
        switch (aExpand->astType) {
        case AST_IDENT: {
            bool equiv = aExpand->data && bExpand->data && !strcmp(aExpand->data, bExpand->data);
            if (!equiv && (!strcmp(aExpand->data, "Int") && bExpand->astType == AST_ENUM)) {
                equiv = true;
            }
            retval = equiv;
            break;
        }
        case AST_ENUM: {
            SymbolNode* aSymbol = aExpand->data;
            retval = aSymbol->parent == bExpand->data;
            break;
        }
        case AST_FUNCTION:
        case AST_PROCEDURE:
            ASTNode* aLeft = List_Begin(aExpand->children)->data;
            ASTNode* aRight = List_Begin(aExpand->children)->next->data;
            ASTNode* bLeft = List_Begin(bExpand->children)->data;
            ASTNode* bRight = List_Begin(bExpand->children)->next->data;
            aExpand->visited = true;
            bExpand->visited = true;
            bool equiv = typesAreEquivalent(aLeft, bLeft) && typesAreEquivalent(aRight, bRight);
            retval = equiv;
            break;
        case AST_DOT: {
            ASTNode* aLeft = List_Begin(aExpand->children)->data;
            ASTNode* aRight = List_Begin(aExpand->children)->next->data;
            ASTNode* bLeft = List_Begin(bExpand->children)->data;
            ASTNode* bRight = List_Begin(bExpand->children)->next->data;
            aExpand->visited = true;
            bExpand->visited = true;
            bool equiv = typesAreEquivalent(aLeft, bLeft) && typesAreEquivalent(aRight, bRight);
            retval = equiv;
            break;
        }
        case AST_C_ARRAY: {
            ASTNode* aLeft = List_Get(aExpand->children, 0);
            ASTNode* bLeft = List_Get(bExpand->children, 0);
            ASTNode* aLength = List_Get(aExpand->children, 1);
            ASTNode* bLength = List_Get(bExpand->children, 1);
            aExpand->visited = true;
            bExpand->visited = true;
            if (bLength->astType == AST_INT && (aLength->astType != AST_INT || aLength->data != bLength->data)) {
                retval = false;
            } else {
                retval = typesAreEquivalent(aLeft, bLeft);
            }
            break;
        }
        case AST_ADDR: {
            ASTNode* aLeft = List_Begin(aExpand->children)->data;
            ASTNode* bLeft = List_Begin(bExpand->children)->data;
            aExpand->visited = true;
            bExpand->visited = true;
            if (aLeft->astType == AST_VOID || bLeft->astType == AST_VOID) {
                // void addr is always compatible
                retval = true;
            } else {
                retval = typesAreEquivalent(aLeft, bLeft);
            }
            break;
        }
        case AST_ARRAY:
        case AST_PARAMLIST: {
            ListElem* aElem = List_Begin(aExpand->children);
            ListElem* bElem = List_Begin(bExpand->children);
            bool allEquiv = true;
            // For each parameter in the procedure's parameter list, print it out
            for (; aElem != List_End(aExpand->children); aElem = aElem->next, bElem = bElem->next) {
                ASTNode* aDefine = aElem->data;
                SymbolNode* aSymbol = aDefine->data;
                ASTNode* aType = aSymbol->type;
                ASTNode* bDefine = bElem->data;
                SymbolNode* bSymbol = bDefine->data;
                ASTNode* bType = bSymbol->type;
                aExpand->visited = true;
                bExpand->visited = true;
                bool fieldNamesSame = (aSymbol == NULL || bSymbol == NULL || !strcmp(aSymbol->name, bSymbol->name));
                bool typeEquiv = typesAreEquivalent(aType, bType);
                bool bothPub = (aSymbol == NULL || bSymbol == NULL || aSymbol->isPublic == bSymbol->isPublic);
                allEquiv &= typeEquiv && fieldNamesSame && bothPub;
            }
            retval = allEquiv;
            break;
        }
        case AST_VOID: {
            retval = true;
            break;
        }
        }
    }
    aExpand->visited = false;
    bExpand->visited = false;
    return retval;
}

bool identIsPrimitive(char* data)
{
    return !strcmp(data, "Int") || //
        !strcmp(data, "Char") || //
        !strcmp(data, "Bool") || //
        !strcmp(data, "Char") || //
        !strcmp(data, "Real") || //
        !strcmp(data, "String") || //
        !strcmp(data, "Type") || //
        !strcmp(data, "Module") || //
        !strcmp(data, "Package") || //
        !strcmp(data, "Enum") || //
        !strcmp(data, "Int8") || //
        !strcmp(data, "Int16") || //
        !strcmp(data, "Int32") || //
        !strcmp(data, "Int64") || //
        !strcmp(data, "Real32") || //
        !strcmp(data, "Real64");
}

void validateType(ASTNode* node)
{
    ASSERT(node != NULL);
    if (node->isValid) {
        return;
    }
    node->isValid = true;

    switch (node->astType) {
    case AST_IDENT: {
        if (strcmp(node->data, "Int") && //
            strcmp(node->data, "Char") && //
            strcmp(node->data, "Bool") && //
            strcmp(node->data, "Char") && //
            strcmp(node->data, "Real") && //
            strcmp(node->data, "String") && //
            strcmp(node->data, "Type") && //
            strcmp(node->data, "Module") && //
            strcmp(node->data, "Package") && //
            strcmp(node->data, "Enum") && //
            strcmp(node->data, "Int8") && //
            strcmp(node->data, "Int16") && //
            strcmp(node->data, "Int32") && //
            strcmp(node->data, "Int64") && //
            strcmp(node->data, "Real32") && //
            strcmp(node->data, "Real64")) {
            SymbolNode* var = Symbol_Find(node->data, node->scope);
            if (var == NULL) {
                restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->data);
            } else if (var == -1) {
                restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->data);
            } else if (var->symbolType != SYMBOL_TYPE && var->symbolType != SYMBOL_ENUM) {
                error(node->pos, "symbol '%s' is not a type 2", node->data);
            }
        }
        break;
    }
    case AST_PARAMLIST: {
        validateAST(node);
        break;
    }
    case AST_DOT: {
        validateAST(node);
        ASTNode* dotType = getType(node, false, false);
        if (dotType->astType != AST_IDENT || !(!strcmp(dotType->data, "Type") || !strcmp(dotType->data, "Enum"))) {
            error(node->pos, "symbol '%s' is not a type 3", ((ASTNode*)List_Get(node->children, 1))->data);
        }
        SymbolNode* var = getDotSymbol(node);
        break;
    }
    case AST_FUNCTION:
    case AST_PROCEDURE: {
        ASTNode* params = List_Get(node->children, 0);
        ASTNode* rets = List_Get(node->children, 1);
        validateType(params);
        validateType(rets);
        break;
    }
    case AST_C_ARRAY:
        ASTNode* base = List_Get(node->children, 0);
        ASTNode* length = List_Get(node->children, 1);
        validateType(base);
        validateAST(length);
        break;
    case AST_ADDR: {
        ASTNode* base = List_Get(node->children, 0);
        validateType(base);
        break;
    }
    case AST_EXTERN: {
        SymbolNode* type = node->data;
        if (!typesAreEquivalent(type->type, TYPE_TYPE) && !typesAreEquivalent(type->type, ENUM_TYPE)) {
            typeMismatchError(node->pos, TYPE_TYPE, type->type);
        }
        break;
    }
    case AST_ARRAY: {
        ASTNode* typeDefine = List_Get(node->children, 1);
        ASTNode* lengthDefine = List_Get(node->children, 0);
        SymbolNode* type = typeDefine->data;
        SymbolNode* length = lengthDefine->data;
        validateType(type->type);
        ASTNode* lengthType = getType(length->def, "", false);
        if (lengthType->astType != AST_UNDEF && !typesAreEquivalent(lengthType, INT32_TYPE)) {
            typeMismatchError(node->pos, INT32_TYPE, lengthType);
        }
        break;
    }
    case AST_VOID:
    case AST_UNDEF:
    case AST_ENUM: {
        break;
    }
    default: {
        error(node->pos, "not a type");
    }
    }
}

void inferTypes(SymbolNode* var)
{
    if (var->def && var->symbolType != SYMBOL_FUNCTION && var->symbolType != SYMBOL_PROCEDURE) {
        if (!var->def->isValid) {
            validateAST(var->def);
        }
        // if type is undef, type is type of def
        // else, type must match type of def
        ASTNode* defType = getType(var->def, false, true);
        if (var->type->astType == AST_UNDEF) {
            // No type annot., infer types
            bool wasConst = var->type->isConst;
            var->type = defType;
            var->type->isConst = wasConst;

            if (defType->astType == AST_IDENT && !strcmp(defType->data, "Type")) {
                var->symbolType = SYMBOL_TYPE;
            } else if (defType->astType == AST_IDENT && !strcmp(defType->data, "Module")) {
                var->symbolType = SYMBOL_MODULE;
                var->type->isConst = true;
            } else if (defType->astType == AST_IDENT && !strcmp(defType->data, "Package")) {
                var->symbolType = SYMBOL_PACKAGE;
                var->type->isConst = true;
            }
            if (var->type->astType == AST_UNDEF) {
                error(var->pos, "cannot infer type of symbol '%s', try using a cast", var->name);
            }
        } else {
            bool typesEquivalent = typesAreEquivalent(defType, var->type);

            if (defType && (defType->astType != AST_UNDEF || var->def->astType != AST_UNDEF) && !typesEquivalent) {
                // Type annot.'d, types disagree
                typeMismatchError(var->pos, var->type, defType);
            } else {
                // Types annot.'d, types agree
                var->type = expandTypeIdent(var->type, true);
                validateType(var->type);
                var->def->type = var->type;
            }
        }
    }
}

void namedArgsMatch(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    Map* argNames = Map_Create(); // maps param names:String -> arg expressions:&ASTNode

    for (ListElem* elem = List_Begin(args->children); elem != List_End(args->children); elem = elem->next) {
        ASTNode* namedArg = elem->data;
        if (namedArg->astType != AST_NAMED_ARG) {
            error(namedArg->pos, "positional argument specified in named argument list");
        }
        ASTNode* argExpr = List_Get(namedArg->children, 0);
        if (Map_Put(argNames, namedArg->data, argExpr)) {
            error(namedArg->pos, "named argument specified twice in the same argument list");
        }
    }

    while (!List_IsEmpty(args->children)) {
        List_Pop(args->children);
    }

    if (expr && expr->astType == AST_DOT && params->children->size > 0) {
        SymbolNode* var = expr->data;
        if (var->parent && var->parent->symbolType == SYMBOL_TYPE) {
            // CALL( DOT(self, methodName), ARGLIST(...) )
            // CALL( DOT(self, methodName), ARGLIST(self, ...) )
            ASTNode* self = List_Get(expr->children, 0);
            ASTNode* firstParamDefine = List_Get(params->children, 0);
            SymbolNode* firstParamVar = firstParamDefine->data;
            if (Map_Put(argNames, firstParamVar->name, self)) {
                error(self->pos, "self argument already specified in the argument list");
            }
        }
    }

    for (ListElem* elem = List_Begin(params->children); elem != List_End(params->children); elem = elem->next) {
        ASTNode* define = elem->data;
        SymbolNode* symbol = define->data;
        inferTypes(symbol);
        ASTNode* argExpr = Map_Get(argNames, symbol->name);
        if (argExpr) {
            ASTNode* argType = getType(argExpr, false, false);
            if (!typesAreEquivalent(argType, symbol->type)) {
                if (expr && expr->astType == AST_IDENT) {
                    SymbolNode* var = Symbol_Find(expr->data, expr->scope);
                    typeMismatchError2(argExpr->pos, var->pos, symbol->type, argType);
                } else if (expr && expr->astType == AST_DOT) {
                    SymbolNode* var = expr->data;
                    typeMismatchError2(argExpr->pos, var->pos, symbol->type, argType);
                } else {
                    typeMismatchError(argExpr->pos, symbol->type, argType);
                }
            }
            List_Append(args->children, argExpr);
        } else if (symbol->def->astType == AST_UNDEF) {
            error2(args->pos, symbol->pos, "named argument list does not specify all non-default parameters");
        } else {
            List_Append(args->children, symbol->def);
        }
    }

    Map_Destroy(argNames);
}

void positionalArgsMatch(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    if (expr && expr->astType == AST_DOT && params->children->size > 0) {
        SymbolNode* var = expr->data;
        ASTNode* exprType = getType(expr, false, false);
        if (exprType->astType == AST_ADDR && var->parent && var->parent->symbolType == SYMBOL_TYPE) {
            // CALL( DOT(self, methodName), ARGLIST(...) )
            // CALL( DOT(self, methodName), ARGLIST(self, ...) )
            ASTNode* self = List_Get(expr->children, 0);
            List_Push(args->children, self);
        }
    }

    // arguments are correct arity
    ListElem* paramElem = List_Begin(params->children);
    bool isVararg = false;
    for (; paramElem != List_End(params->children) && !isVararg; paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* paramSymbol = define->data;
        isVararg = paramSymbol->isVararg;
    }

    if (!isVararg && params->children->size < args->children->size - 1) {
        if (expr && expr->astType == AST_IDENT) {
            SymbolNode* var = Symbol_Find(expr->data, expr->scope);
            error2(args->pos, var->pos, "argument list with too many arguments");
        } else if (expr && expr->astType == AST_DOT) {
            SymbolNode* var = expr->data;
            error2(args->pos, var->pos, "argument list with too many arguments");
        } else {
            error(args->pos, "argument list with too many arguments");
        }
    }

    // arguments are correct type
    paramElem = List_Begin(params->children);
    ListElem* argElem = List_Begin(args->children);
    isVararg = false;
    for (; paramElem != List_End(params->children) && argElem != List_End(args->children) && !isVararg; paramElem = paramElem->next, argElem = argElem->next) {
        ASTNode* paramDefine = paramElem->data;
        SymbolNode* paramSymbol = paramDefine->data;
        inferTypes(paramSymbol);
        ASTNode* paramType = expandTypeIdent(paramSymbol->type, false);
        ASTNode* arg = argElem->data;
        if (arg->astType == AST_NAMED_ARG) {
            error(arg->pos, "named argument specified in positional argument list");
        }
        ASTNode* argType = getType(arg, false, true);
        if (!typesAreEquivalent(argType, paramType)) {
            if (expr && expr->astType == AST_IDENT) {
                SymbolNode* var = Symbol_Find(expr->data, expr->scope);
                typeMismatchError2(arg->pos, var->pos, paramType, argType);
            } else if (expr && expr->astType == AST_DOT) {
                SymbolNode* var = expr->data;
                typeMismatchError2(arg->pos, var->pos, paramType, argType);
            } else {
                typeMismatchError(arg->pos, paramType, argType);
            }
        }
    }
    if (paramElem != List_End(params->children)) {
        for (; paramElem != List_End(params->children); paramElem = paramElem->next) {
            ASTNode* paramDefine = paramElem->data;
            SymbolNode* paramSymbol = paramDefine->data;
            ASTNode* paramDef = paramSymbol->def;
            if (paramDef->astType == AST_UNDEF) {
                if (expr && expr->astType == AST_IDENT) {
                    SymbolNode* var = Symbol_Find(expr->data, expr->scope);
                    error2(args->pos, var->pos, "argument list with too few arguments");
                } else if (expr && expr->astType == AST_DOT) {
                    SymbolNode* var = expr->data;
                    error2(args->pos, var->pos, "argument list with too few arguments");
                } else {
                    error(args->pos, "argument list with too few arguments");
                }
            } else {
                List_Append(args->children, paramDef);
            }
        }
    }
}

void argsMatchParams(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    if (args->children->size == 0 && params->children->size == 0) {
        return;
    }

    if (args->children->size == 0 || ((ASTNode*)List_Get(args->children, 0))->astType == AST_NAMED_ARG) {
        namedArgsMatch(expr, args, params);
    } else {
        positionalArgsMatch(expr, args, params);
    }
}

/*
for reference:
integral = int
scalar = integral + Real
arithmetic = scalar + <addr>
chars are not considered integral for later compatability with Python
*/
void validateAST(ASTNode* node)
{
    static List* loops = NULL;
    if (!loops) {
        loops = List_Create();
    }

    ASSERT(node != NULL);
    if (node->isValid) {
        return;
    }
    node->isValid = true;

    if (node->astType != AST_DOT && node->astType != AST_SIZEOF && node->astType != AST_CAST && node->astType != AST_NEW && node->astType != AST_ENUM) {
        if (node->astType == AST_FOR) {
            ASTNode* lastNode = List_Get(node->children, node->children->size - 2);
            List_Push(loops, lastNode->data);
        }
        ListElem* elem = List_Begin(node->children);
        int i = 0;
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* statement = elem->data;
            validateAST(statement);
            node->containsBreak |= statement->astType == AST_BREAK || statement->containsBreak;
            node->containsContinue |= statement->astType == AST_CONTINUE || statement->containsContinue;
            node->containsReturn |= statement->astType == AST_RETURN || statement->containsReturn;
            if (i == node->children->size - 1 && node->astType == AST_FOR) {
                List_Pop(loops);
            }
            i++;
        }
    }

    switch (node->astType) {
    case AST_IF:
    case AST_IFELSE:
    case AST_NOT: {
        // condition (#0) is bool type
        ASTNode* condition = List_Get(node->children, 0);
        ASTNode* conditionType = getType(condition, false, false);
        if (!typesAreEquivalent(conditionType, BOOL_TYPE)) {
            typeMismatchError(condition->pos, BOOL_TYPE, conditionType);
        }
        break;
    }
    case AST_FOR: {
        // condition (#1) is bool type
        ASTNode* condition = List_Get(node->children, 1);
        ASTNode* conditionType = getType(condition, false, false);
        if (!typesAreEquivalent(conditionType, BOOL_TYPE)) {
            typeMismatchError(condition->pos, BOOL_TYPE, conditionType);
        }
        break;
    }
    case AST_SWITCH: {
        // switch expression must be integral
        ASTNode* element = List_Get(node->children, 0);
        ASTNode* elementType = getType(element, false, false);
        if (!typesAreEquivalent(elementType, INT64_TYPE)) {
            typeMismatchError(element->pos, INT64_TYPE, elementType);
        }
        // only one 'else' case
        int elseCaseCount = 0;
        ListElem* elem = List_Begin(node->children);
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* define = elem->data;
            if (define->children->size == 1) {
                elseCaseCount++;
                if (elseCaseCount > 1) {
                    error(define->pos, "multiple else cases in switch statement");
                }
            }
        }
        // TODO: all cases have different numbers
        // TODO: all cases must be comptime integer exprs
        break;
    }
    case AST_RETURN: {
        ASTNode* retval = List_Get(node->children, 0);
        ASTNode* retType = getType(retval, false, false);
        SymbolNode* function = Symbol_TypeAncestor(node->scope, SYMBOL_PROCEDURE);
        if (function == NULL) {
            function = Symbol_TypeAncestor(node->scope, SYMBOL_FUNCTION);
            if (function == NULL) {
                error(node->pos, "return not within procedure or function");
            }
        }
        ASTNode* functionType = function->type;
        ASTNode* functionRetType = List_Get(functionType->children, 1);
        if (retType->astType == AST_VOID) {
            typesAreEquivalent(retType, functionRetType);
        }
        if (!typesAreEquivalent(retType, functionRetType)) {
            typeMismatchError(retval->pos, functionRetType, retType);
        }
        break;
    }
    case AST_BREAK:
    case AST_CONTINUE: {
        // within a for, while, or do-while loop
        if (loops->size == 0) {
            error(node->pos, "%s not in loop", node->data);
        }
        node->data = List_Peek(loops);
        break;
    }
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        if (var == NULL) {
            restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->data);
        } else if (var == -1) {
            restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->data);
        }
        break;
    }
    case AST_DEFINE: {
        SymbolNode* var = node->data;
        /// var type is not Type or Enum
        if (var->type->astType != AST_IDENT || strcmp(var->type->data, "Type") && strcmp(var->type->data, "Enum")) {
            inferTypes(var);
        } else if (!strcmp(var->type->data, "Type")) {
            var->def = expandTypeIdent(var->def, true);
            validateType(var->def);
        } else if (!strcmp(var->type->data, "Enum")) {
            var->def = expandTypeIdent(var->def, true);
        }
        break;
    }
    case AST_INDEX: {
        // left is array or addr type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* leftType = getType(left, false, false);
        if (leftType->astType != AST_ADDR && leftType->astType != AST_ARRAY) {
            error(left->pos, "expected address or array");
        }

        // subscript is integral type
        ASTNode* subscript = List_Get(node->children, 1);
        ASTNode* subscriptType = getType(subscript, false, false);
        if (!typesAreCompatible(subscriptType, INT32_TYPE)) {
            typeMismatchError(subscript->pos, INT32_TYPE, subscriptType);
        }

        // TODO: if subscript is compt, subscript cannot be negative
        // TODO: if sub is comptime and arr is comptime, cannot be greater than array size
        break;
    }
    case AST_DOT: {
        ASTNode* left = List_Get(node->children, 0);
        validateAST(left);
        getType(node, false, true);
        getDotSymbol(node);
        if (node->data == NULL) {
            error(node->pos, "not an l-value");
        }
        break;
    }
    case AST_OR:
    case AST_AND: {
        // left and right are bool types
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        if (!typesAreEquivalent(getType(left, false, false), BOOL_TYPE)) {
            typeMismatchError(left->pos, BOOL_TYPE, getType(left, false, false));
        } else if (!typesAreEquivalent(getType(right, false, false), BOOL_TYPE)) {
            typeMismatchError(right->pos, BOOL_TYPE, getType(right, false, false));
        }
        break;
    }
    case AST_MODULUS:
    case AST_BIT_OR:
    case AST_BIT_XOR:
    case AST_BIT_AND:
    case AST_LSHIFT:
    case AST_RSHIFT: {
        // types on both sides are integral types
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        if (!typesAreEquivalent(getType(left, false, false), INT64_TYPE)) {
            typeMismatchError(left->pos, INT64_TYPE, getType(left, false, false));
        } else if (!typesAreEquivalent(getType(right, false, false), INT64_TYPE)) {
            typeMismatchError(right->pos, INT64_TYPE, getType(right, false, false));
        }
        break;
    }
    case AST_ADD:
    case AST_SUBTRACT:
    case AST_MULTIPLY: {
        // types on both sides are scalar types
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        if (!typesAreEquivalent(getType(left, false, false), REAL64_TYPE)) {
            typeMismatchError(left->pos, REAL64_TYPE, getType(left, false, false));
        } else if (!typesAreEquivalent(getType(right, false, false), REAL64_TYPE)) {
            typeMismatchError(right->pos, REAL64_TYPE, getType(right, false, false));
        }
        break;
    }
    case AST_DIVIDE: {
        // types on both sides are scalar types
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        if (!typesAreEquivalent(getType(left, false, false), REAL64_TYPE)) {
            typeMismatchError(left->pos, REAL64_TYPE, getType(left, false, false));
        } else if (!typesAreEquivalent(getType(right, false, false), REAL64_TYPE)) {
            typeMismatchError(right->pos, REAL64_TYPE, getType(right, false, false));
        }
        // TODO: if denominator is comptime, cannot be 0
        break;
    }
    case AST_EQ:
    case AST_NEQ:
    case AST_GTR:
    case AST_LSR:
    case AST_GTE:
    case AST_LTE: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        // types on both sides are not paramlist types
        if (leftType->astType == AST_PARAMLIST || leftType->astType == AST_ARRAY || rightType->astType == AST_PARAMLIST || rightType->astType == AST_ARRAY) {
            error(node->pos, "comparison on struct type");
        }
        break;
    }
    case AST_ASSIGN: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, true);
        ASTNode* rightType = getType(right, false, true);
        if (!typesAreEquivalent(rightType, leftType)) {
            typeMismatchError(right->pos, leftType, rightType);
        } else {
            right->type = leftType;
        }

        // left type is an l-value
        validateLValue(left);
        break;
    }
    case AST_ADD_ASSIGN:
    case AST_SUB_ASSIGN:
    case AST_MULT_ASSIGN: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        // right type is scalar type and not addr
        if (!typesAreEquivalent(rightType, REAL64_TYPE)) {
            typeMismatchError(right->pos, REAL64_TYPE, rightType);
        }

        // left type is an l-value
        validateLValue(left);
        break;
    }
    case AST_DIV_ASSIGN: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        // right type is scalar type and not addr
        if (!typesAreEquivalent(rightType, REAL64_TYPE)) {
            typeMismatchError(right->pos, REAL64_TYPE, rightType);
        }

        // left type is an l-value
        validateLValue(left);

        // TODO: if comptime, is not 0
        break;
    }
    case AST_AND_ASSIGN: // TODO: make this polymorphic
    case AST_OR_ASSIGN:
    case AST_XOR_ASSIGN: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        // right type is integral type and not addr
        if (!typesAreEquivalent(rightType, INT64_TYPE) && !typesAreEquivalent(rightType, BOOL_TYPE)) {
            error(node->pos, "operator assignment on invalid type");
        }

        // left type is an l-value
        validateLValue(left);
        break;
    }
    case AST_MOD_ASSIGN:
    case AST_LSHIFT_ASSIGN:
    case AST_RSHIFT_ASSIGN: {
        // right type <= left type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* right = List_Get(node->children, 1);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        // right type is integral type and not addr
        if (!typesAreEquivalent(rightType, INT64_TYPE)) {
            typeMismatchError(right->pos, INT64_TYPE, rightType);
        }

        // left type is an l-value
        validateLValue(left);
        break;
    }
    case AST_NEG: {
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* leftType = getType(left, false, false);
        // right type is scalar type
        if (!typesAreEquivalent(leftType, REAL64_TYPE)) {
            typeMismatchError(left->pos, REAL64_TYPE, leftType);
        }
        break;
    }
    case AST_BIT_NOT: {
        // child is an integral type
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* leftType = getType(left, false, false);
        if (!typesAreEquivalent(leftType, INT64_TYPE)) {
            typeMismatchError(left->pos, INT64_TYPE, leftType);
        }
        break;
    }
    case AST_ADDROF: {
        ASTNode* left = List_Get(node->children, 0);
        // left type is an l-value
        validateLValue(left);
        break;
    }
    case AST_DEREF: {
        // child type is scalar
        ASTNode* left = List_Get(node->children, 0);
        ASTNode* leftType = getType(left, false, false);
        if (leftType->astType != AST_ADDR) {
            error(node->pos, "type mismatch, expected address");
        }
        break;
    }
    case AST_CAST: {
        ASTNode* expr = List_Get(node->children, 0);
        validateAST(expr);
        ListElem* elem = List_Begin(node->children)->next;
        // cast type is valid type
        elem->data = expandTypeIdent(elem->data, true);
        ASTNode* cast = elem->data;
        validateType(cast);

        // cannot cast between function addr and data addr
        ASTNode* exprType = getType(expr, false, false);
        if (exprType->astType == AST_ADDR && cast->astType == AST_PROCEDURE) {
            error(node->pos, "cast from data address to procedure address");
        }
        if (exprType->astType == AST_PROCEDURE && cast->astType == AST_ADDR) {
            error(node->pos, "cast from procedure address to data address");
        }
        if (exprType->astType == AST_ADDR && cast->astType == AST_FUNCTION) {
            error(node->pos, "cast from data address to function address");
        }
        if (exprType->astType == AST_FUNCTION && cast->astType == AST_ADDR) {
            error(node->pos, "cast from function address to data address");
        }

        if (expr->astType == AST_ARGLIST || cast->astType == AST_PARAMLIST || cast->astType == AST_ARRAY) {
            if (cast->astType != AST_PARAMLIST && cast->astType != AST_ARRAY) {
                error(node->pos, "cast from arglist to non-arglist type");
            } else {
                expr->type = cast;
                argsMatchParams(NULL, expr, cast);
            }
        }
        break;
    }
    case AST_CALL: {
        // call is to a function type
        ASTNode* expr = List_Get(node->children, 0);
        ASTNode* exprType = getType(expr, false, false);
        if (exprType->astType != AST_PROCEDURE && exprType->astType != AST_FUNCTION) {
            error(node->pos, "call is not to procedure or function");
        }
        argsMatchParams(expr, List_Get(node->children, 1), List_Get(exprType->children, 0));
        break;
    }
    case AST_ENUM: {
        // No duplicates in enum
        Map* map = Map_Create();
        ListElem* elem = List_Begin(node->children);
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* ident = elem->data;
            if (Map_Put(map, ident->data, 1)) {
                error(ident->pos, "identifier '%s' already included in enum", ident->data);
            }
        }
        Map_Destroy(map);
        break;
    }
    case AST_CHAR: {
        // data is a valid character
        if (node->data[0] == '\\') {
            if (strlen(node->data) != 2 || node->data[1] != 'n' && node->data[1] != 'r' && node->data[1] != 't' && node->data[1] != '\\' && node->data[1] != '\'' && node->data[1] != '0') {
                error(node->pos, "invalid character constant");
            }
        } else if (strlen(node->data) != 1 || node->data[0] == '\n') {
            error(node->pos, "invalid character constant");
        }
        break;
    }
    case AST_SIZEOF:
    case AST_NEW: {
        // type is valid
        ListElem* elem = List_Begin(node->children);
        elem->data = expandTypeIdent(elem->data, true);
        validateType(elem->data);
        break;
    }
    case AST_ARRAY_LITERAL: {
        if (node->children->size <= 0) {
            error(node->pos, "array literal is empty");
        }

        ASTNode* firstElem = List_Begin(node->children)->data;
        ASTNode* arrType = getType(firstElem, false, false);

        ListElem* elem = List_Begin(node->children)->next;
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* arrElem = elem->data;
            ASTNode* elemType = getType(arrElem, false, false);
            if (!typesAreEquivalent(arrType, elemType)) {
                typeMismatchError(arrElem->pos, arrType, elemType);
            }
        }
        break;
    }
    case AST_STRING: {
        node->pos.start_line = strings->size;
        List_Append(strings, node);
    } break;
    case AST_DEFER: {
        if (node->containsReturn) {
            error(node->pos, "defer statement cannot contain return");
        } else if (node->containsBreak) {
            error(node->pos, "defer statement cannot contain break");
        } else if (node->containsContinue) {
            error(node->pos, "defer statement cannot contain continue");
        }
    } break;
    case AST_FREE: {
        ASTNode* child = List_Get(node->children, 0);
        ASTNode* childType = getType(child, false, false);
        if (childType->astType != AST_ADDR) {
            char actualStr[255];
            AST_TypeRepr(actualStr, childType);
            error(node->pos, "expected address, got %s", actualStr);
        }
    } break;
    case AST_PARAMLIST:
    case AST_ARRAY:
    case AST_ADDR:
    case AST_FUNCTION:
    case AST_PROCEDURE:
    case AST_NULL:
    case AST_TRUE:
    case AST_FALSE:
    case AST_INT:
    case AST_REAL:
    case AST_PAREN:
    case AST_ARGLIST:
    case AST_BLOCK:
    case AST_UNDEF:
    case AST_VOID:
    case AST_CASE:
    case AST_NAMED_ARG: {
        // Terminals that do not need to be validated other than their children
        break;
    }
    default: {
        error(node->pos, "unvalidatable %d", node->astType);
    }
    }
    node->type = getType(node, false, true);
}

// Validate that all possible paths return some value
// The actual type validation is done earlier for all return types
static bool allReturnPath(ASTNode* node)
{
    if (node->astType == AST_RETURN) {
        return true;
    }

    if (node->astType == AST_IFELSE) {
        return allReturnPath(List_Get(node->children, 1)) && allReturnPath(List_Get(node->children, 2));
    } else if (node->astType == AST_BLOCK) {
        ListElem* elem = List_Begin(node->children);
        for (; elem != List_End(node->children); elem = elem->next) {
            if (allReturnPath(elem->data)) {
                return true;
            }
        }
    }
    return false;
}

static struct graph* addGraphNode(List* depenGraph, ASTNode* structType)
{
    // Check list to see if any graph node has paramlist type
    // If does, append that graphnode to list of dependencies
    // If not, create new grpahnode, append to list of dependencies
    ListElem* elem = List_Begin(depenGraph);
    for (; elem != List_End(depenGraph); elem = elem->next) {
        DGraph* graphNode = elem->data;
        if (typesAreEquivalent(graphNode->structDef, structType)) {
            return graphNode;
        }
    }

    DGraph* graphNode = calloc(1, sizeof(DGraph));
    graphNode->structDef = structType;
    graphNode->visited = false;
    graphNode->ordinal = depenGraph->size;
    graphNode->dependencies = List_Create();
    List_Append(depenGraph, graphNode);

    return graphNode;
}

// Collects structs that are defined in the type portion of a define
static void collectStructs(ASTNode* type)
{
    // Add struct type if it's unique
    if ((type->astType == AST_PARAMLIST || type->astType == AST_ARRAY) && type->children->size > 0) {
        DGraph* graphNode = addGraphNode(depenGraph, type);

        ListElem* paramElem = List_Begin(type->children);
        for (; paramElem != List_End(type->children); paramElem = paramElem->next) {
            ASTNode* fieldDefine = paramElem->data;
            SymbolNode* fieldVar = fieldDefine->data;
            ASTNode* fieldType = expandTypeIdent(fieldVar->type, true);
            if (fieldType->astType == AST_C_ARRAY) {
                fieldType = List_Get(fieldType->children, 0);
            }
            if (fieldType->astType == AST_PARAMLIST || fieldType->astType == AST_ARRAY) {
                DGraph* dependency = addGraphNode(depenGraph, fieldType);
                List_Append(graphNode->dependencies, dependency);
            }
        }
    }

    struct listElem* elem = List_Begin(type->children);
    for (; elem != List_End(type->children); elem = elem->next) {
        ASTNode* child = elem->data;
        collectStructs(child);
    }
    if (type->astType == AST_DEFINE) {
        SymbolNode* var = type->data;
        if (!var->visited || var->parent == NULL) {
            collectStructs(var->type);
            var->visited = true;
        }
    }
}

void collectStructsAST(ASTNode* node)
{
    if (node->astType != AST_DOT && node->astType != AST_CAST) {
        collectStructs(getType(node, false, false));
        struct listElem* elem = List_Begin(node->children);
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* child = elem->data;
            collectStructsAST(child);
        }
    }
}

void collectStructsMain(SymbolNode* symbol)
{
    symbol->visited = true;
    List* children = symbol->children->keyList;
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        collectStructsMain(child);
    }

    if (symbol->isReachable) {
        if (symbol->symbolType == SYMBOL_VARIABLE && symbol->type || symbol->symbolType == SYMBOL_TYPE) {
            collectStructs(symbol->type);
            collectStructs(symbol->def);
        } else if ((symbol->symbolType == SYMBOL_PROCEDURE || symbol->symbolType == SYMBOL_FUNCTION) && symbol->isReachable) {
            ASTNode* returns = (ASTNode*)List_Get(symbol->type->children, 1);
            if (returns->children->size > 1) {
                collectStructs(returns);
            }
            collectStructsAST(symbol->def);
        }
    }
}

void resolveRestrictions(SymbolNode* symbol)
{
    List* allowedIdentifiers = symbol->restrictionExpr;
    ListElem* e = List_Begin(allowedIdentifiers);
    for (; e != List_End(allowedIdentifiers); e = e->next) {
        ASTNode* expr = e->data;
        if (expr->astType == AST_IDENT) {
            List_Append(symbol->restrictions, Symbol_Find(e->data, symbol->parent));
        } else if (expr->astType == AST_DOT) {
            List_Append(symbol->restrictions, getDotSymbol(expr));
        } else {
            error(expr->pos, "expected symbol expression");
        }
    }

    List* children = symbol->children->keyList;
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        resolveRestrictions(child);
    }
}

void reachableSymbol(SymbolNode* symbol);

void reachableAST(ASTNode* node)
{
    ListElem* elem = List_Begin(node->children);
    for (; elem != List_End(node->children); elem = elem->next) {
        ASTNode* child = elem->data;
        reachableAST(child);
    }
    switch (node->astType) {
    case AST_DEFINE: {
        SymbolNode* var = node->data;
        reachableAST(var->def);
    } break;
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        if (var != 0 && var != -1) {
            reachableSymbol(var);
        }
    } break;
    case AST_DOT:
        reachableSymbol(node->data);
        break;
    }
}

void makeChildrenReachable(SymbolNode* symbol)
{
    symbol->isReachable = true;

    List* children = symbol->children->keyList;
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        makeChildrenReachable(child);
    }
}

void reachableSymbol(SymbolNode* symbol)
{
    if (!symbol) {
        return;
    }
    if (symbol->symbolType != SYMBOL_MODULE && symbol->symbolType != SYMBOL_PACKAGE) {
        bool wasReachable = symbol->isReachable;
        makeChildrenReachable(symbol);
        if (!wasReachable) {
            reachableAST(symbol->def);
        }
    }
}

/*
	- can't call procedures
	- can't dereference pointers
	- can't take addresses of
	- can't call new or free
	- can't reference external symbols
	- can't assign to variables outside of function's scope
*/
ASTNode* isASTStateful(ASTNode* node)
{
    ListElem* elem = List_Begin(node->children);
    if (node->astType != AST_DOT) {
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* child = elem->data;
            ASTNode* res = isASTStateful(child);
            if (res) {
                return res;
            }
        }
    }
    switch (node->astType) {
    case AST_DEREF:
    case AST_ADDROF:
    case AST_NEW:
    case AST_FREE:
        return node;
    case AST_INDEX: {
        ASTNode* child = List_Get(node->children, 0);
        ASTNode* type = getType(child, false, false);
        if (type->astType == AST_ADDR) {
            return node;
        } else {
            return NULL;
        }
    }
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        if (var->isExtern) {
            return node;
        }
        return var->parent != NULL && var->parent->symbolType != SYMBOL_BLOCK && var->parent->symbolType != SYMBOL_FUNCTION && !var->type->isConst ? node : NULL;
    }
    case AST_DOT: {
        SymbolNode* var = getDotSymbol(node);
        if (var->isExtern) {
            return node;
        }
        return var->parent != NULL && var->parent->symbolType != SYMBOL_BLOCK && var->parent->symbolType != SYMBOL_FUNCTION && !var->type->isConst ? node : NULL;
    }
    case AST_DEFINE: {
        SymbolNode* var = node->data;
        ASTNode* res = isASTStateful(var->def);
        if (res != NULL) {
            return res;
        } else if (var->type->astType == AST_ADDR) {
            return node;
        } else {
            return NULL;
        }
    }
    case AST_CALL: {
        ASTNode* expr = List_Get(node->children, 0);
        ASTNode* exprType = getType(expr, false, false);
        if (exprType->astType != AST_FUNCTION) {
            return node;
        } else {
            return NULL;
        }
    }
    default:
        return NULL;
    }
}

Program Validator_Validate(SymbolNode* symbol)
{
    ASSERT(symbol != NULL);

    if (symbol->visited) {
        return;
    } else {
        symbol->visited = true;
    }

    // Done first pass through
    if (depenGraph == NULL) {
        functions = List_Create();
        globalVars = List_Create();
        enums = List_Create();
        depenGraph = List_Create();
        strings = List_Create();
        verbatims = List_Create();

        includes = Map_Create();

        types = List_Create();

        mainFunctionType = AST_Create(AST_PROCEDURE, 0, NULL, (Position) { 0, 0, 0, 0 }, true);
        ASTNode* mainFunctionParams = AST_Create(AST_PARAMLIST, 0, NULL, (Position) { 0, 0, 0, 0 }, true);
        SymbolNode* argsDefineSymbol = Symbol_Create("args", SYMBOL_VARIABLE, NULL, (Position) { 0, 0, 0, 0 });
        argsDefineSymbol->type = STRING_ARR_TYPE;
        argsDefineSymbol->def = AST_Create(AST_UNDEF, 0, NULL, (Position) { 0, 0, 0, 0 }, false);
        ASTNode* argsDefine = AST_Create(AST_DEFINE, argsDefineSymbol, NULL, (Position) { 0, 0, 0, 0 }, false);
        List_Append(mainFunctionParams->children, argsDefine);
        List_Append(mainFunctionType->children, mainFunctionParams);
        List_Append(mainFunctionType->children, INT32_TYPE);
        resolveRestrictions(symbol);
    }

    // Move inner functions up to module level
    if ((symbol->symbolType == SYMBOL_PROCEDURE || symbol->symbolType == SYMBOL_FUNCTION) && symbol->parent->symbolType == SYMBOL_BLOCK) {
        SymbolNode* realParent = symbol->parent;
        while (realParent->symbolType != SYMBOL_MODULE) {
            realParent = realParent->parent;
        }
        symbol->parent = realParent;
    }

    // Expand symbol type
    if (symbol->type) {
        symbol->type = expandTypeIdent(symbol->type, true);
        validateType(symbol->type);
        collectType(symbol->type);
    }

    if (symbol->parent && symbol->parent->symbolType != SYMBOL_TYPE) {
        SymbolNode* collision = Symbol_Find(symbol->name, symbol->parent->parent);
        if (symbol->name[0] && collision != 0 && collision != -1) {
            error2(symbol->pos, collision->pos, "symbol '%s' is shadowed", symbol->name);
        }
    }

    List* children = symbol->children->keyList;
    switch (symbol->symbolType) {
    case SYMBOL_PROGRAM: {
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
            if (child->symbolType != SYMBOL_PACKAGE) {
                typeMismatchError(child->type->pos, PACKAGE_TYPE, child->type);
            }
        }
        if (mainFunction == NULL) {
            gen_error("no main procedure defined");
        }
        // Reachability?
        reachableSymbol(mainFunction);
        looseOnConsts = true;
        collectStructs(CONST_STRING_TYPE);
        collectStructs(STRING_ARR_TYPE);
        unVisitSymbolTree(symbol);
        collectStructsMain(symbol);
        break;
    }
    case SYMBOL_PACKAGE: {
        if (!symbol->type->isConst) {
            error(symbol->pos, "package '%s' is not constant", symbol->name);
        }
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
            if (!child->type->isConst) {
                char typeBuffer[255];
                AST_TypeRepr(typeBuffer, child->type);
                printf("%s\n", typeBuffer);
                error(child->pos, "immediate child symbol '%s' of package '%s' is not constant", child->name, symbol->name);
            }
        }
        if (symbol->def->astType != AST_PARAMLIST && symbol->def->astType != AST_VOID) {
            error(symbol->pos, "expected parameter list");
        }
        validateAST(symbol->def);

        SymbolNode* includesSymbol = Map_Get(symbol->children, "includes");
        SymbolNode* verbatimSymbol = Map_Get(symbol->children, "verbatim");
        if (includesSymbol) {
            if (includesSymbol->def->astType != AST_ARRAY_LITERAL) {
                error(includesSymbol->pos, "includes array must be a string array");
            }
            ListElem* e = List_Begin(includesSymbol->def->children);
            for (; e != List_End(includesSymbol->def->children); e = e->next) {
                ASTNode* stringLiteral = e->data;
                if (!typesAreEquivalent(stringLiteral->type, STRING_TYPE)) {
                    typeMismatchError(stringLiteral->pos, STRING_TYPE, stringLiteral->type);
                }
                Map_Put(includes, stringLiteral->data, 1);
            }
        }
        if (verbatimSymbol) {
            if (verbatimSymbol->def->astType != AST_ARRAY_LITERAL) {
                error(verbatimSymbol->pos, "verbatim array must be a string array");
            }
            ListElem* e = List_Begin(verbatimSymbol->def->children);
            for (; e != List_End(verbatimSymbol->def->children); e = e->next) {
                ASTNode* stringLiteral = e->data;
                if (!typesAreEquivalent(stringLiteral->type, STRING_TYPE)) {
                    typeMismatchError(stringLiteral->pos, STRING_TYPE, stringLiteral->type);
                }
                List_Append(verbatims, stringLiteral->data);
            }
        }
        break;
    }
    case SYMBOL_FUNCTION:
    case SYMBOL_PROCEDURE: {
        if (!symbol->isExtern) {
            List_Append(functions, symbol);
        }
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
        }
        ASTNode* retType = List_Get(symbol->type->children, 1);
        if (!symbol->isExtern && retType->astType != AST_VOID) {
            if (symbol->def->astType != AST_UNDEF && getType(symbol->def, false, false)->astType != AST_UNDEF) {
                if (!typesAreEquivalent(getType(symbol->def, false, false), retType)) {
                    typeMismatchError(symbol->pos, retType, symbol->def->type);
                }
            } else if (!allReturnPath(symbol->def)) {
                error(symbol->pos, "not all paths return a value in '%s'", symbol->name);
            }
        }
        if (!strcmp(symbol->name, "main") && typesAreEquivalent(mainFunctionType, symbol->type)) {
            if (mainFunction) {
                error2(symbol->pos, mainFunction->pos, "multiple main function definitions");
            } else if (symbol->isPublic) {
                mainFunction = symbol;
            }
        }
        validateAST(symbol->def);
        ASTNode* statefulNode = NULL;
        if (symbol->type->isConst && symbol->symbolType == SYMBOL_FUNCTION) {
            if ((statefulNode = isASTStateful(symbol->def)) != NULL) {
                error(statefulNode->pos, "stateful expression in function definition");
            }
        }
        break;
    }
    case SYMBOL_VARIABLE:
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
        }
        break;
    case SYMBOL_TYPE: {
        if (!symbol->type->isConst) {
            error(symbol->pos, "type '%s' is not constant", symbol->name);
        }
        // validate valid type def
        validateType(symbol->def);
        // if def ast type is param list then for all define in paramlist children, define symbol is not extern
        if (symbol->def->astType == AST_PARAMLIST) {
            for (ListElem* elem = List_Begin(symbol->def->children); elem != List_End(symbol->def->children); elem = elem->next) {
                ASTNode* define = elem->data;
                SymbolNode* var = define->data;
                if (var && var->isExtern) {
                    error(var->type->pos, "struct field is marked external");
                }
            }
        }
        break;
    }
    case SYMBOL_MODULE: {
        if (!symbol->type->isConst) {
            error(symbol->pos, "module '%s' is not constant", symbol->name);
        }
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
            if (!child->isExtern) {
                if (child->symbolType == SYMBOL_VARIABLE) {
                    List_Append(globalVars, child);
                } else if (child->symbolType == SYMBOL_ENUM) {
                    List_Append(enums, child);
                }
            }
        }
        validateAST(symbol->def);
        break;
    }
    case SYMBOL_BLOCK: { // Always validated as defs or as children of other block ASTs
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
        }
        for (elem = List_Begin(symbol->defers); elem != List_End(symbol->defers); elem = elem->next) {
            ASTNode* child = elem->data;
            validateAST(child);
        }
        break;
    }
    }

    return (Program) { functions, globalVars, enums, depenGraph, strings, verbatims, includes, mainFunction };
}