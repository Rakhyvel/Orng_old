/*
AST stands for Abstract Syntax Tree. This is a data structure used to organize
and give meaning to the token read in from the file. It is similar to a parse
tree, but slightly different in that it doesn't have redundant nodes.
*/

#ifndef AST_H
#define AST_H

#include "./position.h"
#include "./symbol.h"
#include <stdint.h>

// A list of all types that an AST node can be. Determines how that node is treated.
enum astType {
    // Literals
    AST_IDENT,
    AST_CALL,
    AST_INT,
    AST_STRING,
    AST_CHAR,
    AST_REAL,
    AST_NOTHING,
    AST_TRUE,
    AST_FALSE,
    AST_ARGLIST,
    AST_NAMED_ARG,
    AST_ARRAY_LITERAL,
    AST_UNION_LITERAL,
    AST_UNDEF,
    AST_DOC,
    // Math
    AST_NEG,
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_MODULUS,
    AST_PAREN,
    // Memory
    AST_DEREF,
    AST_INDEX,
    AST_SLICE,
    AST_ADDROF,
    AST_ORELSE,
    // Boolean
    AST_NOT,
    AST_OR,
    AST_AND,
    // Comparison
    AST_EQ,
    AST_NEQ,
    AST_GTR,
    AST_GTE,
    AST_LSR,
    AST_LTE,
    // Bitwise
    AST_BIT_NOT,
    AST_BIT_OR,
    AST_BIT_XOR,
    AST_BIT_AND,
    AST_LSHIFT,
    AST_RSHIFT,
    // Statements
    AST_BLOCK,
    AST_DEFINE,
    AST_ASSIGN,
    AST_ADD_ASSIGN,
    AST_SUB_ASSIGN,
    AST_MULT_ASSIGN,
    AST_DIV_ASSIGN,
    AST_MOD_ASSIGN,
    AST_OR_ASSIGN,
    AST_AND_ASSIGN,
    AST_BIT_OR_ASSIGN,
    AST_BIT_AND_ASSIGN,
    AST_BIT_XOR_ASSIGN,
    AST_LSHIFT_ASSIGN,
    AST_RSHIFT_ASSIGN,
    AST_IF,
    AST_FOR,
    AST_CASE,
    AST_FIELD_CASE,
    AST_MAPPING,
    AST_FIELD_MAPPING,
    AST_RETURN,
    AST_NEW, // Replace with allocator method
    AST_FREE, // Replace with allocator method
    AST_DEFER,
    AST_BREAK,
    AST_CONTINUE,
    // Module
    AST_DOT,
    AST_DEREF_DOT,
    // Types
    AST_SIZEOF,
    AST_VOID,
    AST_CAST,
    AST_PARAMLIST,
    AST_UNIONSET,
    AST_FUNCTION,
    AST_ADDR,
    AST_ARRAY,
    AST_EXTERN
};

// When printing out, should types be unwrapped or not
bool doDefTypes;

struct astNode;

typedef struct astNode_ident {
    char* data;
} astNode_ident;

typedef struct astNode_int {
    int64_t data;
} astNode_int;

typedef struct astNode_string {
    char* data;
    int stringID;
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

typedef struct astNode_unionLiteral {
    int tag;
    struct astNode* expr;
} astNode_unionLiteral;

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
} astNode_dot;

typedef struct astNode_slice {
    struct astNode* arrayExpr;
    struct astNode* lowerBound;
    struct astNode* upperBound;
} astNode_slice;

typedef struct astNode_block {
    List* children;
    struct symbolNode* symbol; // The symbol node for this block ast, possibly unneeded?
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
    int tag;
} astNode_fieldMapping;

// for parameter lists, modules, structs, arrays, unions, a lot!
typedef struct astNode_paramlist {
    List* defines;
} astNode_paramlist;

typedef struct astNode_unionset {
    List* defines;
} astNode_unionset;

typedef struct astNode_function {
    struct astNode* domainType;
    struct astNode* codomainType;
    // field that says if function is stateless?
    // field for if the type is const
} astNode_function;

typedef struct astNode_extern {
    struct symbolNode* symbol;
} astNode_extern;

/* Define the structure of an AST Node */
typedef struct astNode {
    enum astType astType; // The type of the AST node
    struct symbolNode* scope; // The scope that this AST is constrained within
    struct position pos;

    bool visited;
    bool isValid; // TODO: Remove?

    bool isConst; // TODO: remove and put into type asts

    // if subtree contains any of these
    bool containsReturn;
    bool containsContinue;
    bool containsBreak;

    struct astNode* type; // The type of the AST Node

    union {
        astNode_ident ident;
        astNode_int _int;
        astNode_string string;
        astNode_char _char;
        astNode_real real;
        astNode_arglist arglist;
        astNode_namedArg namedArg;
        astNode_arrayLiteral arrayLiteral;
        astNode_unionLiteral unionLiteral;
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
        astNode_paramlist paramlist;
        astNode_paramlist unionset;
        astNode_function function;
        astNode_extern _extern;
    };
} ASTNode;

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

const ASTNode* TRUE_AST;
const ASTNode* FALSE_AST;
const ASTNode* NOTHING_AST;

ASTNode* AST_Create_ident(char* data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_call(struct astNode* functionExpr, struct astNode* arglist, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_int(int64_t data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_string(char* data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_char(char data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_real(double data, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_arglist(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_namedArg(char* name, struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_arrayLiteral(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_unionLiteral(int tag, struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_true(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_false(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_nothing(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_undef(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_neg(struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_add(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_subtract(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_multiply(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_divide(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_modulus(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_orelse(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_paren(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_deref(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_index(struct astNode* arrayExpr, struct astNode* subscript, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_slice(struct astNode* arrayExpr, struct astNode* lowerBound, struct astNode* upperBound, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_not(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_or(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_and(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_eq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_neq(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_gtr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_gte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lsr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lte(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitNot(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitOr(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitXor(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_bitAnd(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_rshift(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_block(struct symbolNode* block, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_define(struct symbolNode* symbol, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_assign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_addAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_subAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_multAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_divAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_modAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_andAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_orAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_xorAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_lshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_rshiftAssign(struct astNode* left, struct astNode* right, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_if(struct astNode* condition, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_for(struct astNode* pre, struct astNode* condition, struct astNode* post, struct astNode* bodyBlock, struct astNode* elseBlock, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_case(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_mapping(struct astNode* block, List* exprs, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_fieldMapping(struct astNode* block, List* exprs, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_new(struct astNode* type, struct astNode* init, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_free(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_return(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_defer(struct astNode* expr, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_break(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_continue(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_dot(struct astNode* container, struct astNode* identifier, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_sizeof(struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_void(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_cast(struct astNode* expr, struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_paramlist(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_unionset(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_array(struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_function(struct astNode* domain, struct astNode* codomain, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_addr(struct astNode* type, struct symbolNode* scope, struct position pos);
ASTNode* AST_Create_extern(struct symbolNode* externSymbol, struct symbolNode* scope, struct position pos);

int getArrayLength(ASTNode* type);
ASTNode* getArrayDataType(ASTNode* type);
ASTNode* getArrayDataTypeAddr(ASTNode* type);
ASTNode* createArrayTypeNode(ASTNode* baseType, int length);
ASTNode* AST_Create(enum astType type, SymbolNode* scope, struct position pos);
void AST_Print(ASTNode* root, char* prefix, char* childrenPrefix);
int AST_TypeRepr(char* str, ASTNode* type);
char* AST_GetString(enum astType type);

#endif
