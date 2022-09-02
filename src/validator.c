// © 2021-2022 Joseph Shimel. All rights reserved.
// Functionality to perform semantic analysis of a parsed-in program

#include "validator.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./errors.h"
#include "./ir.h"
#include "./main.h"
#include "./position.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Maps field names to set of types available for that field
const Map* tagTypes = NULL; // Map(name:String, Set(type))
// Maps field names to set of ids that correspond with field type
const Map* tagIDs = NULL; // Map(name:String, List(tag:Int))
// Set of DGraph nodes for unique product and sum types
static const List* structDepenGraph = NULL;
// Map used as a Set of filenames to include for the Orng program
static const Map* includes = NULL;
// List of verbatim code. TODO: Remove verbatims
static const List* verbatims = NULL;
// The main function of the program, found after traversal
static const SymbolNode* mainFunction = NULL;
// The call graph, built from the functions reachable by the main function
static const CFG* callGraph = NULL;
// Whether to use structural type equivalence or not. True during validation phase, false during generation phase
bool structuralTypeEquiv = false;

static ASTNode* expandTypeIdent(ASTNode* type, bool reassigning);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);
static void inferTypes(SymbolNode* var);
static ASTNode* getType(ASTNode* node, bool intermediate, bool reassigning);
static ASTNode* validateAST(ASTNode* node, ASTNode* coerceType);
static void validateType(ASTNode* node, bool collectThisType);

// Returns the tag ID for a field name/type pair, panics on error
int getTag(char* fieldName, ASTNode* fieldType)
{
    List* set = Map_Get(tagTypes, fieldName);
    if (!set) {
        PANIC("NO!");
    }
    int i = 0;
    forall(elem, set)
    {
        ASTNode* type = elem->data;
        // Types are completely equal
        if (typesAreEquivalent(type, fieldType) && typesAreEquivalent(fieldType, type)) {
            break;
        }
        i++;
    }
    List* ids = Map_Get(tagIDs, fieldName);
    int64_t tag = (int64_t)List_Get(ids, i);
    return tag;
}

// Returns the tag ID for a field name from within a sum type
int getTagEnum(char* fieldName, ASTNode* enumType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (!strcmp(var->name, fieldName)) {
            return getTag(fieldName, var->type);
        }
    }
    PANIC("couldn't find tag enum");
}

// Returns the type of a field given a tag from a sum type
ASTNode* getTypeEnum(int tag, ASTNode* enumType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (getTag(var->name, var->type) == tag) {
            return var->type;
        }
    }
    PANIC("couldn't find tag enum");
}

// Determines whether a sum type contains a field name/type pair
bool enumContainsField(ASTNode* enumType, char* fieldName, ASTNode* fieldType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (!strcmp(var->name, fieldName) && typesAreEquivalent(var->type, fieldType)) {
            return true;
        }
    }
    return false;
}

// Given two sun types, adds all the definitions from the right type to the left type. Field names may collide if types are equal, though fields will not be duplicated.
// TODO: add error if field names are the same and types are not equal
static void unionEnums(ASTNode* left, ASTNode* right)
{
    forall(elem, right->_enum.defines)
    {
        ASTNode* rightDefine = elem->data;
        SymbolNode* rightVar = rightDefine->define.symbol;
        bool found = false;
        forall(elem2, left->_enum.defines)
        {
            ASTNode* leftDefine = elem2->data;
            SymbolNode* leftVar = leftDefine->define.symbol;
            if (!strcmp(rightVar->name, leftVar->name)) {
                found = true;
                break;
            }
        }
        if (!found) {
            List_Append(left->_enum.defines, rightDefine);
        }
    }
}

// Determines the symbol node refered to by a dot expression AST. WARNING: Check returns! may be null (undefined) or -1 (restricted)
static SymbolNode* getDotSymbol(ASTNode* type)
{
    ASTNode* left = type->dot.left;
    ASTNode* newLeft = left;
    ASTNode* right = type->dot.right;
    SymbolNode* leftSymbol = NULL;

    // new left needs to eventually resolve to a parameter list
    bool resolved = false;
    while (!resolved) {
        // Find symbol, if it's a variable, newLeft is its type
        if (!newLeft) {
            resolved = true;
        } else if (newLeft->astType == AST_IDENT) {
            leftSymbol = Symbol_Find(newLeft->ident.data, type->scope);
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
        else if (newLeft->astType == AST_PARAMLIST || newLeft->astType == AST_ARRAY || newLeft->astType == AST_STRING || newLeft->astType == AST_ENUM) {
            resolved = true;
        }
        // newLeft is in the first child
        else if (newLeft->astType == AST_ADDR || newLeft->astType == AST_DEREF || newLeft->astType == AST_PAREN) {
            newLeft = newLeft->unop.expr;
            resolved = false;
        }
        // newLeft is in the second child
        else if (newLeft->astType == AST_CAST) {
            newLeft = newLeft->binop.right;
            resolved = false;
        }
        // newLeft is in the first child's type
        else if (newLeft->astType == AST_INDEX) {
            ASTNode* arrayType = getType(newLeft->binop.left, false, false);
            if (arrayType->astType == AST_ADDR) {
                arrayType = arrayType->binop.left;
            }
            if (arrayType->astType != AST_ARRAY) {
                error(type->pos, "indexing on a non-array type");
            }
            ASTNode* dataDefine = List_Get(arrayType->paramlist.defines, 1);
            SymbolNode* dataSymbol = dataDefine->define.symbol;
            ASTNode* dataAddrType = dataSymbol->type;
            newLeft = dataAddrType->binop.left;
            resolved = false;
        } else if (newLeft->astType == AST_EXTERN) {
            SymbolNode* var = newLeft->_extern.symbol;
            newLeft = var->def;
            resolved = false;
        }
        // newLeft is the type of the array data
        else if (newLeft->astType == AST_ARRAY) {
            ASTNode* define = List_Get(newLeft->paramlist.defines, 1);
            SymbolNode* var = define->define.symbol;
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
    } else if (newLeft->astType == AST_STRING) {
        return NULL;
    } else if (newLeft->astType == AST_PARAMLIST || newLeft->astType == AST_ARRAY || newLeft->astType == AST_ENUM) {
        // Search paramlists' defines for a symbol that matches
        ListElem* elem = List_Begin(newLeft->paramlist.defines);
        for (; rightSymbol == NULL && elem != List_End(newLeft->paramlist.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* attr = define->define.symbol;
            if (!strcmp(attr->name, right->ident.data)) {
                rightSymbol = attr;
                break;
            }
        }
        if (rightSymbol == NULL) {
            notMemberOfExpression(right->pos, right->ident.data, newLeft);
        }
    } else { // ERROR! NOT A PARAM LIST NOR ENUM!
        // Search symbol for a symbol that matches
        rightSymbol = Map_Get(leftSymbol->children, right->ident.data);
        if (rightSymbol == NULL) {
            notMemberOfExpression(right->pos, right->ident.data, newLeft);
        }
    }
    type->dot.symbol = rightSymbol;
    return rightSymbol;
}

// Returns the type refered to by a dot expression
// TODO: rename 'reassigning' to 'keepExternTypes', check whether you need this or not!
static ASTNode* resolveDotTypes(ASTNode* node, bool reassigning)
{
    if (node->astType == AST_DOT) {
        SymbolNode* dotSymbol = getDotSymbol(node);
        if (dotSymbol == 0 || dotSymbol == -1) {
            error(node->pos, "dot expression doesn't resolve to a symbol");
        } else if (reassigning && dotSymbol->isExtern) {
            return AST_Create_extern(dotSymbol, dotSymbol, dotSymbol->pos);
        } else {
            return dotSymbol->def;
        }
    } else {
        return node;
    }
}

// Evaluates a type expr AST. 'keepExternTypes' refers to whether or not to expand extern types further, or keep them
// TODO: rename 'reassigning' => 'keepExternTypes', rename 'expandTypeIdent' => 'evaluateType'
static ASTNode* expandTypeIdent(ASTNode* type, bool reassigning)
{
    int loopCounter = 0;
    ASTNode* expanded = type;
    while (expanded->astType == AST_IDENT) {
        SymbolNode* var = Symbol_Find(expanded->ident.data, expanded->scope);
        if (var != 0 && var != -1) {
            if (var->symbolType != SYMBOL_TYPE) {
                ASTNode* varType = getType(var->def, false, false);
                if (varType->astType != AST_IDENT || strcmp(varType->ident.data, "Type")) {
                    error2(type->pos, var->pos, "symbol '%s' is not a type", var->name);
                }
            }
            if (reassigning && var->isExtern) {
                expanded = AST_Create_extern(var, type->scope, type->pos);
                break;
            } else {
                expanded = var->def;
            }
        } else if (!strcmp(expanded->ident.data, "String")) {
            expanded = STRING_TYPE;
        } else if (!strcmp(expanded->ident.data, "Module") && !expanded->isConst) {
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
        expanded = AST_Create_addr(expandTypeIdent(expanded->unop.expr, true), expanded->scope, expanded->pos);
    } else if (expanded->astType == AST_PARAMLIST || expanded->astType == AST_ARRAY) {
        ListElem* elem = List_Begin(expanded->paramlist.defines);
        for (; elem != List_End(expanded->paramlist.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* symbol = define->define.symbol;
            Validator_Validate(symbol);
        }
    } else if (expanded->astType == AST_ENUM) {
        ListElem* elem = List_Begin(expanded->_enum.defines);
        for (; elem != List_End(expanded->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* symbol = define->define.symbol;
            Validator_Validate(symbol);
        }
    } else if (expanded->astType == AST_UNION) {
        ASTNode* newEnumType = AST_Create_enum(expanded->scope, expanded->pos);
        ASTNode* expandedLeft = expandTypeIdent(expanded->binop.left, reassigning);
        ASTNode* expandedRight = expandTypeIdent(expanded->binop.right, reassigning);
        forall(elem, expandedLeft->_enum.defines)
        {
            ASTNode* define = elem->data;
            List_Append(newEnumType->_enum.defines, define);
        }
        unionEnums(newEnumType, expandedRight);
        expanded = newEnumType;
    } else if (expanded->astType == AST_ERROR) {
        ASTNode* newEnumType = AST_Create_enum(expanded->scope, expanded->pos);
        newEnumType->_enum.wasAnError = true;
        ASTNode* expandedLeft = expandTypeIdent(expanded->binop.left, reassigning);
        ASTNode* expandedRight = expandTypeIdent(expanded->binop.right, reassigning);

        SymbolNode* successSymbol = Symbol_Create("success", SYMBOL_VARIABLE, expanded->scope, expanded->pos);
        ASTNode* successDefine = AST_Create_define(successSymbol, expanded->scope, expanded->pos);
        successSymbol->type = expandedRight;
        List_Append(newEnumType->_enum.defines, successDefine);

        unionEnums(newEnumType, expandedLeft);
        expanded = newEnumType;
    } else if (expanded->astType == AST_FUNCTION) {
        expanded = AST_Create_function(expandTypeIdent(expanded->function.domainType, true), expandTypeIdent(expanded->function.codomainType, true), expanded->scope, expanded->pos);
    }
    if (expanded->astType == AST_EXTERN && !reassigning) {
        SymbolNode* externVar = expanded->_extern.symbol;
        if (externVar->def->astType != AST_UNDEF) { // Extern symbols don't need a def, if they do, expand else leave as an extern
            expanded = expandTypeIdent(externVar->def, reassigning);
        }
    }

    while (expanded->astType == AST_DOT) {
        expanded = resolveDotTypes(expanded, reassigning);
    }

    expanded->originalType = type->originalType ? type->originalType : type;
    expanded->isConst = expanded->originalType->isConst;

    return expanded;
}

// Used for determining integer and real subtypes
static int scalarTypeType(ASTNode* node)
{
    if (structuralTypeEquiv) {
        if (node->astType != AST_IDENT) {
            return -1;
        } else {
            if (!strcmp(node->ident.data, "Int8")) {
                return 0;
            } else if (!strcmp(node->ident.data, "Int16")) {
                return 0;
            } else if (!strcmp(node->ident.data, "Int32")) {
                return 0;
            } else if (!strcmp(node->ident.data, "Int64") || !strcmp(node->ident.data, "Int")) {
                return 0;
            } else if (!strcmp(node->ident.data, "Real32") || !strcmp(node->ident.data, "Real")) {
                return 1;
            } else if (!strcmp(node->ident.data, "Real64")) {
                return 1;
            } else {
                return -1;
            }
        }
    } else {
        if (node->astType != AST_IDENT) {
            return -1;
        } else {
            if (!strcmp(node->ident.data, "Int8")) {
                return 0;
            } else if (!strcmp(node->ident.data, "Int16")) {
                return 1;
            } else if (!strcmp(node->ident.data, "Int32")) {
                return 2;
            } else if (!strcmp(node->ident.data, "Int64") || !strcmp(node->ident.data, "Int")) {
                return 3;
            } else if (!strcmp(node->ident.data, "Real32") || !strcmp(node->ident.data, "Real")) {
                return 4;
            } else if (!strcmp(node->ident.data, "Real64")) {
                return 5;
            } else {
                return -1;
            }
        }
    }
}

// returns whether or not 'a' is not a scalar subtype of 'b', or -1 if any are not scalar types
// TODO: rename to 'scalarSubtype'
static int typesAreCompatible(ASTNode* a, ASTNode* b)
{
    int aIntType = scalarTypeType(a);
    int bIntType = scalarTypeType(b);
    if (aIntType < 0 || bIntType < 0) {
        return -1;
    } else {
        return aIntType <= bIntType;
    }
}

// returns whether or not 'b' has all the fields of 'a'
static bool enumSubtype(ASTNode* a, ASTNode* b)
{
    ASTNode* aExpand = expandTypeIdent(a, false);
    ASTNode* bExpand = expandTypeIdent(b, false);

    bool allEquiv = true;
    forall(elem, aExpand->_enum.defines)
    {
        ASTNode* aDefine = elem->data;
        SymbolNode* aSymbol = aDefine->define.symbol;
        if (aSymbol->type->astType == AST_VOID && !structuralTypeEquiv) {
            continue;
        }
        bool found = false;
        forall(elem2, bExpand->_enum.defines)
        {
            ASTNode* bDefine = elem2->data;
            SymbolNode* bSymbol = bDefine->define.symbol;
            if (bSymbol->type->astType == AST_VOID && !structuralTypeEquiv) {
                continue;
            }
            aExpand->visited = true;
            bExpand->visited = true;
            found |= !strcmp(aSymbol->name, bSymbol->name) && typesAreEquivalent(aSymbol->type, bSymbol->type);
        }
        allEquiv &= found;
    }
    return allEquiv;
}

// returns whether the type 'a' is a subtype of 'b' 
// TODO: rename to 'isSubtype'
bool typesAreEquivalent(ASTNode* a, ASTNode* b)
{
    ASTNode* aExpand = expandTypeIdent(a, true);
    ASTNode* bExpand = expandTypeIdent(b, true);

    if (aExpand->astType == AST_EXTERN) {
        SymbolNode* var = aExpand->_extern.symbol;
        if (var->def->astType == AST_UNDEF) {
            return true;
        } else {
            aExpand = var->def;
        }
    }

    if (bExpand->astType == AST_EXTERN) {
        SymbolNode* var = bExpand->_extern.symbol;
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
    if (bExpand->astType == AST_IDENT && !strcmp(bExpand->ident.data, "Module") && aExpand->astType == AST_IDENT && !strcmp(aExpand->ident.data, "Type")) {
        return true;
    }
    if (bExpand->astType == AST_IDENT && !strcmp(bExpand->ident.data, "Package")) {
        return true;
    }
    if (structuralTypeEquiv && bExpand->isConst && !aExpand->isConst) {
        return false;
    }

    bool retval = true;
    if (bExpand->astType == AST_INFER_ERROR && aExpand->astType != AST_INFER_ERROR) {
        retval = false;
    } else if (aExpand->astType != bExpand->astType && aExpand != AST_FUNCTION) {
        retval = false;
    } else {
        switch (aExpand->astType) {
        case AST_IDENT: {
            retval = aExpand->ident.data && bExpand->ident.data && !strcmp(aExpand->ident.data, bExpand->ident.data);
            break;
        }
        case AST_DOT: {
            ASTNode* aLeft = aExpand->dot.left;
            ASTNode* aRight = aExpand->dot.right;
            ASTNode* bLeft = bExpand->dot.left;
            ASTNode* bRight = bExpand->dot.right;
            aExpand->visited = true;
            bExpand->visited = true;
            bool equiv = typesAreEquivalent(aLeft, bLeft) && typesAreEquivalent(aRight, bRight);
            retval = equiv;
            break;
        }
        case AST_ADDR: {
            ASTNode* aLeft = aExpand->unop.expr;
            ASTNode* bLeft = bExpand->unop.expr;
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
        case AST_PARAMLIST: {
            if (aExpand->paramlist.defines->size != bExpand->paramlist.defines->size) {
                retval = false;
                break;
            }
            ListElem* aElem = List_Begin(aExpand->paramlist.defines);
            ListElem* bElem = List_Begin(bExpand->paramlist.defines);
            bool allEquiv = true;
            for (; aElem != List_End(aExpand->paramlist.defines); aElem = aElem->next, bElem = bElem->next) {
                ASTNode* aDefine = aElem->data;
                SymbolNode* aSymbol = aDefine->define.symbol;
                ASTNode* aType = aSymbol->type;
                ASTNode* bDefine = bElem->data;
                SymbolNode* bSymbol = bDefine->define.symbol;
                ASTNode* bType = bSymbol->type;
                aExpand->visited = true;
                bExpand->visited = true;
                bool fieldNamesSame = (aSymbol == NULL || bSymbol == NULL || !strcmp(aSymbol->name, bSymbol->name));
                bool typeEquiv = typesAreEquivalent(aType, bType);
                allEquiv &= typeEquiv && fieldNamesSame;
            }
            retval = allEquiv;
            break;
        }
        case AST_ARRAY: {
            if (aExpand->paramlist.defines->size != bExpand->paramlist.defines->size) {
                retval = false;
                break;
            }
            ListElem* aElem = List_Begin(aExpand->paramlist.defines);
            ListElem* bElem = List_Begin(bExpand->paramlist.defines);
            bool allEquiv = true;
            // For each parameter in the function's parameter list, print it out
            for (; aElem != List_End(aExpand->paramlist.defines); aElem = aElem->next, bElem = bElem->next) {
                ASTNode* aDefine = aElem->data;
                SymbolNode* aSymbol = aDefine->define.symbol;
                ASTNode* aType = aSymbol->type;
                ASTNode* aDef = aSymbol->def;
                ASTNode* bDefine = bElem->data;
                SymbolNode* bSymbol = bDefine->define.symbol;
                ASTNode* bType = bSymbol->type;
                ASTNode* bDef = bSymbol->def;
                aExpand->visited = true;
                bExpand->visited = true;
                bool lengthSame = !structuralTypeEquiv || bDef->astType != AST_INT || aDef->_int.data == bDef->_int.data;
                bool fieldNamesSame = (aSymbol == NULL || bSymbol == NULL || !strcmp(aSymbol->name, bSymbol->name));
                bool typeEquiv = typesAreEquivalent(aType, bType);
                allEquiv &= lengthSame && typeEquiv && fieldNamesSame;
            }
            retval = allEquiv;
            break;
        }
        case AST_FUNCTION: {
            ASTNode* aLeft = aExpand->function.domainType;
            ASTNode* aRight = aExpand->function.codomainType;
            ASTNode* bLeft = bExpand->function.domainType;
            ASTNode* bRight = bExpand->function.codomainType;
            aExpand->visited = true;
            bExpand->visited = true;
            bool equiv = typesAreEquivalent(aLeft, bLeft) && typesAreEquivalent(aRight, bRight);
            retval = equiv;
            break;
        }
        case AST_ENUM:
            if (structuralTypeEquiv) {
                retval = enumSubtype(aExpand, bExpand);
            } else {
                retval = enumSubtype(aExpand, bExpand) && enumSubtype(bExpand, aExpand);
            }
            break;
        case AST_INFER_ERROR: {
            retval = aExpand == bExpand;
        }
        }
    }
    aExpand->visited = false;
    bExpand->visited = false;
    return retval;
}

// Takes in a sum type AST and an expression. Returns a wrapping expression if the expression can be coerced up to the enum type, else NULL
static ASTNode* tryCoerceToEnum(ASTNode* enumType, ASTNode* member)
{
    validateType(enumType, true);

    ASTNode* expandedEnumType = expandTypeIdent(enumType, false);
    if (expandedEnumType->astType != AST_ENUM && expandedEnumType->astType != AST_INFER_ERROR) {
        return NULL;
    } else if (member->astType == AST_NOTHING) {
        ASTNode* firstDefine = List_Get(enumType->_enum.defines, 0);
        SymbolNode* firstVar = firstDefine->define.symbol;
        if (!strcmp(firstVar->name, "nothing")) {
            ASTNode* retval = AST_Create_enumLiteral(getTag("nothing", VOID_TYPE), NULL, member->scope, member->pos);
            retval->type = expandedEnumType;
            return retval;
        } else {
            return NULL;
        }
    }
    // If the member is an enum expression, and the type of the member is a subtype of the coerce type, create conversion to superenum
    else if (member->type->astType == AST_ENUM && enumType->astType == AST_INFER_ERROR) {
        unionEnums(enumType, member->type);
        ASTNode* defineType = NULL;
        forall(elem, enumType->_enum.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* var = define->define.symbol;
            defineType = var->type;
            if (!strcmp(var->name, "success")) {
                break;
            }
        }
        if ((defineType && defineType->astType == AST_VOID) || enumSubtype(member->type, enumType)) {
            return AST_Create_cast(member, enumType, member->scope, member->pos);
        } else {
            return NULL;
        }
    } else {
        ASTNode* memberType = getType(member, false, false);
        forall(elem, expandedEnumType->_enum.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* var = define->define.symbol;
            ASTNode* defineType = var->type;
            if (typesAreEquivalent(memberType, defineType) && typesAreEquivalent(defineType, memberType)) {
                ASTNode* retval = AST_Create_enumLiteral(getTag(var->name, var->type), member, member->scope, member->pos);
                retval->type = expandedEnumType;
                return retval;
            }
        }
        if (enumType->astType == AST_INFER_ERROR && enumContainsField(enumType, "success", VOID_TYPE)) {
            ASTNode* retval = AST_Create_enumLiteral(getTag("success", VOID_TYPE), member, member->scope, member->pos);
            retval->type = expandedEnumType;
            return retval;
        }
        return NULL;
    }
}

// Given a calling expression (for method calls), an named arglist, and a parameterlist, determines if the arguments match the parameters
static void namedArgsMatch(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    Map* argNames = Map_Create(); // maps param names:String -> arg expressions:&ASTNode

    forall(elem, args->arglist.args)
    {
        ASTNode* namedArg = elem->data;
        if (namedArg->astType != AST_NAMED_ARG) {
            error(namedArg->pos, "positional argument specified in named argument list");
        }
        ASTNode* argExpr = namedArg->namedArg.expr;
        if (Map_Put(argNames, namedArg->namedArg.name, argExpr)) {
            error(namedArg->pos, "named argument specified twice in the same argument list");
        }
    }

    while (!List_IsEmpty(args->arglist.args)) {
        List_Pop(args->arglist.args);
    }

    if (expr && expr->astType == AST_DOT && params->paramlist.defines->size > 0) {
        SymbolNode* var = expr->dot.symbol;
        if (expr->dot.left->astType == AST_DEREF // Implies pointer
            && var->parent && var->parent->symbolType == SYMBOL_TYPE) {
            // CALL( DOT(self, methodName), ARGLIST(...) )
            // CALL( DOT(self, methodName), ARGLIST(self, ...) )
            ASTNode* self = expr->dot.left->unop.expr;
            List_Push(args->arglist.args, self);
        }
    }

    forall(elem, params->paramlist.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* symbol = define->define.symbol;
        inferTypes(symbol);
        ASTNode* argExpr = Map_Get(argNames, symbol->name);
        if (argExpr) {
            ASTNode* argType = getType(argExpr, false, false);
            if (!typesAreEquivalent(argType, symbol->type)) {
                ASTNode* coerced = NULL;
                if (coerced = tryCoerceToEnum(symbol->type, argExpr)) {
                    Map_Put(argNames, symbol->name, coerced);
                } else if (expr && expr->astType == AST_IDENT) {
                    SymbolNode* var = Symbol_Find(expr->ident.data, expr->scope);
                    typeMismatchError2(argExpr->pos, var->pos, symbol->type, argType);
                } else if (expr && expr->astType == AST_DOT) {
                    SymbolNode* var = expr->dot.symbol;
                    typeMismatchError2(argExpr->pos, var->pos, symbol->type, argType);
                } else {
                    typeMismatchError(argExpr->pos, symbol->type, argType);
                }
            }
            List_Append(args->arglist.args, argExpr);
        } else if (symbol->def->astType == AST_UNDEF) {
            error2(args->pos, symbol->pos, "named argument list does not specify all non-default parameters");
        } else if (!symbol->type->isConst) {
            List_Append(args->arglist.args, symbol->def);
        }
    }

    Map_Destroy(argNames);
}

// Given a calling expression (for method calls), a positional arglist, and a parameterlist, determines if the arguments match the parameters
static void positionalArgsMatch(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    if (expr && expr->astType == AST_DOT && params->paramlist.defines->size > 0) {
        SymbolNode* var = expr->dot.symbol;
        if (expr->dot.left->astType == AST_DEREF // Implies pointer
            && var->parent && var->parent->symbolType == SYMBOL_TYPE) {
            // CALL( DOT(self, methodName), ARGLIST(...) )
            // CALL( DOT(self, methodName), ARGLIST(self, ...) )
            ASTNode* self = expr->dot.left->unop.expr;
            List_Push(args->arglist.args, self);
        }
    }

    // arguments are correct arity
    ListElem* paramElem = List_Begin(params->paramlist.defines);
    bool isVararg = false;
    for (; paramElem != List_End(params->paramlist.defines) && !isVararg; paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* paramSymbol = define->define.symbol;
        isVararg = paramSymbol->isVararg;
    }

    if (!isVararg && params->paramlist.defines->size < args->arglist.args->size) {
        if (expr && expr->astType == AST_IDENT) {
            SymbolNode* var = Symbol_Find(expr->ident.data, expr->scope);
            error2(args->pos, var->pos, "argument list with too many arguments");
        } else if (expr && expr->astType == AST_DOT) {
            SymbolNode* var = expr->dot.symbol;
            error2(args->pos, var->pos, "argument list with too many arguments");
        } else {
            error(args->pos, "argument list with too many arguments");
        }
    }

    // arguments are correct type
    paramElem = List_Begin(params->paramlist.defines);
    ListElem* argElem = List_Begin(args->paramlist.defines);
    isVararg = false;
    for (; paramElem != List_End(params->paramlist.defines) && argElem != List_End(args->arglist.args) && !isVararg; paramElem = paramElem->next, argElem = argElem->next) {
        ASTNode* paramDefine = paramElem->data;
        SymbolNode* paramSymbol = paramDefine->define.symbol;
        inferTypes(paramSymbol);
        ASTNode* paramType = expandTypeIdent(paramSymbol->type, false);
        ASTNode* arg = validateAST(argElem->data, paramType);
        if (arg->astType == AST_NAMED_ARG) {
            error(arg->pos, "named argument specified in positional argument list");
        }
        ASTNode* argType = getType(arg, false, false);
        if (!typesAreEquivalent(argType, paramType)) {
            ASTNode* coerced = NULL;
            if (coerced = tryCoerceToEnum(paramType, arg)) {
                argElem->data = coerced;
            } else if (expr && expr->astType == AST_IDENT) {
                SymbolNode* var = Symbol_Find(expr->ident.data, expr->scope);
                typeMismatchError2(arg->pos, var->pos, paramType, argType);
            } else if (expr && expr->astType == AST_DOT) {
                SymbolNode* var = expr->dot.symbol;
                typeMismatchError2(arg->pos, var->pos, paramType, argType);
            } else {
                typeMismatchError(arg->pos, paramType, argType);
            }
        } else {
            argElem->data = arg;
        }
    }
    if (paramElem != List_End(params->paramlist.defines)) {
        for (; paramElem != List_End(params->paramlist.defines); paramElem = paramElem->next) {
            ASTNode* paramDefine = paramElem->data;
            SymbolNode* paramSymbol = paramDefine->define.symbol;
            ASTNode* paramDef = paramSymbol->def;
            if (paramDef->astType == AST_UNDEF) {
                if (expr && expr->astType == AST_IDENT) {
                    SymbolNode* var = Symbol_Find(expr->ident.data, expr->scope);
                    error2(args->pos, var->pos, "argument list with too few arguments");
                } else if (expr && expr->astType == AST_DOT) {
                    SymbolNode* var = expr->dot.symbol;
                    error2(args->pos, var->pos, "argument list with too few arguments");
                } else {
                    error(args->pos, "argument list with too few arguments");
                }
            } else if (!paramSymbol->type->isConst) {
                List_Append(args->arglist.args, paramDef);
            }
        }
    }
}

// Given a calling expression (for method calls), an arglist, and a parameterlist, determines if the arguments match the parameters
static void argsMatchParams(ASTNode* expr, ASTNode* args, ASTNode* params)
{
    if ((args->astType != AST_ARGLIST && args->astType != AST_PAREN) || (params->astType != AST_PARAMLIST && params->astType != AST_VOID)) {
        incompatibleTypesError(args->pos, getType(args, false, false), params);
    }

    ASTNode* firstArg = List_Get(args->arglist.args, 0);
    if (args->arglist.args->size != 0 && firstArg->astType == AST_NAMED_ARG) {
        namedArgsMatch(expr, args, params);
    } else {
        positionalArgsMatch(expr, args, params);
    }
}

// Takes in a symbol, performs either type checking if the type is defined, or type inference if the type is undefined
// TODO: better name! maybe 'symbolTypeCheck'
static void inferTypes(SymbolNode* var)
{
    if (var->def && var->symbolType != SYMBOL_FUNCTION) {
        if (!var->def->isValid) {
            var->def = validateAST(var->def, var->type);
        }
        // if type is undef, type is type of def
        // else, type must match type of def
        ASTNode* defType = getType(var->def, false, true);
        if (var->type->astType == AST_UNDEF) {
            // No type annot., infer types
            bool wasConst = var->type->isConst;
            var->type = defType;
            var->type->isConst = wasConst;

            if (defType->astType == AST_IDENT && !strcmp(defType->ident.data, "Type")) {
                var->symbolType = SYMBOL_TYPE;
            } else if (defType->astType == AST_IDENT && !strcmp(defType->ident.data, "Module")) {
                var->symbolType = SYMBOL_MODULE;
                var->type->isConst = true;
            } else if (defType->astType == AST_IDENT && !strcmp(defType->ident.data, "Package")) {
                var->symbolType = SYMBOL_PACKAGE;
                var->type->isConst = true;
            }
            if (var->type->astType == AST_UNDEF) {
                error(var->pos, "cannot infer type of symbol '%s', try using a cast", var->name);
            }
        } else {
            bool typesEquivalent = typesAreEquivalent(defType, var->type);

            if (defType && (defType->astType != AST_UNDEF || var->def->astType != AST_UNDEF) && !typesEquivalent) {
                if (var->def->astType == AST_ARGLIST) {
                    argsMatchParams(NULL, var->def, var->type);
                } else {
                    // Type annot.'d, types disagree
                    ASTNode* coerced = NULL;
                    if (coerced = tryCoerceToEnum(var->type, var->def)) {
                        var->def = coerced;
                    } else {
                        typeMismatchError(var->pos, var->type, defType);
                    }
                }
            } else {
                // Types annot.'d, types agree
                var->type = expandTypeIdent(var->type, true);
                validateType(var->type, true);
                var->def->type = var->type;
            }
        }
    }
}

// Returns the type AST for an expression. In the case of a dot chain with two or more dots, 'intermediate' whether or not the this node is NOT the head dot in the dot chain
// TOOD: rename 'reassigning' => 'expandExternTypes', 'intermediate' => 'inDotChainTail'
static ASTNode* getType(ASTNode* node, bool intermediate, bool reassigning)
{
    ASSERT(node != NULL);
    //ASSERT(node->isValid);
    if (node->astType != AST_UNDEF && node->type != NULL) {
        return node->type;
    }
    ASTNode* type = NULL;

    switch (node->astType) {
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->ident.data, node->scope);
        if (var == 0) {
            restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->ident.data);
        } else if (var == -1) {
            restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->ident.data);
        }
        if (var->type->astType == AST_UNDEF) {
            inferTypes(var);
        }
        type = expandTypeIdent(var->type, reassigning);
        break;
    }
    case AST_INT:
    case AST_SIZEOF: {
        type = CONST_INT64_TYPE;
        break;
    }
    case AST_CHAR: {
        type = CONST_CHAR_TYPE;
        break;
    }
    case AST_TRUE:
    case AST_FALSE:
    case AST_OR:
    case AST_AND:
    case AST_EQ:
    case AST_NEQ:
    case AST_GTR:
    case AST_GTE:
    case AST_LSR:
    case AST_LTE:
    case AST_NOT: {
        type = CONST_BOOL_TYPE;
        break;
    }
    case AST_REAL: {
        type = REAL64_TYPE;
        break;
    }
    case AST_ARGLIST:
    case AST_UNDEF:
    case AST_ASSIGN:
    case AST_FREE:
    case AST_OR_ASSIGN:
    case AST_AND_ASSIGN:
    case AST_BIT_OR_ASSIGN:
    case AST_BIT_XOR_ASSIGN:
    case AST_BIT_AND_ASSIGN:
    case AST_LSHIFT_ASSIGN:
    case AST_RSHIFT_ASSIGN:
    case AST_ADD_ASSIGN:
    case AST_SUB_ASSIGN:
    case AST_MULT_ASSIGN:
    case AST_DIV_ASSIGN:
    case AST_MOD_ASSIGN:
    case AST_EXPONENT_ASSIGN:
    case AST_DEFINE:
    case AST_FOR:
    case AST_BREAK:
    case AST_CONTINUE:
    case AST_UNREACHABLE:
    case AST_DEFER:
    case AST_ERRDEFER: {
        type = UNDEF_TYPE;
        break;
    }
    case AST_NAMED_ARG:
    case AST_BIT_OR:
    case AST_BIT_XOR:
    case AST_BIT_AND:
    case AST_LSHIFT:
    case AST_RSHIFT:
    case AST_NEG:
    case AST_BIT_NOT:
    case AST_RETURN: {
        ASTNode* left = node->unop.expr;
        type = getType(left, false, reassigning);
        break;
    }
    case AST_NOTHING: {
        type = VOID_TYPE;
        break;
    }
    case AST_ENUM_LITERAL: {
        type = node->type;
        break;
    }
    case AST_ARRAY_LITERAL: {
        ASTNode* firstElem = List_Begin(node->arrayLiteral.members)->data;
        ASTNode* firstType = getType(firstElem, false, reassigning);
        type = createArrayTypeNode(firstType, node->arrayLiteral.members->size, node->pos);
        type->isConst = true;
        break;
    }
    case AST_STRING: {
        type = CONST_STRING_TYPE;
        break;
    }
    case AST_ADD:
    case AST_SUBTRACT:
    case AST_MULTIPLY:
    case AST_DIVIDE:
    case AST_MODULUS:
    case AST_EXPONENT: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        bool tempPermissiveness = structuralTypeEquiv;
        structuralTypeEquiv = true;
        if (typesAreEquivalent(leftType, rightType)) {
            type = rightType;
        } else if (typesAreEquivalent(rightType, leftType)) {
            type = leftType;
        } else {
            incompatibleTypesError(node->pos, leftType, rightType);
        }
        structuralTypeEquiv = tempPermissiveness;
        break;
    }
    case AST_ADDR_OF: {
        ASTNode* innerType = getType(node->unop.expr, false, reassigning);
        ASTNode* addrType = AST_Create_addr(innerType, node->scope, (Position) { 0, 0, 0, 0 });
        type = addrType;
        break;
    }
    case AST_DEREF: {
        ASTNode* left = node->unop.expr;
        ASTNode* addr = getType(left, false, reassigning);
        type = addr->unop.expr;
        break;
    }
    case AST_TRY: {
        ASTNode* left = node->taggedUnop.expr;
        ASTNode* leftType = getType(left, false, false);

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(leftType->_enum.defines);
        for (; elem != List_End(leftType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "success")) {
                innerType = define->define.symbol->type;
                break;
            }
        }
        type = innerType;
        break;
    }
    case AST_CATCH: { // a catch expr has the type of the success field
        ASTNode* left = node->taggedBinop.left;
        ASTNode* leftType = getType(left, false, false);
        ASTNode* right = node->taggedBinop.right;
        ASTNode* rightType = getType(right, false, false);

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(leftType->_enum.defines);
        for (; elem != List_End(leftType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "success")) {
                innerType = define->define.symbol->type;
                break;
            }
        }
        type = innerType;
        break;
    }
    case AST_ORELSE: {
        ASTNode* left = node->taggedBinop.left;
        ASTNode* leftType = getType(left, false, false);
        ASTNode* right = node->taggedBinop.right;
        ASTNode* rightType = getType(right, false, false);

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(leftType->_enum.defines);
        for (; elem != List_End(leftType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "something")) {
                innerType = define->define.symbol->type;
                break;
            }
        }
        type = innerType;
        break;
    }
    case AST_CALL: {
        ASTNode* call = node->binop.left;
        ASTNode* functionType = getType(call, false, reassigning);
        ASTNode* functionReturn = functionType->function.codomainType;
        type = expandTypeIdent(functionReturn, reassigning);
        break;
    }
    case AST_INDEX: {
        ASTNode* arrType = getType(node->binop.left, false, reassigning);
        if (arrType->astType == AST_ARRAY) {
            ASTNode* define = List_Get(arrType->paramlist.defines, 1);
            SymbolNode* arrSymbol = define->define.symbol;
            type = expandTypeIdent(arrSymbol->type->unop.expr, reassigning);
        } else if (arrType->astType == AST_ADDR) {
            ASTNode* innerType = arrType->unop.expr;
            if (innerType->astType == AST_ARRAY) {
                ASTNode* define = List_Get(innerType->paramlist.defines, 1);
                SymbolNode* arrSymbol = define->define.symbol;
                type = expandTypeIdent(arrSymbol->type->unop.expr, reassigning);
            } else {
                type = expandTypeIdent(arrType->unop.expr, reassigning);
            }
        }
        break;
    }
    case AST_SLICE: {
        ASTNode* left = node->slice.arrayExpr;
        ASTNode* leftType = getType(left, false, false);
        if (leftType->astType != AST_PARAMLIST && leftType->astType != AST_ARRAY) {
            expectedArray(left->pos, leftType);
        }
        ASTNode* dataDefine = List_Get(leftType->paramlist.defines, 1);
        SymbolNode* dataSymbol = dataDefine->define.symbol;
        ASTNode* dataType = dataSymbol->type;
        ASTNode* actualType = dataType->unop.expr;
        type = createArrayTypeNode(actualType, -1, node->pos);
        break;
    }
    case AST_DOT: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ASTNode* leftType = getType(left, left->astType != AST_DOT, reassigning); // need to know the type of the left side of dot
        leftType = expandTypeIdent(resolveDotTypes(leftType, false), reassigning);
        ASTNode* paramlist = NULL;

        bool resolved = false;
        if (leftType->astType == AST_IDENT && (!strcmp(leftType->ident.data, "Module") || !strcmp(leftType->ident.data, "Package") || !strcmp(leftType->ident.data, "Enum"))) {
            SymbolNode* leftSymbol = NULL;
            if (left->astType == AST_IDENT) {
                leftSymbol = Symbol_Find(left->ident.data, left->scope);
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
        } else if (leftType->astType == AST_IDENT && !strcmp(leftType->ident.data, "Type")) {
            SymbolNode* leftSymbol = NULL;
            if (left->astType == AST_IDENT) {
                leftSymbol = Symbol_Find(left->ident.data, left->scope);
            } else if (left->astType == AST_DOT) {
                leftSymbol = getDotSymbol(left);
            } else {
                ASSERT(0);
            }
            paramlist = leftSymbol->def;
        } else if (leftType->astType == AST_ADDR) {
            paramlist = expandTypeIdent(leftType->unop.expr, reassigning);
        } else if (leftType->astType == AST_PARAMLIST || leftType->astType == AST_ARRAY) {
            paramlist = leftType;
        } else if (leftType->astType == AST_EXTERN) {
            SymbolNode* leftSymbol = leftType->_extern.symbol;
            paramlist = leftSymbol->def;
        } else if (leftType->astType == AST_ENUM) {
            paramlist = leftType;
        } else {
            error(left->pos, "left side of dot must be container");
        }
        if (paramlist->astType == AST_EXTERN) {
            SymbolNode* var = paramlist->_extern.symbol;
            paramlist = var->def;
        }

        if (paramlist->astType == AST_ADDR) { // done to weed out dots on double addresses, does this work?
            error(left->pos, "left side of dot must be container");
        }

        ListElem* elem = List_Begin(paramlist->paramlist.defines);
        SymbolNode* attr = NULL;
        for (; type == NULL && elem != List_End(paramlist->paramlist.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            attr = define->define.symbol;
            if (!strcmp(attr->name, right->ident.data)) {
                ASTNode* retval = expandTypeIdent(attr->type, reassigning);
                if (intermediate && retval->astType == AST_IDENT && (!strcmp(retval->ident.data, "Module") || !strcmp(retval->ident.data, "Package"))) {
                    type = attr->def;
                    break;
                } else {
                    type = retval;
                    break;
                }
            }
        }
        if (type == NULL) {
            notMemberOfExpression(right->pos, right->ident.data, paramlist);
        }
        break;
    }
    case AST_CAST: {
        type = node->binop.right;
        break;
    }
    case AST_NEW: {
        ASTNode* newType = node->binop.left;
        if (newType->astType != AST_ARRAY) {
            type = AST_Create_addr(newType, node->scope, node->pos);
        } else {
            type = newType;
        }
        break;
    }
    case AST_PAREN: {
        type = getType(List_Get(node->arglist.args, 0), false, reassigning);
        break;
    }
    case AST_BLOCK: {
        ASTNode* lastNode = List_Get(node->block.children, node->block.children->size - 1);
        if (lastNode != NULL) {
            type = getType(validateAST(lastNode, NULL), false, false);
        } else {
            type = UNDEF_TYPE;
        }
        break;
    }
    case AST_IF: {
        if (node->_if.elseBlock->astType != AST_UNDEF) {
            ASTNode* body = node->_if.bodyBlock;
            ASTNode* elseBody = node->_if.elseBlock;
            ASTNode* bodyType = getType(body, false, false);
            ASTNode* elseBodyType = getType(elseBody, false, false);
            bool tempPermissiveness = structuralTypeEquiv;
            structuralTypeEquiv = true;
            if (typesAreEquivalent(bodyType, elseBodyType)) {
                type = elseBodyType;
            } else if (typesAreEquivalent(elseBodyType, bodyType)) {
                type = bodyType;
            } else {
                type = UNDEF_TYPE;
            }
            structuralTypeEquiv = tempPermissiveness;
        } else {
            type = UNDEF_TYPE;
        }
        break;
    }
    case AST_CASE:
    case AST_FIELD_CASE: {
        if (node->_case.mappings->size < 1) {
            type = UNDEF_TYPE;
            break;
        } else {
            ASTNode* firstCase = List_Get(node->_case.mappings, 0);
            ASTNode* firstCaseType = getType(firstCase, false, false);
            if (firstCaseType->astType == AST_ENUM) {
                type = AST_Create_enum(node->scope, node->pos);
                unionEnums(type, firstCaseType);
            } else {
                type = firstCaseType;
            }
            for (ListElem* elem = List_Begin(node->_case.mappings)->next; elem != List_End(node->_case.mappings); elem = elem->next) {
                ASTNode* caseNode = elem->data;
                ASTNode* caseNodeType = getType(caseNode, false, false);
                if (firstCaseType->astType == AST_ENUM) {
                    if (caseNodeType->astType != AST_ENUM) {
                        type = UNDEF_TYPE;
                        break;
                    } else {
                        unionEnums(type, caseNodeType);
                    }
                } else if (!typesAreEquivalent(firstCaseType, caseNodeType) || !typesAreEquivalent(caseNodeType, firstCaseType)) {
                    type = UNDEF_TYPE;
                    break;
                }
            }
            break;
        }
    }
    case AST_MAPPING:
    case AST_FIELD_MAPPING: {
        type = getType(node->mapping.expr, false, false);
        break;
    }
    case AST_VOID: {
        type = node;
        break;
    }
    case AST_ADDR: {
        ASTNode* innerType = getType(node->unop.expr, false, reassigning);
        ASTNode* addrType = AST_Create_addr(innerType, node->scope, (Position) { 0, 0, 0, 0 });
        type = addrType;
        break;
    }
    case AST_PARAMLIST:
    case AST_ARRAY:
    case AST_ENUM:
    case AST_FUNCTION: {
        type = TYPE_TYPE;
        break;
    }
    default:
        error(node->pos, "unimplemented type inference for AST Node %s", AST_GetString(node->astType));
    }
    if (!type) {
        printf("What\n");
    }
    node->type = type;
    return type;
}

// Validates properties for L value expressions 
static void validateLValue(ASTNode* node)
{
    switch (node->astType) {
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->ident.data, node->scope);
        if (var->type->isConst) {
            error(node->pos, "symbol '%s' is constant", var->name);
        }
        break;
    }
    case AST_DEREF: {
        ASTNode* child = node->unop.expr;
        if (child->astType != AST_ADDR) {
            validateLValue(child);
        }
        ASTNode* childType = getType(child, false, false);
        if (childType->astType != AST_ADDR) {
            ASSERT(0);
        }
        ASTNode* underlyingType = childType->unop.expr;

        if (underlyingType->isConst) {
            error(node->pos, "address expression is constant");
        }
        break;
    }
    case AST_INDEX: {
        ASTNode* child = node->binop.left;
        validateLValue(child);
        ASTNode* childType = getType(child, false, false);
        if (childType->astType != AST_ARRAY && childType->astType != AST_ADDR) {
            ASSERT(0);
        }
        if (childType->astType == AST_ADDR) {
            childType = childType->unop.expr;
        }
        ASTNode* dataType = getArrayDataType(childType);
        if (dataType->isConst) {
            error(node->pos, "array data type is constant");
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
    case AST_PAREN: {
        ASTNode* child = List_Get(node->arglist.args, 0);
        validateLValue(child);
        break;
    }
    default:
        error(node->pos, "left side of assignment is not assignable");
    }
}

// Returns the size in bytes a type AST would take up in memory, padding included
static int getTypeSize(ASTNode* type)
{
    switch (type->astType) {
    case AST_IDENT: {
        if (!strcmp(type->ident.data, "Int")) {
            return 8;
        } else if (!strcmp(type->ident.data, "Char")) {
            return 1;
        } else if (!strcmp(type->ident.data, "Bool")) {
            return 1;
        } else if (!strcmp(type->ident.data, "Real")) {
            return 8;
        } else if (!strcmp(type->ident.data, "String")) {
            return 16;
        } else if (!strcmp(type->ident.data, "Int8")) {
            return 1;
        } else if (!strcmp(type->ident.data, "Int16")) {
            return 2;
        } else if (!strcmp(type->ident.data, "Int32")) {
            return 4;
        } else if (!strcmp(type->ident.data, "Int64")) {
            return 8;
        } else if (!strcmp(type->ident.data, "Real32")) {
            return 4;
        } else if (!strcmp(type->ident.data, "Real64")) {
            return 8;
        }
        return -1;
    }
    case AST_VOID: {
        return 0;
    }
    case AST_ADDR: {
        return 8;
    }
    case AST_PARAMLIST:
    case AST_ARRAY: {
        int prevAlign = 0;
        int size = 0;
        forall(elem, type->paramlist.defines)
        {
            ASTNode* memberDefine = elem->data;
            SymbolNode* memberSymbol = memberDefine->define.symbol;
            int typeSize = getTypeSize(memberSymbol->type);
            int padding = typeSize - prevAlign;
            if (memberSymbol->symbolType != SYMBOL_VARIABLE) {
            }
            size += typeSize + padding;
            prevAlign = size;
        }
        return size;
    }
    case AST_ENUM: {
        int maxMemberSize = 0;
        forall(elem, type->_enum.defines)
        {
            ASTNode* memberDefine = elem->data;
            SymbolNode* memberSymbol = memberDefine->define.symbol;
            int typeSize = getTypeSize(memberSymbol->type);
            maxMemberSize = max(maxMemberSize, typeSize);
        }
        return maxMemberSize + 8; // add 8 for the tag size
    }
    case AST_FUNCTION: {
        return 8;
    }
    case AST_EXTERN:
        return 0;
    case AST_DOT:
    case AST_UNDEF: {
        error(type->pos, "idk how to calculate this size yet");
    }
    default: {
        error(type->pos, "not a type");
    }
    }
}

// Validates and possibly evaluates an AST expression, returns resulting original AST. Takes in an expected type to coerce the expression to, set to NULL for no type check
static ASTNode* validateAST(ASTNode* node, ASTNode* coerceType)
{
    static int loops = 0;
    static bool lastEval = true;
    static bool errorHandled = false;

    ASSERT(node != NULL);
    if (node->isValid) {
        return;
    }
    node->isValid = true;

    ASTNode* retval = NULL;

    switch (node->astType) {
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->ident.data, node->scope);
        if (var == NULL) {
            restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->ident.data);
        } else if (var == -1) {
            restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->ident.data);
        }
        Validator_Validate(var);
        if (var->symbolType != SYMBOL_FUNCTION && !var->isExtern && var->type->isConst) {
            retval = var->def;
            break;
        } else {
            retval = node;
            break;
        }
    }
    case AST_INT:
    case AST_TRUE:
    case AST_FALSE:
    case AST_REAL:
    case AST_NOTHING:
    case AST_STRING:
    case AST_UNREACHABLE:
        retval = node;
        break;
    case AST_CHAR: {
        // data is a valid character
        if (node->_char.data[0] == '\\') {
            if (strlen(node->_char.data) != 2 || node->_char.data[1] != 'n' && node->_char.data[1] != 'r' && node->_char.data[1] != 't' && node->_char.data[1] != '\\' && node->_char.data[1] != '\'' && node->_char.data[1] != '0') {
                error(node->pos, "invalid character constant");
            }
        } else if (strlen(node->_char.data) != 1 || node->_char.data[0] == '\n') {
            error(node->pos, "invalid character constant");
        }
        retval = node;
        break;
    }
    case AST_ARGLIST: {
        List* validArgs = List_Create();
        forall(elem, node->arglist.args)
        {
            ASTNode* arg = elem->data;
            List_Append(validArgs, validateAST(arg, NULL));
        }
        node->arglist.args = validArgs;
        if (coerceType) {
            node->type = coerceType;
        }
        retval = node;
        break;
    }
    case AST_NAMED_ARG: {
        node->namedArg.expr = validateAST(node->namedArg.expr, coerceType);
        retval = node;
        break;
    }
    case AST_ENUM_LITERAL: {
        if (node->enumLiteral.expr) {
            node->enumLiteral.expr = validateAST(node->enumLiteral.expr, NULL);
        }
        retval = node;
        break;
    }
    case AST_ARRAY_LITERAL: {
        if (node->arrayLiteral.members->size <= 0) {
            error(node->pos, "array literal is empty");
        }

        List* validMembers = List_Create();
        ASTNode* dataType = NULL;
        if (coerceType && coerceType->astType != AST_UNDEF) {
            ASTNode* dataDefine = List_Get(coerceType->paramlist.defines, 1);
            SymbolNode* dataSymbol = dataDefine->define.symbol;
            dataType = dataSymbol->type->unop.expr;
        } else {
            dataType = getType(List_Get(node->arrayLiteral.members, 0), false, false);
        }

        forall(elem, node->arrayLiteral.members)
        {
            ASTNode* arrElem = validateAST(elem->data, dataType);
            List_Append(validMembers, arrElem);
        }

        node->arrayLiteral.members = validMembers;
        retval = node;
        break;
    }
    case AST_UNDEF:
    case AST_VOID:
    case AST_ADDR:
    case AST_FUNCTION: {
        retval = UNDEF_TYPE;
        break;
    }
    case AST_ASSIGN: {
        // right type <= left type
        ASTNode* left = validateAST(node->binop.left, NULL);
        ASTNode* leftType = getType(left, false, true);
        ASTNode* right = validateAST(node->binop.right, leftType);
        ASTNode* rightType = getType(right, false, true);
        if (!typesAreEquivalent(rightType, leftType)) {
            // check if can coerce to enum given leftType, if so, set right to it, else give error
            ASTNode* coerced = NULL;
            if (coerced = tryCoerceToEnum(leftType, right)) {
                right = coerced;
                right->type = leftType;
            } else {
                typeMismatchError(right->pos, leftType, rightType);
            }
        } else {
            right->type = leftType;
        }

        // left type is an l-value
        validateLValue(left);
        node->binop.left = left;
        node->binop.right = right;

        retval = node;
        break;
    }
    case AST_OR: {
        node->binop.left = validateAST(node->binop.left, BOOL_TYPE);
        node->binop.right = validateAST(node->binop.right, BOOL_TYPE);
        retval = node;
        break;
    }
    case AST_AND: {
        node->binop.left = validateAST(node->binop.left, BOOL_TYPE);
        node->binop.right = validateAST(node->binop.right, BOOL_TYPE);
        retval = node;
        break;
    }
    case AST_BIT_OR:
    case AST_BIT_XOR:
    case AST_BIT_AND:
    case AST_LSHIFT:
    case AST_RSHIFT:
    case AST_MODULUS: {
        ASTNode* left = validateAST(node->binop.left, INT64_TYPE);
        ASTNode* right = validateAST(node->binop.right, INT64_TYPE);

        node->binop.left = left;
        node->binop.right = right;

        retval = node;
        break;
    }
    case AST_EQ:
    case AST_NEQ: {
        ASTNode* left = validateAST(node->binop.left, NULL);
        ASTNode* right = validateAST(node->binop.right, NULL);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);

        node->binop.left = left;
        node->binop.right = right;

        if (leftType->astType == AST_ENUM) {
            if (rightType->astType != AST_ENUM) {
                ASTNode* coerce = tryCoerceToEnum(leftType, right);
                if (coerce) {
                    right = coerce;
                } else {
                    typeMismatchError(right->pos, leftType, rightType);
                }
            }
            retval = node;
            break;
        } else if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        } else if (leftType->astType == AST_PARAMLIST || leftType->astType == AST_ARRAY || rightType->astType == AST_PARAMLIST || rightType->astType == AST_ARRAY) {
            error(node->pos, "comparison on struct type"); // TODO: allow struct comparisons
        } else {
            retval = node;
            break;
        }
    }
    case AST_GTR:
    case AST_LSR:
    case AST_GTE:
    case AST_LTE:
    case AST_ADD:
    case AST_SUBTRACT:
    case AST_MULTIPLY:
    case AST_DIVIDE:
    case AST_EXPONENT: {
        node->binop.left = validateAST(node->binop.left, REAL64_TYPE);
        node->binop.right = validateAST(node->binop.right, REAL64_TYPE);
        retval = node;
        break;
    }
    case AST_NOT: {
        node->unop.expr = validateAST(node->unop.expr, BOOL_TYPE);
        retval = node;
        break;
    }
    case AST_NEG: {
        node->unop.expr = validateAST(node->unop.expr, REAL64_TYPE);
        if (node->unop.expr->astType == AST_INT) {
            node->unop.expr->_int.data *= -1;
            retval = node->unop.expr;
        } else if (node->unop.expr->astType == AST_REAL) {
            node->unop.expr->real.data *= -1;
            retval = node->unop.expr;
        } else {
            retval = node;
        }
        break;
    }
    case AST_BIT_NOT: {
        node->unop.expr = validateAST(node->unop.expr, INT64_TYPE);
        retval = node;
        break;
    }
    case AST_ADDR_OF: {
        ASTNode* left = validateAST(node->unop.expr, NULL);
        validateLValue(left);
        node->unop.expr = left;
        retval = node;
        break;
    }
    case AST_SIZEOF: {
        node->unop.expr = expandTypeIdent(node->unop.expr, true);
        validateType(node->unop.expr, true);
        if (node->unop.expr->astType != AST_EXTERN) {
            retval = AST_Create_int(getTypeSize(node->unop.expr), node->scope, node->pos);
        } else {
            retval = node;
        }
        break;
    }
    case AST_DEREF: {
        // child type is scalar
        ASTNode* left = validateAST(node->unop.expr, NULL);
        ASTNode* leftType = getType(left, false, false);
        if (leftType->astType != AST_ADDR) {
            error(node->pos, "type mismatch, expected address");
        }
        node->unop.expr = left;
        retval = node;
        break;
    }
    case AST_TRY: {
        bool oldErrorHandled = errorHandled;
        errorHandled = true;
        ASTNode* validExpr = validateAST(node->taggedUnop.expr, coerceType);
        ASTNode* exprType = getType(validExpr, false, false);
        errorHandled = oldErrorHandled;

        if (exprType->astType != AST_ENUM) {
            error(validExpr->pos, "left side of catch must be error enum type");
        }

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(exprType->_enum.defines);
        for (; elem != List_End(exprType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "success")) {
                innerType = define->define.symbol->type;
                break;
            }
        }

        if (!innerType) {
            error(validExpr->pos, "left side of catch must be error enum type");
        }

        // return must be in function
        SymbolNode* function = Symbol_TypeAncestor(node->scope, SYMBOL_FUNCTION);
        if (function == NULL) {
            function = Symbol_TypeAncestor(node->scope, SYMBOL_FUNCTION);
            if (function == NULL) {
                error(node->pos, "return not within function");
                break;
            }
        }
        // return type matches function type
        ASTNode* functionType = function->type;
        ASTNode* functionRetType = functionType->function.codomainType;
        if (functionRetType->astType == AST_INFER_ERROR) {
            unionEnums(functionRetType, exprType);
        } else {
            if (exprType->astType == AST_VOID) {
                typesAreEquivalent(exprType, functionRetType);
            }
            if (!typesAreEquivalent(exprType, functionRetType)) {
                ASTNode* coerced = NULL;
                if (coerced = tryCoerceToEnum(functionRetType, validExpr)) {
                    validExpr = coerced;
                } else {
                    typeMismatchError(node->pos, functionRetType, exprType);
                }
            }
        }

        node->taggedUnop.tag = getTagEnum("success", exprType);
        node->taggedUnop.expr = validExpr;
        retval = node;
        break;
    }
    case AST_CATCH: {
        bool oldErrorHandled = errorHandled;
        errorHandled = true;
        ASTNode* left = validateAST(node->taggedBinop.left, NULL);
        ASTNode* leftType = getType(left, false, false);
        errorHandled = oldErrorHandled;

        ASTNode* right = validateAST(node->taggedBinop.right, NULL);
        ASTNode* rightType = getType(right, false, false);

        if (leftType->astType != AST_ENUM) {
            error(left->pos, "left side of catch must be error enum type");
        }

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(leftType->_enum.defines);
        for (; elem != List_End(leftType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "success")) {
                innerType = define->define.symbol->type;
                break;
            }
        }

        if (!innerType) {
            error(left->pos, "left side of catch must be error enum type");
        }

        if (rightType->astType != AST_UNDEF && !typesAreEquivalent(rightType, innerType)) {
            incompatibleTypesError(node->pos, innerType, rightType);
        }

        node->taggedBinop.tag = getTagEnum("success", leftType);
        node->taggedBinop.left = left;
        node->taggedBinop.right = right;
        retval = node;
        break;
    }
    case AST_ORELSE: {
        ASTNode* left = validateAST(node->taggedBinop.left, NULL);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* right = validateAST(node->taggedBinop.right, NULL);
        ASTNode* rightType = getType(right, false, false);

        if (leftType->astType != AST_ENUM) {
            error(left->pos, "left side of orelse must be maybe enum type");
        }

        ASTNode* innerType = NULL;
        ListElem* elem = List_Begin(leftType->_enum.defines);
        for (; elem != List_End(leftType->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            if (!strcmp(define->define.symbol->name, "something")) {
                innerType = define->define.symbol->type;
                break;
            }
        }

        if (!innerType) {
            error(left->pos, "left side of orelse must be maybe enum type");
        }

        if (rightType->astType != AST_UNDEF && !typesAreEquivalent(rightType, innerType)) {
            incompatibleTypesError(node->pos, innerType, rightType);
        }

        node->taggedBinop.tag = getTagEnum("nothing", leftType);
        node->taggedBinop.left = left;
        node->taggedBinop.right = right;
        retval = node;
        break;
    }
    case AST_CALL: {
        // call is to a function type
        ASTNode* expr = node->call.left;
        validateAST(expr, NULL);
        ASTNode* exprType = getType(expr, false, false);
        node->call.left = expr;
        expr->type = exprType;
        node->call.fnType = exprType;
        if (exprType->astType != AST_FUNCTION) {
            error(node->pos, "call is not to function");
        }
        argsMatchParams(expr, node->call.right, exprType->function.domainType);
        node->call.right->astType = AST_ARGLIST;
        node->call.right = validateAST(node->call.right, NULL);
        retval = node;
        break;
    }
    case AST_INDEX: {
        ASTNode* left = node->binop.left;
        left->type = validateAST(left, NULL)->type;
        ASTNode* leftType = getType(left, false, false);
        if (leftType->astType != AST_ADDR && leftType->astType != AST_ARRAY) {
            expectedArray(node->binop.left->pos, leftType);
        }

        node->binop.left = left;
        node->binop.right = validateAST(node->binop.right, INT64_TYPE);
        retval = node;
        break;
    }
    case AST_SLICE: {
        ASTNode* validArrExpr = validateAST(node->slice.arrayExpr, NULL);
        ASTNode* leftType = getType(validArrExpr, false, false);
        if (leftType->astType != AST_ADDR && leftType->astType != AST_ARRAY) {
            expectedArray(node->slice.arrayExpr->pos, leftType);
        }

        node->slice.arrayExpr = validArrExpr;
        if (node->slice.lowerBound->astType != AST_UNDEF) {
            node->slice.lowerBound = validateAST(node->slice.lowerBound, INT64_TYPE);
        }
        if (node->slice.upperBound->astType != AST_UNDEF) {
            node->slice.upperBound = validateAST(node->slice.upperBound, INT64_TYPE);
        }
        retval = node;
        break;
    }
    case AST_DOT: {
        ASTNode* left = validateAST(node->dot.left, NULL);

        SymbolNode* leftVar = NULL;
        if (left->astType == AST_IDENT) {
            leftVar = Symbol_Find(left->ident.data, node->scope);
            node->dot.left = left;
        } else if (left->astType == AST_DOT) {
            leftVar = getDotSymbol(left);
            node->dot.left = left;
        } else if (node->dot.left->astType == AST_IDENT) {
            leftVar = Symbol_Find(node->dot.left->ident.data, node->scope);
        } else if (node->dot.left->astType == AST_DOT) {
            leftVar = getDotSymbol(node->dot.left);
        }

        ASTNode* leftType = getType(left, false, false);
        ASTNode* dotType = getType(node, false, true);

        getDotSymbol(node); // TODO: comptime collapse
        if (left->astType == AST_ENUM) {
            retval = AST_Create_enumLiteral(getTagEnum(node->dot.right->ident.data, left), NULL, node->scope, node->pos);
            retval->type = left;
        } else if (leftType->astType == AST_ENUM) {
            if (dotType->astType == AST_VOID) {
                return NOTHING_AST;
            } else {
                retval = node;
                break;
            }
        } else if (leftType->astType == AST_ADDR) {
            node->dot.left = validateAST(AST_Create_deref(left, node->scope, node->pos), NULL);
            retval = node;
            break;
        } else {
            retval = node;
            break;
        }
        break;
    }
    case AST_CAST: {
        ASTNode* expr = validateAST(node->binop.left, NULL);
        // cast type is valid type
        node->binop.right = expandTypeIdent(node->binop.right, true);
        ASTNode* cast = node->binop.right;
        validateType(cast, true);

        // cannot cast between function addr and data addr
        ASTNode* exprType = getType(expr, false, false);
        if (cast->isConst && !exprType->isConst) {
            error(node->pos, "cast from variable type to constant type");
        }
        if (exprType->astType == AST_ADDR && cast->astType == AST_FUNCTION) {
            error(node->pos, "cast from data address to function address");
        }
        if (exprType->astType == AST_FUNCTION && cast->astType == AST_ADDR) {
            error(node->pos, "cast from function address to data address");
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

        node->binop.left = expr;
        retval = node;
        break;
    }
    case AST_NEW: {
        // type is valid
        node->binop.left = expandTypeIdent(node->binop.left, true);
        validateType(node->binop.left, true);

        ASTNode* type = node->binop.left;
        if (type->astType == AST_ARRAY) {
            ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
            SymbolNode* lengthSymbol = lengthDefine->define.symbol;
            ASTNode* lengthCode = lengthSymbol->def;
            if (lengthCode->astType == AST_UNDEF) {
                error(lengthCode->pos, "array size is missing");
            }
        }

        // If intializer is array, initializer is correct type
        ASTNode* validInit = validateAST(node->binop.right, type);
        if (validInit->astType == AST_ARRAY_LITERAL) {
            ASTNode* initType = getType(validInit, false, false);
            if (!typesAreEquivalent(initType, type)) {
                typeMismatchError(node->pos, type, initType);
            }
            ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
            SymbolNode* lengthSymbol = lengthDefine->define.symbol;
            ASTNode* lengthCode = lengthSymbol->def;
            if (lengthCode->astType != AST_INT) {
                error(node->pos, "cannot use initializer, array size is not known at compile time");
            }
        } else if (validInit->astType == AST_ARGLIST || validInit->astType == AST_PAREN) {
            validInit->astType = AST_ARGLIST;
            argsMatchParams(NULL, validInit, type);
            validInit->type = type;
        }
        node->binop.right = validInit;
        retval = node;
        break;
    }
    case AST_FREE: {
        ASTNode* validChild = validateAST(node->unop.expr, NULL);
        ASTNode* childType = getType(validChild, false, false);
        if (childType->astType != AST_ADDR && childType->astType != AST_ARRAY) {
            char actualStr[255];
            AST_TypeRepr(actualStr, childType);
            error(node->pos, "expected address, got %s", actualStr);
        }
        node->unop.expr = validChild;
        retval = node;
        break;
    }
    case AST_PAREN: {
        retval = validateAST(List_Get(node->arglist.args, 0), coerceType);
        break;
    }
    case AST_OR_ASSIGN:
    case AST_AND_ASSIGN: {
        ASTNode* left = node->binop.left;
        left->type = validateAST(left, BOOL_TYPE)->type;
        ASTNode* right = validateAST(node->binop.right, BOOL_TYPE);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        validateLValue(left);

        BinopConstructor constructor = getBinopConstructor(node->astType);
        retval = AST_Create_assign(left, constructor(left, right, node->scope, node->pos), node->scope, node->pos);
        validateAST(retval, NULL); // To give it a type
        break;
    }
    case AST_BIT_OR_ASSIGN:
    case AST_BIT_XOR_ASSIGN:
    case AST_BIT_AND_ASSIGN:
    case AST_LSHIFT_ASSIGN:
    case AST_RSHIFT_ASSIGN:
    case AST_MOD_ASSIGN: {
        ASTNode* left = node->binop.left;
        left->type = validateAST(left, INT64_TYPE)->type;
        ASTNode* right = validateAST(node->binop.right, INT64_TYPE);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        validateLValue(left);

        BinopConstructor constructor = getBinopConstructor(node->astType);
        retval = AST_Create_assign(left, constructor(left, right, node->scope, node->pos), node->scope, node->pos);
        validateAST(retval, NULL); // To give it a type
        break;
    }
    case AST_ADD_ASSIGN:
    case AST_SUB_ASSIGN:
    case AST_MULT_ASSIGN:
    case AST_DIV_ASSIGN:
    case AST_EXPONENT_ASSIGN: {
        ASTNode* left = node->binop.left;
        left->type = validateAST(left, REAL64_TYPE)->type;
        ASTNode* right = validateAST(node->binop.right, REAL64_TYPE);
        ASTNode* leftType = getType(left, false, false);
        ASTNode* rightType = getType(right, false, false);
        if (!typesAreEquivalent(rightType, leftType)) {
            incompatibleTypesError(node->pos, leftType, rightType);
        }

        validateLValue(left);

        BinopConstructor constructor = getBinopConstructor(node->astType);
        retval = AST_Create_assign(left, constructor(left, right, node->scope, node->pos), node->scope, node->pos);
        validateAST(retval, NULL); // To give it a type
        break;
    }
    case AST_DEFINE: {
        SymbolNode* var = node->define.symbol;
        /// var type is not Type or Enum
        if (var->type->astType != AST_IDENT || strcmp(var->type->ident.data, "Type")) {
            inferTypes(var);
        } else if (!strcmp(var->type->ident.data, "Type")) {
            var->def = expandTypeIdent(var->def, true);
            validateType(var->def, true);
        }
        retval = node;
        break;
    }
    case AST_BLOCK: {
        node->block.returnEval = lastEval;
        List* validChildren = List_Create();
        forall(elem, node->block.children)
        {
            ASTNode* child = elem->data;
            if (elem->next == List_End(node->block.children)) {
                lastEval = true;
                bool oldErrorHandled = errorHandled;
                errorHandled = node->block.returnEval;
                List_Append(validChildren, validateAST(child, coerceType));
                errorHandled = oldErrorHandled;
            } else {
                lastEval = false;
                List_Append(validChildren, validateAST(child, NULL));
            }
        }
        node->block.children = validChildren;
        retval = node;
        break;
    }
    case AST_IF: {
        ASTNode* validCondition = validateAST(node->_if.condition, BOOL_TYPE);
        ASTNode* validBodyBlock = validateAST(node->_if.bodyBlock, coerceType);
        ASTNode* validElseBlock = validateAST(node->_if.elseBlock, coerceType);

        if (validElseBlock->astType != AST_UNDEF) {
            node->type = coerceType;
        }

        node->_if.condition = validCondition;
        node->_if.bodyBlock = validBodyBlock;
        node->_if.elseBlock = validElseBlock;
        retval = node;
        break;
    }
    case AST_FOR: {
        // condition (#1) is bool type
        ASTNode* validPre = validateAST(node->_for.pre, NULL);
        ASTNode* validCondition = validateAST(node->_for.condition, BOOL_TYPE);
        ASTNode* validPost = validateAST(node->_for.post, NULL);

        loops++;
        ASTNode* validBodyBlock = validateAST(node->_for.bodyBlock, coerceType);
        loops--;

        ASTNode* validElseBlock = validateAST(node->_for.elseBlock, coerceType);

        if (validCondition->astType == AST_UNDEF) {
            validCondition = TRUE_AST;
        } else {
            ASTNode* conditionType = getType(validCondition, false, false);
            if (!typesAreEquivalent(conditionType, BOOL_TYPE)) {
                typeMismatchError(validCondition->pos, BOOL_TYPE, conditionType);
            }
        }

        node->_for.pre = validPre;
        node->_for.condition = validCondition;
        node->_for.post = validPost;
        node->_for.bodyBlock = validBodyBlock;
        node->_for.elseBlock = validElseBlock;
        retval = node;
        break;
    }
    case AST_CASE: {
        bool oldErrorHandled = errorHandled;
        errorHandled = true;
        ASTNode* validExpr = validateAST(node->_case.expr, NULL);
        ASTNode* elementType = getType(validExpr, false, false);
        errorHandled = oldErrorHandled; // TODO: require full field for errors

        List* validMappings = List_Create();
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            List_Append(validMappings, validateAST(mapping, coerceType));
        }

        // only one 'else' mapping
        int elseCaseCount = 0;
        ListElem* elem = List_Begin(validMappings);
        for (; elem != List_End(validMappings); elem = elem->next) {
            ASTNode* mapping = elem->data;
            if (mapping->mapping.exprs->size == 0) {
                elseCaseCount++;
                if (elseCaseCount > 1) {
                    error(mapping->pos, "multiple 'else' mappings in case statement");
                }
            }
        }
        // TODO: all cases have different numbers
        // TODO: all cases must be comptime integer exprs
        node->_case.expr = validExpr;
        node->_case.mappings = validMappings;
        retval = node;
        break;
    }
    case AST_FIELD_CASE: {
        ASTNode* validExpr = validateAST(node->_case.expr, NULL); // TODO: what goes here?

        // switch expression must be a enum set
        ASTNode* elementType = getType(validExpr, false, false);
        bool isEnumCase = false;
        if (elementType->astType != AST_ENUM) {
            error(node->pos, "must be a enum type");
        }

        List* validMappings = List_Create();
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            ASTNode* validMapping = NULL;
            SymbolNode* var = NULL;
            // TODO: change syntax so that only one field mapping is parsed
            ASTNode* mappingIdent = NULL;
            if (mapping->fieldMapping.exprs->size == 1) {
                mappingIdent = List_Get(mapping->fieldMapping.exprs, 0);
                if (mappingIdent->astType != AST_IDENT) {
                    error(mappingIdent->pos, "expected identifier");
                }
            }
            validMapping = validateAST(mapping, coerceType);
            if (validMapping->fieldMapping.exprs->size > 1) {
                error(validMapping->pos, "field mapping with too many expressions");
            }
            validMapping->fieldMapping.tag = getTagEnum(mappingIdent->ident.data, elementType);
            List_Append(validMappings, validMapping);
        }

        // only one 'else' mapping
        int elseCaseCount = 0;
        ListElem* elem = List_Begin(validMappings);
        for (; elem != List_End(validMappings); elem = elem->next) {
            ASTNode* mapping = elem->data;
            if (mapping->mapping.exprs->size == 0) {
                elseCaseCount++;
                if (elseCaseCount > 1) {
                    error(mapping->pos, "multiple 'else' mappings in case statement");
                }
            }
        }
        node->_case.expr = validExpr;
        node->_case.mappings = validMappings;
        retval = node;
        break;
    }
    case AST_MAPPING: {
        List* validExprs = List_Create();
        forall(elem, node->mapping.exprs)
        {
            ASTNode* mapping = elem->data;
            List_Append(validExprs, validateAST(mapping, NULL));
        }
        ASTNode* validExpr = validateAST(node->mapping.expr, coerceType);
        node->mapping.exprs = validExprs;
        node->mapping.expr = validExpr;
        retval = node;
        break;
    }
    case AST_FIELD_MAPPING: {
        ASTNode* validExpr = validateAST(node->mapping.expr, coerceType);
        node->mapping.expr = validExpr;
        retval = node;
        break;
    }
    case AST_RETURN: {
        // return must be in function
        SymbolNode* function = Symbol_TypeAncestor(node->scope, SYMBOL_FUNCTION);
        if (function == NULL) {
            function = Symbol_TypeAncestor(node->scope, SYMBOL_FUNCTION);
            if (function == NULL) {
                error(node->pos, "return not within function");
                break;
            }
        }
        // return type matches function type
        ASTNode* functionType = function->type;
        ASTNode* functionRetType = functionType->function.codomainType;
        ASTNode* validRetval = NULL;
        bool oldErrorHandled = errorHandled;
        errorHandled = true;
        if (functionRetType->astType == AST_VOID) {
            validRetval = validateAST(node->unop.expr, NULL);
        } else {
            validRetval = validateAST(node->unop.expr, functionRetType);
        }
        errorHandled = oldErrorHandled;

        node->unop.expr = validRetval;
        retval = node;
        break;
    }
    case AST_BREAK: {
        // within a for, while, or do-while loop
        if (loops == 0) {
            error(node->pos, "break not in loop");
        }
        retval = node;
        break;
    }
    case AST_CONTINUE: {
        // within a for, while, or do-while loop
        if (loops == 0) {
            error(node->pos, "continue not in loop");
        }
        retval = node;
        break;
    }
    case AST_DEFER: {
        ASTNode* validStatement = validateAST(node->defer.statement, NULL);
        if (node->containsReturn) {
            error(node->pos, "defer statement cannot contain return");
        } else if (node->containsBreak) {
            error(node->pos, "defer statement cannot contain break");
        } else if (node->containsContinue) {
            error(node->pos, "defer statement cannot contain continue");
        }
        node->defer.statement = validStatement;
        retval = node;
        break;
    }
    case AST_ERRDEFER: {
        ASTNode* validStatement = validateAST(node->defer.statement, NULL);
        if (node->containsReturn) {
            error(node->pos, "errdefer statement cannot contain return");
        } else if (node->containsBreak) {
            error(node->pos, "errdefer statement cannot contain break");
        } else if (node->containsContinue) {
            error(node->pos, "errdefer statement cannot contain continue");
        }
        node->defer.statement = validStatement;
        retval = node;
        break;
    }
    case AST_PARAMLIST:
    case AST_ARRAY: {
        ListElem* elem = List_Begin(node->paramlist.defines);
        for (; elem != List_End(node->paramlist.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            validateAST(define, NULL);
        }
        retval = UNDEF_TYPE;
        break;
    }
    case AST_ENUM:
    case AST_INFER_ERROR: {
        ListElem* elem = List_Begin(node->_enum.defines);
        for (; elem != List_End(node->_enum.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            validateAST(define, NULL);
        }
        retval = UNDEF_TYPE;
        break;
    }
    default: {
        error(node->pos, "unvalidatable %d", node->astType);
    }
    }
    if (retval) {
        retval->type = getType(retval, false, true);
        if (retval->astType == AST_ARGLIST && coerceType && coerceType->astType != AST_UNDEF) {
            argsMatchParams(NULL, retval, coerceType);
        } else if (coerceType && coerceType->astType != AST_UNDEF && retval->astType != AST_UNDEF && retval->type->astType != AST_UNDEF && !typesAreEquivalent(retval->type, coerceType)) {
            ASTNode* coercedEnum = NULL;
            if (coercedEnum = tryCoerceToEnum(coerceType, retval)) {
                retval = coercedEnum;
            } else {
                typeMismatchError(retval->pos, coerceType, retval->type);
            }
        }
    } else {
        ASSERT(0);
    }
    return retval;
}

// Registers the field name/type pair if it is unique
static void putTag(char* fieldName, ASTNode* fieldType)
{
    static int tagID = 0;
    List* typeSet = Map_Get(tagTypes, fieldName);
    List* typeList = Map_Get(tagIDs, fieldName);
    if (!typeSet && !typeList) {
        typeSet = List_Create();
        Map_Put(tagTypes, fieldName, typeSet);

        typeList = List_Create();
        Map_Put(tagIDs, fieldName, typeList);
    }

    // Add the type to the set using type equality, not equivalence
    bool typeSetContainsType = false;
    forall(elem2, typeSet) // Find if the type is in the typeSet
    {
        ASTNode* type = elem2->data;
        if (typesAreEquivalent(fieldType, type) && typesAreEquivalent(type, fieldType)) {
            typeSetContainsType = true;
            break;
        }
    }
    if (!typeSetContainsType) {
        int tag = tagID;
        tagID += 1;
        List_Append(typeList, tag);
        List_Append(typeSet, fieldType);
    }
}

// Adds a struct to the dependency graph if it is unique, with all dependencies 
static struct graph* addGraphNode(List* depenGraph, ASTNode* structType)
{
    // Check if type is enum, if so, collect tags
    if (structType->astType == AST_ENUM || structType->astType == AST_INFER_ERROR) {
        forall(elem, structType->_enum.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* symbol = define->define.symbol;
            // Check if there is a set created in the map, if not create it
            putTag(symbol->name, symbol->type);
        }
    }

    // Check list to see if any graph node has paramlist type
    // If does, return that graph node
    // If not, create new grpahnode, append to list of dependencies, return new graph node
    bool oldTypePermissiveness = structuralTypeEquiv;
    structuralTypeEquiv = false;
    ListElem* elem = List_Begin(depenGraph);
    for (; elem != List_End(depenGraph); elem = elem->next) {
        DGraph* graphNode = elem->data;
        if (typesAreEquivalent(graphNode->structDef, structType)) {
            return graphNode;
        }
    }
    structuralTypeEquiv = oldTypePermissiveness;

    DGraph* graphNode = calloc(1, sizeof(DGraph));
    graphNode->structDef = structType;
    graphNode->visited = false;
    graphNode->ordinal = depenGraph->size;
    graphNode->dependencies = List_Create();
    List_Append(depenGraph, graphNode);

    return graphNode;
}

// Checks that a dependency graph doesn't have loops in it
static void validateNoLoops(DGraph* graphNode)
{
    graphNode->visited = true;
    ListElem* elem = List_Begin(graphNode->dependencies);
    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
        DGraph* child = elem->data;
        if (child->visited) {
            error(child->structDef->pos, "loop detected");
        }
        validateNoLoops(child);
    }
    graphNode->visited = false;
}

// Validates that a type AST is correctly formed. 'collectThisType' is whether to add type to the dependency graph or not
static void validateType(ASTNode* node, bool collectThisType)
{
    ASSERT(node != NULL);
    if (node->isValid) {
        return;
    }

    switch (node->astType) {
    case AST_IDENT: {
        if (strcmp(node->ident.data, "Int") && //
            strcmp(node->ident.data, "Char") && //
            strcmp(node->ident.data, "Bool") && //
            strcmp(node->ident.data, "Char") && //
            strcmp(node->ident.data, "Real") && //
            strcmp(node->ident.data, "String") && //
            strcmp(node->ident.data, "Type") && //
            strcmp(node->ident.data, "Package") && //
            strcmp(node->ident.data, "Module") && //
            strcmp(node->ident.data, "Enum") && //
            strcmp(node->ident.data, "Int8") && //
            strcmp(node->ident.data, "Int16") && //
            strcmp(node->ident.data, "Int32") && //
            strcmp(node->ident.data, "Int64") && //
            strcmp(node->ident.data, "Real32") && //
            strcmp(node->ident.data, "Real64")) {
            SymbolNode* var = Symbol_Find(node->ident.data, node->scope);
            if (var == NULL) {
                restrictedOrUndefError(node->pos, (Position) { NULL, 0 }, node->ident.data);
            } else if (var == -1) {
                restrictedOrUndefError(node->pos, rejectingSymbol->pos, node->ident.data);
            } else if (var->symbolType != SYMBOL_TYPE) {
                error(node->pos, "symbol '%s' is not a type 2", node->ident.data);
            }
        }
        break;
    }
    case AST_DOT: {
        validateAST(node, NULL);
        ASTNode* dotType = getType(node, false, false);
        if (dotType->astType != AST_IDENT || !(!strcmp(dotType->ident.data, "Type") || !strcmp(dotType->ident.data, "Enum"))) {
            error(node->pos, "symbol '%s' is not a type 3", node->dot.right->ident.data);
        }
        SymbolNode* var = getDotSymbol(node);
        break;
    }
    case AST_VOID:
    case AST_UNDEF: {
        break;
    }
    case AST_ADDR: {
        validateType(node->unop.expr, collectThisType);
        break;
    }
    case AST_PARAMLIST: {
        validateAST(node, NULL);
        break;
    }
    case AST_ARRAY: {
        ASTNode* typeDefine = List_Get(node->paramlist.defines, 1);
        ASTNode* lengthDefine = List_Get(node->paramlist.defines, 0);
        SymbolNode* type = typeDefine->define.symbol;
        SymbolNode* length = lengthDefine->define.symbol;
        validateType(type->type, collectThisType);
        length->def = validateAST(length->def, NULL);
        ASTNode* lengthType = getType(length->def, "", false);
        if (lengthType->astType != AST_UNDEF && !typesAreEquivalent(lengthType, INT64_TYPE)) {
            typeMismatchError(node->pos, INT32_TYPE, lengthType);
        }
        break;
    }
    case AST_ENUM:
    case AST_INFER_ERROR: {
        validateAST(node, NULL);
        break;
    }
    case AST_FUNCTION: {
        ASTNode* params = node->function.domainType;
        ASTNode* rets = node->function.codomainType;
        validateType(params, false);
        validateType(rets, true);
        break;
    }
    case AST_EXTERN: {
        SymbolNode* type = node->_extern.symbol;
        if (!typesAreEquivalent(type->type, TYPE_TYPE)) {
            typeMismatchError(node->pos, TYPE_TYPE, type->type);
        }
        break;
    }
    default: {
        error(node->pos, "not a type");
    }
    }
    node->isValid = true;

    // Collect structs
    if (collectThisType && (node->astType == AST_PARAMLIST || node->astType == AST_ARRAY || node->astType == AST_ENUM || node->astType == AST_INFER_ERROR) && node->paramlist.defines->size > 0) {
        DGraph* graphNode = addGraphNode(structDepenGraph, node);

        // go through fields, if field is a parameter list, add to dependencies
        ListElem* paramElem = List_Begin(node->paramlist.defines);
        for (; paramElem != List_End(node->paramlist.defines); paramElem = paramElem->next) {
            ASTNode* fieldDefine = paramElem->data;
            SymbolNode* fieldVar = fieldDefine->define.symbol;
            ASTNode* fieldType = expandTypeIdent(fieldVar->type, true);
            if (fieldType->astType == AST_PARAMLIST || fieldType->astType == AST_ARRAY || fieldType->astType == AST_ENUM || fieldType->astType == AST_INFER_ERROR) {
                DGraph* dependency = addGraphNode(structDepenGraph, fieldType);
                List_Append(graphNode->dependencies, dependency);
            }
        }

        validateNoLoops(graphNode);
    }
}

// Figures out which symbols are allowed through the given symbol's restriction
static void resolveRestrictions(SymbolNode* symbol)
{
    List* allowedIdentifiers = symbol->restrictionExpr;
    ListElem* e = List_Begin(allowedIdentifiers);
    for (; e != List_End(allowedIdentifiers); e = e->next) {
        ASTNode* expr = e->data;
        SymbolNode* var = NULL;
        if (expr->astType == AST_IDENT) {
            var = Symbol_Find(expr->ident.data, symbol->parent);
        } else if (expr->astType == AST_DOT) {
            var = getDotSymbol(expr);
        } else {
            error(expr->pos, "expected symbol expression");
        }
        if (var == NULL) {
            error(expr->pos, "unable to resolve symbol");
        } else if (var->parent != symbol->parent) {
            error(expr->pos, "not in parent scope");
        }
        List_Append(symbol->restrictions, var);
    }

    List* children = symbol->children->keyList;
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        resolveRestrictions(child);
    }
}

// Validate that all possible paths return some value
static bool allReturnPath(ASTNode* node)
{
    if (node->astType == AST_RETURN) {
        return true;
    } else if (node->astType == AST_CASE) {
        return true;
    } else if (node->astType == AST_IF && node->_if.elseBlock->astType != AST_UNDEF) {
        return allReturnPath(node->_if.bodyBlock) && allReturnPath(node->_if.elseBlock);
    } else if (node->astType == AST_BLOCK) {
        ListElem* elem = List_Begin(node->block.children);
        for (; elem != List_End(node->block.children); elem = elem->next) {
            if (allReturnPath(elem->data)) {
                return true;
            }
        }
    }
    return true;
}

// TODO: rename to validateSymbol or somem
// Validates that a symbol is correct
Program Validator_Validate(SymbolNode* symbol)
{
    ASSERT(symbol != NULL);

    if (symbol->visited) {
        return;
    } else {
        symbol->visited = true;
    }

    // Done first pass through
    if (structDepenGraph == NULL) {
        structDepenGraph = List_Create();
        includes = Map_Create();
        verbatims = List_Create();
        tagTypes = Map_Create();
        tagIDs = Map_Create();

        validateType(CONST_STRING_TYPE, true);
        validateType(STRING_ARR_TYPE, true);
        validateType(MAYBE_VOID_TYPE, true);
        structuralTypeEquiv = true;
        resolveRestrictions(symbol);
    }

    // Move inner functions up to module level
    if (symbol->symbolType == SYMBOL_FUNCTION && symbol->parent->symbolType == SYMBOL_BLOCK) {
        SymbolNode* realParent = symbol->parent;
        while (realParent->symbolType != SYMBOL_MODULE) {
            realParent = realParent->parent;
        }
        symbol->parent = realParent;
    }

    // Expand symbol type
    if (symbol->type) {
        symbol->originalType = symbol->type;
        symbol->type = expandTypeIdent(symbol->type, true);
        validateType(symbol->type, true);
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
        if (mainFunction) {
            callGraph = createCFG(mainFunction, NULL);
        } else {
            gen_error("no main function defined");
        }
        structuralTypeEquiv = false;
        unVisitSymbolTree(symbol);
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
                error(child->pos, "immediate child symbol '%s' of package '%s' is not constant", child->name, symbol->name);
            }
        }
        if (symbol->def->astType != AST_PARAMLIST && symbol->def->astType != AST_VOID) {
            error(symbol->pos, "expected parameter list");
        }
        validateAST(symbol->def, NULL);

        SymbolNode* includesSymbol = Map_Get(symbol->children, "includes");
        SymbolNode* verbatimSymbol = Map_Get(symbol->children, "verbatim");
        if (includesSymbol) {
            if (includesSymbol->def->astType != AST_ARRAY_LITERAL) {
                error(includesSymbol->pos, "includes array must be a string array");
            }
            ListElem* e = List_Begin(includesSymbol->def->arrayLiteral.members);
            for (; e != List_End(includesSymbol->def->arrayLiteral.members); e = e->next) {
                ASTNode* stringLiteral = e->data;
                if (!typesAreEquivalent(stringLiteral->type, STRING_TYPE)) {
                    typeMismatchError(stringLiteral->pos, STRING_TYPE, stringLiteral->type);
                }
                Map_Put(includes, stringLiteral->string.data, 1);
            }
        }
        if (verbatimSymbol) {
            if (verbatimSymbol->def->astType != AST_ARRAY_LITERAL) {
                error(verbatimSymbol->pos, "verbatim array must be a string array");
            }
            ListElem* e = List_Begin(verbatimSymbol->def->arrayLiteral.members);
            for (; e != List_End(verbatimSymbol->def->arrayLiteral.members); e = e->next) {
                ASTNode* stringLiteral = e->data;
                if (!typesAreEquivalent(stringLiteral->type, STRING_TYPE)) {
                    typeMismatchError(stringLiteral->pos, STRING_TYPE, stringLiteral->type);
                }
                List_Append(verbatims, stringLiteral->string.data);
            }
        }
        break;
    }
    case SYMBOL_FUNCTION: {
        ListElem* elem = List_Begin(children);
        for (; elem != List_End(children); elem = elem->next) {
            SymbolNode* child = Map_Get(symbol->children, elem->data);
            Validator_Validate(child);
        }

        ASTNode* retType = symbol->type->function.codomainType;
        if (retType->astType != AST_VOID && !(retType->astType == AST_INFER_ERROR && enumContainsField(retType, "success", VOID_TYPE))) {
            symbol->def = validateAST(symbol->def, symbol->type->function.codomainType);
        } else {
            symbol->def = validateAST(symbol->def, NULL);
        }
        if (symbol->type->function.codomainType->astType == AST_INFER_ERROR) {
            symbol->type->function.codomainType->astType = AST_ENUM;
            addGraphNode(structDepenGraph, symbol->type->function.codomainType);
        }

        if (!symbol->isExtern && retType->astType != AST_VOID && !allReturnPath(symbol->def)) {
            error(symbol->pos, "not all paths return a value in '%s'", symbol->name);
        }
        if (!strcmp(symbol->name, "main")) {
            if (symbol->type->function.codomainType->astType == AST_ENUM && enumContainsField(symbol->type->function.codomainType, "success", VOID_TYPE)) {
                if (mainFunction) {
                    error2(symbol->pos, mainFunction->pos, "multiple main function definitions");
                } else {
                    mainFunction = symbol;
                }
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
        validateType(symbol->def, true);
        // if def ast type is param list then for all define in paramlist children, define symbol is not extern
        if (symbol->def->astType == AST_PARAMLIST || symbol->def->astType == AST_ENUM) {
            forall(elem, symbol->def->paramlist.defines)
            {
                ASTNode* define = elem->data;
                SymbolNode* var = define->define.symbol;
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
        }
        validateAST(symbol->def, NULL);
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
            validateAST(child, NULL);
        }
        break;
    }
    }

    return (Program) { structDepenGraph, includes, verbatims, callGraph };
}