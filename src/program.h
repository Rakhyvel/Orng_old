// © 2022 Joseph Shimel. All rights reserved.

#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>
#include <stdint.h>

// Represents a node in the product/sum dependency graph
typedef struct graph {
    struct astNode* typeDef; // Definition of the product/sum type
    int id; // The unique ID of this dependency graph node
    struct list* dependencies; // List of other DGraph nodes for product/sum types used by the fields of the type of this DGraph node
    bool visited; // Used for graph traversal
} DGraph;

// Represents the entire program through compilation
typedef struct program {
    struct list* typeDependencyGraph;
    struct map* includes;
    struct list* verbatims;
    struct CFG* callGraph;
    struct map* tagTypes; // Maps field names to set of types available for that field
    struct map* tagIDs; // Maps field names to set of ids that correspond with field type
    struct symbolNode* mainFunction; // The main function of the program, found after traversal
    char* packagesPath; // The path to the orng/dependencies folder
    char* filename; // The filename of the current input file
    bool isDebug; // Whether the compiler is in debug mode
    struct map* files; // Maps filenames to lists of lines
} Program;

extern struct program* program;

int64_t getTag(char* fieldName, struct astNode* fieldType);
int64_t getTagEnum(char* fieldName, struct astNode* enumType);
struct astNode* getTypeEnum(int64_t tag, struct astNode* enumType);
bool enumContainsField(struct astNode* enumType, char* fieldName, struct astNode* fieldType);
void putTag(char* fieldName, struct astNode* fieldType);
struct graph* addGraphNode(struct list* depenGraph, struct astNode* structType);
void validateNoLoops(DGraph* graphNode);
void Program_Init();

#endif