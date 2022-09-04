// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef ERRORS_H
#define ERRORS_H

#include "../util/debug.h"
#include <stdio.h>

void printPos(FILE* out, struct position pos);

void error(struct position pos, const char* message, ...);
void error2(struct position pos1, struct position pos2, const char* message, ...);
void error3(struct position pos1, struct position pos2, struct position pos3, const char* message, ...);
void gen_error(const char* message, ...);

void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType);
void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType);
void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType);
void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName);
void expectedArrayError(struct position pos, struct astNode* actualType);
void expectedAddrError(struct position pos, struct astNode* actualType);
void expectedEnumError(struct position pos, struct astNode* actualType);
void expectedErrorEnumError(struct position pos, struct astNode* actualType);
void expectedMaybeEnumError(struct position pos, struct astNode* actualType);
void expectedFunctionError(struct position pos, struct astNode* actualType);
void expectedTypeError(struct position pos, struct astNode* actualType);
void notMemberOfExpressionError(struct position pos, char* fieldName, struct astNode* product);

#endif