// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "./main.h"
#include "symbol.h"

const struct map* tagTypes;
const struct map* tagIDs;

bool typesAreEquivalent(ASTNode* a, ASTNode* b);
int getTag(char* fieldName, ASTNode* fieldType);
int getTagEnum(char* fieldName, ASTNode* enumType);
ASTNode* getTypeEnum(int tag, ASTNode* enumType);
bool enumContainsField(ASTNode* enumType, char* fieldName, ASTNode* fieldType);
Program Validator_Validate(SymbolNode* symbol);

#endif