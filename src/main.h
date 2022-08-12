// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef MAIN_H
#define MAIN_H

#include "../util/list.h"
#include "./ast.h"
#include "./position.h"
#include "./symbol.h"
#include <stdio.h>

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
    List* verbatims;
    struct CFG* callGraph;
} Program;

bool isDebug;

char* getRelPath(char*);
char* pathToFilename(char* path);
void gen_error(const char* message, ...);
void printPos(FILE* out, struct position pos);
void error(struct position pos, const char* message, ...);
void error2(struct position pos1, Position pos2, const char* message, ...);
void error3(struct position pos1, Position pos2, Position pos3, const char* message, ...);
void unVisitSymbolTree(SymbolNode* node);

#endif