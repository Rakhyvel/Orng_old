#pragma once
#include "./main.h"
#include "symbol.h"

SymbolNode* Validator_Validate(SymbolNode* symbol);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);
int getTypeSize(ASTNode* type);