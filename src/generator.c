/*
This file deals with generating the output C file from the AST and Symbol trees
parsed from the input file.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "generator.h"
#include "./main.h"
#include "./parse.h"
#include "./position.h"
#include "./validator.h"
#include <stdlib.h>
#include <string.h>

Program program;

static int generateAST(FILE* out, ASTNode* node);
static void generateParamList(FILE* out, ASTNode* parameters);

static bool global = false;

/*
Given a symbol node representing a symbol, prints the path from the root of the
symbol tree to the given node out to the given file.
*/
static void printPath(FILE* out, SymbolNode* symbol)
{
    // Local variables
    if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && symbol->parent->symbolType == SYMBOL_BLOCK) {
        fprintf(out, "_%s_%s", symbol->parent->name, symbol->name);
    }
    // Parameters
    else if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && (symbol->parent->symbolType == SYMBOL_FUNCTION || symbol->parent->symbolType == SYMBOL_PROCEDURE)) {
        fprintf(out, "_%s", symbol->name);
    }
    // Everything else
    else if (symbol->parent && (symbol->parent->symbolType != SYMBOL_TYPE || symbol->symbolType == SYMBOL_PROCEDURE) && symbol->parent->parent && !symbol->isExtern) {
        if (symbol->parent->symbolType != SYMBOL_VARIABLE) { // Done so that fields in anon structs collected by variable types don't have their variable names appended
            // Done so that inner functions print correctly (i think)
            if (symbol->symbolType == SYMBOL_VARIABLE || (symbol->parent->parent->symbolType != SYMBOL_BLOCK && symbol->parent->symbolType != SYMBOL_PROCEDURE && symbol->parent->symbolType != SYMBOL_FUNCTION)) {
                printPath(out, symbol->parent);
            }
            fprintf(out, "_%s", symbol->name);
        } else {
            fprintf(out, "%s", symbol->name);
        }
    } else if (symbol->isExtern) {
        fprintf(out, "%s", symbol->externName);
    } else {
        fprintf(out, "%s", symbol->name);
    }
}

// Used for enum printing
static int sprintPath(char* str, SymbolNode* symbol)
{
    char* origStr = str;
    if (symbol->parent && symbol->parent->symbolType != SYMBOL_TYPE && symbol->parent->parent && !symbol->isExtern) {
        if (symbol->parent->parent->symbolType != SYMBOL_BLOCK && symbol->parent->symbolType != SYMBOL_PROCEDURE && symbol->parent->symbolType != SYMBOL_FUNCTION) {
            str += sprintPath(str, symbol->parent);
        }
        str += sprintf(str, "_%s", symbol->name);
    } else if (symbol->isExtern) {
        str += sprintf(str, "%s", symbol->externName);
    } else {
        str += sprintf(str, "%s", symbol->name);
    }
    return str - origStr;
}

static void printStructOrd(FILE* out, ASTNode* type)
{
    struct listElem* elem = List_Begin(program.dependencyGraph);
    int i = 1;
    bool found = false;
    for (; !found && elem != List_End(program.dependencyGraph); elem = List_Next(elem), i++) {
        DGraph* node = (DGraph*)elem->data;
        ASTNode* child = node->structDef;
        if (typesAreEquivalent(child, type)) {
            fprintf(out, "struct_%s", myItoa(i));
            found = true;
        }
    }
}

static void printType(FILE* out, ASTNode* type)
{
    switch (type->astType) {
    case AST_IDENT:
        if (!strcmp(type->data, "Int8") || !strcmp(type->data, "Char")) {
            fprintf(out, "%s", "int8_t");
        } else if (!strcmp(type->data, "Int16")) {
            fprintf(out, "%s", "int16_t");
        } else if (!strcmp(type->data, "Int32")) {
            fprintf(out, "%s", "int32_t");
        } else if (!strcmp(type->data, "Int64") || !strcmp(type->data, "Int")) {
            fprintf(out, "%s", "int64_t");
        } else if (!strcmp(type->data, "Bool")) {
            fprintf(out, "%s", "bool");
        } else if (!strcmp(type->data, "Real32") || !strcmp(type->data, "Real")) {
            fprintf(out, "%s", "float");
        } else if (!strcmp(type->data, "Real64")) {
            fprintf(out, "%s", "double");
        } else if (!strcmp(type->data, "String")) {
            printType(out, STRING_TYPE);
        } else {
            fprintf(out, "%s", type->data);
        }
        break;
    case AST_DOT:
        SymbolNode* var = type->data;
        if (var->isExtern) {
            fprintf(out, "%s", var->externName);
        } else {
            printType(out, type->type);
        }
        break;
    case AST_ADDR:
        printType(out, List_Get(type->children, 0));
        fprintf(out, "*");
        break;
    case AST_C_ARRAY:
        printType(out, List_Get(type->children, 0));
        break;
    case AST_ARRAY:
    case AST_PARAMLIST: {
        fprintf(out, "struct ");
        printStructOrd(out, type);
    } break;
    case AST_VOID: {
        fprintf(out, "void");
        break;
    }
    case AST_FUNCTION:
    case AST_PROCEDURE:
        // The second child in a function is the return type
        ASTNode* ret = List_Get(type->children, 1);
        printType(out, ret);
        break;

    case AST_ENUM: {
        fprintf(out, "unsigned int");
        break;
    }
    case AST_EXTERN: {
        SymbolNode* var = type->data;
        fprintf(out, "%s", var->externName);
        break;
    }
    default: {
        fprintf(out, "%s", AST_GetString(type->astType));
    }
    }
}

static void generateDefaultValue(FILE* out, ASTNode* type)
{
    switch (type->astType) {
    default:
        fprintf(out, "0");
        break;
    case AST_ARRAY: {
        ASTNode* dataDefine = List_Get(type->children, 1);
        SymbolNode* dataSymbol = dataDefine->data;
        ASTNode* dataAddrType = dataSymbol->type;
        ASTNode* dataType = List_Get(dataAddrType->children, 0);
        ASTNode* dataLength = List_Get(dataAddrType->children, 1);
        fprintf(out, "((");
        printType(out, type);
        fprintf(out, "){%d", (int)dataLength->data);
        for (int i = 0; i < (int)dataLength->data; i++) {
            fprintf(out, ", ");
            generateDefaultValue(out, dataType);
        }
        fprintf(out, "})");
    } break;
    case AST_PARAMLIST: {
        fprintf(out, "((");
        printType(out, type);
        fprintf(out, "){");
        for (ListElem* elem = List_Begin(type->children); elem != List_End(type->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* var = define->data;
            if (var->def->astType == AST_UNDEF) {
                generateDefaultValue(out, var->type);
                if (elem->next != List_End(type->children)) {
                    fprintf(out, ", ");
                }
            } else if (!((var->symbolType == SYMBOL_PROCEDURE || var->symbolType == SYMBOL_FUNCTION) && var->type->isConst)) {
                generateAST(out, var->def, true);
                if (elem->next != List_End(type->children)) {
                    fprintf(out, ", ");
                }
            }
        }
        fprintf(out, "})");
    } break;
    }
}

static void generateDefine(FILE* out, SymbolNode* var, bool param)
{
    int defID = -1;
    if (!param) {
        if (var->def->astType != AST_UNDEF) {
            defID = generateAST(out, var->def, false);
        }
        fprintf(out, "\t");
    }
    printType(out, var->type);
    fprintf(out, " ");
    bool functionPtr = !var->type->isConst && (var->type->astType == AST_PROCEDURE || var->type->astType == AST_FUNCTION);
    if (functionPtr) {
        fprintf(out, "(*");
    }
    printPath(out, var);
    if (functionPtr) {
        fprintf(out, ") (");
        ASTNode* params = List_Get(var->type->children, 0);
        generateParamList(out, params);
        fprintf(out, ")");
    }
    if (var->type->astType == AST_C_ARRAY) {
        ASTNode* length = List_Get(var->type->children, 1);
        if (length->astType == AST_INT) {
            fprintf(out, "[%d]", (int)length->data);
        } else {
            fprintf(out, "[]");
        }
    }
    if (var->isVararg) {
        fprintf(out, ", ...");
    }
    if (!param) {
        if (var->def->astType != AST_UNDEF) {
            fprintf(out, " = _%d", defID);
        } else if (var->type->astType != AST_EXTERN) {
            fprintf(out, " = ");
            if (var->type->astType == AST_IDENT && !strcmp(var->type->data, "Type")) {
                generateDefaultValue(out, var->def);
            } else {
                generateDefaultValue(out, var->type);
            }
        }
        fprintf(out, ";\n");
    }
}

static void resetBlockName(ASTNode* node)
{
    if (node->astType == AST_BLOCK) {
        SymbolNode* symbol = node->data;
        strncpy(symbol->name, myItoa(blockUID++), 255);
    }
    for (ListElem* elem = List_Begin(node->children); elem != List_End(node->children); elem = elem->next) {
        ASTNode* child = elem->data;
        resetBlockName(child);
    }
}

static void generateDefers(FILE* out, List* defers)
{
    int defer = defers->size - 1;
    for (ListElem* elem = List_End(defers)->prev; elem->prev != NULL; elem = elem->prev) {
        ASTNode* statement = elem->data;
        resetBlockName(statement);
        fprintf(out, "\tif (defer_%d) {\n", defer);
        generateAST(out, statement, false);
        fprintf(out, "\t}\n");
        defer--;
    }
}

int printTempVar(FILE* out, ASTNode* node)
{
    fprintf(out, "\t");
    printType(out, node->type);
    SymbolNode* scope = node->scope;
    while (scope && scope->symbolType != SYMBOL_FUNCTION && scope->symbolType != SYMBOL_PROCEDURE) {
        scope = scope->parent;
    }
    if (scope) {
        fprintf(out, " _%d = ", scope->tempVars);
        return scope->tempVars++;
    } else {
        return -1;
    }
}

int printTempVarUndef(FILE* out, ASTNode* node)
{
    fprintf(out, "\t");
    printType(out, node->type);
    SymbolNode* scope = node->scope;
    while (scope && scope->symbolType != SYMBOL_FUNCTION && scope->symbolType != SYMBOL_PROCEDURE) {
        scope = scope->parent;
    }
    if (scope) {
        fprintf(out, " _%d;\n", scope->tempVars);
        return scope->tempVars++;
    } else {
        return -1;
    }
}

void printID(FILE* out, ASTNode* node, int id)
{
    fprintf(out, "\t");
    printType(out, node->type);
    fprintf(out, " _%d = ", id);
}

int newLabel(ASTNode* node)
{
    SymbolNode* scope = node->scope;
    while (scope && scope->symbolType != SYMBOL_FUNCTION && scope->symbolType != SYMBOL_PROCEDURE) {
        scope = scope->parent;
    }
    if (scope) {
        return scope->labels++;
    } else {
        return -1;
    }
}

/*
Prints out an AST to the output file. Returns the id of the temporary veriable used to store the result
*/
static int generateAST(FILE* out, ASTNode* node, bool isLValue)
{
    static List* blockStack = NULL;
    static bool printTab = false;
    if (blockStack == NULL) {
        blockStack = List_Create();
    }

    if (node == NULL)
        return;

    // Depending on the type of the node, print out node
    switch (node->astType) {
    case AST_BLOCK: {
        List_Push(blockStack, node);
        SymbolNode* symbolTree = node->data;

        for (int i = 0; i < symbolTree->defers->size; i++) {
            fprintf(out, "\tint defer_%d = 0;\n", i);
        }

        int id = -1;
        int lastID = -1;
        if (node->type->astType != AST_UNDEF && node->type->astType != AST_VOID) {
            id = printTempVarUndef(out, node);
        }

        // Print each child of the block
        for (ListElem* elem = List_Begin(node->children); elem != List_End(node->children); elem = elem->next) {
            ASTNode* statement = elem->data;
            fprintf(out, "// %s\n", AST_GetString(statement->astType));
            fprintf(out, "// %s:%d\n", getRelPath(statement->pos.filename), statement->pos.start_line);
            lastID = generateAST(out, elem->data, false);
        }
        List_Pop(blockStack);

        if (!List_IsEmpty(blockStack) && (node->containsReturn || node->containsContinue || node->containsBreak) && symbolTree->defers->size > 0) {
            fprintf(out, "\tgoto continue_%s;\n", symbolTree->name);
            if (node->containsReturn) {
                fprintf(out, "return_block_%s:;\n", symbolTree->name);
                generateDefers(out, symbolTree->defers);
                ASTNode* parentBlock = List_Peek(blockStack);
                fprintf(out, "\tgoto return_block_%s;\n", ((SymbolNode*)parentBlock->data)->name);
            }

            if (node->containsBreak) {
                fprintf(out, "break_defer_%s:;\n", symbolTree->name);
                generateDefers(out, symbolTree->defers);
                fprintf(out, "\tgoto end_%s;\n", symbolTree->name);
            }
            fprintf(out, "continue_%s:;\n", symbolTree->name);
            generateDefers(out, symbolTree->defers);
        }
        if (id != -1 && lastID != -1 && node->type->astType != AST_UNDEF) {
            fprintf(out, "\t_%d = _%d;\n", id, lastID);
        }
        return id;
    }
    case AST_IF: {
        ASTNode* condition = List_Begin(node->children)->data;
        ASTNode* body = List_Begin(node->children)->next->data;
        SymbolNode* bodySymbol = body->data;
        int conditionID = generateAST(out, condition, false);
        fprintf(out, "\tif (!_%d) goto end_%s;\n", conditionID, bodySymbol->name);
        generateAST(out, body, false);
        fprintf(out, "end_%s:;\n", bodySymbol->name);
        break;
    }
    case AST_IFELSE: {
        ASTNode* condition = List_Begin(node->children)->data;
        ASTNode* body = List_Begin(node->children)->next->data;
        ASTNode* elseBody = List_Begin(node->children)->next->next->data;
        SymbolNode* bodySymbol = body->data;
        int id = -1;
        if (node->type->astType != AST_UNDEF) {
            id = printTempVarUndef(out, node);
        }
        int conditionID = generateAST(out, condition, false);
        fprintf(out, "\tif (!_%d) goto else_%s;\n", conditionID, bodySymbol->name);
        int bodyID = generateAST(out, body, false);
        if (bodyID != -1 && id != -1) {
            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
        }
        fprintf(out, "\tgoto end_%s;\nelse_%s:;\n", bodySymbol->name, bodySymbol->name);
        int elseID = generateAST(out, elseBody, false);
        if (elseID != -1 && id != -1) {
            fprintf(out, "\t_%d = _%d;\n", id, elseID);
        }
        fprintf(out, "end_%s:;\n", bodySymbol->name);
        return id;
    }
    case AST_FOR: {
        ASTNode* pre = List_Get(node->children, 0);
        ASTNode* condition = List_Get(node->children, 1);
        ASTNode* post = List_Get(node->children, 2);
        ASTNode* body = List_Get(node->children, 3);
        SymbolNode* bodySymbol = body->data;
        int id = -1;
        if (node->type->astType != AST_UNDEF) {
            id = printTempVarUndef(out, node);
        }
        generateAST(out, pre, 0, false);
        fprintf(out, "begin_%s:;\n", bodySymbol->name);
        int conditionID = generateAST(out, condition, 0, false);
        fprintf(out, "\tif (!_%d) goto end_%s;\n", conditionID, bodySymbol->name);
        int bodyID = generateAST(out, body, false);
        if (bodyID != -1 && id != -1) {
            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
        }
        generateAST(out, post, 0, false);
        fprintf(out, "\tgoto begin_%s;\nend_%s:;\n", bodySymbol->name, bodySymbol->name);
        if (bodyID != -1 && id != -1) {
            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
        }
        return id;
    }
    case AST_SWITCH: {
        ASTNode* expr = List_Begin(node->children)->data;
        ASTNode* body = List_Get(node->children, 1);
        int id = -1;
        if (node->type->astType != AST_UNDEF) {
            id = printTempVarUndef(out, node);
        }
        fprintf(out, "\tswitch (");
        generateAST(out, expr, true);
        fprintf(out, ")\n");
        fprintf(out, "\t{");
        ListElem* elem = List_Begin(node->children)->next;
        for (; elem != List_End(node->children); elem = elem->next) {
            ASTNode* child = elem->data;
            if (child->children->size == 1) {
                fprintf(out, "\n");
                fprintf(out, "\tdefault:\n\t{\n");
                ASTNode* body = List_Get(child->children, 0);
                SymbolNode* blockSymbol = body->data;
                int bodyID = generateAST(out, body, false);
                if (bodyID != -1 && id != -1) {
                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
                }
                fprintf(out, "end_%s:;\n\tbreak;\n\t}", blockSymbol->name);
            } else {
                ListElem* elem = List_Begin(child->children);
                ASTNode* block = List_Get(child->children, child->children->size - 1);
				SymbolNode* blockSymbol = block->data;
                for (; elem != List_End(child->children)->prev; elem = elem->next) {
                    fprintf(out, "\n");
                    fprintf(out, "\tcase ");
                    generateAST(out, elem->data, true);
                    fprintf(out, ":");
                }
                fprintf(out, "\n\t{\n");
                int bodyID = generateAST(out, elem->data, false);
                if (bodyID != -1 && id != -1) {
                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
                }
                fprintf(out, "end_%s:;\n\tbreak;\n\t}", blockSymbol->name);
            }
        }
        fprintf(out, "\n\t}\n");
        return id;
    }
    case AST_RETURN: {
        ASTNode* expr = List_Get(node->children, 0);
        int retID = -1;
        if (expr->astType != AST_UNDEF && expr->astType != AST_VOID) {
            retID = generateAST(out, expr, false);
            fprintf(out, "\tretval = _%d;\n", retID);
        }
        ASTNode* parentBlock = List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->data;
        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK) {
            parentSymbol = parentSymbol->parent;
        }
        fprintf(out, "\tgoto return_block_%s;\n", parentSymbol->name);
        return retID;
    }
    case AST_BREAK: {
        ASTNode* parentBlock = List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->data;
        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
            parentSymbol = parentSymbol->parent;
        }
        if (parentSymbol->defers->size == 0) {
            fprintf(out, "\tgoto end_%s;\n", parentSymbol->name);
        } else {
            fprintf(out, "\tgoto break_defer_%s;\n", parentSymbol->name);
        }
    } break;
    case AST_CONTINUE: {
        ASTNode* parentBlock = List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->data;
        while (parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
            parentSymbol = parentSymbol->parent;
        }
        fprintf(out, "\tgoto continue_%s;\n", parentSymbol->name);
    } break;
    case AST_DEFER: {
        fprintf(out, "\tdefer_%d = 1;\n", (int)node->data);
        return -1;
    }
    case AST_DEFINE:
        SymbolNode* var = node->data;
        if (!((var->symbolType == SYMBOL_PROCEDURE || var->symbolType == SYMBOL_FUNCTION) && var->type->isConst)) {
            generateDefine(out, var, false);
        }
        break;
    case AST_NEW: {
        ASTNode* type = List_Get(node->children, 0);
        int id = -1;
        if (type->astType == AST_ARRAY) {
            ASTNode* dataDefine = List_Get(type->children, 1);
            SymbolNode* dataSymbol = dataDefine->data;
            ASTNode* dataAddrType = dataSymbol->type;
            ASTNode* dataType = List_Get(dataAddrType->children, 0);
            ASTNode* dataLength = List_Get(dataAddrType->children, 1);
            int lengthID = generateAST(out, dataLength, false);
            id = printTempVar(out, node);
            fprintf(out, "malloc(sizeof(signed int) + sizeof(");
            printType(out, dataType);
            fprintf(out, ") * _%d);\n", lengthID);
            fprintf(out, "\t_%d->length = _%d;\n", id, lengthID);
            fprintf(out, "\tfor(int i = 0; i < _%d; i++) {_%d->data[i] = ", lengthID, id);
            generateDefaultValue(out, dataType);
            fprintf(out, ";}\n");
        } else if (type->astType == AST_PARAMLIST) {
            id = printTempVar(out, node);
            fprintf(out, "calloc(sizeof(");
            printType(out, type);
            fprintf(out, "), 1);\n");
            fprintf(out, "\t*_%d = ", id);
            generateDefaultValue(out, type);
            fprintf(out, ";\n");
        } else {
            id = printTempVar(out, node);
            fprintf(out, "calloc(sizeof(");
            printType(out, type);
            fprintf(out, "), 1);\n");
        }
        return id;
    }
    case AST_FREE: {
        ASTNode* child = List_Get(node->children, 0);
        int leftID = generateAST(out, child, false);
        fprintf(out, "\tfree(_%d);\n", leftID);
        return -1;
    }
    case AST_IDENT: {
        SymbolNode* var = Symbol_Find(node->data, node->scope);
        int id = -1;
        if (!isLValue) {
            id = printTempVar(out, node);
        } else if (printTab) {
            fprintf(out, "\t");
            printTab = false;
        }

        if (var->isExtern) {
            fprintf(out, "%s", var->externName);
        } else {
            printPath(out, var);
        }

        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_NULL:
    case AST_TRUE:
    case AST_FALSE:
    case AST_INT: {
        int id = -1;
        if (!isLValue) {
            id = printTempVar(out, node);
        }
        fprintf(out, "%d", (int)node->data);
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_REAL: {
        int id = -1;
        if (!isLValue) {
            id = printTempVar(out, node);
        }
        fprintf(out, "%f", (float)((int)node->data));
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_STRING: {
        int id = -1;
        if (!isLValue) {
            id = printTempVar(out, node);
        }
        fprintf(out, "&string_%d", node->pos.start_line);
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_CHAR: {
        int id = -1;
        if (!isLValue) {
            id = printTempVar(out, node);
        }
        fprintf(out, "'%s'", node->data);
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_ARRAY_LITERAL: {
        List* ids = List_Create();
        for (ListElem* elem = List_Begin(node->children); elem != List_End(node->children); elem = elem->next) {
            int* ptr = malloc(sizeof(int));
            int elemID = generateAST(out, elem->data, false);
            *ptr = elemID;
            List_Append(ids, ptr);
        }
        int id = printTempVar(out, node);
        fprintf(out, "{%d, {", node->children->size);
        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next) {
            int* elemID = elem->data;
            fprintf(out, "_%d", *elemID);
            if (elem->next != List_End(ids)) {
                fprintf(out, ", ", *elemID);
            }
        }
        fprintf(out, "}};\n");
        List_Destroy(ids);
        return id;
    }
    case AST_INDEX: {
        ASTNode* left = List_Begin(node->children)->data;
        ASTNode* right = List_Begin(node->children)->next->data;
        ASTNode* leftType = left->type;

        int indexID = generateAST(out, right, false);
        int arrID = -1;
        if (leftType->astType != AST_ARRAY || !isLValue) { // Expensive to copy arrays, just index it directly
            arrID = generateAST(out, left, false);
        }
        int id = -1;

        if (!isLValue) {
            id = printTempVar(out, node);
        }

        if (leftType->astType == AST_ARRAY) {
            if (arrID != -1) {
                if (printTab) {
                    fprintf(out, "\t");
                    printTab = false;
                }
                fprintf(out, "_%d.data", arrID);
            } else {
                generateAST(out, left, true);
                fprintf(out, ".data");
            }
        } else if (leftType->astType == AST_ADDR && ((ASTNode*)List_Get(leftType->children, 0))->astType == AST_ARRAY) {
            if (arrID != -1) {
                if (printTab) {
                    fprintf(out, "\t");
                    printTab = false;
                }
                fprintf(out, "_%d->data", arrID);
            } else {
                generateAST(out, left, true);
                fprintf(out, "->data");
            }
        }
        fprintf(out, "[_%d]", indexID);
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_SIZEOF: {
        int id = -1;
        ASTNode* type = List_Get(node->children, 0);
        if (!isLValue) {
            id = printTempVar(out, node);
            fprintf(out, "sizeof(");
            printType(out, type);
            fprintf(out, ");\n");
        } else {
            if (printTab) {
                fprintf(out, "\t");
                printTab = false;
            }
            fprintf(out, "sizeof(");
            printType(out, type);
            fprintf(out, ");\n");
        }
        return id;
    }
    case AST_PAREN: {
        int id = -1;
        if (!isLValue) {
            int leftID = generateAST(out, node->children->head.next->data, false);
            id = printTempVar(out, node);
            fprintf(out, "_%d;\n", leftID);
        } else {
            if (printTab) {
                fprintf(out, "\t");
                printTab = false;
            }
            generateAST(out, node->children->head.next->data, true);
        }
        return id;
    }
    case AST_ARGLIST: {
        List* ids = List_Create();
        for (ListElem* elem = List_Begin(node->children); elem != List_End(node->children); elem = elem->next) {
            int* ptr = malloc(sizeof(int));
            int elemID = generateAST(out, elem->data, false);
            *ptr = elemID;
            List_Append(ids, ptr);
        }
        int id = printTempVar(out, node);
        fprintf(out, "{");
        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next) {
            int* elemID = elem->data;
            fprintf(out, "_%d", *elemID);
            if (elem->next != List_End(ids)) {
                fprintf(out, ", ");
            }
        }
        fprintf(out, "};\n");
        List_Destroy(ids);
        return id;
    }
    case AST_DOT: {
        int id = -1;
        SymbolNode* dotSymbol = node->data;
        if (dotSymbol && dotSymbol->isExtern) {
            if (!isLValue) {
                id = printTempVar(out, node);
            } else if (printTab) {
                fprintf(out, "\t");
                printTab = false;
            }
            fprintf(out, "%s", dotSymbol->externName);
        } else {
            ASTNode* left = List_Begin(node->children)->data;
            ASTNode* right = List_Begin(node->children)->next->data;
            ASTNode* leftType = left->type;
            if (dotSymbol && leftType->astType == AST_IDENT && (!strcmp(leftType->data, "Module") || !strcmp(leftType->data, "Package") || !strcmp(leftType->data, "Enum"))) {
                if (!isLValue) {
                    id = printTempVar(out, node);
                } else if (printTab) {
                    fprintf(out, "\t");
                    printTab = false;
                }
                printPath(out, dotSymbol);
            } else if (dotSymbol && dotSymbol->type->isConst && (dotSymbol->type->astType == AST_PROCEDURE || dotSymbol->type->astType == AST_FUNCTION)) {
                if (!isLValue) {
                    id = printTempVar(out, node);
                } else if (printTab) {
                    fprintf(out, "\t");
                    printTab = false;
                }
                printPath(out, dotSymbol);
            } else if (leftType->astType == AST_ADDR) {
                if (!isLValue) {
                    int leftID = generateAST(out, left, false);
                    id = printTempVar(out, node);
                    fprintf(out, "_%d->%s", leftID, right->data);
                } else {
                    if (printTab) {
                        fprintf(out, "\t");
                        printTab = false;
                    }
                    generateAST(out, left, true);
                    fprintf(out, "->%s", right->data);
                }
            } else {
                if (!isLValue) {
                    int leftID = generateAST(out, left, false);
                    id = printTempVar(out, node);
                    fprintf(out, "_%d.%s", leftID, right->data);
                } else {
                    if (printTab) {
                        fprintf(out, "\t");
                        printTab = false;
                    }
                    generateAST(out, left, true);
                    fprintf(out, ".%s", right->data);
                }
            }
        }
        if (!isLValue) {
            fprintf(out, ";\n");
        }
        return id;
    }
    case AST_AND: {
        ASTNode* left = List_Begin(node->children)->data;
        ASTNode* right = List_Begin(node->children)->next->data;

        int overLabel = newLabel(node);

        int id = printTempVar(out, node);
        fprintf(out, "0;\n");
        int leftID = generateAST(out, left, false);

        fprintf(out, "\tif (!_%d) goto over_%d;\n", leftID, overLabel);
        int rightID = generateAST(out, right, false);
        fprintf(out, "\t_%d = _%d;\n", id, rightID);
        fprintf(out, "over_%d:;\n", overLabel);
        return id;
    }
    case AST_OR: {
        ASTNode* left = List_Begin(node->children)->data;
        ASTNode* right = List_Begin(node->children)->next->data;

        int overLabel = newLabel(node);

        int id = printTempVar(out, node);
        fprintf(out, "1;\n");
        int leftID = generateAST(out, left, false);

        fprintf(out, "\tif (_%d) goto over_%d;\n", leftID, overLabel);
        int rightID = generateAST(out, right, false);
        fprintf(out, "\t_%d = _%d;\n", id, rightID);
        fprintf(out, "over_%d:;\n", overLabel);
        return id;
    }
    case AST_BIT_OR:
    case AST_BIT_XOR:
    case AST_BIT_AND:
    case AST_LSHIFT:
    case AST_RSHIFT:
    case AST_EQ:
    case AST_NEQ:
    case AST_GTR:
    case AST_LSR:
    case AST_GTE:
    case AST_LTE:
    case AST_ADD:
    case AST_SUBTRACT:
    case AST_MULTIPLY:
    case AST_DIVIDE:
    case AST_MODULUS: {
        int leftID = generateAST(out, node->children->head.next->data, false);
        int rightID = generateAST(out, node->children->head.next->next->data, false);
        int id = printTempVar(out, node);
        fprintf(out, "_%d %s _%d;\n", leftID, node->data, rightID);
        return id;
    }
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
    case AST_RSHIFT_ASSIGN: {
        int rightID = generateAST(out, node->children->head.next->next->data, false);
        printTab = true;
        generateAST(out, node->children->head.next->data, true);
        fprintf(out, " %s _%d;\n", node->data, rightID);
        return rightID;
    }
    case AST_NEG:
    case AST_BIT_NOT:
    case AST_NOT:
    case AST_ADDROF:
    case AST_DEREF: {
        int id = -1;
        if (!isLValue) {
            int leftID = generateAST(out, node->children->head.next->data, false);
            id = printTempVar(out, node);
            fprintf(out, "%s_%d;\n", node->data, leftID);
        } else {
            if (printTab) {
                fprintf(out, "\t");
                printTab = false;
            }
            fprintf(out, "%s", node->data);
            generateAST(out, node->children->head.next->data, true);
        }
        return id;
    }
    case AST_CAST: {
        int id = -1;
        if (!isLValue) {
            int leftID = generateAST(out, List_Get(node->children, 0), false);
            ASTNode* innerType = List_Get(node->children, 1);
            if (innerType->astType != AST_PARAMLIST && innerType->astType != AST_ARRAY) {
                id = printTempVar(out, node);
                fprintf(out, "(");
                printType(out, innerType);
                fprintf(out, ")");
                fprintf(out, "_%d;\n", leftID);
            } else {
                return leftID;
            }
        } else {
            if (printTab) {
                fprintf(out, "\t");
                printTab = false;
            }
            fprintf(out, "(");
            printType(out, List_Get(node->children, 1));
            fprintf(out, ")");
            generateAST(out, List_Get(node->children, 0), true);
        }
        return id;
    }
    case AST_CALL: {
        ASTNode* arglist = List_Get(node->children, 1);
        List* ids = List_Create();
        for (ListElem* elem = List_Begin(arglist->children); elem != List_End(arglist->children); elem = elem->next) {
            int* ptr = malloc(sizeof(int));
            ASTNode* child = elem->data;
            if (child->astType != AST_IDENT) {
                int elemID = generateAST(out, child, false);
                *ptr = elemID;
            } else {
                *ptr = -1;
            }
            List_Append(ids, ptr);
        }

        int id = -1;
        if (node->type->astType != AST_VOID) {
            id = printTempVar(out, node);
        } else {
            fprintf(out, "\t");
        }
        generateAST(out, List_Begin(node->children)->data, true);
        fprintf(out, "(");
        ListElem* elem2 = List_Begin(arglist->children);
        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next, elem2 = elem2->next) {
            int* elemID = elem->data;
            if (*elemID != -1) {
                fprintf(out, "_%d", *elemID);
            } else {
                ASTNode* child = elem2->data;
                generateAST(out, child, true);
            }
            if (elem->next != List_End(ids)) {
                fprintf(out, ", ");
            }
        }
        fprintf(out, ");\n");
        List_Destroy(ids);
        return id;
    }
    }
}

/*
Prints out the parameter list for a procedure
*/
static void generateParamList(FILE* out, ASTNode* parameters)
{
    ListElem* paramElem = List_Begin(parameters->children);
    // For each parameter in the procedure's parameter list, print it out
    for (; paramElem != List_End(parameters->children); paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* var = define->data;
        generateDefine(out, var, true);
        if (paramElem != List_End(parameters->children)->prev) {
            fprintf(out, ", ");
        }
    }
}

static void generateIncludes(FILE* out, Map* includes)
{
    fprintf(out, "/* Includes used by the program */\n");
    List* keys = includes->keyList;
    ListElem* e = List_Begin(keys);
    for (; e != List_End(keys); e = e->next) {
        char* include = e->data;
        if (include[0] == '<') {
            fprintf(out, "#include %s\n", include);
        } else {
            fprintf(out, "#include \"%s\"\n", include);
        }
    }
    fprintf(out, "\n");
}

static void generateStruct(FILE* out, DGraph* graphNode)
{
    if (graphNode->visited) {
        return;
    } else {
        graphNode->visited = true;
    }

    // Print out all dependencies
    ListElem* elem = List_Begin(graphNode->dependencies);
    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
        DGraph* child = elem->data;
        generateStruct(out, child);
    }

    ASTNode* _struct = graphNode->structDef;
    char* structOrdStr = myItoa(graphNode->ordinal + 1);
    fprintf(out, "struct struct_%s {\n", structOrdStr);

    ListElem* paramElem = List_Begin(_struct->children);
    // For each parameter in the procedure's parameter list, print it out
    for (; paramElem != List_End(_struct->children); paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* var = define->data;
        if (!((var->symbolType == SYMBOL_PROCEDURE || var->symbolType == SYMBOL_FUNCTION) && var->type->isConst)) {
            fprintf(out, "\t");
            generateDefine(out, var, true);
            fprintf(out, ";\n");
        }
    }
    fprintf(out, "};\n\n");
}

void generateStructDefinitions(FILE* out, List* depenGraph)
{
    fprintf(out, "/* Struct definitions */\n");
    ListElem* elem = List_Begin(depenGraph);
    for (; elem != List_End(depenGraph); elem = elem->next) {
        struct graph* graphNode = elem->data;
        generateStruct(out, graphNode);
    }
}

void generateVerbatims(FILE* out, List* verbatims)
{
    fprintf(out, "/* Verbatim code */\n");
    ListElem* elem = List_Begin(verbatims);
    for (; elem != List_End(verbatims); elem = elem->next) {
        fprintf(out, (char*)elem->data);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

void generateString(FILE* out, char* string)
{
    int backslashes = 0;
    for (int j = 0; j < strlen(string); j++) {
        if (string[j] == '\\') {
            backslashes++;
        }
    }
    fprintf(out, "{%d, {", strlen(string) - backslashes);
    for (int j = 0; j < strlen(string); j++) {
        char c = string[j];
        if (c == '\\') {
            fprintf(out, "'%c", c);
            j++;
            fprintf(out, "%c', ", string[j]);
        } else {
            fprintf(out, "'%c', ", c);
        }
    }
    fprintf(out, "'\\0'}};\n");
}

void generateForwardStrings(FILE* out, List* strings)
{
    fprintf(out, "/* Forward string declarations */\n");
    ListElem* elem = List_Begin(strings);
    int i = -1;
    ASTNode* stringRawType = List_Get(STRING_TYPE->children, 0);
    for (; elem != List_End(strings); elem = elem->next) {
        i++;
        ASTNode* node = elem->data;
        if (!node->scope->isReachable) {
            continue;
        }
        printType(out, stringRawType);
        fprintf(out, " string_%d;\n", i);
    }
    fprintf(out, "\n");
}

void generateStrings(FILE* out, List* strings)
{
    fprintf(out, "/* String definitions */\n");
    ListElem* elem = List_Begin(strings);
    int i = -1;
    ASTNode* stringRawType = List_Get(STRING_TYPE->children, 0);
    for (; elem != List_End(strings); elem = elem->next) {
        i++;
        ASTNode* node = elem->data;
        if (!node->scope->isReachable) {
            continue;
        }
        printType(out, stringRawType);
        fprintf(out, " string_%d = ", i);
        generateString(out, node->data);
    }
    fprintf(out, "\n");
}

void generateForwardFunctions(FILE* out, List* functions)
{
    fprintf(out, "/* Forward function and procedure declarations */\n");
    for (ListElem* elem = List_Begin(functions); elem != List_End(functions); elem = elem->next) {
        SymbolNode* symbol = elem->data;
        if (!symbol->isReachable) {
            continue;
        }

        ASTNode* functionType = symbol->type;
        ASTNode* params = List_Get(functionType->children, 0);
        ASTNode* returns = List_Get(functionType->children, 1);
        if (returns->children->size <= 1) {
            printType(out, functionType);
        } else {
            printType(out, returns);
        }
        fprintf(out, " ");
        printPath(out, symbol);
        fprintf(out, "(");
        generateParamList(out, params);
        fprintf(out, ");\n");
    }
    fprintf(out, "\n");
}

void generateForwardGlobals(FILE* out, List* globals)
{
    fprintf(out, "/* Forward global declarations */\n");
    for (ListElem* elem = List_Begin(globals); elem != List_End(globals); elem = elem->next) {
        SymbolNode* symbol = elem->data;
        if (!symbol->isReachable) {
            continue;
        }

        printType(out, symbol->type);
        fprintf(out, " ");
        printPath(out, symbol);
        fprintf(out, ";\n");
    }
    fprintf(out, "\n");
}

void generateEnums(FILE* out, List* enums)
{
    fprintf(out, "/* Enums */\n");
    for (ListElem* elem = List_Begin(enums); elem != List_End(enums); elem = elem->next) {
        SymbolNode* symbol = elem->data;
        if (!symbol->isReachable) {
            continue;
        }

        int i = 0;
        ASTNode* root = symbol->def;
        for (ListElem* elem = List_Begin(root->children); elem != List_End(root->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* var = define->data;
            fprintf(out, "#define ");
            printPath(out, symbol);
            fprintf(out, "_%s %d", var->name, i);
            i++;
            fprintf(out, "\n");
        }

        printType(out, STRING_TYPE);
        fprintf(out, " ");
        printPath(out, symbol);
        fprintf(out, "_toString(int x);\n");

        fprintf(out, "int ");
        printPath(out, symbol);
        fprintf(out, "_length;\n");
    }
    fprintf(out, "\n");
}

static int getPathLength(SymbolNode* symbol)
{
    if (symbol->parent->parent != NULL && !symbol->isExtern) {
        int length = 0;
        if (symbol->parent->symbolType != SYMBOL_PROCEDURE && symbol->parent->symbolType != SYMBOL_FUNCTION) {
            length += getPathLength(symbol->parent);
        }
        return length + strlen(symbol->name) + 1;
    } else {
        return strlen(symbol->name);
    }
}

void generateEnumFunctions(FILE* out, List* enums)
{
    fprintf(out, "/* Enum definitions */\n");
    ASTNode* stringRawType = List_Get(STRING_TYPE->children, 0);
    for (ListElem* elem = List_Begin(enums); elem != List_End(enums); elem = elem->next) {
        SymbolNode* symbol = elem->data;
        if (!symbol->isReachable) {
            continue;
        }

        ASTNode* root = symbol->def;
        for (ListElem* elem = List_Begin(root->children); elem != List_End(root->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* var = define->data;
            printType(out, stringRawType);
            fprintf(out, " ");
            printPath(out, var);
            fprintf(out, "_str = ");
            char nameBuffer[255];
            sprintPath(nameBuffer, var);
            generateString(out, nameBuffer);
        }

        printType(out, STRING_TYPE);
        fprintf(out, " ");
        printPath(out, symbol);
        fprintf(out, "_toString(unsigned int x)\n{\n\tswitch(x)\n\t{\n");
        for (ListElem* elem = List_Begin(root->children); elem != List_End(root->children); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* var = define->data;
            fprintf(out, "\tcase ");
            printPath(out, var);
            fprintf(out, ":\n\t\treturn &");
            printPath(out, var);
            fprintf(out, "_str;\n");
        }
        fprintf(out, "\t}\n}\n");

        fprintf(out, "unsigned int ");
        printPath(out, symbol);
        fprintf(out, "_length = %d;\n", root->children->size);
    }
    fprintf(out, "\n");
}

void generateGlobalDefinitions(FILE* out, List* globals)
{
    global = true;
    for (ListElem* elem = List_Begin(globals); elem != List_End(globals); elem = elem->next) {
        SymbolNode* var = elem->data;
        if (!var->isReachable) {
            continue;
        }
        fprintf(out, "\t");
        generateDefine(out, var, false);
        fprintf(out, ";\n");
    }
}

void generateFunctionDefinitions(FILE* out, List* functions)
{
    fprintf(out, "/* Function and procedure definitions */\n");
    global = false;
    for (ListElem* elem = List_Begin(functions); elem != List_End(functions); elem = elem->next) {
        SymbolNode* symbol = elem->data;
        if (!symbol->isReachable) {
            continue;
        }

        ASTNode* functionType = symbol->type;
        ASTNode* params = List_Get(functionType->children, 0);
        ASTNode* returns = List_Get(functionType->children, 1);
        if (returns->children->size <= 1) {
            printType(out, functionType);
        } else {
            printType(out, returns);
        }
        fprintf(out, " ");
        printPath(out, symbol);
        fprintf(out, "(");
        generateParamList(out, params);
        fprintf(out, ")\n{\n");
        if (returns->astType != AST_VOID) {
            fprintf(out, "\t");
            printType(out, returns);
            fprintf(out, " retval;\n");
        }
        int blockID = generateAST(out, symbol->def, false);
        SymbolNode* block = Map_Get(symbol->def->scope->children, List_Get(symbol->def->scope->children->keyList, symbol->def->scope->children->size - 1));
        if (returns->astType != AST_VOID && blockID != -1) {
            fprintf(out, "\tretval = _%d;\n", blockID);
        }
        fprintf(out, "return_block_%s:;\n", block->name);
        generateDefers(out, block->defers, 0);
        if (returns->astType != AST_VOID) {
            fprintf(out, "\treturn retval;\n");
        }
        fprintf(out, "}\n\n");
    }
}

void generateMainFunction(FILE* out, SymbolNode* mainFunction)
{
    /*
	int main(int argc, char** argv)
	{
		struct struct_5* args = calloc(sizeof(struct struct_5) + sizeof(struct struct_1*) * argc, 1);
		args->length = argc;
		for (int i = 0; i < argc; i++) {
			args->data[i] = calloc(sizeof(struct struct_1) + sizeof(char) * strlen(argv[i]) + 1, 1);
			args->data[i]->length = strlen(argv[i] + 1);
			memcpy(&args->data[i]->data, argv[i], strlen(argv[i]) + 1);
		}
		int retval = test_testModule_main(*args);
		free(args);
		return retval;
	}
	*/
    fprintf(out, "\int main(int argc, char** argv)\n");

    fprintf(out, "{\n");

    generateGlobalDefinitions(out, program.globalVars);

    fprintf(out, "\t");
    printType(out, STRING_ARR_TYPE);
    fprintf(out, " args = calloc(sizeof(");
    printType(out, STRING_ARR_TYPE);
    fprintf(out, ") + sizeof(");
    printType(out, STRING_TYPE);
    fprintf(out, ") * argc, 1);\n");

    fprintf(out, "\targs->length = argc;\n");

    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");

    fprintf(out, "\t\targs->data[i] = calloc(sizeof(");
    printType(out, STRING_TYPE);
    fprintf(out, ") + sizeof(char) * strlen(argv[i]) + 1, 1);\n");

    fprintf(out, "\t\targs->data[i]->length = strlen(argv[i] + 1);\n");

    fprintf(out, "\t\tmemcpy(&args->data[i]->data, argv[i], strlen(argv[i]) + 1);\n");

    fprintf(out, "\t}\n");

    fprintf(out, "\tint retval = ");
    printPath(out, mainFunction);
    fprintf(out, "(args);\n");

    fprintf(out, "\tfree(args);\n");

    fprintf(out, "\treturn retval;\n");

    fprintf(out, "}\n");
}

/*
Prints out a program to an output file.
*/
void Generator_Generate(Program _program, FILE* out)
{
    srand(time(0));
    int randID = rand();
    fprintf(out, "/* Code generated using Orange Translator http://josephs-projects.com */\n\n");

    program = _program;

    generateIncludes(out, program.includes);
    generateStructDefinitions(out, program.dependencyGraph);
    generateVerbatims(out, program.verbatims);
    generateForwardStrings(out, program.strings);
    generateEnums(out, program.enums);
    generateForwardGlobals(out, program.globalVars);
    generateForwardFunctions(out, program.functions);
    fprintf(out, "#ifndef ORANGE_PROGRAM_%s\n#define ORANGE_PROGRAM_%s\n\n", myItoa(randID), myItoa(randID));
    generateStrings(out, program.strings);
    generateEnumFunctions(out, program.enums);
    generateFunctionDefinitions(out, program.functions);
    generateMainFunction(out, program.mainFunction);
    fprintf(out, "#endif\n");
}