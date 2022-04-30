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
	AST_ARRAY_LITERAL,
    AST_NAMED_ARG,
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
    AST_ADDROF,
    AST_DEREF,
    AST_INDEX,
	AST_SLICE,
    AST_NULL,
    AST_SIZEOF,
    // Boolean
    AST_NOT,
    AST_OR,
    AST_AND,
    AST_NEQ,
    AST_EQ,
    AST_GTR,
    AST_GTE,
    AST_LSR,
    AST_LTE,
    AST_TRUE,
    AST_FALSE,
    // Bitwise
    AST_BIT_OR,
    AST_BIT_XOR,
    AST_BIT_AND,
    AST_LSHIFT,
    AST_RSHIFT,
    AST_BIT_NOT,
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
    AST_NEW,         // Replace with allocator method 
    AST_FREE,        // Replace with allocator method
	AST_DEFER,
	AST_BREAK,
	AST_CONTINUE,
    // Module
    AST_DOT,
    // Types
    AST_VOID,
    AST_CAST,
    AST_PARAMLIST,
	AST_PROCEDURE,
    AST_FUNCTION,
    AST_ADDR,
	//AST_C_ARRAY,
    AST_ARRAY,
    AST_ENUM,
	AST_EXTERN
};

bool doDefTypes;

/* Define the structure of an AST Node */
typedef struct astNode {
    enum astType astType; // The type of the AST node
    List* children; // list of OTHER AST's ONLY!
    char* data; // Data that the AST Node refers to
    struct symbolNode* scope; // The scope that this AST is constrained within
    struct position pos;
    bool visited;
    bool isValid;

	bool isConst;

	// if subtree contains any of these
    bool containsReturn;
    bool containsContinue;
    bool containsBreak;

    struct astNode* type; // The type of the AST Node
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
