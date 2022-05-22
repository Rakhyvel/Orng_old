#pragma once
#include "./main.h"
#include "symbol.h"

Program Validator_Validate(SymbolNode* symbol);
bool typesAreEquivalent(ASTNode* a, ASTNode* b);