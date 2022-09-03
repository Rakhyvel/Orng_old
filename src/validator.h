// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "./main.h"
#include "symbol.h"

bool structuralTypeEquiv;
bool isSubtype(ASTNode* a, ASTNode* b);

void Validator_ValidateSymbol(SymbolNode* symbol);

#endif