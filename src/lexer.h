/*
Delcares the line global, and the Lexer_GetNextToken() function for other files to use.
Implementation is in the lexer.c file
*/

#ifndef LEXER_H
#define LEXER_H

#include "./token.h"
#include <stdio.h>

int line;
int span;
Token* Lexer_GetNextToken(FILE* in);

#endif