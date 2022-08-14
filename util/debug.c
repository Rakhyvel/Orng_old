// © 2021-2022 Joseph Shimel. All rights reserved.

#include "./debug.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
	Halts the program, allows me to see stack trace when something goes wrong */
void debug_panic(const char* file, int line, const char* function,
    const char* message, ...)
{
    va_list args;

    fprintf(stderr, "ERROR: %s:%d in %s(): ", file, line, function);

    va_start(args, message);
    vprintf(message, args);
    printf("\n");
    va_end(args);
    while (1)
        ;
}

void debug_log(const char* file, int line, const char* function,
    const char* message, ...)
{
    va_list args;

    fprintf(stderr, "LOG: %s:%d in %s(): ", file, line, function);

    va_start(args, message);
    vprintf(message, args);
    va_end(args);
}

void debug_break(int condition)
{
    if (condition) {
        printf("breakpoint\n");
    }
}