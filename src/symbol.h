#ifndef SYMBOL_H
#define SYMBOL_H

#include "../util/map.h"
#include "./position.h"

struct astNode;

typedef enum symbolType {
    SYMBOL_PROGRAM,
	SYMBOL_PACKAGE,
    SYMBOL_MODULE,
    SYMBOL_FUNCTION,
    SYMBOL_TYPE, // typedef or struct def
    SYMBOL_ENUM,
    SYMBOL_BLOCK,
    SYMBOL_VARIABLE
} SymbolType;

/*
    The Symbol Tree describes symbols and their relationship to other symbols.
    
    Symbols include:
    - Modules
    - Structs
    - Variables
    - Functions
    - The program as a whole */
typedef struct symbolNode {
    SymbolType symbolType;
    struct astNode* type;
    char name[255];
    char externName[255];
    char desc[255];

    struct astNode* def; // SymbolDefine ASTNode where this symbol is defined
	
	bool isDeclared;
    bool isExtern;
    bool isRestricted;
    bool isVararg;
    bool isReachable;

    // Parse tree
    struct symbolNode* parent;
    Map* children; // name -> other symbolNodes
    List* restrictionExpr; // list of symbol_expr
    List* restrictions; // list of symbol*

	// IR
    List* instructions; // list of code_lowered instructions

	// Defer/block
    List* defers; // list of ast's, in order of declaration
    bool isLoop;
    int tempVars;
    int labels;

    struct position pos;
    bool visited;
} SymbolNode;

struct symbolNode* rejectingSymbol; // When symbol_find fails, this is the symbol that rejected it

struct symbolNode* Symbol_Create(char* name, SymbolType symbolType, struct symbolNode* parent, struct position pos);
void Symbol_Print(SymbolNode* root, char* prefix, char* childrenPrefix);
struct symbolNode* Symbol_Find(const char* symbolName, const struct symbolNode* scope);
struct symbolNode* Symbol_Root(const struct symbolNode* scope);
struct symbolNode* Symbol_TypeAncestor(struct symbolNode* scope, SymbolType type);
struct symbolNode* Symbol_MostRecentNonBlock(struct symbolNode* scope);

#endif