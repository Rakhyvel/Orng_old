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

// Represents a node in the product/sum dependency graph
typedef struct {
    ASTNode* structDef; // Definition of the product/sum type TODO: rename to 'typeDef'
    int ordinal; // The unique ID of this dependency graph node TODO: rename to 'id'
    List* dependencies; // List of other DGraph nodes for product/sum types used by the fields of the type of this DGraph node
    bool visited; // Used for graph traversal
} DGraph;

// Represents the entire program through compilation
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