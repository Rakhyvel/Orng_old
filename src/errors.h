#ifndef ERRORS_H
#define ERRORS_H

void printType(struct astNode* type);

void typeMismatchError(struct position pos, struct astNode* expectedType, struct astNode* actualType);

void typeMismatchError2(struct position pos, struct position pos2, struct astNode* expectedType, struct astNode* actualType);

void incompatibleTypesError(struct position pos, struct astNode* leftType, struct astNode* rightType);

void restrictedOrUndefError(struct position pos1, struct position pos2, char* symbolName);

#endif