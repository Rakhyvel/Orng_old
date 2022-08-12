// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef LEXER_H
#define LEXER_H

#include "./token.h"
#include <stdio.h>

int line;
int span;
Token* Lexer_GetNextToken(FILE* in);

#endif