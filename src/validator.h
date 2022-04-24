#pragma once
#include "symbol.h"
#include "./main.h"

Program Validator_Validate(SymbolNode* symbol);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);