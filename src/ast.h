// � 2021-2022 Joseph Shimel. All rights reserved.

#ifndef AST_H
#define AST_H

#include "./position.h"
#include "./symbol.h"
#include <stdint.h>

// A list of all types that an AST node can be. Determines how that node is treated.
enum astType {
    // Literals
    AST_IDENT,
    AST_INT,
    AST_CHAR,
    AST_TRUE,
    AST_FALSE,
    AST_REAL,
    AST_ARGLIST,
    AST_NAMED_ARG,
    AST_NOTHING,
    AST_ENUM_LITERAL,
    AST_ARRAY_LITERAL,
    AST_STRING,
    AST_UNDEF,
    AST_DOC,

    // Operations
    AST_ASSIGN,
    AST_OR,
    AST_AND,
    AST_BIT_OR,
    AST_BIT_XOR,
    AST_BIT_AND,
    AST_EQ,
    AST_NEQ,
    AST_GTR,
    AST_GTE,
    AST_LSR,
    AST_LTE,
    AST_LSHIFT,
    AST_RSHIFT,
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_MODULUS,
    AST_EXPONENT,
    AST_NOT,
    AST_NEG,
    AST_BIT_NOT,
    AST_ADDR_OF,
    AST_SIZEOF,
    AST_DEREF,
    AST_TRY,
    AST_CATCH,
    AST_ORELSE,
    AST_CALL,
    AST_INDEX,
    AST_SLICE,
    AST_DOT,
    AST_DEREF_DOT,
    AST_MAYBE,
    AST_CAST,
    AST_NEW,
    AST_FREE,
    AST_PAREN,
    // Operator assign
    AST_OR_ASSIGN,
    AST_AND_ASSIGN,
    AST_BIT_OR_ASSIGN,
    AST_BIT_XOR_ASSIGN,
    AST_BIT_AND_ASSIGN,
    AST_LSHIFT_ASSIGN,
    AST_RSHIFT_ASSIGN,
    AST_ADD_ASSIGN,
    AST_SUB_ASSIGN,
    AST_MULT_ASSIGN,
    AST_DIV_ASSIGN,
    AST_MOD_ASSIGN,
    AST_EXPONENT_ASSIGN,

    // Control flow
    AST_DEFINE,
    AST_BLOCK,
    AST_IF,
    AST_FOR,
    AST_CASE,
    AST_FIELD_CASE,
    AST_MAPPING,
    AST_FIELD_MAPPING,
    AST_RETURN,
    AST_BREAK,
    AST_CONTINUE,
    AST_UNREACHABLE,
    AST_DEFER,
    AST_ERRDEFER,

    // Types
    AST_VOID,
    AST_ADDR,
    AST_PRODUCT,
    AST_ARRAY,
    AST_ENUM,
    AST_UNION,
    AST_ERROR,
    AST_INFER_ERROR,
    AST_FUNCTION,
    AST_EXTERN
};

struct astNode;

// The following structs are used for data for specific sorts of AST nodes. Check the constructors for which one is used
typedef struct astNode_ident {
    char* data;
} astNode_ident;

typedef struct astNode_int {
    int64_t data;
} astNode_int;

typedef struct astNode_string {
    char* data;
} astNode_string;

typedef struct astNode_char {
    char* data;
} astNode_char;

typedef struct astNode_real {
    double data;
} astNode_real;

typedef struct astNode_arglist {
    List* args; // list of astnodes representing the arguments of the arglist, may be different types and even named
} astNode_arglist;

typedef struct astNode_namedArg {
    char* name; // field/param name of arg
    struct astNode* expr; // expression this argument is set to
} astNode_namedArg;

typedef struct astNode_arrayLiteral {
    List* members; // members in the array literal, all of which are the same type
} astNode_arrayLiteral;

typedef struct astNode_enumLiteral {
    int64_t tag;
    struct astNode* expr;
} astNode_enumLiteral;

typedef struct astNode_taggedUnop {
    int64_t tag;
    struct astNode* expr;
} astNode_taggedUnop;

typedef struct astNode_taggedBinop {
    int64_t tag;
    struct astNode* left;
    struct astNode* right;
} astNode_taggedBinop;

typedef struct astNode_unop {
    struct astNode* expr;
} astNode_unop;

typedef struct astNode_binop {
    struct astNode* left;
    struct astNode* right;
} astNode_binop;

typedef struct astNode_call {
    struct astNode* left;
    struct astNode* right;
    struct astNode* fnType;
} astNode_call;

typedef struct astNode_dot {
    struct astNode* left;
    struct astNode* right;
    struct symbolNode* symbol;
    bool assign;
    bool dotChainHead;
} astNode_dot;

typedef struct astNode_slice {
    struct astNode* arrayExpr;
    struct astNode* lowerBound;
    struct astNode* upperBound;
} astNode_slice;

typedef struct astNode_block {
    List* children;
    struct symbolNode* symbol; // This block scope, while ASTs scope is parent scope
    bool returnEval; // Does this block produce the return value for a function?
} astNode_block;

typedef struct astNode_defer {
    struct astNode* statement;
    int deferID;
} astNode_defer;

typedef struct astNode_define {
    struct symbolNode* symbol;
} astNode_define;

typedef struct astNode_if { // no need for separate ifelse ast type!
    struct astNode* condition;
    struct astNode* bodyBlock;
    struct astNode* elseBlock;
} astNode_if;

typedef struct astNode_for {
    struct astNode* pre;
    struct astNode* condition;
    struct astNode* post;
    struct astNode* bodyBlock;
    struct astNode* elseBlock;
} astNode_for;

typedef struct astNode_case {
    struct astNode* expr;
    List* mappings;
} astNode_case;

typedef struct astNode_mapping {
    List* exprs;
    struct astNode* expr;
} astNode_mapping;

typedef struct astNode_fieldMapping {
    List* exprs;
    struct astNode* expr;
    int64_t tag;
} astNode_fieldMapping;

// for product type literals, modules, arrays, enums, a lot!
typedef struct astNode_product {
    List* defines;
} astNode_product;

typedef struct astNode_enum {
    List* defines;
    bool wasAnError;
    struct astNode* expr; // Used for infer errors
} astNode_enum;

typedef struct astNode_function {
    struct astNode* domainType;
    struct astNode* codomainType;
} astNode_function;

typedef struct astNode_extern {
    struct symbolNode* symbol;
} astNode_extern;

// Used to represent a node in an Abstract Syntax Tree. ASTs are used for expressions and for types
typedef struct astNode {
    enum astType astType; // The type of the AST node
    struct symbolNode* scope; // The scope that this AST is constrained within
    struct position pos; // Position the AST is found in the source text

    bool visited; // Used during traversal, particularly for ASTs that represent types
    bool isValid; // Whether this AST has been checked for validity
    bool isConst; // For type ASTs, whether or not the type is compile-time constant

    bool containsReturn; // AST contains a return node
    bool containsContinue; // AST contains a continue node
    bool containsBreak; // AST contains a break node

    struct astNode* type; // The type of the AST expression
    struct astNode* originalType; // Is never expanded, used to print error messages and documentation

	// Data stored in AST
    union {
        astNode_ident ident;
        astNode_int _int;
        astNode_string string;
        astNode_char _char;
        astNode_real real;
        astNode_arglist arglist;
        astNode_namedArg namedArg;
        astNode_arrayLiteral arrayLiteral;
        astNode_enumLiteral enumLiteral;
        astNode_taggedUnop taggedUnop;
        astNode_taggedBinop taggedBinop;
        astNode_unop unop;
        astNode_binop binop;
        astNode_call call;
        astNode_dot dot;
        astNode_slice slice;
        astNode_block block;
        astNode_defer defer;
        astNode_define define;
        astNode_if _if;
        astNode_for _for;
        astNode_case _case;
        astNode_mapping mapping;
        astNode_fieldMapping fieldMapping;
        astNode_product product;
        astNode_enum _enum;
        astNode_function function;
        astNode_extern _extern;
    };
} ASTNode;

// Binary operator constructors will follow this type
typedef ASTNode* (*BinopConstructor)(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);

// Some well-known types and constants
const ASTNode* INT8_TYPE;
const ASTNode* INT16_TYPE;
const ASTNode* INT32_TYPE;
const ASTNode* CONST_INT64_TYPE;
const ASTNode* INT64_TYPE;
const ASTNode* CONST_STRING_TYPE;
const ASTNode* STRING_TYPE;
const ASTNode* STRING_ARR_TYPE;
const ASTNode* CONST_CHAR_TYPE;
const ASTNode* CHAR_TYPE;
const ASTNode* REAL32_TYPE;
const ASTNode* REAL64_TYPE;
const ASTNode* CONST_BOOL_TYPE;
const ASTNode* BOOL_TYPE;
const ASTNode* TYPE_TYPE;
const ASTNode* PACKAGE_TYPE;
const ASTNode* UNDEF_TYPE;
const ASTNode* VOID_ADDR_TYPE;
const ASTNode* VOID_TYPE;
const ASTNode* MAYBE_VOID_TYPE;
const ASTNode* TRUE_AST;
const ASTNode* FALSE_AST;
const ASTNode* NOTHING_AST;

int AST_TypeRepr(char* str, ASTNode* type);
char* AST_GetString(enum astType type);
void AST_Print(ASTNode* root, char* prefix, char* childrenPrefix);

ASTNode* AST_GetArrayDataType(ASTNode* type);
int64_t AST_GetArrayLength(ASTNode* type);
ASTNode* AST_GetArrayLengthAST(ASTNode* type);
ASTNode* AST_GetArrayDataTypeAddr(ASTNode* type);
BinopConstructor AST_GetBinopConstructor(enum astType astType);
ASTNode* AST_CreateArrayTypeNode(ASTNode* baseType, int length, struct position pos);
ASTNode* AST_CreateMaybeType(ASTNode* somethingBaseType);

void AST_Init();

ASTNode* AST_Create_ident(char* data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_int(int64_t data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_char(char* data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_true(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_false(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_real(double data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_arglist(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_namedArg(char* name, struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_nothing(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_enumLiteral(int64_t tag, struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_arrayLiteral(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_string(char* data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_undef(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_assign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_or(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_and(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitOr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitXor(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitAnd(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_eq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_neq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_gtr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_gte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lsr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_rshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_add(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_subtract(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_multiply(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_divide(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_modulus(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_exponent(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_neg(struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitNot(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_not(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_addrOf(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_sizeof(struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_deref(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_try(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_catch(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_orelse(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_call(struct astNode* functionExpr, struct astNode* arglist, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_index(struct astNode* arrayExpr, struct astNode* subscript, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_slice(struct astNode* arrayExpr, struct astNode* lowerBound, struct astNode* upperBound, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_dot(struct astNode* container, struct astNode* identifier, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_maybe(struct astNode* container, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_cast(struct astNode* expr, struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_new(struct astNode* type, struct astNode* init, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_free(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_paren(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_orAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_andAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitOrAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitXorAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitAndAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_rshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_addAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_subAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_multAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_divAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_modAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_exponentAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_define(struct symbolNode* symbol, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_block(struct symbolNode* block, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_if(struct astNode* condition, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_for(struct astNode* pre, struct astNode* condition, struct astNode* post, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_case(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_mapping(struct astNode* block, List* exprs, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_fieldMapping(struct astNode* block, List* exprs, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_return(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_break(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_continue(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_unreachable(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_defer(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_errdefer(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_void(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_addr(struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_product(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_array(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_enum(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_union(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_error(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_inferError(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_function(struct astNode* domain, struct astNode* codomain, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_extern(struct symbolNode* externSymbol, struct symbolNode* scope, struct position pos);

#endif
