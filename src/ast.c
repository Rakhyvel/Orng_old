/*
 * Provides functionality for creating and maintaining an Abstract Syntax Tree.
 *
 * See ast.h for more information.
 * 
 * Author: Joseph Shimel
*/

#define _CRT_SECURE_NO_WARNINGS
#include "ast.h"
#include "../util/debug.h"
#include "../util/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const ASTNode* INT8_TYPE = NULL;
const ASTNode* INT16_TYPE = NULL;
const ASTNode* INT32_TYPE = NULL;
const ASTNode* INT64_TYPE = NULL;
const ASTNode* CONST_STRING_TYPE = NULL;
const ASTNode* STRING_ARR_TYPE = NULL;
const ASTNode* CONST_CHAR_TYPE = NULL;
const ASTNode* CHAR_TYPE = NULL;
const ASTNode* REAL32_TYPE = NULL;
const ASTNode* REAL64_TYPE = NULL;
const ASTNode* CONST_BOOL_TYPE = NULL;
const ASTNode* BOOL_TYPE = NULL;
const ASTNode* TYPE_TYPE = NULL;
const ASTNode* UNDEF_TYPE = NULL;
const ASTNode* VOID_ADDR_TYPE = NULL;

bool doDefTypes = false;

// Generates common ptr-to-array types
ASTNode* createArrayTypeNode(ASTNode* baseType, int length)
{
    ASTNode* retval = NULL;
    if (length == -1) {
        retval = AST_Create(AST_ADDR, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);
    }
    ASTNode* array = AST_Create(AST_ARRAY, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);

    SymbolNode* lengthSymbol = Symbol_Create("length", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* lengthDefine = AST_Create(AST_DEFINE, lengthSymbol, NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* lengthType = AST_Create(AST_IDENT, "Int", NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* lengthCode = AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);
    lengthSymbol->def = lengthCode;
    lengthSymbol->type = lengthType;
    lengthSymbol->isPublic = true;
    lengthType->isConst = true;

    SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* dataDefine = AST_Create(AST_DEFINE, dataSymbol, NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* dataType = AST_Create(AST_C_ARRAY, NULL, NULL, (Position) { NULL, 0, 0, 0 }, false);
    List_Append(dataType->children, baseType);
    if (length != -1) {
        List_Append(dataType->children, AST_Create(AST_INT, length, NULL, (Position) { NULL, 0, 0, 0 }, false));
    } else {
        List_Append(dataType->children, AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, false));
    }
    ASTNode* dataCode = AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);
    dataSymbol->def = dataCode;
    dataSymbol->type = dataType;
    dataSymbol->isPublic = true;

    List_Append(array->children, lengthDefine);
    List_Append(array->children, dataDefine);

    if (length == -1) {
        List_Append(retval->children, array);
    } else {
        retval = array;
    }

    return retval;
}

void AST_Init()
{
    INT8_TYPE = AST_Create(AST_IDENT, "Int8", NULL, (Position) { NULL, 0, 0, 0 }, true);
    INT16_TYPE = AST_Create(AST_IDENT, "Int16", NULL, (Position) { NULL, 0, 0, 0 }, true);
    INT32_TYPE = AST_Create(AST_IDENT, "Int32", NULL, (Position) { NULL, 0, 0, 0 }, true);
    INT64_TYPE = AST_Create(AST_IDENT, "Int64", NULL, (Position) { NULL, 0, 0, 0 }, true);
    CONST_CHAR_TYPE = AST_Create(AST_IDENT, "Char", NULL, (Position) { NULL, 0, 0, 0 }, true);
    CHAR_TYPE = AST_Create(AST_IDENT, "Char", NULL, (Position) { NULL, 0, 0, 0 }, false);
    CONST_STRING_TYPE = createArrayTypeNode(CHAR_TYPE, -1, true);
    STRING_TYPE = createArrayTypeNode(CHAR_TYPE, -1, false);
    STRING_ARR_TYPE = createArrayTypeNode(STRING_TYPE, -1, true);
    REAL32_TYPE = AST_Create(AST_IDENT, "Real32", NULL, (Position) { NULL, 0, 0, 0 }, true);
    REAL64_TYPE = AST_Create(AST_IDENT, "Real64", NULL, (Position) { NULL, 0, 0, 0 }, true);
    CONST_BOOL_TYPE = AST_Create(AST_IDENT, "Bool", NULL, (Position) { NULL, 0, 0, 0 }, true);
    BOOL_TYPE = AST_Create(AST_IDENT, "Bool", NULL, (Position) { NULL, 0, 0, 0 }, false);
    TYPE_TYPE = AST_Create(AST_IDENT, "Type", NULL, (Position) { NULL, 0, 0, 0 }, true);
    PACKAGE_TYPE = AST_Create(AST_IDENT, "Package", NULL, (Position) { NULL, 0, 0, 0 }, true);
    UNDEF_TYPE = AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, true);
    VOID_ADDR_TYPE = AST_Create(AST_ADDR, 0, NULL, (Position) { NULL, 0, 0, 0 }, true);
    ENUM_TYPE = AST_Create(AST_IDENT, "Enum", NULL, (Position) { NULL, 0, 0, 0 }, true);
    List_Append(VOID_ADDR_TYPE->children, AST_Create(AST_PARAMLIST, 0, 0, (Position) { NULL, 0, 0, 0 }, true));
}

/*
 * Creates an AST node
 *
 * Parameters:
 *	type	The type of node to have the node be
 *	data	Some data that the AST node should have. See astData in ast.h
 *	scope	The scope that the AST node belongs into. See symbol.h
 *	line	The line that this AST node comes from
 *
 * Returns:
 *	The AST node with the given parameters
 */
ASTNode* AST_Create(enum astType type, uint64_t data, SymbolNode* scope, struct position pos, bool isConst)
{
    ASTNode* retval = calloc(1, sizeof(ASTNode));
    retval->children = List_Create();
    retval->astType = type;
    retval->data = data;
    retval->scope = scope;
    retval->pos = pos;
    retval->visited = false;
    retval->type = NULL;
    retval->isConst = isConst;
    return retval;
}

/*
 * Prints out an AST node
 *
 * Parameters:
 *	root			The AST node to print out. Cannot be null.
 *	prefix			The string to prefix. Should be empty if calling from userspace code
 *	childrenPrefix	The string to print before all children. Should be empty string if in userspace
 */
void AST_Print(ASTNode* root, char* prefix, char* childrenPrefix)
{
    // Crash program if root is null
    if (root == NULL) {
        PANIC("Malformed AST, child here was null!\n");
    }
    // Switch on the type and print the data specific for each node
    switch (root->astType) {
    case AST_INT:
        printf("%s%s [%d]\n", prefix, AST_GetString(root->astType), root->data);
        break;
    case AST_STRING:
    case AST_CHAR:
        printf("%s%s [%s]\n", prefix, AST_GetString(root->astType), root->data);
        break;
    case AST_DEFINE:
        printf("%s%s [0x%p]\n", prefix, AST_GetString(root->astType), root->data);
        Symbol_Print(root->data, prefix, childrenPrefix);
        break;
    case AST_BLOCK:
        printf("%s%s [0x%p]\n", prefix, AST_GetString(root->astType), root->data);
        break;
    case AST_IDENT:
        printf("%s%s [%s]\n", prefix, AST_GetString(root->astType), root->data);
        break;
    default:
        printf("%s%s []\n", prefix, AST_GetString(root->astType));
    }
    // Go through each child of the node in the tree
    for (ListElem* elem = List_Begin(root->children); elem != List_End(root->children); elem = elem->next) {
        bool hasNext = elem->next != List_End(root->children);
        char newPrefix[255];
        char newChildrenPrefix[255];
        if (hasNext) {
            // Some children will be printed after this
            strncpy_s(newPrefix, 255, childrenPrefix, 254);
            strncat_s(newPrefix, 255, "+--", 254);
            strncpy_s(newChildrenPrefix, 255, childrenPrefix, 254);
            strncat_s(newChildrenPrefix, 255, "|  ", 254);
        } else {
            // No children after this
            strncpy_s(newPrefix, 255, childrenPrefix, 254);
            strncat_s(newPrefix, 255, "\\--", 254);
            strncpy_s(newChildrenPrefix, 255, childrenPrefix, 254);
            strncat_s(newChildrenPrefix, 255, "   ", 254);
        }
        // Recursively call on child
        AST_Print(elem->data, newPrefix, newChildrenPrefix);
    }
}

int AST_TypeRepr(char* str, ASTNode* type)
{
    char* origStr = str;
    if (type->isConst) {
        str += sprintf(str, ":");
    }
    switch (type->astType) {
    case AST_ENUM: {
        SymbolNode* symbol = type->data;
        str += sprintf(str, "%s", symbol->name);
    } break;
    case AST_VOID:
        str += sprintf(str, "()", (char*)type->data);
        break;
    case AST_IDENT:
        str += sprintf(str, "%s", (char*)type->data);
        break;
    case AST_DEFINE:
        SymbolNode* symbol = type->data;
        ASTNode* type2 = symbol->type;
        str += sprintf(str, "%s:", symbol->name);
        if (symbol->type->astType != AST_PARAMLIST) {
            str += AST_TypeRepr(str, symbol->type);
        } else if (doDefTypes) {
            str += AST_TypeRepr(str, symbol->type);
        } else {
            str += sprintf(str, "( .. )");
        }
        break;
    case AST_PARAMLIST:
        str += sprintf(str, "(");
        for (struct listElem* elem = List_Begin(type->children); elem != List_End(type->children); elem = elem->next) {
            ASTNode* param = elem->data;
            str += AST_TypeRepr(str, param);
            if (elem->next == List_End(type->children)) {
                str += sprintf(str, ")");
            } else {
                str += sprintf(str, ", ");
            }
        }
        break;
    case AST_FUNCTION:
        ASTNode* input = List_Get(type->children, 0);
        ASTNode* output = List_Get(type->children, 1);
        str += AST_TypeRepr(str, input);
        str += sprintf(str, " -> ");
        str += AST_TypeRepr(str, output);
        break;
    case AST_ADDR: {
        ASTNode* child = List_Get(type->children, 0);
        str += sprintf(str, "&");
        str += AST_TypeRepr(str, child);
    } break;
    case AST_C_ARRAY: {
        ASTNode* child = List_Get(type->children, 0);
        str += sprintf(str, "[static]");
        str += AST_TypeRepr(str, child);
    } break;
    case AST_ARRAY: {
        ASTNode* dataDefine = List_Get(type->children, 1);
        SymbolNode* dataSymbol = dataDefine->data;
        ASTNode* dataAddrType = dataSymbol->type;
        ASTNode* dataType = List_Get(dataAddrType->children, 0);
        ASTNode* dataLength = List_Get(dataAddrType->children, 1);
        if (dataLength->astType == AST_INT) {
            str += sprintf(str, "[%d]", (int)dataLength->data);
        } else {
            str += sprintf(str, "[]");
        }
        str += AST_TypeRepr(str, dataType);
    } break;
    case AST_EXTERN: {
        SymbolNode* var = type->data;
        str += AST_TypeRepr(str, var->type);
    } break;
    case AST_UNDEF: {
        str += sprintf(str, "Undef");
    } break;
    case AST_DOT: {
        ASTNode* left = List_Get(type->children, 0);
        ASTNode* right = List_Get(type->children, 1);
        str += AST_TypeRepr(str, left);
        str += sprintf(str, ".");
        str += AST_TypeRepr(str, right);
        break;
    }
    default:
        break;
    }
    return str - origStr;
}

/*
 * Returns the name that corresponds to a given ASTType
 *
 * Parameters:
 *	type	The type to get the name for
 *
 * Returns:
 *	The name of the given type
 */
char* AST_GetString(enum astType type)
{
    switch (type) {
    case AST_IDENT:
        return "AST_IDENT";
    case AST_CALL:
        return "AST_CALL";
    case AST_INT:
        return "AST_INT";
    case AST_STRING:
        return "AST_STRING";
    case AST_CHAR:
        return "AST_CHAR";
    case AST_REAL:
        return "AST_REAL";
    case AST_ARGLIST:
        return "AST_ARGLIST";
    case AST_ARRAY_LITERAL:
        return "AST_ARRAY_LITERAL";
    case AST_NEG:
        return "AST_NEG";
    case AST_ADD:
        return "AST_ADD";
    case AST_SUBTRACT:
        return "AST_SUBTRACT";
    case AST_MULTIPLY:
        return "AST_MULTIPLY";
    case AST_DIVIDE:
        return "AST_DIVIDE";
    case AST_MODULUS:
        return "AST_MODULUS";
    case AST_PAREN:
        return "AST_PAREN";
    case AST_INDEX:
        return "AST_INDEX";
    case AST_DEREF:
        return "AST_DEREF";
    case AST_ADDROF:
        return "AST_ADDROF";
    case AST_NULL:
        return "AST_NULL";
    case AST_SIZEOF:
        return "AST_SIZEOF";
    case AST_NOT:
        return "AST_NOT";
    case AST_OR:
        return "AST_OR";
    case AST_AND:
        return "AST_AND";
    case AST_NEQ:
        return "AST_NEQ";
    case AST_EQ:
        return "AST_EQ";
    case AST_GTR:
        return "AST_GTR";
    case AST_GTE:
        return "AST_GTE";
    case AST_LSR:
        return "AST_LSR";
    case AST_LTE:
        return "AST_LTE";
    case AST_TRUE:
        return "AST_TRUE";
    case AST_FALSE:
        return "AST_FALSE";
    case AST_BIT_OR:
        return "AST_BIT_OR";
    case AST_BIT_XOR:
        return "AST_BIT_XOR";
    case AST_BIT_AND:
        return "AST_BIT_AND";
    case AST_MULT_ASSIGN:
        return "AST_DIV_ASSIGN";
    case AST_DIV_ASSIGN:
        return "AST_DIV_ASSIGN";
    case AST_LSHIFT:
        return "AST_LSHIFT";
    case AST_RSHIFT:
        return "AST_RSHIFT";
    case AST_BIT_NOT:
        return "AST_BIT_NOT";
    case AST_UNDEF:
        return "AST_UNDEF";
    case AST_BLOCK:
        return "AST_BLOCK";
    case AST_DEFINE:
        return "AST_DEFINE";
    case AST_ASSIGN:
        return "AST_ASSIGN";
    case AST_IF:
        return "AST_IF";
    case AST_IFELSE:
        return "AST_IFELSE";
    case AST_WHILE:
        return "AST_WHILE";
    case AST_FOR:
        return "AST_FOR";
    case AST_DO_WHILE:
        return "AST_DO_WHILE";
    case AST_SWITCH:
        return "AST_SWITCH";
    case AST_CASE:
        return "AST_CASE";
    case AST_RETURN:
        return "AST_RETURN";
    case AST_NEW:
        return "AST_NEW";
    case AST_FREE:
        return "AST_FREE";
    case AST_DOT:
        return "AST_DOT";
    case AST_VOID:
        return "AST_VOID";
    case AST_CAST:
        return "AST_CAST";
    case AST_PARAMLIST:
        return "AST_PARAMLIST";
    case AST_FUNCTION:
        return "AST_FUNCTION";
    case AST_ADDR:
        return "AST_ADDR";
    case AST_C_ARRAY:
        return "AST_C_ARRAY";
    case AST_ARRAY:
        return "AST_ARRAY";
    case AST_ENUM:
        return "AST_ENUM";
    case AST_EXTERN:
        return "AST_EXTERN";
    default:
        return "Unknown ASTNode type";
    }
}
