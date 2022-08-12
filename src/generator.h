// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef GENERATOR_H
#define GENERATOR_H

#include "./ast.h"
#include "./main.h"
#include "./symbol.h"
#include <stdio.h>

void Generator_Generate(FILE* out, Program program);

#endif