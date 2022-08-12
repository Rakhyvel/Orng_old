// © 2021-2022 Joseph Shimel. All rights reserved.

#include "errors.h"
#include "./main.h"

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