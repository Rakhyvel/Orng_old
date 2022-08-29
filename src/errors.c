// © 2021-2022 Joseph Shimel. All rights reserved.

#include "errors.h"
#include "./main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

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

static char* firstNonSpace(char* str)
{
    int i = 0;
    for (; str[i] != '\0' && isspace(str[i]); i++)
        ;
    return str + i;
}

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

void printPos(FILE* out, struct position pos)
{
    char* newLine = out == stderr ? "\n" : "\\n";
    if (pos.filename) {
        fprintf(out, "%s: ", getRelPath(pos.filename));
        fprintf(out, "%s", newLine);
        // fprintf(out, "      |");
        //fprintf(out, "%s", newLine);
        int minWhiteSpace = 100000;
        int maxLineLength = 0;
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            List* lines = Map_Get(files, pos.filename);
            char* lineStr = List_Get(lines, i - 1);
            minWhiteSpace = min(minWhiteSpace, countLeadingWhitespace(lineStr));
        }
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            fprintf(out, "%d", i);
            for (int j = 0; j < 5 - (int)(log(i) / log(10)); j++) {
                fprintf(out, " ");
            }
            List* lines = Map_Get(files, pos.filename);
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
                maxLineLength = max(maxLineLength, strlen(stripped) + spaces);
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

/*
Prints out an error message, with a filename and line number
*/
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

/*
prints out a general error message about the program with no position given
*/
void gen_error(const char* message, ...)
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

void printType(ASTNode* type)
{
    char typeStr[255];
    AST_TypeRepr(typeStr, type);
    printf("%s\n", typeStr);
}

void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType->originalType);
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType)
{
    char expectedStr[255];
    char actualStr[255];
    AST_TypeRepr(expectedStr, expectedType);
    AST_TypeRepr(actualStr, actualType);
    error2(pos, pos2, "type mismatch: expected %s, got %s", expectedStr, actualStr);
}

void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType)
{
    char leftStr[255];
    char rightStr[255];
    AST_TypeRepr(leftStr, leftType);
    AST_TypeRepr(rightStr, rightType);
    error(pos, "incompatible types: %s and %s", leftStr, rightStr);
}

void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName)
{
    if (pos2.start_line != 0) {
        error2(pos1, pos2, "symbol '%s' is undefined or not allowed through restriction", symbolName);
    } else {
        error(pos1, "symbol '%s' is undefined", symbolName);
    }
}

void expectedArray(struct position pos, struct astNode* actualType)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, actualType->originalType);
    error(pos, "type mismatch: expected array type, got %s", actualStr);
}

void notMemberOfExpression(struct position pos, char* fieldName, struct astNode* paramlist)
{
    char actualStr[255];
    AST_TypeRepr(actualStr, paramlist->originalType);
    error(pos, "symbol '%s' is not a member of left-side expression, which is of type %s", fieldName, actualStr);
}