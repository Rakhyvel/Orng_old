/*
Parses out a queue of tokens into a symbol tree that represents the program
*/

#ifndef PARSE_H
#define PARSE_H

#include "./ast.h"
#include "./symbol.h"
#include <stdio.h>

int blockUID;
void rebaseScope(ASTNode* node, SymbolNode* newScope);
char* myItoa(int val);
ASTNode* Parser_Parse(FILE* in, SymbolNode* program);

#endif