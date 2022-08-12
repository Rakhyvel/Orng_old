#pragma once
#include "./main.h"
#include "symbol.h"

const struct map* tagTypes;
const struct map* tagIDs;
Program Validator_Validate(SymbolNode* symbol);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);
int getTypeSize(ASTNode* type);
int getTag(char* fieldName, ASTNode* fieldType);
int getTagEnum(char* fieldName, ASTNode* enumType);
ASTNode* getTypeEnum(int tag, ASTNode* enumType);
bool enumContainsField(ASTNode* enumType, char* fieldName, ASTNode* fieldType);