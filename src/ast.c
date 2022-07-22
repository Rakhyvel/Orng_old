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

const ASTNode* TRUE_AST = NULL;
const ASTNode* FALSE_AST = NULL;
const ASTNode* NOTHING_AST = NULL;

bool doDefTypes = false;

// Generates common ptr-to-array types
ASTNode* createArrayTypeNode(ASTNode* baseType, int length)
{
    ASTNode* array = AST_Create_array(NULL, (Position) { NULL, 0, 0, 0 });

    SymbolNode* lengthSymbol = Symbol_Create("length", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* lengthDefine = AST_Create_define(lengthSymbol, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* lengthType = AST_Create_ident("Int", NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* lengthCode;
    if (length != -1) {
        lengthCode = AST_Create_int(length, NULL, (Position) { NULL, 0, 0, 0 });
    } else {
        lengthCode = AST_Create_undef(NULL, (Position) { NULL, 0, 0, 0 });
    }
    lengthSymbol->def = lengthCode;
    lengthSymbol->type = lengthType;
    lengthType->isConst = true;

    SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* dataDefine = AST_Create_define(dataSymbol, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* dataType = AST_Create_addr(baseType, NULL, (Position) { NULL, 0, 0, 0 });
    ASTNode* dataCode = AST_Create_undef(NULL, (Position) { NULL, 0, 0, 0 });
    dataSymbol->def = dataCode;
    dataSymbol->type = dataType;

    List_Append(array->paramlist.defines, lengthDefine);
    List_Append(array->paramlist.defines, dataDefine);

    return array;
}

void AST_Init()
{
    INT8_TYPE = AST_Create_ident("Int8", NULL, (Position) { NULL, 0, 0, 0 });
    INT16_TYPE = AST_Create_ident("Int16", NULL, (Position) { NULL, 0, 0, 0 });
    INT32_TYPE = AST_Create_ident("Int32", NULL, (Position) { NULL, 0, 0, 0 });
    CONST_INT64_TYPE = AST_Create_ident("Int64", NULL, (Position) { NULL, 0, 0, 0 });
    INT64_TYPE = AST_Create_ident("Int64", NULL, (Position) { NULL, 0, 0, 0 });
    CONST_CHAR_TYPE = AST_Create_ident("Char", NULL, (Position) { NULL, 0, 0, 0 });
    CHAR_TYPE = AST_Create_ident("Char", NULL, (Position) { NULL, 0, 0, 0 });
    CONST_STRING_TYPE = createArrayTypeNode(CHAR_TYPE, -1, true);
    STRING_TYPE = createArrayTypeNode(CHAR_TYPE, -1, false);
    STRING_ARR_TYPE = createArrayTypeNode(STRING_TYPE, -1, true);
    REAL32_TYPE = AST_Create_ident("Real32", NULL, (Position) { NULL, 0, 0, 0 });
    REAL64_TYPE = AST_Create_ident("Real64", NULL, (Position) { NULL, 0, 0, 0 });
    CONST_BOOL_TYPE = AST_Create_ident("Bool", NULL, (Position) { NULL, 0, 0, 0 });
    BOOL_TYPE = AST_Create_ident("Bool", NULL, (Position) { NULL, 0, 0, 0 });
    TYPE_TYPE = AST_Create_ident("Type", NULL, (Position) { NULL, 0, 0, 0 });
    PACKAGE_TYPE = AST_Create_ident("Package", NULL, (Position) { NULL, 0, 0, 0 });
    UNDEF_TYPE = AST_Create_undef(NULL, (Position) { NULL, 0, 0, 0 });
    VOID_ADDR_TYPE = AST_Create_addr(AST_Create_paramlist(NULL, (Position) { NULL, 0, 0, 0 }), NULL, (Position) { NULL, 0, 0, 0 });
    VOID_TYPE = AST_Create_void(NULL, (Position) { NULL, 0, 0, 0 });
    TRUE_AST = AST_Create_true(NULL, (Position) { NULL, 0, 0, 0 });
    FALSE_AST = AST_Create_false(NULL, (Position) { NULL, 0, 0, 0 });
    NOTHING_AST = AST_Create_nothing(NULL, (Position) { NULL, 0, 0, 0 });
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
    retval->call.left = functionExpr;
    retval->call.right = arglist;
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

ASTNode* AST_Create_char(char* data, struct symbolNode* scope, struct position pos)
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

ASTNode* AST_Create_unionLiteral(int tag, struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_UNION_LITERAL, scope, pos);
    retval->unionLiteral.tag = tag;
    retval->unionLiteral.expr = expr;
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

ASTNode* AST_Create_nothing(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NOTHING, scope, pos);
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
    retval->unop.expr = right;
    return retval;
}

ASTNode* AST_Create_add(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADD, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_subtract(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SUBTRACT, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_multiply(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MULTIPLY, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_divide(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DIVIDE, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_modulus(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MODULUS, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_orelse(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ORELSE, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_paren(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_PAREN, scope, pos);
    retval->arglist.args = List_Create();
    List_Append(retval->arglist.args, expr);
    return retval;
}

ASTNode* AST_Create_deref(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DEREF, scope, pos);
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_index(struct astNode* arrayExpr, struct astNode* subscript, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_INDEX, scope, pos);
    retval->binop.left = arrayExpr;
    retval->binop.right = subscript;
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
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_addrOf(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADDROF, scope, pos);
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_or(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_OR, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_and(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_AND, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_eq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_EQ, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_neq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NEQ, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_gtr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_GTR, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_gte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_GTE, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_lsr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSR, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_lte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LTE, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_isTag(struct astNode* expr, int tag, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_IS_TAG, scope, pos);
    retval->unionLiteral.expr = expr;
    retval->unionLiteral.tag = tag;
    return retval;
}

ASTNode* AST_Create_isntTag(struct astNode* expr, int tag, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ISNT_TAG, scope, pos);
    retval->unionLiteral.expr = expr;
    retval->unionLiteral.tag = tag;
    return retval;
}

ASTNode* AST_Create_bitNot(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_NOT, scope, pos);
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_bitOr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_OR, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_bitXor(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_XOR, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_bitAnd(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_AND, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_lshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSHIFT, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_rshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_RSHIFT, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_block(struct symbolNode* block, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BLOCK, scope, pos);
    retval->block.children = List_Create();
    retval->block.symbol = block;
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
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_addAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ADD_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_subAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SUB_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_multAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MULT_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_divAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DIV_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_modAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MOD_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_andAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_AND_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_orAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_OR_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_bitAndAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_AND_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_bitOrAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_OR_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_bitXorAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_BIT_XOR_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_lshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_LSHIFT_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
    return retval;
}

ASTNode* AST_Create_rshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_RSHIFT_ASSIGN, scope, pos);
    retval->binop.left = left;
    retval->binop.right = right;
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

ASTNode* AST_Create_case(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_CASE, scope, pos);
    retval->_case.mappings = List_Create();
    retval->_case.expr = expr;
    return retval;
}

ASTNode* AST_Create_mapping(struct astNode* expr, List* exprs, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_MAPPING, scope, pos);
    retval->mapping.exprs = exprs;
    retval->mapping.expr = expr;
    return retval;
}

ASTNode* AST_Create_fieldMapping(struct astNode* expr, List* exprs, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FIELD_MAPPING, scope, pos);
    retval->mapping.exprs = exprs;
    retval->mapping.expr = expr;
    return retval;
}

ASTNode* AST_Create_new(struct astNode* type, struct astNode* init, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_NEW, scope, pos);
    retval->binop.left = type;
    retval->binop.right = init;
    return retval;
}

ASTNode* AST_Create_free(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_FREE, scope, pos);
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_return(struct astNode* expr, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_RETURN, scope, pos);
    retval->unop.expr = expr;
    return retval;
}

ASTNode* AST_Create_defer(struct astNode* statement, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DEFER, scope, pos);
    retval->defer.statement = statement;
    retval->defer.deferID = scope->defers->size;
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
    retval->dot.left = container;
    retval->dot.right = identifier;
    return retval;
}

ASTNode* AST_Create_maybe(struct astNode* container, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_DOT, scope, pos);
    retval->dot.left = container;
    retval->dot.right = AST_Create_ident("something", scope, pos);
    return retval;
}

ASTNode* AST_Create_sizeof(struct astNode* type, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_SIZEOF, scope, pos);
    retval->unop.expr = type;
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
    retval->binop.left = expr;
    retval->binop.right = type;
    return retval;
}

ASTNode* AST_Create_paramlist(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_PARAMLIST, scope, pos);
    retval->paramlist.defines = List_Create();
    return retval;
}

ASTNode* AST_Create_unionset(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_UNIONSET, scope, pos);
    retval->paramlist.defines = List_Create();
    return retval;
}

ASTNode* AST_Create_array(struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_ARRAY, scope, pos);
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
    retval->unop.expr = type;
    return retval;
}

ASTNode* AST_Create_extern(struct symbolNode* externSymbol, struct symbolNode* scope, struct position pos)
{
    ASTNode* retval = AST_Create(AST_EXTERN, scope, pos);
    retval->_extern.symbol = externSymbol;
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
        printf("%s%s [%d]\n", prefix, AST_GetString(root->astType), root->_int.data);
        break;
    case AST_STRING:
        printf("%s%s [%s]\n", prefix, AST_GetString(root->astType), root->_char.data);
        break;
    case AST_CHAR:
        printf("%s%s [%c]\n", prefix, AST_GetString(root->astType), root->_char.data);
        break;
    case AST_DEFINE:
        printf("%s%s [0x%p]\n", prefix, AST_GetString(root->astType), root->define.symbol);
        Symbol_Print(root->define.symbol, prefix, childrenPrefix);
        break;
    case AST_BLOCK:
        printf("%s%s [0x%p]\n", prefix, AST_GetString(root->astType), root->block.symbol);
        break;
    case AST_IDENT:
        printf("%s%s [%s]\n", prefix, AST_GetString(root->astType), root->ident.data);
        break;
    default:
        printf("%s%s []\n", prefix, AST_GetString(root->astType));
    }
}

int AST_TypeRepr(char* str, ASTNode* type)
{
    char* origStr = str;
    if (type->isConst) {
        str += sprintf(str, ":");
    }
    switch (type->astType) {
    case AST_VOID:
        str += sprintf(str, "()");
        break;
    case AST_IDENT:
        str += sprintf(str, "%s", type->ident.data);
        break;
    case AST_DEFINE:
        SymbolNode* symbol = type->define.symbol;
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
        for (struct listElem* elem = List_Begin(type->paramlist.defines); elem != List_End(type->paramlist.defines); elem = elem->next) {
            ASTNode* param = elem->data;
            str += AST_TypeRepr(str, param);
            if (elem->next == List_End(type->paramlist.defines)) {
                str += sprintf(str, ")");
            } else {
                str += sprintf(str, ", ");
            }
        }
        break;
    case AST_UNIONSET:
        str += sprintf(str, "(|");
        for (struct listElem* elem = List_Begin(type->unionset.defines); elem != List_End(type->unionset.defines); elem = elem->next) {
            ASTNode* param = elem->data;
            str += AST_TypeRepr(str, param);
            if (elem->next == List_End(type->unionset.defines)) {
                str += sprintf(str, ")");
            } else {
                str += sprintf(str, ", ");
            }
        }
        break;
    case AST_FUNCTION: {
        ASTNode* input = type->function.domainType;
        ASTNode* output = type->function.codomainType;
        str += AST_TypeRepr(str, input);
        str += sprintf(str, "->");
        str += AST_TypeRepr(str, output);
        break;
    }
    case AST_ADDR: {
        ASTNode* child = type->unop.expr;
        str += sprintf(str, "&");
        str += sprintf(str, "..");
        // str += AST_TypeRepr(str, child);
    } break;
    case AST_ARRAY: {
        ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
        SymbolNode* lengthSymbol = lengthDefine->define.symbol;
        ASTNode* lengthCode = lengthSymbol->def;
        ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
        SymbolNode* dataSymbol = dataDefine->define.symbol;
        ASTNode* dataType = dataSymbol->type;
        if (lengthCode->astType == AST_INT) {
            str += sprintf(str, "[%d]", (int)lengthCode->_int.data);
        } else {
            str += sprintf(str, "[]");
        }
        str += AST_TypeRepr(str, dataType);
    } break;
    case AST_EXTERN: {
        SymbolNode* var = type->_extern.symbol;
        str += AST_TypeRepr(str, var->type);
    } break;
    case AST_UNDEF: {
        str += sprintf(str, "Undef");
    } break;
    case AST_DOT: {
        ASTNode* left = type->binop.left;
        ASTNode* right = type->binop.right;
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
    case AST_NOTHING:
        return "AST_NOTHING";
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
    case AST_FOR:
        return "AST_FOR";
    case AST_CASE:
        return "AST_CASE";
    case AST_MAPPING:
        return "AST_MAPPING";
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
    case AST_EXTERN:
        return "AST_EXTERN";
    case AST_DEFER:
        return "AST_DEFER";
    default:
        return "Unknown ASTNode type";
    }
}

ASTNode* getArrayLengthAST(ASTNode* type)
{
    ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
    SymbolNode* lengthSymbol = lengthDefine->define.symbol;
    ASTNode* lengthCode = lengthSymbol->def;
    return lengthCode;
}

int getArrayLength(ASTNode* type)
{
    ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
    SymbolNode* lengthSymbol = lengthDefine->define.symbol;
    ASTNode* lengthCode = lengthSymbol->def;
    return lengthCode->astType == AST_INT ? lengthCode->_int.data : -1;
}

ASTNode* getArrayDataType(ASTNode* type)
{
    ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
    SymbolNode* dataSymbol = dataDefine->define.symbol;
    ASTNode* dataType = dataSymbol->type->unop.expr;
    return dataType;
}

ASTNode* getArrayDataTypeAddr(ASTNode* type)
{
    ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
    SymbolNode* dataSymbol = dataDefine->define.symbol;
    ASTNode* dataType = dataSymbol->type;
    return dataType;
}