// � 2021-2022 Joseph Shimel. All rights reserved.
// Generates output code based on program struct constructed and validated in early stages

#include "generator.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "./errors.h"
#include "./ir.h"
#include "./main.h"
#include "./parse.h"
#include "./position.h"
#include "./program.h"
#include "./validator.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void generateDefine(FILE* out, SymbolNode* var, bool param, bool field);
static void generateEnum(FILE* out, DGraph* graphNode);

// Generates the includes used by the program
static void generateIncludes(FILE* out, Map* includes)
{
    fprintf(out, "/* Includes */\n");
    forall(elem, includes->keyList)
    {
        char* include = elem->data;
        if (include[0] == '<') {
            fprintf(out, "#include %s\n", include);
        } else {
            fprintf(out, "#include \"%s\"\n", include);
        }
    }
    fprintf(out, "\n");
}

// Generates some built-in functions and types for a debug build for the callstack
static void generateDebug(FILE* out)
{
    fprintf(out, "/* Debug */\n");
    fprintf(out, "struct list {\n");
    fprintf(out, "	int length;\n");
    fprintf(out, "	char* data[1000];\n");
    fprintf(out, "};\n\n");
    fprintf(out, "struct list stackTrace;\n");
    fprintf(out, "struct list errorTrace;\n\n");
    fprintf(out, "void stackTracePrint(struct list* list) {\n");
    fprintf(out, "	for (int i = 0; i < list->length; i++) {\n");
    fprintf(out, "		fprintf(stderr, \"%%s\", list->data[i]);\n");
    fprintf(out, "	}\n");
    fprintf(out, "}\n\n");
    fprintf(out, "void stackTracePrintReverse(struct list* list) {\n");
    fprintf(out, "	for (int i = list->length - 1; i >= 0; i--) {\n");
    fprintf(out, "		fprintf(stderr, \"%%s\", list->data[i]);\n");
    fprintf(out, "	}\n");
    fprintf(out, "}\n\n");

    fprintf(out, "char* tagGetFieldName(int tag) {\n");
    fprintf(out, "	switch(tag) {\n");
    forall(elem, program->tagIDs->keyList)
    {
        char* fieldName = elem->data;
        List* idList = Map_Get(program->tagIDs, fieldName);
        for (int i = 0; i < idList->size; i++) {
            int64_t data = (int64_t)List_Get(idList, i);
            fprintf(out, "\tcase %d:\n", (int)data);
        }
        fprintf(out, "\t\treturn \"%s\";\n", fieldName);
    }
    fprintf(out, "\t}\n}\n\n");
}

// Generates the code for pushing a function onto the callstack
static void stackTracePush(FILE* out, char* list)
{
    fprintf(out, "	if (%s->length >= 1000) {\n", list);
    fprintf(out, "		fprintf(stderr, \"error: stack overflow\\n\");\n");
    fprintf(out, "		stackTracePrintReverse(%s);\n", list);
    fprintf(out, "		exit(1);\n");
    fprintf(out, "	}\n");
    fprintf(out, "	%s->data[%s->length++] = ", list, list);
}

// Prints out the ordinal of a given struct type
static void printStructOrd(FILE* out, ASTNode* type)
{
    int i = 1;
    forall(elem, program->typeDependencyGraph)
    {
        DGraph* node = (DGraph*)elem->data;
        ASTNode* child = node->typeDef;
        if (isSubtype(child, type)) {
            fprintf(out, "struct_%s", myItoa(i));
            break;
        }
        i++;
    }
}

// Prints out a type
static void printType(FILE* out, ASTNode* type)
{
    switch (type->astType) {
    case AST_IDENT: {
        if (!strcmp(type->ident.data, "Int8") || !strcmp(type->ident.data, "Char")) {
            fprintf(out, "%s", "int8_t");
        } else if (!strcmp(type->ident.data, "Int16")) {
            fprintf(out, "%s", "int16_t");
        } else if (!strcmp(type->ident.data, "Int32")) {
            fprintf(out, "%s", "int32_t");
        } else if (!strcmp(type->ident.data, "Int64") || !strcmp(type->ident.data, "Int")) {
            fprintf(out, "%s", "int64_t");
        } else if (!strcmp(type->ident.data, "Bool")) {
            fprintf(out, "%s", "bool");
        } else if (!strcmp(type->ident.data, "Real32") || !strcmp(type->ident.data, "Real")) {
            fprintf(out, "%s", "float");
        } else if (!strcmp(type->ident.data, "Real64")) {
            fprintf(out, "%s", "double");
        } else if (!strcmp(type->ident.data, "String")) {
            printType(out, STRING_TYPE);
        } else {
            fprintf(out, "%s", type->ident.data);
        }
        break;
    }
    case AST_DOT: {
        SymbolNode* var = type->dot.symbol;
        if (var->isExtern) {
            fprintf(out, "%s", var->externName);
        } else {
            printType(out, type->type);
        }
        break;
    }
    case AST_VOID: {
        fprintf(out, "void");
        break;
    }
    case AST_ADDR: {
        printType(out, type->unop.expr);
        fprintf(out, "*");
        break;
    }
    case AST_PRODUCT:
    case AST_ARRAY:
    case AST_ENUM: {
        fprintf(out, "struct ");
        printStructOrd(out, type);
    } break;
    case AST_FUNCTION:
        // The second child in a function is the return type
        ASTNode* ret = type->function.codomainType;
        printType(out, ret);
        break;
    case AST_EXTERN: {
        SymbolNode* var = type->_extern.symbol;
        fprintf(out, "%s", var->externName);
        break;
    }
    default: {
        fprintf(out, "Not a type: %s", AST_GetString(type->astType));
    }
    }
}

// Prints the name of a symbol
static void printPath(FILE* out, SymbolNode* symbol)
{
    // Local variables
    if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && symbol->parent->symbolType == SYMBOL_BLOCK) {
        fprintf(out, "_%s_%s", symbol->parent->name, symbol->name);
    }
    // Parameters
    else if (symbol->symbolType == SYMBOL_VARIABLE && symbol->parent && symbol->parent->symbolType == SYMBOL_FUNCTION) {
        fprintf(out, "_%s", symbol->name);
    }
    // Everything else
    else if (symbol->parent && (symbol->parent->symbolType != SYMBOL_TYPE || symbol->symbolType == SYMBOL_FUNCTION) && symbol->parent->parent && !symbol->isExtern) {
        if (symbol->parent->symbolType != SYMBOL_VARIABLE) { // Done so that fields in product/enum types collected by variable types don't have their variable names appended
            // Done so that inner functions print correctly (i think)
            if (symbol->symbolType == SYMBOL_VARIABLE || (symbol->parent->parent->symbolType != SYMBOL_BLOCK && symbol->parent->symbolType != SYMBOL_FUNCTION)) {
                printPath(out, symbol->parent);
            }
            fprintf(out, "_%s", symbol->name);
        } else {
            fprintf(out, "%s", symbol->name);
        }
    } else if (symbol->isExtern) {
        fprintf(out, "%s", symbol->externName);
    } else {
        fprintf(out, "%s", symbol->name);
    }
}

// Prints out the definitions of a product type
static void generateProductParamlist(FILE* out, ASTNode* parameters)
{
    // For each parameter in the procedure's parameter list, print it out
    forall(elem, parameters->product.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        generateDefine(out, var, true, false);
        if (elem != List_End(parameters->product.defines)->prev) {
            fprintf(out, ", ");
        }
    }
}

// Generates a definition of a symbol. May be a regular definition, a function parameter, or a struct field
static void generateDefine(FILE* out, SymbolNode* var, bool param, bool field)
{
    printType(out, var->type);
    fprintf(out, " ");
    bool functionPtr = !var->type->isConst && var->type->astType == AST_FUNCTION;
    if (functionPtr) {
        fprintf(out, "(*");
    }
    if (!field) {
        printPath(out, var);
    } else {
        fprintf(out, "%s", var->name);
    }
    if (functionPtr) {
        fprintf(out, ") (");
        ASTNode* params = var->type->function.domainType;
        generateProductParamlist(out, params);
        fprintf(out, ")");
    }
    if (var->isVararg) {
        fprintf(out, ", ...");
    }
    if (!param) {
        fprintf(out, ";\n");
    }
}

// Prints out a struct from a dependency graph node in such a way that all dependencies are defined
static void generateProduct(FILE* out, DGraph* graphNode)
{
    if (graphNode->visited) {
        return;
    } else {
        graphNode->visited = true;
    }

    // Print out all dependencies
    forall(elem, graphNode->dependencies)
    {
        DGraph* child = elem->data;
        if (child->typeDef->astType == AST_ENUM) {
            generateEnum(out, child);
        } else {
            generateProduct(out, child);
        }
    }

    ASTNode* _struct = graphNode->typeDef;
    fprintf(out, "struct struct_%d {\n", graphNode->id + 1);

    // For each parameter in the procedure's parameter list, print it out
    forall(elem, _struct->product.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
            fprintf(out, "\t");
            generateDefine(out, var, true, true);
            fprintf(out, ";\n");
        }
    }
    fprintf(out, "};\n\n");
}

// Prints out a sum-type struct from a dependency graph node in such a way that all dependencies are defined.
static void generateEnum(FILE* out, DGraph* graphNode)
{
    if (graphNode->visited) {
        return;
    } else {
        graphNode->visited = true;
    }

    // Print out all dependencies
    forall(elem, graphNode->dependencies)
    {
        DGraph* child = elem->data;
        if (child->typeDef->astType == AST_ENUM) {
            generateEnum(out, child);
        } else {
            generateProduct(out, child);
        }
    }

    ASTNode* _enum = graphNode->typeDef;
    fprintf(out, "struct struct_%d {\n\tint64_t tag;\n", graphNode->id + 1);

    int numOfNonVoidMembers = 0;
    forall(elem, _enum->_enum.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* var = define->define.symbol;
        if (var->type->astType != AST_VOID) {
            numOfNonVoidMembers = 1;
            break;
        }
    }

    if (numOfNonVoidMembers > 0) {
        fprintf(out, "\tunion {\n");

        // For each parameter in the procedure's parameter list, print it out
        forall(elem, _enum->_enum.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* var = define->define.symbol;
            if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst) && var->type->astType != AST_VOID) {
                fprintf(out, "\t\t");
                generateDefine(out, var, true, true);
                fprintf(out, ";\n");
            }
        }
        fprintf(out, "\t};\n");
    }
    fprintf(out, "};\n\n");
}

// Takes a list of dependency nodes that are either sum or product types, prints them out
static void generateProductDefinitions(FILE* out, List* depenGraph)
{
    fprintf(out, "/* Struct definitions */\n");
    forall(elem, depenGraph)
    {
        DGraph* graphNode = elem->data;
        if (graphNode->typeDef->astType == AST_ENUM) {
            generateEnum(out, graphNode);
        } else {
            generateProduct(out, graphNode);
        }
    }
}

// Prints out verbatim code for a program. TODO: Remove verbatim code entirely
static void generateVerbatims(FILE* out, List* verbatims)
{
    fprintf(out, "/* Verbatim code */\n");
    forall(elem, verbatims)
    {
        fprintf(out, (char*)elem->data);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

// Prints out the forward function declarations used in the program
static void generateForwardFunctions(FILE* out, CFG* callGraphNode)
{
    if (callGraphNode->visited) {
        return;
    }
    callGraphNode->visited = true;

    SymbolNode* symbol = callGraphNode->symbol;

    ASTNode* functionType = symbol->type;
    ASTNode* params = functionType->function.domainType;
    ASTNode* returns = functionType->function.codomainType;
    if (returns->astType != AST_PRODUCT) {
        printType(out, functionType);
    } else {
        printType(out, returns);
    }
    fprintf(out, " ");
    printPath(out, symbol);
    fprintf(out, "(");
    generateProductParamlist(out, params);
    fprintf(out, ");\n");

    forall(elem, callGraphNode->leaves)
    {
        generateForwardFunctions(out, elem->data);
    }
    callGraphNode->visited = false;
}

// Prints out the definition of a symbol version
static void printVarDef(FILE* out, SymbolVersion* version)
{
    fprintf(out, "\t");
    printType(out, version->type);
    fprintf(out, " ");
    bool functionPtr = version->type->astType == AST_FUNCTION;
    if (functionPtr) {
        fprintf(out, "(*");
    }
    if (version->symbol->name[0] != '$') {
        printPath(out, version->symbol);
    }
    if (!version->symbol->isVolatile) {
        fprintf(out, "_%d", version->version);
    } else {
        //version->symbol->visited = true;
    }
    if (functionPtr) {
        fprintf(out, ") (");
        ASTNode* params = version->type->function.domainType;
        generateProductParamlist(out, params);
        fprintf(out, ")");
    }
    fprintf(out, ";\n");
}

// Prints out the left-hand side of a symbol version assignment
static void printVarAssign(FILE* out, SymbolVersion* version)
{
    fprintf(out, "\t");
    if (!strcmp(version->symbol->name, "$return")) {
        fprintf(out, "retval = ");
    } else {
        if (version->symbol->name[0] != '$') {
            printPath(out, version->symbol);
        }
        if (!version->symbol->isVolatile) {
            fprintf(out, "_%d = ", version->version);
        } else {
            fprintf(out, " = ");
        }
    }
}

// Prints out the name of a symbol version
static void printVar(FILE* out, SymbolVersion* version)
{
    if (version->symbol->name[0] != '$') {
        printPath(out, version->symbol);
    }
    if (!version->symbol->isVolatile) {
        fprintf(out, "_%d", version->version);
    }
}

// Prints out the left side of an assignment to an L-value
static void generateLValueIR(FILE* out, SymbolVersion* version)
{
    if (!version->def || !version->lvalue) {
        printVar(out, version);
    } else {
        switch (version->def->irType) {
        case IR_LOAD_SYMBOL: {
            printPath(out, version->def->symbol);
            break;
        }
        case IR_ADDR_OF: {
            fprintf(out, "(&");
            generateLValueIR(out, version->def->src1);
            fprintf(out, ")");
            break;
        }
        case IR_DEREF: {
            fprintf(out, "(*");
            generateLValueIR(out, version->def->src1);
            fprintf(out, ")");
            break;
        }
        case IR_INDEX: {
            fprintf(out, "(");
            generateLValueIR(out, version->def->src1);
            fprintf(out, ".data[");
            printVar(out, version->def->src2);
            fprintf(out, "])");
            break;
        }
        case IR_DOT: {
            fprintf(out, "(");
            generateLValueIR(out, version->def->src1);
            fprintf(out, ".%s)", version->def->strData);
            break;
        }
        }
    }
}

// Prints out an IR instruction
static void generateIR(FILE* out, CFG* cfg, IR* ir)
{
    // Don't generate L value IRs, UNLESS they are copies
    if (ir->dest && ir->dest->lvalue && ir->irType != IR_COPY && ir->irType != IR_LOAD_ARGLIST && ir->irType != IR_LOAD_ARRAY_LITERAL && ir->irType != IR_LOAD_DEFAULT_ARRAY && ir->irType != IR_LOAD_STRING) {
        return;
    }

    switch (ir->irType) {
    case IR_LOAD_SYMBOL:
    case IR_LOAD_EXTERN: {
        printVarAssign(out, ir->dest);
        printPath(out, ir->symbol);
        fprintf(out, ";\n");
        break;
    }
    case IR_LOAD_INT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "%d;\n", (int)ir->intData);
        break;
    }
    case IR_LOAD_REAL: {
        printVarAssign(out, ir->dest);
        fprintf(out, "%f;\n", ir->realData);
        break;
    }
    case IR_LOAD_ARGLIST:
    case IR_SLICE: {
        printVarAssign(out, ir->dest);
        fprintf(out, "(");
        ASSERT(ir->dest != NULL);
        printType(out, ir->dest->type);
        fprintf(out, ") {");
        forall(elem, ir->listData)
        {
            SymbolVersion* symbver = elem->data;
            printVar(out, symbver);
            if (elem->next != List_End(ir->listData)) {
                fprintf(out, ", ");
            } else {
                fprintf(out, "};\n");
            }
        }
        break;
    }
    case IR_LOAD_ARRAY_LITERAL: {
        printVarAssign(out, ir->dest);
        fprintf(out, "(");
        ASSERT(ir->dest != NULL);
        printType(out, ir->dest->type);
        fprintf(out, ") {%d, (", ir->listData->size);
        printType(out, ((SymbolVersion*)List_Get(ir->listData, 0))->type);
        fprintf(out, "[]){");
        forall(elem, ir->listData)
        {
            SymbolVersion* symbver = elem->data;
            printVar(out, symbver);
            if (elem->next != List_End(ir->listData)) {
                fprintf(out, ", ");
            } else {
                fprintf(out, "}};\n");
            }
        }
        break;
    }
    case IR_LOAD_DEFAULT_ARRAY: {
        fprintf(out, "\tfor(int i = 0; i < ");
        printVar(out, ir->src2);
        fprintf(out, "; i++) {");
        printVar(out, ir->dest);
        fprintf(out, ".data[i] = ");
        printVar(out, ir->src1);
        fprintf(out, ";}\n");
        break;
    }
    case IR_LOAD_STRING: {
        printVarAssign(out, ir->dest);
        fprintf(out, "(");
        ASSERT(ir->dest != NULL);
        printType(out, ir->dest->type);
        fprintf(out, ") {%d, \"%s\"};\n", strlen(ir->strData), ir->strData);
        break;
    }
    case IR_COPY: {
        ASSERT(ir->dest != NULL && ir->dest->type != NULL);
        if (ir->dest->type->astType != AST_VOID) {
            printVarAssign(out, ir->dest);
            printVar(out, ir->src1);
            fprintf(out, ";\n");
        }
        break;
    }
    case IR_BIT_OR: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " | ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_BIT_XOR: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " ^ ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_BIT_AND: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " & ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_EQ: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " == ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_NEQ: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " != ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_GTR: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " > ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_LSR: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " < ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_GTE: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " >= ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_LTE: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " <= ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_LSHIFT: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " << ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_RSHIFT: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " >> ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_ADD: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " + ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_SUBTRACT: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " - ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_MULTIPLY: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " * ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_DIVIDE: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " / ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_MODULUS: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, " %% ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_EXPONENT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "powf(");
        printVar(out, ir->src1);
        fprintf(out, ", ");
        printVar(out, ir->src2);
        fprintf(out, ");\n");
        break;
    }
    case IR_NOT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "!");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_NEG: {
        printVarAssign(out, ir->dest);
        fprintf(out, "-");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_BIT_NOT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "~");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_ADDR_OF: {
        printVarAssign(out, ir->dest);
        fprintf(out, "&");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_SIZEOF: {
        printVarAssign(out, ir->dest);
        fprintf(out, "sizeof(");
        printType(out, ir->fromType);
        fprintf(out, ");\n");
        break;
    }
    case IR_DEREF: {
        printVarAssign(out, ir->dest);
        fprintf(out, "*");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_DEREF_COPY: {
        fprintf(out, "\t*");
        generateLValueIR(out, ir->src1);
        fprintf(out, " = ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_INDEX: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, ".data[");
        printVar(out, ir->src2);
        fprintf(out, "];\n");
        break;
    }
    case IR_INDEX_COPY: {
        fprintf(out, "\t");
        generateLValueIR(out, ir->src1);
        fprintf(out, ".data[");
        printVar(out, ir->src2);
        fprintf(out, "] = ");
        printVar(out, ir->src3);
        fprintf(out, ";\n");
        break;
    }
    case IR_DOT: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, ".%s;\n", ir->strData);
        break;
    }
    case IR_DOT_COPY: {
        fprintf(out, "\t");
        generateLValueIR(out, ir->src1);
        fprintf(out, ".%s = ", ir->strData);
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_CAST: {
        if (ir->toType->astType == AST_ENUM) {
            printVarAssign(out, ir->dest);
            fprintf(out, "*((");
            printType(out, ir->toType);
            fprintf(out, "*) &");
            printVar(out, ir->src1);
            fprintf(out, ");\n");
        } else {
            printVarAssign(out, ir->dest);
            fprintf(out, "(");
            printType(out, ir->toType);
            fprintf(out, ") ");
            printVar(out, ir->src1);
            fprintf(out, ";\n");
        }
        break;
    }
    case IR_NEW: {
        printVarAssign(out, ir->dest);
        fprintf(out, "calloc(sizeof(");
        printType(out, ir->src1->type);
        fprintf(out, "), 1);\n");
        fprintf(out, "\t*");
        printVar(out, ir->dest);
        fprintf(out, " = ");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_NEW_ARR: {
        fprintf(out, "\t");
        SymbolVersion* lastLen = NULL;
        int dim = 0;
        ASSERT(ir->dest != NULL);
        ASTNode* arrType = ir->dest->type;
        forall(elem, ir->listData)
        {
            SymbolVersion* len = elem->data;
            lastLen = len;
            dim++;

            printVar(out, ir->dest);
            for (ListElem* elem2 = List_Begin(ir->listData); elem2 != elem; elem2 = elem2->next) {
                SymbolVersion* len2 = elem2->data;
                fprintf(out, ".data[i");
                printVar(out, len2);
                fprintf(out, "]");
            }
            fprintf(out, " = ");

            fprintf(out, "(");
            printType(out, arrType);
            arrType = AST_GetArrayDataType(arrType);
            fprintf(out, ") ");
            fprintf(out, "{");
            printVar(out, len);
            fprintf(out, ", malloc(sizeof(");
            printType(out, arrType);
            fprintf(out, ") * ");
            printVar(out, len);
            fprintf(out, ")}");

            fprintf(out, "; ");

            fprintf(out, "for (int i");
            printVar(out, len);
            fprintf(out, " = 0; i");
            printVar(out, len);
            fprintf(out, " < ");
            printVar(out, len);
            fprintf(out, "; i");
            printVar(out, len);
            fprintf(out, "++) {");
        }

        printVar(out, ir->dest);
        forall(elem, ir->listData)
        {
            SymbolVersion* len2 = elem->data;
            fprintf(out, ".data[i");
            printVar(out, len2);
            fprintf(out, "]");
        }
        fprintf(out, " = ");
        if (ir->src1) {
            printVar(out, ir->src1);
        } else {
            printVar(out, ir->src2);
            fprintf(out, ".data[i");
            printVar(out, lastLen);
            fprintf(out, "]");
        }
        fprintf(out, ";");
        for (int i = 0; i < dim; i++) {
            fprintf(out, "}");
        }
        fprintf(out, "\n");
        break;
    }
    case IR_FREE: {
        fprintf(out, "\tfree(");
        printVar(out, ir->src1);
        fprintf(out, ");\n");
        break;
    }
    case IR_PHONY: {
        break;
    }
    case IR_DECLARE_LABEL: // Just don't do anything... these instructions are generated at the end of a basic block
    case IR_JUMP:
    case IR_BRANCH_IF_FALSE: {
        break;
    }
    case IR_CALL: {
        stackTracePush(out, "(&stackTrace)");
        fprintf(out, "\"");
        printPos(out, ir->pos);
        fprintf(out, "\";\n");
        ASSERT(ir->dest != NULL && ir->dest->type != NULL);
        if (ir->dest->type->astType != AST_VOID) {
            printVarAssign(out, ir->dest);
        } else {
            fprintf(out, "\t");
        }
        printVar(out, ir->src1);
        fprintf(out, "(");
        forall(elem, ir->listData)
        {
            SymbolVersion* arg = elem->data;
            printVar(out, arg);
            if (elem->next != List_End(ir->listData)) {
                fprintf(out, ", ");
            }
        }
        fprintf(out, ");\n");
        fprintf(out, "\tstackTrace.length--;\n");
        break;
    }
    case IR_PUSH_STACK_TRACE: {
        stackTracePush(out, "(&errorTrace)");
        fprintf(out, "\"");
        printPos(out, ir->pos);
        fprintf(out, "\";\n");
        break;
    }
    case IR_CLEAR_STACK_TRACE: {
        fprintf(out, "\terrorTrace.length = 0;\n");
        break;
    }
    case IR_ERROR: {
        fprintf(out, "\tfprintf(stderr, \"error: %s\\n\");\n", ir->strData);
        stackTracePush(out, "(&stackTrace)");
        fprintf(out, "\"");
        printPos(out, ir->pos);
        fprintf(out, "\";\n\tstackTracePrintReverse(&stackTrace);\n\texit(1);\n");
        break;
    }
    default: {
        PANIC("unknown IR");
    }
    }
}

// Prints out the phi parameter-argument copies between basic block jumps
static void generatePhi(FILE* out, List* argsList, BasicBlock* to, bool extraTab)
{
    forall(elem, argsList)
    {
        SymbolVersion* argument = elem->data;
        SymbolVersion* parameter = NULL;
        forall(elem2, to->parameters)
        {
            SymbolVersion* symbver = elem2->data;
            if (symbver->symbol == argument->symbol) {
                parameter = symbver;
                break;
            }
        }
        if (parameter) {
            if (extraTab) {
                fprintf(out, "\t");
            }
            printVarAssign(out, parameter);
            printVar(out, argument);
            fprintf(out, ";\n");
        }
    }
}

// Prints the copies of the function's arguments to the functions root basic-block's phi parameters
static void generatePhiFunction(FILE* out, CFG* cfg)
{
    forall(elem, cfg->symbol->type->function.domainType->product.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* symbol = define->define.symbol;

        SymbolVersion* parameter = NULL;
        forall(elem2, cfg->blockGraph->parameters)
        {
            SymbolVersion* symbver = elem2->data;
            if (!strcmp(symbver->symbol->name, symbol->name)) {
                parameter = symbver;
                break;
            }
        }
        if (parameter) {
            printVarAssign(out, parameter);
            printPath(out, symbol);
            fprintf(out, ";\n");
        }
    }
}

// Prints out a basic block
static void generateBasicBlock(FILE* out, CFG* cfg, BasicBlock* bb)
{
    if (bb->visited) {
        return;
    }
    bb->visited = true;
    fprintf(out, "L%d:;\n", bb->id);
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        generateIR(out, cfg, ir);
    }

    if (bb->hasBranch) {
        fprintf(out, "\tif (!");
        printVar(out, bb->condition);
        fprintf(out, ") {\n");
        generatePhi(out, bb->branchArguments, bb->branch, true);
        if (bb->branch) {
            fprintf(out, "\t\tgoto L%d;\n\t} else {\n", (int)bb->branch->id);
        } else {
            fprintf(out, "\t\tgoto end;\n\t} else {\n");
        }
        generatePhi(out, bb->nextArguments, bb->next, true);
        if (bb->next) {
            fprintf(out, "\t\tgoto L%d;\n\t}\n", (int)bb->next->id);
            generateBasicBlock(out, cfg, bb->next);
        } else {
            fprintf(out, "\t\tgoto end;\n\t}\n");
        }
        if (bb->branch) {
            generateBasicBlock(out, cfg, bb->branch);
        }
    } else if (bb->next) {
        generatePhi(out, bb->nextArguments, bb->next, false);
        fprintf(out, "\tgoto L%d;\n", (int)bb->next->id);
        generateBasicBlock(out, cfg, bb->next);
    } else {
        fprintf(out, "\tgoto end;\n");
    }
}

// Prints out the definition for a function
static void generateFunctionDefinitions(FILE* out, CFG* callGraphNode)
{
    if (callGraphNode->visited) {
        return;
    }
    callGraphNode->visited = true;

    SymbolNode* symbol = callGraphNode->symbol;

    ASTNode* functionType = symbol->type;
    ASTNode* params = functionType->function.domainType;
    ASTNode* returns = functionType->function.codomainType;
    if (returns->astType != AST_PRODUCT) {
        printType(out, functionType);
    } else {
        printType(out, returns);
    }
    fprintf(out, " ");
    printPath(out, symbol);
    fprintf(out, "(");
    generateProductParamlist(out, params);
    fprintf(out, ")\n{\n");
    if (callGraphNode->symbol->type->function.codomainType->astType != AST_VOID) {
        fprintf(out, "\t");
        printType(out, returns);
        fprintf(out, " retval;\n");
    }
    forall(elem, callGraphNode->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            SymbolVersion* symbver = ir->dest;
            if (!symbver // Symbvers cant be null
                || !symbver->used // Symbols must be used of course
                //|| symbver->symbol->visited // Uncommenting this prevents symbols in methods from being generated properly
                || symbver->type->astType == AST_VOID // Not allowed in C, sometimes allowable in Orng
                || symbver->def != ir // Prevents Phi noded symbols from having every def of them declared more than once
            ) {
                continue;
            }
            printVarDef(out, symbver);
        }
        forall(elem2, bb->parameters)
        {
            SymbolVersion* symbver = elem2->data;
            printVarDef(out, symbver);
        }
    }
    if (callGraphNode->blockGraph) {
        generatePhiFunction(out, callGraphNode);
        generateBasicBlock(out, callGraphNode, callGraphNode->blockGraph);
    }
    fprintf(out, "end:;\n");
    if (callGraphNode->symbol->type->function.codomainType->astType != AST_VOID) {
        fprintf(out, "\treturn retval;\n}\n\n");
    } else {
        fprintf(out, "\treturn;\n}\n\n");
    }

    forall(elem, callGraphNode->leaves)
    {
        generateFunctionDefinitions(out, elem->data);
    }
    callGraphNode->visited = false;
}

// Prints out the main function
static void generateMainFunction(FILE* out, CFG* callGraph)
{
    fprintf(out, "void pause() {system(\"pause\");}\n\n");

    fprintf(out, "int main(int argc, char** argv)\n");

    fprintf(out, "{\n");

    fprintf(out, "\tatexit(pause);\n");

    fprintf(out, "\t");
    printType(out, STRING_ARR_TYPE);
    fprintf(out, " args = {argc, calloc(sizeof(");
    printType(out, STRING_TYPE);
    fprintf(out, ") * argc, 1)};\n");

    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");

    fprintf(out, "\t\tint length = strlen(argv[i]);\n");

    fprintf(out, "\t\targs.data[i] = (");
    printType(out, STRING_TYPE);
    fprintf(out, "){length, calloc(sizeof(char) * (length + 1), 1)};\n");

    fprintf(out, "\t\tmemcpy(args.data[i].data, argv[i], length);\n");

    fprintf(out, "\t}\n");

    fprintf(out, "\t");
    printType(out, callGraph->symbol->type->function.codomainType);
    fprintf(out, " retval = ");
    printPath(out, callGraph->symbol);
    fprintf(out, "(args);\n");

    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");

    fprintf(out, "\t\tfree(args.data[i].data);\n");

    fprintf(out, "\t}\n");

    fprintf(out, "\tfree(args.data);\n");

    fprintf(out, "\tif (errorTrace.length > 0) {\n\t\tfprintf(stderr, \"error: %%s\\n\", tagGetFieldName(retval.tag));\n\t}\n\tstackTracePrint(&errorTrace);\n\treturn retval.tag != %d;\n", (int)getTag("success", VOID_TYPE));

    fprintf(out, "}\n");
}

// Prints out the Orng program
void Generator_Generate(FILE* out)
{
    srand((int)time(0));
    int randID = rand();
    fprintf(out, "/* Code generated using the Orng compiler http://josephs-projects.com */\n");
    fprintf(out, "\n#ifndef ORNG_%s\n#define ORNG_%s\n#define _CRT_SECURE_NO_WARNINGS\n\n", myItoa(randID), myItoa(randID));
    generateIncludes(out, program->includes);
    generateDebug(out);
    generateProductDefinitions(out, program->typeDependencyGraph);
    generateVerbatims(out, program->verbatims);
    fprintf(out, "/* Function definitions */\n");
    generateForwardFunctions(out, program->callGraph);
    fprintf(out, "\n");
    generateFunctionDefinitions(out, program->callGraph);
    generateMainFunction(out, program->callGraph);

    fprintf(out, "#endif\n");
}