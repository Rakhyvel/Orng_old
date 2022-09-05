// © 2022 Joseph Shimel. All rights reserved.
#include "./program.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./errors.h"
#include "./tinydir.h"
#include "./validator.h"
#include <io.h> // For access().
#include <stdlib.h>
#include <sys/stat.h> // For stat().
#include <sys/types.h> // For stat().
#include <windows.h>

struct program* program;

// Returns the tag ID for a field name/type pair, panics on error
int64_t getTag(char* fieldName, ASTNode* fieldType)
{
    List* set = Map_Get(program->tagTypes, fieldName);
    if (!set) {
        PANIC("NO!");
    }
    int i = 0;
    forall(elem, set)
    {
        ASTNode* type = elem->data;
        // Types are completely equal
        if (isSubtype(type, fieldType) && isSubtype(fieldType, type)) {
            break;
        }
        i++;
    }
    List* ids = Map_Get(program->tagIDs, fieldName);
    int64_t tag = (int64_t)List_Get(ids, i);
    return tag;
}

// Returns the tag ID for a field name from within a sum type
int64_t getTagEnum(char* fieldName, ASTNode* enumType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (!strcmp(var->name, fieldName)) {
            return getTag(fieldName, var->type);
        }
    }
    PANIC("couldn't find tag enum");
}

// Returns the type of a field given a tag from a sum type
ASTNode* getTypeEnum(int64_t tag, ASTNode* enumType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (getTag(var->name, var->type) == tag) {
            return var->type;
        }
    }
    PANIC("couldn't find tag enum");
}

// Determines whether a sum type contains a field name/type pair
bool enumContainsField(ASTNode* enumType, char* fieldName, ASTNode* fieldType)
{
    forall(elem, enumType->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (!strcmp(var->name, fieldName) && isSubtype(var->type, fieldType)) {
            return true;
        }
    }
    return false;
}

// Registers the field name/type pair if it is unique
void putTag(char* fieldName, ASTNode* fieldType)
{
    static int tagID = 0;
    List* typeSet = Map_Get(program->tagTypes, fieldName);
    List* typeList = Map_Get(program->tagIDs, fieldName);
    if (!typeSet && !typeList) {
        typeSet = List_Create();
        Map_Put(program->tagTypes, fieldName, typeSet);

        typeList = List_Create();
        Map_Put(program->tagIDs, fieldName, typeList);
    }

    // Add the type to the set using type equality, not equivalence
    bool typeSetContainsType = false;
    forall(elem2, typeSet) // Find if the type is in the typeSet
    {
        ASTNode* type = elem2->data;
        if (isSubtype(fieldType, type) && isSubtype(type, fieldType)) {
            typeSetContainsType = true;
            break;
        }
    }
    if (!typeSetContainsType) {
        int tag = tagID;
        tagID += 1;
        List_Append(typeList, (void*)tag);
        List_Append(typeSet, fieldType);
    }
}

// Adds a struct to the dependency graph if it is unique, with all dependencies
struct graph* addGraphNode(List* depenGraph, ASTNode* type)
{
    // Check if type is enum, if so, collect tags
    if (type->astType == AST_ENUM || type->astType == AST_INFER_ERROR) {
        forall(elem, type->_enum.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* symbol = define->define.symbol;
            // Check if there is a set created in the map, if not create it
            putTag(symbol->name, symbol->type);
        }
    }

    // Check list to see if any graph node has product type
    // If does, return that graph node
    // If not, create new grpahnode, append to list of dependencies, return new graph node
    bool oldTypePermissiveness = structuralTypeEquiv;
    structuralTypeEquiv = false;
    forall(elem, depenGraph)
    {
        DGraph* graphNode = elem->data;
        if (isSubtype(graphNode->typeDef, type)) {
            return graphNode;
        }
    }
    structuralTypeEquiv = oldTypePermissiveness;

    DGraph* graphNode = calloc(1, sizeof(DGraph));
    ASSERT(graphNode != NULL);
    graphNode->typeDef = type;
    graphNode->visited = false;
    graphNode->id = depenGraph->size;
    graphNode->dependencies = List_Create();
    List_Append(depenGraph, graphNode);

    return graphNode;
}

// Checks that a dependency graph doesn't have loops in it
void validateNoLoops(DGraph* graphNode)
{
    graphNode->visited = true;
    forall(elem, graphNode->dependencies)
    {
        DGraph* child = elem->data;
        if (child->visited) {
            error(child->typeDef->pos, "loop detected");
            return;
        }
        validateNoLoops(child);
    }
    graphNode->visited = false;
}

// Gets the user directory. Wors on Windows and on UNIX
static char* getUserDirectory()
{
#ifdef _WIN32
    char* userDir = NULL;
    size_t sz = 0;
    if (_dupenv_s(&userDir, &sz, "USERPROFILE") || userDir == NULL) {
        compilerError("user profile environment variable not defined\n");
        return NULL;
    }
    return userDir;
#else
    return getenv("HOME");
#endif
}

// Takes in a parent absolute directory, and a sub directory path. Creates the subdirectory if it does not exist in absolute directory. Returns the concatonated path name
static char* createIfNotExist(char* parentAbsDir, char* subDirPath)
{
    int userDirLen = strlen(parentAbsDir);
    int subDirLen = userDirLen + strlen(subDirPath) + 1;
    char* subDir = calloc(subDirLen, sizeof(char));
    ASSERT(subDir != NULL);
    strcpy_s(subDir, subDirLen, parentAbsDir);
    strcat_s(subDir, subDirLen, subDirPath);

    bool exists = false;
    if (_access(subDir, 0) == 0) {
        struct stat status;
        stat(subDir, &status);
        exists = (status.st_mode & S_IFDIR) != 0;
    } else {
        exists = false;
    }

    if (!exists) {
#ifdef _WIN32
        _mkdir(subDir);
#else
        mkdir(subDir, 0700);
#endif
    }

    return subDir;
}

void Program_Init()
{
    program = calloc(sizeof(struct program), 1);
    ASSERT(program != NULL);

    program->typeDependencyGraph = List_Create();
    program->includes = Map_Create();
    program->verbatims = List_Create();
    program->tagTypes = Map_Create();
    program->tagIDs = Map_Create();
    program->files = Map_Create();
    // Create orange directories if they don't exist
    char* userDir = getUserDirectory();
    createIfNotExist(userDir, "\\orange");
    program->packagesPath = createIfNotExist(userDir, "\\orange\\packages");
}