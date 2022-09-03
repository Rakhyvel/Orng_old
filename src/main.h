// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef MAIN_H
#define MAIN_H

#include "../util/list.h"
#include "./ast.h"
#include "./position.h"
#include "./symbol.h"
#include <stdio.h>

char* Main_GetRelPath(char*);
char* Main_PathToFilename(char* path);

#endif