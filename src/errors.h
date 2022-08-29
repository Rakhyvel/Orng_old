// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

void printPos(FILE* out, struct position pos);

void error(struct position pos, const char* message, ...);
void error2(struct position pos1, struct position pos2, const char* message, ...);
void error3(struct position pos1, struct position pos2, struct position pos3, const char* message, ...);
void gen_error(const char* message, ...);

void printType(struct astNode* type);

void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType);
void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType);
void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType);
void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName);
void expectedArray(struct position pos, struct astNode* actualType);
void notMemberOfExpression(struct position pos, char* fieldName, struct astNode* paramlist);

#endif