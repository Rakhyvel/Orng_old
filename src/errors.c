// © 2021-2022 Joseph Shimel. All rights reserved.
// Handles error collection and output

#include "errors.h"
#include "../util/list.h"
#include "./ast.h"
#include "./main.h"
#include "./position.h"
#include "./program.h"
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Counts the amount of leading whitespace in a string. Tabs count for four whitespaces.
static int countLeadingWhitespace(char* str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0' && isspace(str[i]); i++) {
        if (str[i] == ' ') {
            count++;
        } else if (str[i] == '\t') {
            count += 4;
        }
    }
    return count;
}

// Returns the address to the first non-space character in a string
static char* firstNonSpace(char* str)
{
    int i = 0;
    for (; str[i] != '\0' && isspace(str[i]); i++)
        ;
    return str + i;
}

// If 'out' is stderr, prints char as normal. Otherwise, prints character so that it would be escaped in a C string
static void printPosChar(FILE* out, char c)
{
    if (out != stderr) {
        if (c == '"') {
            fprintf(out, "\\\"");
        } else if (c == '\\') {
            fprintf(out, "\\");
        } else {
            fprintf(out, "%c", c);
        }
    } else {
        fprintf(out, "%c", c);
    }
}

// Prints out a given position's information, including the context of the file
void printPos(FILE* out, struct position pos)
{
    char* newLine = out == stderr ? "\n" : "\\n";
    if (pos.filename) {
        fprintf(out, "%s: ", Main_GetRelPath(pos.filename));
        fprintf(out, "%s", newLine);
        // fprintf(out, "      |");
        //fprintf(out, "%s", newLine);
        int minWhiteSpace = 100000;
        int maxLineLength = 0;
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            List* lines = Map_Get(program->files, pos.filename);
            char* lineStr = List_Get(lines, i - 1);
            minWhiteSpace = min(minWhiteSpace, countLeadingWhitespace(lineStr));
        }
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            fprintf(out, "%d", i);
            for (int j = 0; j < 5 - (int)(log(i) / log(10)); j++) {
                fprintf(out, " ");
            }
            List* lines = Map_Get(program->files, pos.filename);
            char* lineStr = List_Get(lines, i - 1);
            int spaces = countLeadingWhitespace(lineStr) - minWhiteSpace;
            fprintf(out, "| ");
            for (int j = 0; j < spaces; j++) {
                fprintf(out, " ");
            }
            if (pos.start_line == pos.end_line || (i != pos.start_line && i != pos.end_line)) {
                char* stripped = firstNonSpace(lineStr);
                for (char* c = stripped; *c; c++) {
                    printPosChar(out, *c);
                }
                maxLineLength = max(maxLineLength, (int)(strlen(stripped)) + spaces);
            } else {
                bool seenNonWhiteSpace = false;
                int start = i == pos.start_line ? pos.start_span : 1;
                int end = i == pos.start_line ? strlen(lineStr) + 1 : pos.end_span + 1;
                int charsPrinted = spaces;
                for (int j = start; j <= end; j++) {
                    char c = lineStr[j - 1];
                    if (isspace(c) && !seenNonWhiteSpace) {
                        continue;
                    } else {
                        seenNonWhiteSpace = true;
                        printPosChar(out, c);
                        charsPrinted++;
                    }
                }
                maxLineLength = max(maxLineLength, charsPrinted - 1);
            }
            fprintf(out, "%s", newLine);
        }

        fprintf(out, "      | ");
        if (pos.start_line == pos.end_line) {
            for (int i = 0; i < pos.start_span - 1; i++) {
                fprintf(out, " ");
            }
            for (int i = pos.start_span; i < pos.end_span; i++) {
                fprintf(out, "^");
            }
        } else {
            for (int i = 0; i < maxLineLength; i++) {
                fprintf(out, "^");
            }
        }
        fprintf(out, "%s", newLine);
    }
}

// Prints out an error message, with a filename and line number
void error(struct position pos, const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");

    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    printPos(stderr, pos);

	system("pause");
    exit(1);
}

// Prints out an error message with two positions
void error2(Position pos1, Position pos2, const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");

    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    printPos(stderr, pos1);
    printPos(stderr, pos2);
    system("pause");
    exit(1);
}

// Prints out an error message with three positions
void error3(Position pos1, Position pos2, Position pos3, const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");

    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    printPos(stderr, pos1);
    printPos(stderr, pos2);
    printPos(stderr, pos3);
    system("pause");
    exit(1);
}

// prints out a general error message about the program with no position given
void compilerError(const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");
    system("pause");
    exit(1);
}

// Prints out a message about two types being mismatched
void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType->originalType);
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

// Prints out a message about two types being mismatched, with two positions
void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType);
    AST_TypeRepr(actualStr, actualType);
    error2(pos, pos2, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

// Prints a message about incompatible types
void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType)
{
    char leftStr[255];
    char rightStr[255];
    AST_TypeRepr(leftStr, leftType);
    AST_TypeRepr(rightStr, rightType);
    error(pos, "incompatible types: %s and %s", leftStr, rightStr);
}

// Prints a message about restriction or an undefined symbol
void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName)
{
    if (pos2.start_line != 0) {
        error2(pos1, pos2, "symbol '%s' is undefined or not allowed through restriction", symbolName);
    } else {
        error(pos1, "symbol '%s' undefined", symbolName);
    }
}

// Prints out a message about expecting an array type
void expectedArrayError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected array type, got %s", actualStr);
}

// Prints out a message about expecting an address type
void expectedAddrError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected address type, got %s", actualStr);
}

// Prints out a message about expecting an enum type
void expectedEnumError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected enum type, got %s", actualStr);
}

// Prints out a message about expecting an enum type
void expectedErrorEnumError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected error enum type, got %s", actualStr);
}

// Prints out a message about expecting an enum type
void expectedMaybeEnumError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected maybe enum type, got %s", actualStr);
}

// Prints out a message about expecting a function type
void expectedFunctionError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected function type, got %s", actualStr);
}

// Prints out a message about expecting a type type
void expectedTypeError(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected type, got %s", actualStr);
}

// Prints out a message about a field not being in a given expression
void notMemberOfExpressionError(struct position pos, char* fieldName, struct astNode* product)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, product->originalType);
    error(pos, "symbol '%s' not member of left-side expression, which is of type %s", fieldName, actualStr);
}