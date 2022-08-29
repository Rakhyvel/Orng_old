// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef MAIN_H
#define MAIN_H

#include "../util/list.h"
#include "./ast.h"
#include "./position.h"
#include "./symbol.h"
#include <stdio.h>

char* filename;
Map* files;

typedef struct {
    ASTNode* structDef;
    int ordinal;
    List* dependencies;
    bool visited;
} DGraph;

typedef struct program {
    List* structDependencyGraph;
    Map* includes;
    List* verbatims;
    struct CFG* callGraph;
} Program;

bool isDebug;

char* getRelPath(char*);
char* pathToFilename(char* path);

#endif