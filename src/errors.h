// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef ERRORS_H
#define ERRORS_H

#include "../util/debug.h"
#include <stdio.h>

void printPos(FILE* out, struct position pos);

NO_RETURN void error(struct position pos, const char* message, ...);
NO_RETURN void error2(struct position pos1, struct position pos2, const char* message, ...);
NO_RETURN void error3(struct position pos1, struct position pos2, struct position pos3, const char* message, ...);
NO_RETURN void gen_error(const char* message, ...);

NO_RETURN void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType);
NO_RETURN void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType);
NO_RETURN void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType);
NO_RETURN void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName);
NO_RETURN void expectedArrayError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedAddrError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedEnumError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedErrorEnumError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedMaybeEnumError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedFunctionError(struct position pos, struct astNode* actualType);
NO_RETURN void expectedTypeError(struct position pos, struct astNode* actualType);
NO_RETURN void notMemberOfExpressionError(struct position pos, char* fieldName, struct astNode* product);

#endif