// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef PARSE_H
#define PARSE_H

#include "./ast.h"
#include "./symbol.h"
#include <stdio.h>

void rebaseScope(ASTNode* node, SymbolNode* newScope);
char* myItoa(int val);
ASTNode* Parser_Parse(FILE* in, SymbolNode* program);

#endif