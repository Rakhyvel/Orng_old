/*
easy to define new types that apply to existing methods - interfaces
easy to define new methods that apply to existing types - implmentation of interface methods for types is done anywhere

want: crazy cool type system from haskell without needing to optimize the hell out of declarative code
*/

#ifndef MAIN_H
#define MAIN_H

#include "../util/list.h"
#include "./ast.h"
#include "./position.h"
#include "./symbol.h"

char* filename;

typedef struct {
    ASTNode* structDef;
    int ordinal;
    List* dependencies;
    bool visited;
} DGraph;

typedef struct {
    List* structDependencyGraph;
    Map* includes;
    struct CFG* callGraph;
} Program;

char* getRelPath(char*);
char* pathToFilename(char* path);
void gen_error(const char* message, ...);
void error(struct position pos, const char* message, ...);
void error2(struct position pos1, Position pos2, const char* message, ...);
void unVisitSymbolTree(SymbolNode* node);

#endif