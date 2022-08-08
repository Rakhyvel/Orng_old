#pragma once
#include "./main.h"
#include "symbol.h"

Program Validator_Validate(SymbolNode* symbol);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);
int getTypeSize(ASTNode* type);
int getTag(char* fieldName, ASTNode* fieldType);
int getTagEnum(char* fieldName, ASTNode* enumType);