// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef SYMBOL_H
#define SYMBOL_H

#include "../util/map.h"
#include "./position.h"

struct astNode;

// A list of all types that a symbol node can be. Determines how that node is treated.
typedef enum symbolType {
    SYMBOL_PROGRAM,
    SYMBOL_PACKAGE,
    SYMBOL_MODULE,
    SYMBOL_FUNCTION,
    SYMBOL_TYPE, // typedef or struct def
    SYMBOL_BLOCK,
    SYMBOL_VARIABLE
} SymbolType;

// Symbols abstract the idea of variables, functions, modules, and other nodes in the scope tree
typedef struct symbolNode {
    SymbolType symbolType;
    struct astNode* type; // Type for this symbol
    struct astNode* originalType; // Is never expanded, used to print
    char name[255];
    char externName[255]; // If symbol is external, printed out instead of the symbol's name
    char desc[255];

    struct astNode* def; // SymbolDefine ASTNode where this symbol is defined
    struct CFG* cfg; // Control flow graph node of this symbol, if it is a function

    bool isError; // If the type of this symbol was constructed using the ! operator
    bool isDeclared;
    bool isExtern; // Whether or not the symbol is external
    bool hasRestrictions; // Whether or not the symbol has symbol restrictions
    bool isVararg; // Whether or not the symbol is a variable argument. Only applicable to varargs

    struct symbolNode* parent; // Parent symbol node in the symbol tree
    Map* children; // Maps child symbol names to the symbol nodes
    List* restrictionExpr; // List of expressions for whitelisted symbols
    List* restrictions; // List of actual symbols where are whitelisted

    bool isVolatile; // Whether or not the symbol's value may change in a way that makes it hard to optimize
    int numberVersions; // How many versions there are of this symbol

    List* defers; // For block symbols, list of expressions of defer ASTs, in order of declaration
    List* errdefers; // For block symbols, list of expressions of defer AND errdefer ASTs, in order of declaration

    struct position pos; // Position of the symbol in the source text
    bool visited; // Used for traversal
} SymbolNode;

struct symbolNode* rejectingSymbol; // When symbol_find fails, this is the symbol that rejected it

struct symbolNode* Symbol_Create(char* name, SymbolType symbolType, struct symbolNode* parent, struct position pos);
struct symbolNode* Symbol_Find(const char* symbolName, const struct symbolNode* scope);
struct symbolNode* Symbol_TypeAncestor(struct symbolNode* scope, SymbolType type);
void Symbol_Print(SymbolNode* root, char* prefix, char* childrenPrefix);
void unVisitSymbolTree(SymbolNode* node);
struct symbolNode* Symbol_MostRecentNonBlock(struct symbolNode* scope);
struct symbolNode* Symbol_Root(const struct symbolNode* scope);

#endif