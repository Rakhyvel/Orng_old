/*
This file declares the Generator_Generate() function for other files to use.
Implementation is in the file generator.c
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include "./ast.h"
#include "./symbol.h"
#include "./main.h"
#include <stdio.h>

void Generator_Generate(Program program, FILE* out);

#endif