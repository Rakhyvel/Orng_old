///*
//This file deals with generating the output C file from the AST and Symbol trees
//parsed from the input file.
//*/
//
//#define _CRT_SECURE_NO_WARNINGS
//#include "generator.h"
//#include "./main.h"
//#include "./parse.h"
//#include "./position.h"
//#include "./validator.h"
//#include <stdlib.h>
//#include <string.h>
//
////Program program;
//
//static int generateAST(FILE* out, ASTNode* node);
//static void generateParamList(FILE* out, ASTNode* parameters);
//
//static bool global = false;
//
///*
//Given a symbol node representing a symbol, prints the path from the root of the
//symbol tree to the given node out to the given file.
//*/
//static void printPath(FILE* out, SymbolNode* symbol)
//{
//    // Local variables
//    if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && symbol->parent->symbolType == SYMBOL_BLOCK) {
//        fprintf(out, "_%s_%s", symbol->parent->name, symbol->name);
//    }
//    // Parameters
//    else if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && symbol->parent->symbolType == SYMBOL_FUNCTION) {
//        fprintf(out, "_%s", symbol->name);
//    }
//    // Everything else
//    else if (symbol->parent && (symbol->parent->symbolType != SYMBOL_TYPE || symbol->symbolType == SYMBOL_FUNCTION) && symbol->parent->parent && !symbol->isExtern) {
//        if (symbol->parent->symbolType != SYMBOL_VARIABLE) { // Done so that fields in anon structs collected by variable types don't have their variable names appended
//            // Done so that inner functions print correctly (i think)
//            if (symbol->symbolType == SYMBOL_VARIABLE || (symbol->parent->parent->symbolType != SYMBOL_BLOCK && symbol->parent->symbolType != SYMBOL_FUNCTION)) {
//                printPath(out, symbol->parent);
//            }
//            fprintf(out, "_%s", symbol->name);
//        } else {
//            fprintf(out, "%s", symbol->name);
//        }
//    } else if (symbol->isExtern) {
//        fprintf(out, "%s", symbol->externName);
//    } else {
//        fprintf(out, "%s", symbol->name);
//    }
//}
//
//// Used for enum printing
//static int sprintPath(char* str, SymbolNode* symbol)
//{
//    char* origStr = str;
//    if (symbol->parent && symbol->parent->symbolType != SYMBOL_TYPE && symbol->parent->parent && !symbol->isExtern) {
//        if (symbol->parent->parent->symbolType != SYMBOL_BLOCK && symbol->parent->symbolType != SYMBOL_FUNCTION) {
//            str += sprintPath(str, symbol->parent);
//        }
//        str += sprintf(str, "_%s", symbol->name);
//    } else if (symbol->isExtern) {
//        str += sprintf(str, "%s", symbol->externName);
//    } else {
//        str += sprintf(str, "%s", symbol->name);
//    }
//    return str - origStr;
//}
//
//static void printStructOrd(FILE* out, ASTNode* type)
//{
//    struct listElem* elem = List_Begin(program.dependencyGraph);
//    int i = 1;
//    bool found = false;
//    for (; !found && elem != List_End(program.dependencyGraph); elem = List_Next(elem), i++) {
//        DGraph* node = (DGraph*)elem->data;
//        ASTNode* child = node->structDef;
//        if (typesAreEquivalent(child, type)) {
//            fprintf(out, "struct_%s", myItoa(i));
//            found = true;
//        }
//    }
//}
//
//static void printType(FILE* out, ASTNode* type)
//{
//    switch (type->astType) {
//    case AST_IDENT:
//        if (!strcmp(type->ident.data, "Int8") || !strcmp(type->ident.data, "Char")) {
//            fprintf(out, "%s", "int8_t");
//        } else if (!strcmp(type->ident.data, "Int16")) {
//            fprintf(out, "%s", "int16_t");
//        } else if (!strcmp(type->ident.data, "Int32")) {
//            fprintf(out, "%s", "int32_t");
//        } else if (!strcmp(type->ident.data, "Int64") || !strcmp(type->ident.data, "Int")) {
//            fprintf(out, "%s", "int64_t");
//        } else if (!strcmp(type->ident.data, "Bool")) {
//            fprintf(out, "%s", "bool");
//        } else if (!strcmp(type->ident.data, "Real32") || !strcmp(type->ident.data, "Real")) {
//            fprintf(out, "%s", "float");
//        } else if (!strcmp(type->ident.data, "Real64")) {
//            fprintf(out, "%s", "double");
//        } else if (!strcmp(type->ident.data, "String")) {
//            printType(out, STRING_TYPE);
//        } else {
//            fprintf(out, "%s", type->ident.data);
//        }
//        break;
//    case AST_DOT:
//        SymbolNode* var = type->dot.symbol;
//        if (var->isExtern) {
//            fprintf(out, "%s", var->externName);
//        } else {
//            printType(out, type->type);
//        }
//        break;
//    case AST_ADDR:
//        printType(out, type->unop.expr);
//        fprintf(out, "*");
//        break;
//    case AST_ARRAY:
//    case AST_PARAMLIST:
//    case AST_UNIONSET: {
//        fprintf(out, "struct ");
//        printStructOrd(out, type);
//    } break;
//    case AST_VOID: {
//        fprintf(out, "void");
//        break;
//    }
//    case AST_FUNCTION:
//        // The second child in a function is the return type
//        ASTNode* ret = type->function.codomainType;
//        printType(out, ret);
//        break;
//    case AST_EXTERN: {
//        SymbolNode* var = type->_extern.symbol;
//        fprintf(out, "%s", var->externName);
//        break;
//    }
//    default: {
//        fprintf(out, "Not a type: %s", AST_GetString(type->astType));
//    }
//    }
//}
//
//static void generateDefaultValue(FILE* out, ASTNode* type)
//{
//    switch (type->astType) {
//    default:
//        fprintf(out, "0");
//        break;
//    case AST_ARRAY: {
//        ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
//        SymbolNode* lengthSymbol = lengthDefine->define.symbol;
//        ASTNode* lengthCode = lengthSymbol->def;
//        ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
//        SymbolNode* dataSymbol = dataDefine->define.symbol;
//        ASTNode* dataType = dataSymbol->type;
//        fprintf(out, "((");
//        printType(out, type);
//        if (lengthCode->astType == AST_INT && lengthCode->_int.data != 0) {
//            fprintf(out, "){%d, (", (int)lengthCode->_int.data);
//            printType(out, dataType);
//            fprintf(out, "[]){");
//            for (int i = 0; i < (int)lengthCode->_int.data; i++) {
//                generateDefaultValue(out, dataType);
//                if (i + 1 < lengthCode->_int.data) {
//                    fprintf(out, ", ");
//                }
//            }
//            fprintf(out, "}})");
//        } else {
//            fprintf(out, "){0, 0})");
//        }
//    } break;
//    case AST_PARAMLIST: {
//        fprintf(out, "((");
//        printType(out, type);
//        fprintf(out, "){");
//        for (ListElem* elem = List_Begin(type->paramlist.defines); elem != List_End(type->paramlist.defines); elem = elem->next) {
//            ASTNode* define = elem->data;
//            SymbolNode* var = define->define.symbol;
//            if (var->def->astType == AST_UNDEF) {
//                generateDefaultValue(out, var->type);
//                if (elem->next != List_End(type->paramlist.defines)) {
//                    fprintf(out, ", ");
//                }
//            } else if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
//                generateAST(out, var->def, true);
//                if (elem->next != List_End(type->paramlist.defines)) {
//                    fprintf(out, ", ");
//                }
//            }
//        }
//        fprintf(out, "})");
//    } break;
//    case AST_UNIONSET: {
//        fprintf(out, "((");
//        printType(out, type);
//        fprintf(out, "){0");
//        ASTNode* firstDefine = List_Get(type->unionset.defines, 0);
//        SymbolNode* firstVar = firstDefine->define.symbol;
//        if (firstVar->type->astType == AST_VOID) {
//            fprintf(out, "})");
//        } else {
//            fprintf(out, ", ");
//            generateDefaultValue(out, firstVar->type);
//            fprintf(out, "})");
//        }
//    }
//    }
//}
//
//static void generateDefine(FILE* out, SymbolNode* var, bool param)
//{
//    int defID = -1;
//    if (!param) {
//        if (var->def->astType != AST_UNDEF) {
//            defID = generateAST(out, var->def, false);
//        }
//        fprintf(out, "\t");
//    }
//    printType(out, var->type);
//    fprintf(out, " /* %d */ ", var->typeSize);
//    bool functionPtr = !var->type->isConst && var->type->astType == AST_FUNCTION;
//    if (functionPtr) {
//        fprintf(out, "(*");
//    }
//    printPath(out, var);
//    if (functionPtr) {
//        fprintf(out, ") (");
//        ASTNode* params = var->type->function.domainType;
//        generateParamList(out, params);
//        fprintf(out, ")");
//    }
//    if (var->isVararg) {
//        fprintf(out, ", ...");
//    }
//    if (!param) {
//        if (var->def->astType != AST_UNDEF) {
//            fprintf(out, " = _%d", defID);
//        } else if (var->type->astType != AST_EXTERN) {
//            fprintf(out, " = ");
//            if (var->type->astType == AST_IDENT && !strcmp(var->type->ident.data, "Type")) {
//                generateDefaultValue(out, var->def);
//            } else {
//                generateDefaultValue(out, var->type);
//            }
//        }
//        fprintf(out, ";\n");
//    }
//}
//
//static void resetBlockName(ASTNode* node)
//{
//    /*
//    if (node->astType == AST_BLOCK) {
//        SymbolNode* symbol = node->block.symbol;
//        strncpy(symbol->name, myItoa(blockUID++), 255); // TODO: better implementation of this so that defers don't collide
//    }
//    // TODO: traverse AST
//    for (ListElem* elem = List_Begin(node->children); elem != List_End(node->children); elem = elem->next) {
//        ASTNode* child = elem->data;
//        resetBlockName(child);
//    }
//	*/
//}
//
//static void generateDefers(FILE* out, List* defers)
//{
//    int defer = defers->size - 1;
//    for (ListElem* elem = List_End(defers)->prev; elem->prev != NULL; elem = elem->prev) {
//        ASTNode* statement = elem->data;
//        resetBlockName(statement);
//        fprintf(out, "\tif (defer_%d) {\n", defer);
//        generateAST(out, statement, false);
//        fprintf(out, "\t}\n");
//        defer--;
//    }
//}
//
//int printTempVar(FILE* out, ASTNode* node)
//{
//    fprintf(out, "\t");
//    printType(out, node->type);
//    SymbolNode* scope = node->scope;
//    while (scope && scope->symbolType != SYMBOL_FUNCTION) {
//        scope = scope->parent;
//    }
//    if (scope) {
//        fprintf(out, " _%d = ", scope->tempVars);
//        return scope->tempVars++;
//    } else {
//        printf("scope is null\n");
//        return -1;
//    }
//}
//
//int printTempVarUndef(FILE* out, ASTNode* node)
//{
//    fprintf(out, "\t");
//    printType(out, node->type);
//    SymbolNode* scope = node->scope;
//    while (scope && scope->symbolType != SYMBOL_FUNCTION) {
//        scope = scope->parent;
//    }
//    if (scope) {
//        fprintf(out, " _%d;\n", scope->tempVars);
//        return scope->tempVars++;
//    } else {
//        return -1;
//    }
//}
//
//int printTempVarType(FILE* out, ASTNode* node, ASTNode* type)
//{
//    fprintf(out, "\t");
//    printType(out, type);
//    SymbolNode* scope = node->scope;
//    while (scope && scope->symbolType != SYMBOL_FUNCTION) {
//        scope = scope->parent;
//    }
//    if (scope) {
//        fprintf(out, " _%d = ", scope->tempVars);
//        return scope->tempVars++;
//    } else {
//        fprintf(out, "wtf scope was null\n");
//        return -1;
//    }
//}
//
//void printID(FILE* out, ASTNode* node, int id)
//{
//    fprintf(out, "\t");
//    printType(out, node->type);
//    fprintf(out, " _%d = ", id);
//}
//
//int newLabel(ASTNode* node)
//{
//    SymbolNode* scope = node->scope;
//    while (scope && scope->symbolType != SYMBOL_FUNCTION) {
//        scope = scope->parent;
//    }
//    if (scope) {
//        return scope->labels++;
//    } else {
//        return -1;
//    }
//}
//
///*
//Prints out an AST to the output file. Returns the id of the temporary veriable used to store the result
//*/
//static int generateAST(FILE* out, ASTNode* node, bool isLValue)
//{
//    static List* blockStack = NULL;
//    static bool printTab = false;
//    if (blockStack == NULL) {
//        blockStack = List_Create();
//    }
//
//    if (node == NULL)
//        return;
//
//    // Depending on the type of the node, print out node
//    switch (node->astType) {
//    case AST_BLOCK: {
//        List_Push(blockStack, node);
//        SymbolNode* symbolTree = node->block.symbol;
//
//        for (int i = 0; i < symbolTree->defers->size; i++) {
//            fprintf(out, "\tint defer_%d = 0;\n", i);
//        }
//
//        int id = -1;
//        int lastID = -1;
//        if (node->type->astType != AST_UNDEF && node->type->astType != AST_VOID) {
//            id = printTempVarUndef(out, node);
//        }
//
//        // Print each child of the block
//        for (ListElem* elem = List_Begin(node->block.children); elem != List_End(node->block.children); elem = elem->next) {
//            ASTNode* statement = elem->data;
//            if (statement) {
//                fprintf(out, "// %s\n", AST_GetString(statement->astType));
//                fprintf(out, "// %s:%d\n", getRelPath(statement->pos.filename), statement->pos.start_line);
//                lastID = generateAST(out, elem->data, false);
//            }
//        }
//        List_Pop(blockStack);
//
//        if (!List_IsEmpty(blockStack) && (node->containsReturn || node->containsContinue || node->containsBreak) && symbolTree->defers->size > 0) {
//            fprintf(out, "\tgoto continue_%s;\n", symbolTree->name);
//            if (node->containsReturn) {
//                fprintf(out, "return_block_%s:;\n", symbolTree->name);
//                generateDefers(out, symbolTree->defers);
//                ASTNode* parentBlock = List_Peek(blockStack);
//                fprintf(out, "\tgoto return_block_%s;\n", parentBlock->block.symbol->name);
//            }
//
//            if (node->containsBreak) {
//                fprintf(out, "break_defer_%s:;\n", symbolTree->name);
//                generateDefers(out, symbolTree->defers);
//                fprintf(out, "\tgoto end_%s;\n", symbolTree->name);
//            }
//            fprintf(out, "continue_%s:;\n", symbolTree->name);
//            generateDefers(out, symbolTree->defers);
//        }
//        if (id != -1 && lastID != -1 && node->type->astType != AST_UNDEF) {
//            fprintf(out, "\t_%d = _%d;\n", id, lastID);
//        }
//        return id;
//    }
//    case AST_IF: {
//        ASTNode* condition = node->_if.condition;
//        ASTNode* body = node->_if.bodyBlock;
//        ASTNode* elseBody = node->_if.elseBlock;
//        SymbolNode* bodySymbol = body->block.symbol;
//        int id = -1;
//        if (node->type->astType != AST_UNDEF) {
//            id = printTempVarUndef(out, node);
//        }
//        int conditionID = generateAST(out, condition, false);
//        fprintf(out, "\tif (!_%d) goto else_%s;\n", conditionID, bodySymbol->name);
//        int bodyID = generateAST(out, body, false);
//        if (bodyID != -1 && id != -1) {
//            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//        }
//        fprintf(out, "\tgoto end_%s;\nelse_%s:;\n", bodySymbol->name, bodySymbol->name);
//        int elseID = generateAST(out, elseBody, false);
//        if (elseID != -1 && id != -1) {
//            fprintf(out, "\t_%d = _%d;\n", id, elseID);
//        }
//        fprintf(out, "end_%s:;\n", bodySymbol->name);
//        return id;
//    }
//    case AST_FOR: {
//        ASTNode* pre = node->_for.pre;
//        ASTNode* condition = node->_for.condition;
//        ASTNode* post = node->_for.post;
//        ASTNode* body = node->_for.bodyBlock;
//        SymbolNode* bodySymbol = body->block.symbol;
//        int id = -1;
//        if (node->type->astType != AST_UNDEF) {
//            id = printTempVarUndef(out, node);
//        }
//        generateAST(out, pre, 0, false);
//        fprintf(out, "begin_%s:;\n", bodySymbol->name);
//        int conditionID = generateAST(out, condition, 0, false);
//        fprintf(out, "\tif (!_%d) goto end_%s;\n", conditionID, bodySymbol->name);
//        int bodyID = generateAST(out, body, false);
//        if (bodyID != -1 && id != -1) {
//            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//        }
//        fprintf(out, "\t// for post\n");
//        generateAST(out, post, 0, false);
//        fprintf(out, "\tgoto begin_%s;\n", bodySymbol->name);
//        if (bodyID != -1 && id != -1) {
//            fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//        }
//        fprintf(out, "end_%s:;\n", bodySymbol->name);
//        return id;
//    }
//    case AST_CASE: {
//        ASTNode* expr = node->_case.expr;
//        int id = -1;
//        if (node->type->astType != AST_UNDEF) {
//            id = printTempVarUndef(out, node);
//        }
//        int exprID = generateAST(out, expr, false);
//        fprintf(out, "\tswitch (_%d) {", exprID);
//        ListElem* elem = List_Begin(node->_case.mappings);
//        for (; elem != List_End(node->_case.mappings); elem = elem->next) {
//            ASTNode* child = elem->data;
//            if (child->mapping.exprs->size == 0) {
//                fprintf(out, "\n\tdefault:\n\t{\n");
//                ASTNode* body = child->mapping.expr;
//                int bodyID = generateAST(out, body, false);
//                if (bodyID != -1 && id != -1) {
//                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//                }
//                fprintf(out, "\tbreak;\n\t} // end default");
//            } else {
//                ListElem* elem = List_Begin(child->mapping.exprs);
//                for (; elem != List_End(child->mapping.exprs); elem = elem->next) {
//                    ASTNode* intExpr = elem->data;
//                    fprintf(out, "\n\tcase %d:", (int)intExpr->_int.data);
//                }
//                fprintf(out, "\n\t{\n");
//                int bodyID = generateAST(out, child->mapping.expr, false);
//                if (bodyID != -1 && id != -1) {
//                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//                }
//                fprintf(out, "\tbreak;\n\t} // end case");
//            }
//        }
//        fprintf(out, "\n\t} // end switch\n");
//        return id;
//    }
//    case AST_FIELD_CASE: {
//        ASTNode* expr = node->_case.expr;
//        int id = -1;
//        if (node->type->astType != AST_UNDEF) {
//            id = printTempVarUndef(out, node);
//        }
//        int exprID = generateAST(out, expr, false);
//        fprintf(out, "\tswitch (_%d.tag) {", exprID);
//        ListElem* elem = List_Begin(node->_case.mappings);
//        for (; elem != List_End(node->_case.mappings); elem = elem->next) {
//            ASTNode* child = elem->data;
//            if (child->mapping.exprs->size == 0) {
//                fprintf(out, "\n\tdefault:\n\t{\n");
//                ASTNode* body = child->mapping.expr;
//                int bodyID = generateAST(out, body, false);
//                if (bodyID != -1 && id != -1) {
//                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//                }
//                fprintf(out, "\tbreak;\n\t} // end default");
//            } else {
//                fprintf(out, "\n\tcase %d:\n\t{\n", child->fieldMapping.tag);
//                int bodyID = generateAST(out, child->mapping.expr, false);
//                if (bodyID != -1 && id != -1) {
//                    fprintf(out, "\t_%d = _%d;\n", id, bodyID);
//                }
//                fprintf(out, "\tbreak;\n\t} // end case");
//            }
//        }
//        fprintf(out, "\n\t} // end switch\n");
//        return id;
//    }
//    case AST_RETURN: {
//        ASTNode* expr = node->unop.expr;
//        int retID = -1;
//        if (expr->astType != AST_UNDEF && expr->astType != AST_VOID) {
//            retID = generateAST(out, expr, false);
//            fprintf(out, "\tretval = _%d;\n", retID);
//        }
//        ASTNode* parentBlock = List_Peek(blockStack);
//        SymbolNode* parentSymbol = parentBlock->block.symbol;
//        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK) {
//            parentSymbol = parentSymbol->parent;
//        }
//        fprintf(out, "\tgoto return_block_%s;\n", parentSymbol->name);
//        return retID;
//    }
//    case AST_BREAK: {
//        ASTNode* parentBlock = List_Peek(blockStack);
//        SymbolNode* parentSymbol = parentBlock->block.symbol;
//        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
//            parentSymbol = parentSymbol->parent;
//        }
//        if (parentSymbol->defers->size == 0) {
//            fprintf(out, "\tgoto end_%s;\n", parentSymbol->name);
//        } else {
//            fprintf(out, "\tgoto break_defer_%s;\n", parentSymbol->name);
//        }
//        return -1;
//    }
//    case AST_CONTINUE: {
//        ASTNode* parentBlock = List_Peek(blockStack);
//        SymbolNode* parentSymbol = parentBlock->block.symbol;
//        while (parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
//            parentSymbol = parentSymbol->parent;
//        }
//        fprintf(out, "\tgoto continue_%s;\n", parentSymbol->name);
//        return -1;
//    }
//    case AST_DEFER: {
//        fprintf(out, "\tdefer_%d = 1;\n", node->defer.deferID);
//        return -1;
//    }
//    case AST_DEFINE:
//        SymbolNode* var = node->define.symbol;
//        if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
//            generateDefine(out, var, false);
//        }
//        return -1;
//    case AST_NEW: {
//        ASTNode* type = node->binop.left;
//        ASTNode* init = node->binop.right;
//        int id = -1;
//        int initID = -1;
//        if (init->astType != AST_UNDEF) {
//            initID = generateAST(out, init, false);
//        }
//        if (type->astType == AST_ARRAY) {
//            ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
//            SymbolNode* lengthSymbol = lengthDefine->define.symbol;
//            ASTNode* lengthCode = lengthSymbol->def;
//            ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
//            SymbolNode* dataSymbol = dataDefine->define.symbol;
//            ASTNode* dataType = dataSymbol->type->unop.expr;
//            int lengthID = generateAST(out, lengthCode, false);
//            id = printTempVar(out, node);
//            fprintf(out, "{_%d, malloc(sizeof(", lengthID);
//            printType(out, dataType);
//            fprintf(out, ") * _%d)};\n", lengthID);
//            fprintf(out, "\t_%d.length = _%d;\n", id, lengthID);
//            fprintf(out, "\tfor(int i = 0; i < _%d; i++) {_%d.data[i] = ", lengthID, id);
//            if (initID == -1) {
//                generateDefaultValue(out, dataType);
//            } else {
//                fprintf(out, "_%d.data[i]", initID);
//            }
//            fprintf(out, ";}\n");
//        } else if (type->astType == AST_PARAMLIST) {
//            id = printTempVar(out, node);
//            fprintf(out, "calloc(sizeof(");
//            printType(out, type);
//            fprintf(out, "), 1);\n");
//            fprintf(out, "\t*_%d = ", id);
//            if (initID == -1) {
//                generateDefaultValue(out, type);
//            } else {
//                fprintf(out, "_%d", initID);
//            }
//            fprintf(out, ";\n");
//        } else {
//            id = printTempVar(out, node);
//            fprintf(out, "calloc(sizeof(");
//            printType(out, type);
//            fprintf(out, "), 1);\n");
//        }
//        return id;
//    }
//    case AST_FREE: {
//        ASTNode* child = node->unop.expr;
//        int leftID = generateAST(out, child, false);
//        ASTNode* type = child->type;
//        int id = -1;
//        if (type->astType != AST_ARRAY) {
//            fprintf(out, "\tfree(_%d);\n", leftID);
//        } else {
//            fprintf(out, "\tfree(_%d.data);\n", leftID);
//        }
//        return -1;
//    }
//    case AST_IDENT: {
//        SymbolNode* var = Symbol_Find(node->ident.data, node->scope);
//        int id = -1;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        } else if (printTab) {
//            fprintf(out, "\t");
//            printTab = false;
//        }
//        if (var->isExtern) {
//            fprintf(out, "%s", var->externName);
//        } else {
//            printPath(out, var);
//        }
//
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_TRUE: {
//        int id = printTempVar(out, node);
//        fprintf(out, "1;\n");
//        return id;
//    }
//    case AST_FALSE: {
//        int id = printTempVar(out, node);
//        fprintf(out, "0;\n");
//        return id;
//    }
//    case AST_NOTHING: {
//        int id = printTempVarType(out, node, INT64_TYPE);
//        fprintf(out, "0;\n");
//        return id;
//    }
//    case AST_INT: {
//        int id = -1;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        }
//        fprintf(out, "%d", (int)node->_int.data);
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_REAL: {
//        int id = -1;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        }
//        fprintf(out, "%f", node->real.data);
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_STRING: {
//        int id = -1;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        }
//        fprintf(out, "string_%d", node->string.stringID);
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_CHAR: {
//        int id = -1;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        }
//        fprintf(out, "'%s'", node->_char.data);
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_ARRAY_LITERAL: {
//        List* ids = List_Create();
//        for (ListElem* elem = List_Begin(node->arrayLiteral.members); elem != List_End(node->arrayLiteral.members); elem = elem->next) {
//            int* ptr = malloc(sizeof(int));
//            int elemID = generateAST(out, elem->data, false);
//            *ptr = elemID;
//            List_Append(ids, ptr);
//        }
//        int id = printTempVar(out, node);
//        fprintf(out, "{%d, (", node->arrayLiteral.members->size);
//        printType(out, ((ASTNode*)List_Begin(node->arrayLiteral.members)->data)->type);
//        fprintf(out, "[]){");
//        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next) {
//            int* elemID = elem->data;
//            fprintf(out, "_%d", *elemID);
//            if (elem->next != List_End(ids)) {
//                fprintf(out, ", ");
//            }
//        }
//        fprintf(out, "}};\n");
//        List_Destroy(ids);
//        return id;
//    }
//    case AST_UNION_LITERAL: {
//        int id = -1;
//        if (node->unionLiteral.expr) {
//            int exprID = generateAST(out, node->unionLiteral.expr, false);
//            id = printTempVarUndef(out, node);
//            ASTNode* memberDefine = List_Get(node->type->unionset.defines, node->unionLiteral.tag);
//            SymbolNode* symbol = memberDefine->define.symbol;
//            fprintf(out, "\t_%d.tag = %d;\n", id, node->unionLiteral.tag);
//            if (symbol->type->astType != AST_VOID) {
//                fprintf(out, "\t_%d.%s = _%d;\n", id, symbol->name, exprID);
//            }
//        } else {
//            id = printTempVarUndef(out, node);
//            ASTNode* memberDefine = List_Get(node->type->unionset.defines, node->unionLiteral.tag);
//            SymbolNode* symbol = memberDefine->define.symbol;
//            fprintf(out, "\t_%d.tag = %d;\n", id, node->unionLiteral.tag);
//            if (symbol->type->astType != AST_VOID) {
//                fprintf(out, "\t_%d.%s = ", id, symbol->name);
//                generateDefaultValue(out, symbol->type);
//                fprintf(out, ";\n");
//            }
//        }
//
//        return id;
//    }
//    case AST_INDEX: {
//        ASTNode* left = node->binop.left;
//        ASTNode* right = node->binop.right;
//        ASTNode* leftType = left->type;
//
//        int indexID = generateAST(out, right, false);
//        int arrID = -1;
//        if (leftType->astType != AST_ARRAY || !isLValue) { // Expensive to copy arrays, just index it directly
//            arrID = generateAST(out, left, false);
//        }
//        int id = -1;
//
//        if (!isLValue) {
//            id = printTempVar(out, node);
//        }
//
//        if (leftType->astType == AST_ARRAY) {
//            if (arrID != -1) {
//                if (printTab) {
//                    fprintf(out, "\t");
//                    printTab = false;
//                }
//                fprintf(out, "_%d.data", arrID);
//            } else {
//                generateAST(out, left, true);
//                fprintf(out, ".data");
//            }
//        } else if (leftType->astType == AST_ADDR && leftType->unop.expr->astType == AST_ARRAY) {
//            if (arrID != -1) {
//                if (printTab) {
//                    fprintf(out, "\t");
//                    printTab = false;
//                }
//                fprintf(out, "_%d->data", arrID);
//            } else {
//                generateAST(out, left, true);
//                fprintf(out, "->data");
//            }
//        }
//        fprintf(out, "[_%d]", indexID);
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_SLICE: {
//        /*
//		struct struct_3 _172_arr = {4, (int64_t[]){0, 0, 0, 0}}
//		int64_t _0 = 4;
//		int64_t _1 = 2;
//		_172_subArr = {_0 - _1, arr.data + _1};
//		*/
//        ASTNode* arr = node->slice.arrayExpr;
//        ASTNode* lowerBound = node->slice.lowerBound;
//        ASTNode* upperBound = node->slice.upperBound;
//        int arrID = generateAST(out, arr, false);
//        int lowerBoundID = -1;
//        int upperBoundID = -1;
//        if (lowerBound->astType != AST_UNDEF) {
//            lowerBoundID = generateAST(out, lowerBound, false);
//        } else {
//            lowerBoundID = printTempVarType(out, node, INT64_TYPE);
//            fprintf(out, "0;\n");
//        }
//        if (upperBound->astType != AST_UNDEF) {
//            upperBoundID = generateAST(out, upperBound, false);
//        } else {
//            upperBoundID = printTempVarType(out, node, INT64_TYPE);
//            fprintf(out, "_%d.length;\n", arrID);
//        }
//        int id = printTempVar(out, node);
//        fprintf(out, "{_%d - _%d, _%d.data + _%d};\n", upperBoundID, lowerBoundID, arrID, lowerBoundID);
//        return id;
//    }
//    case AST_SIZEOF: {
//        int id = -1;
//        ASTNode* type = node->unop.expr;
//        if (!isLValue) {
//            id = printTempVar(out, node);
//            fprintf(out, "sizeof(");
//            printType(out, type);
//            fprintf(out, ");\n");
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "sizeof(");
//            printType(out, type);
//            fprintf(out, ");\n");
//        }
//        return id;
//    }
//    case AST_PAREN: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->arglist.args->head.next->data, false);
//            id = printTempVar(out, node);
//            fprintf(out, "_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            generateAST(out, node->arglist.args->head.next->data, true);
//        }
//        return id;
//    }
//    case AST_ARGLIST: {
//        List* ids = List_Create();
//        for (ListElem* elem = List_Begin(node->arglist.args); elem != List_End(node->arglist.args); elem = elem->next) {
//            int* ptr = malloc(sizeof(int));
//            int elemID = generateAST(out, elem->data, false);
//            *ptr = elemID;
//            List_Append(ids, ptr);
//        }
//        int id = printTempVar(out, node);
//        fprintf(out, "{");
//        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next) {
//            int* elemID = elem->data;
//            fprintf(out, "_%d", *elemID);
//            if (elem->next != List_End(ids)) {
//                fprintf(out, ", ");
//            }
//        }
//        fprintf(out, "};\n");
//        List_Destroy(ids);
//        return id;
//    }
//    case AST_DOT: {
//        int id = -1;
//        SymbolNode* dotSymbol = node->dot.symbol;
//        if (dotSymbol && dotSymbol->isExtern) {
//            if (!isLValue) {
//                id = printTempVar(out, node);
//            } else if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "%s", dotSymbol->externName);
//        } else {
//            ASTNode* left = node->dot.left;
//            ASTNode* right = node->dot.right;
//            ASTNode* leftType = left->type;
//            if (dotSymbol && leftType->astType == AST_IDENT && (!strcmp(leftType->ident.data, "Module") || !strcmp(leftType->ident.data, "Package"))) {
//                if (!isLValue) {
//                    id = printTempVar(out, node);
//                } else if (printTab) {
//                    fprintf(out, "\t");
//                    printTab = false;
//                }
//                printPath(out, dotSymbol);
//            } else if (dotSymbol && dotSymbol->type->isConst && dotSymbol->type->astType == AST_FUNCTION) {
//                if (!isLValue) {
//                    id = printTempVar(out, node);
//                } else if (printTab) {
//                    fprintf(out, "\t");
//                    printTab = false;
//                }
//                printPath(out, dotSymbol);
//            } else if (leftType->astType == AST_ADDR) {
//                if (!isLValue) {
//                    int leftID = generateAST(out, left, false);
//                    id = printTempVar(out, node);
//                    fprintf(out, "_%d->%s", leftID, right->ident.data);
//                } else {
//                    if (printTab) {
//                        fprintf(out, "\t");
//                        printTab = false;
//                    }
//                    generateAST(out, left, true);
//                    fprintf(out, "->%s", right->ident.data);
//                }
//            } else {
//                if (!isLValue) {
//                    int leftID = generateAST(out, left, false);
//                    id = printTempVar(out, node);
//                    fprintf(out, "_%d.%s", leftID, right->ident.data);
//                } else {
//                    if (printTab) {
//                        fprintf(out, "\t");
//                        printTab = false;
//                    }
//                    generateAST(out, left, true);
//                    fprintf(out, ".%s", right->ident.data);
//                }
//            }
//        }
//        if (!isLValue) {
//            fprintf(out, ";\n");
//        }
//        return id;
//    }
//    case AST_ORELSE: {
//        ASTNode* left = node->binop.left;
//        ASTNode* right = node->binop.right;
//
//        int id = printTempVarUndef(out, node);
//        int leftID = generateAST(out, left, false);
//        int elseLabel = newLabel(node);
//        int endLabel = newLabel(node);
//
//        fprintf(out, "\tif (_%d.tag == 0) goto else_%d;\n", leftID, elseLabel);
//        fprintf(out, "\t_%d = _%d.something;\n", id, leftID);
//        fprintf(out, "\tgoto end_%d;\nelse_%d:;\n", endLabel, elseLabel);
//        int rightID = generateAST(out, right, false);
//        if (rightID != -1 && id != -1) {
//            fprintf(out, "\t_%d = _%d;\n", id, rightID);
//        }
//        fprintf(out, "end_%d:;\n", endLabel);
//        return id;
//        return id;
//    }
//    case AST_AND: {
//        ASTNode* left = node->binop.left;
//        ASTNode* right = node->binop.right;
//
//        int overLabel = newLabel(node);
//
//        int id = printTempVar(out, node);
//        fprintf(out, "0;\n");
//        int leftID = generateAST(out, left, false);
//
//        fprintf(out, "\tif (!_%d) goto over_%d;\n", leftID, overLabel);
//        int rightID = generateAST(out, right, false);
//        fprintf(out, "\t_%d = _%d;\n", id, rightID);
//        fprintf(out, "over_%d:;\n", overLabel);
//        return id;
//    }
//    case AST_OR: {
//        ASTNode* left = node->binop.left;
//        ASTNode* right = node->binop.right;
//
//        int overLabel = newLabel(node);
//
//        int id = printTempVar(out, node);
//        fprintf(out, "1;\n");
//        int leftID = generateAST(out, left, false);
//
//        fprintf(out, "\tif (_%d) goto over_%d;\n", leftID, overLabel);
//        int rightID = generateAST(out, right, false);
//        fprintf(out, "\t_%d = _%d;\n", id, rightID);
//        fprintf(out, "over_%d:;\n", overLabel);
//        return id;
//    }
//    case AST_BIT_OR: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d | _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_BIT_XOR: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d ^ _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_BIT_AND: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d & _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_LSHIFT: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d << _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_RSHIFT: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d >> _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_EQ: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int id = -1;
//        if (node->binop.right->astType != AST_NOTHING) {
//            int rightID = generateAST(out, node->binop.right, false);
//            id = printTempVar(out, node);
//            fprintf(out, "_%d == _%d;\n", leftID, rightID);
//        } else {
//            id = printTempVar(out, node);
//            fprintf(out, "_%d.tag == 0;\n", leftID);
//        }
//        return id;
//    }
//    case AST_NEQ: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int id = -1;
//        if (node->binop.right->astType != AST_NOTHING) {
//            int rightID = generateAST(out, node->binop.right, false);
//            id = printTempVar(out, node);
//            fprintf(out, "_%d != _%d;\n", leftID, rightID);
//        } else {
//            id = printTempVar(out, node);
//            fprintf(out, "_%d.tag != 0;\n", leftID);
//        }
//        return id;
//    }
//    case AST_GTR: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d > _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_LSR: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d < _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_GTE: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d >= _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_LTE: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d <= _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_ADD: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d + _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_SUBTRACT: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d - _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_MULTIPLY: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d * _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_DIVIDE: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d / _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_MODULUS: {
//        int leftID = generateAST(out, node->binop.left, false);
//        int rightID = generateAST(out, node->binop.right, false);
//        int id = printTempVar(out, node);
//        fprintf(out, "_%d %% _%d;\n", leftID, rightID);
//        return id;
//    }
//    case AST_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " = _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_ADD_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " += _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_SUB_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " -= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_MULT_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " *= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_DIV_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " /= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_MOD_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " %= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_AND_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " &= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_OR_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " |= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_XOR_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " ^= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_LSHIFT_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " <<= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_RSHIFT_ASSIGN: {
//        int rightID = generateAST(out, node->binop.right, false);
//        printTab = true;
//        generateAST(out, node->binop.left, true);
//        fprintf(out, " >>= _%d;\n", rightID);
//        return rightID;
//    }
//    case AST_NEG: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->unop.expr, false);
//            id = printTempVar(out, node);
//            fprintf(out, "-_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "-");
//            generateAST(out, node->unop.expr, true);
//        }
//        return id;
//    }
//    case AST_BIT_NOT: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->unop.expr, false);
//            id = printTempVar(out, node);
//            fprintf(out, "~_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "~");
//            generateAST(out, node->unop.expr, true);
//        }
//        return id;
//    }
//    case AST_NOT: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->unop.expr, false);
//            id = printTempVar(out, node);
//            fprintf(out, "!_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "!");
//            generateAST(out, node->unop.expr, true);
//        }
//        return id;
//    }
//    case AST_ADDROF: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->unop.expr, false);
//            id = printTempVar(out, node);
//            fprintf(out, "&_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "&");
//            generateAST(out, node->unop.expr, true);
//        }
//        return id;
//    }
//    case AST_DEREF: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->unop.expr, false);
//            id = printTempVar(out, node);
//            fprintf(out, "*_%d;\n", leftID);
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "*");
//            generateAST(out, node->unop.expr, true);
//        }
//        return id;
//    }
//    case AST_CAST: {
//        int id = -1;
//        if (!isLValue) {
//            int leftID = generateAST(out, node->binop.left, false);
//            ASTNode* innerType = node->binop.right;
//            if (innerType->astType != AST_PARAMLIST && innerType->astType != AST_ARRAY) {
//                id = printTempVar(out, node);
//                fprintf(out, "(");
//                printType(out, innerType);
//                fprintf(out, ")");
//                fprintf(out, "_%d;\n", leftID);
//            } else {
//                return leftID;
//            }
//        } else {
//            if (printTab) {
//                fprintf(out, "\t");
//                printTab = false;
//            }
//            fprintf(out, "(");
//            printType(out, node->binop.right);
//            fprintf(out, ")");
//            generateAST(out, node->binop.left, true);
//        }
//        return id;
//    }
//    case AST_CALL: {
//        ASTNode* arglist = node->call.right;
//        List* ids = List_Create();
//        for (ListElem* elem = List_Begin(arglist->arglist.args); elem != List_End(arglist->arglist.args); elem = elem->next) {
//            int* ptr = malloc(sizeof(int));
//            ASTNode* child = elem->data;
//            if (child->astType != AST_IDENT) {
//                child->scope = node->scope;
//                int elemID = generateAST(out, child, false);
//                *ptr = elemID;
//            } else {
//                *ptr = -1;
//            }
//            List_Append(ids, ptr);
//        }
//
//        int id = -1;
//        if (node->call.fnType->function.codomainType->astType != AST_VOID) {
//            id = printTempVar(out, node);
//        } else {
//            fprintf(out, "\t");
//        }
//        generateAST(out, node->call.left, true);
//        fprintf(out, "(");
//        ListElem* elem2 = List_Begin(arglist->arglist.args);
//        for (ListElem* elem = List_Begin(ids); elem != List_End(ids); elem = elem->next, elem2 = elem2->next) {
//            int* elemID = elem->data;
//            if (*elemID != -1) {
//                fprintf(out, "_%d", *elemID);
//            } else {
//                ASTNode* child = elem2->data;
//                generateAST(out, child, true);
//            }
//            if (elem->next != List_End(ids)) {
//                fprintf(out, ", ");
//            }
//        }
//        fprintf(out, ");\n");
//        List_Destroy(ids);
//        return id;
//    }
//    }
//}
//
///*
//Prints out the parameter list for a procedure
//*/
//static void generateParamList(FILE* out, ASTNode* parameters)
//{
//    ListElem* paramElem = List_Begin(parameters->paramlist.defines);
//    // For each parameter in the procedure's parameter list, print it out
//    for (; paramElem != List_End(parameters->paramlist.defines); paramElem = paramElem->next) {
//        ASTNode* define = paramElem->data;
//        SymbolNode* var = define->define.symbol;
//        generateDefine(out, var, true);
//        if (paramElem != List_End(parameters->paramlist.defines)->prev) {
//            fprintf(out, ", ");
//        }
//    }
//}
//
//static void generateIncludes(FILE* out, Map* includes)
//{
//    fprintf(out, "/* Includes used by the program */\n#define _CRT_SECURE_NO_WARNINGS\n");
//    List* keys = includes->keyList;
//    ListElem* e = List_Begin(keys);
//    for (; e != List_End(keys); e = e->next) {
//        char* include = e->data;
//        if (include[0] == '<') {
//            fprintf(out, "#include %s\n", include);
//        } else {
//            fprintf(out, "#include \"%s\"\n", include);
//        }
//    }
//    fprintf(out, "\n");
//}
//
//void generateUnion(FILE* out, DGraph* graphNode);
//
//static void generateStruct(FILE* out, DGraph* graphNode)
//{
//    if (graphNode->visited) {
//        return;
//    } else {
//        graphNode->visited = true;
//    }
//
//    // Print out all dependencies
//    ListElem* elem = List_Begin(graphNode->dependencies);
//    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
//        DGraph* child = elem->data;
//        if (child->structDef->astType == AST_UNIONSET) {
//            generateUnion(out, child);
//        } else {
//            generateStruct(out, child);
//        }
//    }
//
//    ASTNode* _struct = graphNode->structDef;
//    char* structOrdStr = myItoa(graphNode->ordinal + 1);
//    fprintf(out, "struct struct_%s {\n", structOrdStr);
//
//    ListElem* paramElem = List_Begin(_struct->paramlist.defines);
//    // For each parameter in the procedure's parameter list, print it out
//    for (; paramElem != List_End(_struct->paramlist.defines); paramElem = paramElem->next) {
//        ASTNode* define = paramElem->data;
//        SymbolNode* var = define->define.symbol;
//        if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
//            fprintf(out, "\t");
//            generateDefine(out, var, true);
//            fprintf(out, ";\n");
//        }
//    }
//    fprintf(out, "};\n\n");
//}
//
//void generateUnion(FILE* out, DGraph* graphNode)
//{
//    if (graphNode->visited) {
//        return;
//    } else {
//        graphNode->visited = true;
//    }
//
//    // Print out all dependencies
//    ListElem* elem = List_Begin(graphNode->dependencies);
//    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
//        DGraph* child = elem->data;
//        if (child->structDef->astType == AST_UNIONSET) {
//            generateUnion(out, child);
//        } else {
//            generateStruct(out, child);
//        }
//    }
//
//    ASTNode* _union = graphNode->structDef;
//    char* structOrdStr = myItoa(graphNode->ordinal + 1);
//    fprintf(out, "struct struct_%s {\n\tint64_t tag;\n", structOrdStr);
//
//    int numOfNonVoidMembers = 0;
//    ListElem* paramElem = List_Begin(_union->unionset.defines);
//    for (; paramElem != List_End(_union->unionset.defines); paramElem = paramElem->next) {
//        ASTNode* define = paramElem->data;
//        SymbolNode* var = define->define.symbol;
//        if (var->type->astType != AST_VOID) {
//            numOfNonVoidMembers = 1;
//            break;
//        }
//    }
//
//    if (numOfNonVoidMembers > 0) {
//        fprintf(out, "\tunion {\n");
//
//        paramElem = List_Begin(_union->unionset.defines);
//        // For each parameter in the procedure's parameter list, print it out
//        for (; paramElem != List_End(_union->unionset.defines); paramElem = paramElem->next) {
//            ASTNode* define = paramElem->data;
//            SymbolNode* var = define->define.symbol;
//            if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst) && var->type->astType != AST_VOID) {
//                fprintf(out, "\t\t");
//                generateDefine(out, var, true);
//                fprintf(out, ";\n");
//            }
//        }
//        fprintf(out, "\t};\n");
//    }
//    fprintf(out, "};\n\n");
//}
//
//void generateStructDefinitions(FILE* out, List* depenGraph)
//{
//    fprintf(out, "/* Struct definitions */\n");
//    ListElem* elem = List_Begin(depenGraph);
//    for (; elem != List_End(depenGraph); elem = elem->next) {
//        DGraph* graphNode = elem->data;
//        if (graphNode->structDef->astType == AST_UNIONSET) {
//            generateUnion(out, graphNode);
//        } else {
//            generateStruct(out, graphNode);
//        }
//    }
//}
//
//void generateVerbatims(FILE* out, List* verbatims)
//{
//    fprintf(out, "/* Verbatim code */\n");
//    ListElem* elem = List_Begin(verbatims);
//    for (; elem != List_End(verbatims); elem = elem->next) {
//        fprintf(out, (char*)elem->data);
//        fprintf(out, "\n");
//    }
//    fprintf(out, "\n");
//}
//
//void generateString(FILE* out, char* string)
//{
//    int backslashes = 0;
//    for (int j = 0; j < strlen(string); j++) {
//        if (string[j] == '\\') {
//            backslashes++;
//        }
//    }
//    fprintf(out, "{%d, (char[]){", strlen(string) - backslashes);
//    for (int j = 0; j < strlen(string); j++) {
//        char c = string[j];
//        if (c == '\\') {
//            fprintf(out, "'%c", c);
//            j++;
//            fprintf(out, "%c', ", string[j]);
//        } else if (c == '\'') {
//            fprintf(out, "'\\'', ");
//        } else {
//            fprintf(out, "'%c', ", c);
//        }
//    }
//    fprintf(out, "'\\0'}};\n");
//}
//
//void generateForwardStrings(FILE* out, List* strings)
//{
//    fprintf(out, "/* Forward string declarations */\n");
//    ListElem* elem = List_Begin(strings);
//    int i = -1;
//    for (; elem != List_End(strings); elem = elem->next) {
//        i++;
//        ASTNode* node = elem->data;
//        if (!node->scope->isReachable) {
//            continue;
//        }
//        printType(out, STRING_TYPE);
//        fprintf(out, " string_%d;\n", i);
//    }
//    fprintf(out, "\n");
//}
//
//void generateStrings(FILE* out, List* strings)
//{
//    fprintf(out, "/* String definitions */\n");
//    ListElem* elem = List_Begin(strings);
//    int i = -1;
//    for (; elem != List_End(strings); elem = elem->next) {
//        i++;
//        ASTNode* node = elem->data;
//        if (!node->scope->isReachable) {
//            continue;
//        }
//        printType(out, STRING_TYPE);
//        fprintf(out, " string_%d = ", i);
//        generateString(out, node->string.data);
//    }
//    fprintf(out, "\n");
//}
//
//void generateForwardFunctions(FILE* out, List* functions)
//{
//    fprintf(out, "/* Forward function and procedure declarations */\n");
//    for (ListElem* elem = List_Begin(functions); elem != List_End(functions); elem = elem->next) {
//        SymbolNode* symbol = elem->data;
//        if (!symbol->isReachable) {
//            continue;
//        }
//
//        ASTNode* functionType = symbol->type;
//        ASTNode* params = functionType->function.domainType;
//        ASTNode* returns = functionType->function.codomainType;
//        if (returns->astType != AST_PARAMLIST) {
//            printType(out, functionType);
//        } else {
//            printType(out, returns);
//        }
//        fprintf(out, " ");
//        printPath(out, symbol);
//        fprintf(out, "(");
//        generateParamList(out, params);
//        fprintf(out, ");\n");
//    }
//    fprintf(out, "\n");
//}
//
//void generateForwardGlobals(FILE* out, List* globals)
//{
//    fprintf(out, "/* Forward global declarations */\n");
//    for (ListElem* elem = List_Begin(globals); elem != List_End(globals); elem = elem->next) {
//        SymbolNode* symbol = elem->data;
//        if (!symbol->isReachable) {
//            continue;
//        }
//
//        printType(out, symbol->type);
//        fprintf(out, " ");
//        printPath(out, symbol);
//        fprintf(out, ";\n");
//    }
//    fprintf(out, "\n");
//}
//
//static int getPathLength(SymbolNode* symbol)
//{
//    if (symbol->parent->parent != NULL && !symbol->isExtern) {
//        int length = 0;
//        if (symbol->parent->symbolType != SYMBOL_FUNCTION) {
//            length += getPathLength(symbol->parent);
//        }
//        return length + strlen(symbol->name) + 1;
//    } else {
//        return strlen(symbol->name);
//    }
//}
//
//void generateGlobalDefinitions(FILE* out, List* globals)
//{
//    global = true;
//    for (ListElem* elem = List_Begin(globals); elem != List_End(globals); elem = elem->next) {
//        SymbolNode* var = elem->data;
//        if (!var->isReachable) {
//            continue;
//        }
//        fprintf(out, "\t");
//        generateDefine(out, var, false);
//        fprintf(out, ";\n");
//    }
//}
//
//void generateFunctionDefinitions(FILE* out, List* functions)
//{
//    fprintf(out, "/* Function and procedure definitions */\n");
//    global = false;
//    for (ListElem* elem = List_Begin(functions); elem != List_End(functions); elem = elem->next) {
//        SymbolNode* symbol = elem->data;
//        if (!symbol->isReachable) {
//            continue;
//        }
//
//        ASTNode* functionType = symbol->type;
//        ASTNode* params = functionType->function.domainType;
//        ASTNode* returns = functionType->function.codomainType;
//        if (returns->astType != AST_PARAMLIST) {
//            printType(out, functionType);
//        } else {
//            printType(out, returns);
//        }
//        fprintf(out, " ");
//        printPath(out, symbol);
//        fprintf(out, "(");
//        generateParamList(out, params);
//        fprintf(out, ")\n{\n");
//        if (returns->astType != AST_VOID) {
//            fprintf(out, "\t");
//            printType(out, returns);
//            fprintf(out, " retval;\n");
//        }
//        int blockID = generateAST(out, symbol->def, false);
//        SymbolNode* block = Map_Get(symbol->def->scope->children, List_Get(symbol->def->scope->children->keyList, symbol->def->scope->children->size - 1));
//        if (returns->astType != AST_VOID && blockID != -1) {
//            fprintf(out, "\tretval = _%d;\n", blockID);
//        }
//        fprintf(out, "return_block_%s:;\n", block->name);
//        generateDefers(out, block->defers, 0);
//        if (returns->astType != AST_VOID) {
//            fprintf(out, "\treturn retval;\n");
//        }
//        fprintf(out, "}\n\n");
//    }
//}
//
//void generateMainFunction(FILE* out, SymbolNode* mainFunction)
//{
//    fprintf(out, "\int main(int argc, char** argv)\n");
//
//    fprintf(out, "{\n");
//
//    generateGlobalDefinitions(out, program.globalVars);
//
//    fprintf(out, "\t");
//    printType(out, STRING_ARR_TYPE);
//    fprintf(out, " args = {argc, calloc(sizeof(");
//    printType(out, STRING_TYPE);
//    fprintf(out, ") * argc, 1)};\n");
//
//    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");
//
//    fprintf(out, "\t\tint length = strlen(argv[i]);\n");
//
//    fprintf(out, "\t\targs.data[i] = (");
//    printType(out, STRING_TYPE);
//    fprintf(out, "){length, calloc(sizeof(char) * length, 1)};\n");
//
//    fprintf(out, "\t\tmemcpy(args.data[i].data, argv[i], length);\n");
//
//    fprintf(out, "\t}\n");
//
//    fprintf(out, "\tint retval = ");
//    printPath(out, mainFunction);
//    fprintf(out, "(args);\n");
//
//    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");
//
//    fprintf(out, "\t\tfree(args.data[i].data);\n");
//
//    fprintf(out, "\t}\n");
//
//    fprintf(out, "\tfree(args.data);\n");
//
//    fprintf(out, "\tsystem(\"pause\");\n\treturn retval;\n");
//
//    fprintf(out, "}\n");
//}
//
///*
//Prints out a program to an output file.
//*/
//void Generator_Generte(Program _program, FILE* out)
//{
//    srand(time(0));
//    int randID = rand();
//    fprintf(out, "/* Code generated using Orange Translator http://josephs-projects.com */\n\n");
//
//    program = _program;
//
//    generateIncludes(out, program.includes);
//    generateStructDefinitions(out, program.dependencyGraph);
//    generateVerbatims(out, program.verbatims);
//    generateForwardStrings(out, program.strings);
//    generateForwardGlobals(out, program.globalVars);
//    generateForwardFunctions(out, program.functions);
//    fprintf(out, "#ifndef ORANGE_PROGRAM_%s\n#define ORANGE_PROGRAM_%s\n\n", myItoa(randID), myItoa(randID));
//    generateStrings(out, program.strings);
//    generateFunctionDefinitions(out, program.functions);
//    generateMainFunction(out, program.mainFunction);
//    fprintf(out, "#endif\n");
//}