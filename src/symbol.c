/*
A symbol is a name in the program that refers to something in the program.
Examples are variable names, procedures, even block {} statements are their
own symbols.

The symbol tree is used to determine scope.
*/

#include "symbol.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "../util/map.h"
#include "./lexer.h"
#include "./main.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Allocates and initializes the program struct
*/
struct symbolNode* Symbol_Create(char* name, SymbolType symbolType, struct symbolNode* parent, struct position pos)
{
    struct symbolNode* retval = (struct symbolNode*)calloc(1, sizeof(struct symbolNode));

    retval->symbolType = symbolType;
    retval->parent = parent;
    retval->children = Map_Create();
    retval->restrictionExpr = List_Create();
    retval->restrictions = List_Create();
    retval->defers = List_Create();
    retval->pos = pos;

    strncpy_s(retval->name, 255, name, 254);
    if (parent != NULL) {
        SymbolNode* collision = Symbol_Find(name, retval);
        if (Map_Put(parent->children, name, retval)) {
            Symbol_Print(parent->parent, "", "");
            Symbol_Print(collision->parent->parent, "", "");
            SymbolNode* nonblock = Symbol_MostRecentNonBlock(parent);
            SymbolNode* collision = Map_Get(parent->children, name);
            error2(pos, collision->pos, "symbol '%s' already defined in '%s'", name, nonblock->name);
        }
    }

    return retval;
}

/*
Prints out the symbol tree
*/
void Symbol_Print(SymbolNode* root, wchar_t* prefix, wchar_t* childrenPrefix)
{
    ASSERT(root != NULL);

    printf("%s%s", prefix, root->name);
    switch (root->symbolType) {
    case SYMBOL_MODULE:
        printf("[SYMBOL_MODULE]\n");
        break;
    case SYMBOL_FUNCTION:
        printf("[SYMBOL_FUNCTION]\n");
        break;
    case SYMBOL_VARIABLE:
        printf("[SYMBOL_VARIABLE]\n");
        break;
    case SYMBOL_BLOCK:
        printf("[SYMBOL_BLOCK]\n");
        break;
    default:
        printf("[SYMBOL_TYPE]\n");
        break;
    }
    List* children = root->children->keyList;
    char newPrefix[255];
    char newChildrenPrefix[255];
    for (ListElem* elem = List_Begin(children); elem != List_End(children); elem = elem->next) {
        bool hasNext = elem->next != List_End(children);
        if (hasNext) {
            strncpy_s(newPrefix, 254, childrenPrefix, 254);
            strncat_s(newPrefix, 254, "+--", 254);
            strncpy_s(newChildrenPrefix, 254, childrenPrefix, 254);
            strncat_s(newChildrenPrefix, 254, "|  ", 254);
        } else {
            strncpy_s(newPrefix, 254, childrenPrefix, 254);
            strncat_s(newPrefix, 254, "\\--", 254);
            strncpy_s(newChildrenPrefix, 254, childrenPrefix, 254);
            strncat_s(newChildrenPrefix, 254, "   ", 254);
        }
        Symbol_Print(Map_Get(root->children, elem->data), newPrefix, newChildrenPrefix);
    }
}

/*
Returns the symbol with the given name relative to a given starting scope.
    
Will return NULL if no symbol with the name is found in any direct ancestor
scopes. 

Will return -1 if symbol name is not in scope restriction
*/
struct symbolNode* Symbol_Find(const char* symbolName, const struct symbolNode* scope)
{
    rejectingSymbol = NULL;
    if (!symbolName || !scope) {
        return NULL;
    }

    struct symbolNode* symbol = Map_Get(scope->children, symbolName);
    if (symbol != NULL) {
        return symbol;
    } else if (scope->parent != NULL) {
        SymbolNode* parentNode = scope->parent;
        if (scope->symbolType == SYMBOL_FUNCTION) {
            while (parentNode->symbolType == SYMBOL_TYPE || parentNode->symbolType == SYMBOL_FUNCTION) {
                parentNode = parentNode->parent;
            }
        }
        SymbolNode* var = Map_Get(parentNode->children, symbolName);
        if (scope->isRestricted && !List_Contains(scope->restrictions, var) && scope != var && var != 0) {
            rejectingSymbol = scope;
            return -1;
        } else {
            return Symbol_Find(symbolName, scope->parent);
        }
    } else {
        return NULL;
    }
}

struct symbolNode* Symbol_Root(const struct symbolNode* scope)
{
    if (scope->parent == NULL) {
        return scope;
    } else {
        return Symbol_Root(scope->parent);
    }
}

struct symbolNode* Symbol_TypeAncestor(struct symbolNode* scope, SymbolType type)
{
    if (scope == NULL || scope->symbolType == type) {
        return scope;
    } else {
        return Symbol_TypeAncestor(scope->parent, type);
    }
}

struct symbolNode* Symbol_MostRecentNonBlock(struct symbolNode* scope)
{
    if (scope->symbolType != SYMBOL_BLOCK) {
        return scope;
    } else {
        return Symbol_MostRecentNonBlock(scope->parent);
    }
}