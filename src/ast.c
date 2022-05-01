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
const ASTNode* CONST_INT64_TYPE = NULL;
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
    ASTNode* array = AST_Create(AST_ARRAY, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);

    SymbolNode* lengthSymbol = Symbol_Create("length", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* lengthDefine = AST_Create(AST_DEFINE, lengthSymbol, NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* lengthType = AST_Create(AST_IDENT, "Int", NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* lengthCode;
    if (length != -1) {
        lengthCode = AST_Create(AST_INT, length, NULL, (Position) { NULL, 0, 0, 0 }, false);
    } else {
        lengthCode = AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);
    }
    lengthSymbol->def = lengthCode;
    lengthSymbol->type = lengthType;
    lengthSymbol->isPublic = true;
    lengthType->isConst = true;

    SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* dataDefine = AST_Create(AST_DEFINE, dataSymbol, NULL, (Position) { NULL, 0, 0, 0 }, false);
    ASTNode* dataType = AST_Create(AST_ADDR, NULL, NULL, (Position) { NULL, 0, 0, 0 }, false);
    List_Append(dataType->children, baseType);
    ASTNode* dataCode = AST_Create(AST_UNDEF, 0, NULL, (Position) { NULL, 0, 0, 0 }, false);
    dataSymbol->def = dataCode;
    dataSymbol->type = dataType;
    dataSymbol->isPublic = true;

    List_Append(array->children, lengthDefine);
    List_Append(array->children, dataDefine);

    return array;
}

void AST_Init()
{
    INT8_TYPE = AST_Create(AST_IDENT, "Int8", NULL, (Position) { NULL, 0, 0, 0 }, false);
    INT16_TYPE = AST_Create(AST_IDENT, "Int16", NULL, (Position) { NULL, 0, 0, 0 }, false);
    INT32_TYPE = AST_Create(AST_IDENT, "Int32", NULL, (Position) { NULL, 0, 0, 0 }, false);
    CONST_INT64_TYPE = AST_Create(AST_IDENT, "Int64", NULL, (Position) { NULL, 0, 0, 0 }, true);
    INT64_TYPE = AST_Create(AST_IDENT, "Int64", NULL, (Position) { NULL, 0, 0, 0 }, false);
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
ASTNode* AST_Create(enum astType type, SymbolNode* scope, struct position pos)
{
    ASTNode* retval = calloc(1, sizeof(ASTNode));
    retval->astType = type;
    retval->scope = scope;
    retval->pos = pos;
    retval->visited = false;
    retval->type = NULL;
    return retval;
}

ASTNode* AST_Create_ident(char* data, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_IDENT, scope, pos);
    retval->ident.data = data;
    return retval;
}

ASTNode* AST_Create_call(struct astNode* functionExpr, struct astNode* arglist, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CALL, scope, pos);
    retval->call.functionExpr = functionExpr;
    retval->call.arglist = arglist;
    return retval;
}

ASTNode* AST_Create_int(int64_t data, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_INT, scope, pos);
    retval->_int.data = data;
    return retval;
}

ASTNode* AST_Create_string(char* data, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_STRING, scope, pos);
    retval->string.data = data;
    return retval;
}

ASTNode* AST_Create_char(char data, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CHAR, scope, pos);
    retval->_char.data = data;
    return retval;
}

ASTNode* AST_Create_real(double data, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_REAL, scope, pos);
    retval->real.data = data;
    return retval;
}

ASTNode* AST_Create_arglist(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ARGLIST, scope, pos);
    retval->arglist.args = List_Create();
    return retval;
}

ASTNode* AST_Create_namedArg(char* name, struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NAMED_ARG, scope, pos);
    return retval;
}

ASTNode* AST_Create_arrayLiteral(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ARRAY_LITERAL, scope, pos);
    retval->arrayLiteral.members = List_Create();
    return retval;
}

ASTNode* AST_Create_true(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_TRUE, scope, pos);
    return retval;
}

ASTNode* AST_Create_false(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FALSE, scope, pos);
    return retval;
}

ASTNode* AST_Create_null(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NULL, scope, pos);
    return retval;
}

ASTNode* AST_Create_undef(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_UNDEF, scope, pos);
    return retval;
}

ASTNode* AST_Create_neg(struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NEG, scope, pos);
    retval->neg.right = right;
    return retval;
}

ASTNode* AST_Create_add(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADD, scope, pos);
    retval->add.left = left;
    retval->add.right = right;
    return retval;
}

ASTNode* AST_Create_subtract(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SUBTRACT, scope, pos);
    retval->subtract.left = left;
    retval->subtract.right = right;
    return retval;
}

ASTNode* AST_Create_multiply(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MULTIPLY, scope, pos);
    retval->multiply.left = left;
    retval->multiply.right = right;
    return retval;
}

ASTNode* AST_Create_divide(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DIVIDE, scope, pos);
    retval->divide.left = left;
    retval->divide.right = right;
    return retval;
}

ASTNode* AST_Create_modulus(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MODULUS, scope, pos);
    retval->modulus.left = left;
    retval->modulus.right = right;
    return retval;
}

ASTNode* AST_Create_paren(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_PAREN, scope, pos);
    retval->paren.expr = expr;
    return retval;
}

ASTNode* AST_Create_addrOf(struct astNode* lvalue, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADDROF, scope, pos);
    retval->addrOf.lvalue = lvalue;
    return retval;
}

ASTNode* AST_Create_deref(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DEREF, scope, pos);
    retval->deref.expr = expr;
    return retval;
}

ASTNode* AST_Create_index(struct astNode* arrayExpr, struct astNode* subscript, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_INDEX, scope, pos);
    retval->index.arrayExpr = arrayExpr;
    retval->index.subscript = subscript;
    return retval;
}

ASTNode* AST_Create_slice(struct astNode* arrayExpr, struct astNode* lowerBound, struct astNode* upperBound, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SLICE, scope, pos);
    retval->slice.arrayExpr = arrayExpr;
    retval->slice.lowerBound = lowerBound;
    retval->slice.upperBound = upperBound;
    return retval;
}

ASTNode* AST_Create_not(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NOT, scope, pos);
    retval->not .expr = expr;
    return retval;
}

ASTNode* AST_Create_or(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_OR, scope, pos);
    retval->or.left = left;
    retval->or.right = right;
    return retval;
}

ASTNode* AST_Create_and(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_AND, scope, pos);
    retval->and.left = left;
    retval->and.right = right;
    return retval;
}

ASTNode* AST_Create_eq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_EQ, scope, pos);
    retval->eq.left = left;
    retval->eq.right = right;
    return retval;
}

ASTNode* AST_Create_neq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NEQ, scope, pos);
    retval->neq.left = left;
    retval->neq.right = right;
    return retval;
}

ASTNode* AST_Create_gtr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_GTR, scope, pos);
    retval->gtr.left = left;
    retval->gtr.right = right;
    return retval;
}

ASTNode* AST_Create_gte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_GTE, scope, pos);
    retval->gte.left = left;
    retval->gte.right = right;
    return retval;
}

ASTNode* AST_Create_lsr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSR, scope, pos);
    retval->lsr.left = left;
    retval->lsr.right = right;
    return retval;
}

ASTNode* AST_Create_lte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LTE, scope, pos);
    retval->lte.left = left;
    retval->lte.right = right;
    return retval;
}

ASTNode* AST_Create_bitNot(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_NOT, scope, pos);
    retval->bitNot.expr = expr;
    return retval;
}

ASTNode* AST_Create_bitOr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_OR, scope, pos);
    retval->bitAnd.left = left;
    retval->bitAnd.right = right;
    return retval;
}

ASTNode* AST_Create_bitXor(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_XOR, scope, pos);
    retval->bitXor.left = left;
    retval->bitXor.right = right;
    return retval;
}

ASTNode* AST_Create_bitAnd(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_AND, scope, pos);
    retval->bitAnd.left = left;
    retval->bitAnd.right = right;
    return retval;
}

ASTNode* AST_Create_lshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSHIFT, scope, pos);
    retval->lshift.left = left;
    retval->lshift.right = right;
    return retval;
}

ASTNode* AST_Create_rshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_RSHIFT, scope, pos);
    retval->rshift.left = left;
    retval->rshift.right = right;
    return retval;
}

ASTNode* AST_Create_block(struct symbolNode* block, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BLOCK, scope, pos);
    retval->block.children = List_Create();
    retval->block.blockSymbol = block;
    return retval;
}

ASTNode* AST_Create_define(struct symbolNode* symbol, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DEFINE, scope, pos);
    retval->define.symbol = symbol;
    return retval;
}

ASTNode* AST_Create_assign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ASSIGN, scope, pos);
    retval->assign.left = left;
    retval->assign.right = right;
    return retval;
}

ASTNode* AST_Create_addAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADD_ASSIGN, scope, pos);
    retval->addAssign.left = left;
    retval->addAssign.right = right;
    return retval;
}

ASTNode* AST_Create_subAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SUB_ASSIGN, scope, pos);
    retval->subAssign.left = left;
    retval->subAssign.right = right;
    return retval;
}

ASTNode* AST_Create_multAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MULT_ASSIGN, scope, pos);
    retval->multAssign.left = left;
    retval->multAssign.right = right;
    return retval;
}

ASTNode* AST_Create_divAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DIV_ASSIGN, scope, pos);
    retval->divAssign.left = left;
    retval->divAssign.right = right;
    return retval;
}

ASTNode* AST_Create_modAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MOD_ASSIGN, scope, pos);
    retval->modAssign.left = left;
    retval->modAssign.right = right;
    return retval;
}

ASTNode* AST_Create_andAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_AND_ASSIGN, scope, pos);
    retval->andAssign.left = left;
    retval->andAssign.right = right;
    return retval;
}

ASTNode* AST_Create_orAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_OR_ASSIGN, scope, pos);
    retval->orAssign.left = left;
    retval->orAssign.right = right;
    return retval;
}

ASTNode* AST_Create_xorAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_XOR_ASSIGN, scope, pos);
    retval->xorAssign.left = left;
    retval->xorAssign.right = right;
    return retval;
}

ASTNode* AST_Create_lshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSHIFT_ASSIGN, scope, pos);
    retval->lshiftAssign.left = left;
    retval->lshiftAssign.right = right;
    return retval;
}

ASTNode* AST_Create_rshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_RSHIFT_ASSIGN, scope, pos);
    retval->rshiftAssign.left = left;
    retval->rshiftAssign.right = right;
    return retval;
}


ASTNode* AST_Create_if(struct astNode* condition, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_IF, scope, pos);
    retval->_if.condition = condition;
    retval->_if.bodyBlock = bodyBlock;
    retval->_if.elseBlock = elseBlock;
    return retval;
}

ASTNode* AST_Create_for(struct astNode* pre, struct astNode* condition, struct astNode* post, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FOR, scope, pos);
    retval->_for.pre = pre;
    retval->_for.condition = condition;
    retval->_for.post = post;
    retval->_for.bodyBlock = bodyBlock;
    retval->_for.elseBlock = elseBlock;
    return retval;
}

ASTNode* AST_Create_switch(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SWITCH, scope, pos);
    retval->_switch.cases = List_Create();
    retval->_switch.expr = expr;
    return retval;
}

ASTNode* AST_Create_case(struct astNode* block, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CASE, scope, pos);
    retval->_case.exprs = List_Create();
    retval->_case.block = block;
    return retval;
}

ASTNode* AST_Create_new(struct astNode* type, struct astNode* init, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NEW, scope, pos);
    retval->new.type = type;
    retval->new.init = init;
    return retval;
}

ASTNode* AST_Create_free(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FREE, scope, pos);
    retval->free.expr = expr;
    return retval;
}

ASTNode* AST_Create_defer(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DEFER, scope, pos);
    retval->defer.expr = expr;
    return retval;
}

ASTNode* AST_Create_break(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BREAK, scope, pos);
    return retval;
}

ASTNode* AST_Create_continue(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CONTINUE, scope, pos);
    return retval;
}

ASTNode* AST_Create_dot(struct astNode* container, struct astNode* identifier, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DOT, scope, pos);
    retval->dot.container = container;
    retval->dot.identifier = identifier;
    return retval;
}

ASTNode* AST_Create_sizeof(struct astNode* type, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SIZEOF, scope, pos);
    retval->_sizeof.type = type;
    return retval;
}

ASTNode* AST_Create_void(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_VOID, scope, pos);
    return retval;
}

ASTNode* AST_Create_cast(struct astNode* expr, struct astNode* type, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CAST, scope, pos);
    retval->cast.expr = expr;
    retval->cast.type = type;
    return retval;
}

ASTNode* AST_Create_paramlist(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_PARAMLIST, scope, pos);
    retval->paramlist.defines = List_Create();
    return retval;
}

ASTNode* AST_Create_function(struct astNode* domain, struct astNode* codomain, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FUNCTION, scope, pos);
    retval->function.domainType = domain;
    retval->function.codomainType = codomain;
    return retval;
}

ASTNode* AST_Create_addr(struct astNode* type, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADDR, scope, pos);
    retval->addr.type = type;
    return retval;
}

ASTNode* AST_Create_extern(struct symbolNode* externSymbol, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_EXTERN, scope, pos);
    retval->_extern.externSymbol = externSymbol;
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
    case AST_FUNCTION: {
        ASTNode* input = List_Get(type->children, 0);
        ASTNode* output = List_Get(type->children, 1);
        str += AST_TypeRepr(str, input);
        str += sprintf(str, "->");
        str += AST_TypeRepr(str, output);
        break;
    }
    case AST_ADDR: {
        ASTNode* child = List_Get(type->children, 0);
        str += sprintf(str, "&");
        if (child->visited) {
            str += sprintf(str, "..");
        } else {
            child->visited = true;
            str += AST_TypeRepr(str, child);
        }
    } break;
    case AST_ARRAY: {
        ASTNode* lengthDefine = List_Get(type->children, 0);
        SymbolNode* lengthSymbol = lengthDefine->data;
        ASTNode* lengthCode = lengthSymbol->def;
        ASTNode* dataDefine = List_Get(type->children, 1);
        SymbolNode* dataSymbol = dataDefine->data;
        ASTNode* dataType = dataSymbol->type;
        if (lengthCode->astType == AST_INT) {
            str += sprintf(str, "[%d]", (int)lengthCode->data);
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
    case AST_SLICE:
        return "AST_SLICE";
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
    case AST_ADD_ASSIGN:
        return "AST_ADD_ASSIGN";
    case AST_SUB_ASSIGN:
        return "AST_SUB_ASSIGN";
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
    case AST_FOR:
        return "AST_FOR";
    case AST_SWITCH:
        return "AST_SWITCH";
    case AST_CASE:
        return "AST_CASE";
    case AST_RETURN:
        return "AST_RETURN";
    case AST_BREAK:
        return "AST_BREAK";
    case AST_CONTINUE:
        return "AST_CONTINUE";
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
    case AST_ARRAY:
        return "AST_ARRAY";
    case AST_ENUM:
        return "AST_ENUM";
    case AST_EXTERN:
        return "AST_EXTERN";
    case AST_DEFER:
        return "AST_DEFER";
    default:
        return "Unknown ASTNode type";
    }
}
