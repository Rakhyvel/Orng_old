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
    AST_ARGLIST,
    AST_NAMED_ARG,
    AST_ARRAY_LITERAL,
    AST_TRUE,
    AST_FALSE,
    AST_UNDEF,
    AST_NULL,
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
    AST_ADDROF,
    AST_DEREF,
    AST_INDEX,
    AST_SLICE,
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
    AST_AND_ASSIGN,
    AST_OR_ASSIGN,
    AST_XOR_ASSIGN,
    AST_LSHIFT_ASSIGN,
    AST_RSHIFT_ASSIGN,
    AST_IF,
    AST_IFELSE,
    AST_FOR,
    AST_SWITCH,
    AST_CASE,
    AST_RETURN,
    AST_NEW, // Replace with allocator method
    AST_FREE, // Replace with allocator method
    AST_DEFER,
    AST_BREAK,
    AST_CONTINUE,
    // Module
    AST_DOT,
    // Types
    AST_SIZEOF,
    AST_VOID,
    AST_CAST,
    AST_PARAMLIST,
    AST_FUNCTION,
    AST_ADDR,
    AST_ARRAY,
    AST_ENUM,
    AST_EXTERN
};

// When printing out, should types be unwrapped or not
bool doDefTypes;

struct astNode;

typedef struct astNode_ident {
    char* data;
} astNode_ident;

typedef struct astNode_call {
    struct astNode* functionExpr; // expression representing a function somehow
    struct astNode* arglist;
} astNode_call;

typedef struct astNode_int {
    int64_t data;
} astNode_int;

typedef struct astNode_string {
    char* data;
    // Possible a field for the string id number?
} astNode_string;

typedef struct astNode_char {
    char data;
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

typedef struct astNode_arrayliteral {
    List* members; // members in the array literal, all of which are the same type
} astNode_arrayliteral;

typedef struct astNode_true {
    int no_data;
} astNode_true;

typedef struct astNode_false {
    int no_data;
} astNode_false;

typedef struct astNode_null {
    int no_data;
} astNode_null;

typedef struct astNode_undef {
    int no_data;
} astNode_undef;

typedef struct astNode_neg {
    struct astNode* right;
} astNode_neg;

typedef struct astNode_add {
    struct astNode* left;
    struct astNode* right;
} astNode_add;

typedef struct astNode_subtract {
    struct astNode* left;
    struct astNode* right;
} astNode_subtract;

typedef struct astNode_multiply {
    struct astNode* left;
    struct astNode* right;
} astNode_multiply;

typedef struct astNode_divide {
    struct astNode* left;
    struct astNode* right;
} astNode_divide;

typedef struct astNode_modulus {
    struct astNode* left;
    struct astNode* right;
} astNode_modulus;

typedef struct astNode_paren {
    struct astNode* expr;
} astNode_paren;

typedef struct astNode_addrOf {
    struct astNode* lvalue;
} astNode_addrOf;

typedef struct astNode_deref {
    struct astNode* expr;
} astNode_deref;

typedef struct astNode_index {
    struct astNode* arrayExpr;
    struct astNode* subscript;
} astNode_index;

typedef struct astNode_slice {
    struct astNode* arrayExpr;
    struct astNode* lowerBound;
    struct astNode* upperBound;
} astNode_slice;

typedef struct astNode_not {
    struct astNode* expr;
} astNode_not;

typedef struct astNode_or {
    struct astNode* left;
    struct astNode* right;
} astNode_or;

typedef struct astNode_and {
    struct astNode* left;
    struct astNode* right;
} astNode_and;

typedef struct astNode_eq {
    struct astNode* left;
    struct astNode* right;
} astNode_eq;

typedef struct astNode_neq {
    struct astNode* left;
    struct astNode* right;
} astNode_neq;

typedef struct astNode_gtr {
    struct astNode* left;
    struct astNode* right;
} astNode_gtr;

typedef struct astNode_gte {
    struct astNode* left;
    struct astNode* right;
} astNode_gte;

typedef struct astNode_lsr {
    struct astNode* left;
    struct astNode* right;
} astNode_lsr;

typedef struct astNode_lte {
    struct astNode* left;
    struct astNode* right;
} astNode_lte;

typedef struct astNode_bitNot {
    struct astNode* expr;
} astNode_bitNot;

typedef struct astNode_bitOr {
    struct astNode* left;
    struct astNode* right;
} astNode_bitOr;

typedef struct astNode_bitXor {
    struct astNode* left;
    struct astNode* right;
} astNode_bitXor;

typedef struct astNode_bitAnd {
    struct astNode* left;
    struct astNode* right;
} astNode_bitAnd;

typedef struct astNode_lshift {
    struct astNode* left;
    struct astNode* right;
} astNode_lshift;

typedef struct astNode_rshift {
    struct astNode* left;
    struct astNode* right;
} astNode_rshift;

typedef struct astNode_block {
    List* children;
    SymbolNode* blockSymbol; // The symbol node for this block ast, possibly unneeded?
} astNode_block;

typedef struct astNode_define {
    SymbolNode* symbol;
} astNode_define;

typedef struct astNode_assign {
    struct astNode* left;
    struct astNode* right;
} astNode_assign;

typedef struct astNode_addAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_addAssign;

typedef struct astNode_subAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_subAssign;

typedef struct astNode_multAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_multAssign;

typedef struct astNode_divAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_divAssign;

typedef struct astNode_modAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_modAssign;

typedef struct astNode_andAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_andAssign;

typedef struct astNode_orAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_orAssign;

typedef struct astNode_xorAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_xorAssign;

typedef struct astNode_lshiftAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_lshiftAssign;

typedef struct astNode_rshiftAssign {
    struct astNode* left;
    struct astNode* right;
} astNode_rshiftAssign;

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

typedef struct astNode_switch {
    struct astNode* expr;
    List* cases;
} astNode_switch;

typedef struct astNode_case {
    List* exprs;
    struct astNode* block;
} astNode_case;

typedef struct astNode_return {
    struct astNode* expr;
} astNode_return;

typedef struct astNode_new {
    struct astNode* type;
    struct astNode* init;
} astNode_new;

typedef struct astNode_free {
    struct astNode* free;
} astNode_free;

typedef struct astNode_defer {
    struct astNode* expr;
} astNode_defer;

typedef struct astNode_break {
    int no_data;
} astNode_break;

typedef struct astNode_continue {
    int no_data;
} astNode_continue;

typedef struct astNode_dot {
    struct astNode* container;
    struct astNode* identifier;
} astNode_dot;

typedef struct astNode_sizeof {
    struct astNode* type;
} astNode_sizeof;

typedef struct astNode_void {
    int no_data;
} astNode_void;

typedef struct astNode_cast {
    struct astNode* expr;
    struct astNode* type;
} astNode_cast;

// for parameter lists, modules, structs, arrays, unions, a lot!
typedef struct astNode_paramlist {
    List* defines;
} astNode_paramlist;

typedef struct astNode_function {
    struct astNode* domainType;
    struct astNode* codomainType;
    // field that says if function is tateless?
} astNode_function;

typedef struct astNode_addr {
    struct astNode* type;
} astNode_addr;

typedef struct astNode_extern {
    struct symbolNode* externSymbol;
} astNode_extern;

/* Define the structure of an AST Node */
typedef struct astNode {
    enum astType astType; // The type of the AST node
    struct symbolNode* scope; // The scope that this AST is constrained within
    struct position pos;

    List* children; // list of OTHER AST's ONLY! // TODO: REmove
    char* data; // Data that the AST Node refers to // TODO: Remove
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
        astNode_call call;
        astNode_int _int;
        astNode_string string;
        astNode_char _char;
        astNode_real real;
        astNode_namedArg namedArg;
        astNode_arrayliteral arrayliteral;
        astNode_true _true;
        astNode_false _false;
        astNode_null null;
        astNode_undef undef;
        astNode_neg neg;
        astNode_add add;
        astNode_subtract subtract;
        astNode_multiply multiply;
        astNode_divide divide;
        astNode_modulus modulus;
        astNode_paren paren;
        astNode_addrOf addrOf;
        astNode_deref deref;
        astNode_index index;
        astNode_slice slice;
        astNode_not not ;
        astNode_or or ;
        astNode_and and;
        astNode_eq eq;
        astNode_neq neq;
        astNode_gtr gtr;
        astNode_gte gte;
        astNode_lsr lsr;
        astNode_lte lte;
        astNode_bitNot bitNot;
        astNode_bitOr bitOr;
        astNode_bitXor bitXor;
        astNode_bitAnd bitAnd;
        astNode_lshift lshift;
        astNode_rshift rshift;
        astNode_block block;
        astNode_define define;
        astNode_assign assign;
        astNode_addAssign addAssign;
        astNode_subAssign subAssign;
        astNode_multAssign multAssign;
        astNode_divAssign divAssign;
        astNode_modAssign modAssign;
        astNode_andAssign andAssign;
        astNode_orAssign orAssign;
        astNode_xorAssign xorAssign;
        astNode_lshiftAssign lshiftAssign;
        astNode_rshiftAssign rshiftAssign;
        astNode_if _if;
        astNode_for _for;
        astNode_switch _switch;
        astNode_case _case;
        astNode_return _return;
        astNode_new new;
        astNode_free free;
        astNode_defer defer;
        astNode_break _break;
        astNode_continue _continue;
        astNode_dot dot;
        astNode_sizeof _sizeof;
        astNode_void _void;
        astNode_cast cast;
        astNode_paramlist paramlist;
        astNode_function function;
        astNode_addr addr;
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
const ASTNode* ENUM_TYPE;

// Functions that are defined in the file ast.c
ASTNode* createArrayTypeNode(ASTNode* baseType, int length);
ASTNode* AST_Create(enum astType type, uint64_t data, SymbolNode* scope, struct position pos, bool isConst);
void AST_Print(ASTNode* root, char* prefix, char* childrenPrefix);
int AST_TypeRepr(char* str, ASTNode* type);
char* AST_GetString(enum astType type);

#endif
