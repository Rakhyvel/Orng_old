#include "generator.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "./ir.h"
#include "./main.h"
#include "./parse.h"
#include "./position.h"
#include "./validator.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

Program program;

static void generateDefine(FILE* out, SymbolNode* var, bool param);
static void generateUnion(FILE* out, DGraph* graphNode);

static void generateIncludes(FILE* out, Map* includes)
{
    fprintf(out, "/* Includes */\n");
    List* keys = includes->keyList;
    ListElem* e = List_Begin(keys);
    for (; e != List_End(keys); e = e->next) {
        char* include = e->data;
        if (include[0] == '<') {
            fprintf(out, "#include %s\n", include);
        } else {
            fprintf(out, "#include \"%s\"\n", include);
        }
    }
    fprintf(out, "\n");
}

static void printStructOrd(FILE* out, ASTNode* type)
{
    struct listElem* elem = List_Begin(program.structDependencyGraph);
    int i = 1;
    bool found = false;
    for (; !found && elem != List_End(program.structDependencyGraph); elem = List_Next(elem), i++) {
        DGraph* node = (DGraph*)elem->data;
        ASTNode* child = node->structDef;
        if (typesAreEquivalent(child, type)) {
            fprintf(out, "struct_%s", myItoa(i));
            found = true;
        }
    }
}

static void printType(FILE* out, ASTNode* type)
{
    switch (type->astType) {
    case AST_IDENT:
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
    case AST_DOT:
        SymbolNode* var = type->dot.symbol;
        if (var->isExtern) {
            fprintf(out, "%s", var->externName);
        } else {
            printType(out, type->type);
        }
        break;
    case AST_ADDR:
        printType(out, type->unop.expr);
        fprintf(out, "*");
        break;
    case AST_ARRAY:
    case AST_PARAMLIST:
    case AST_UNIONSET: {
        fprintf(out, "struct ");
        printStructOrd(out, type);
    } break;
    case AST_VOID: {
        fprintf(out, "void");
        break;
    }
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
        if (symbol->parent->symbolType != SYMBOL_VARIABLE) { // Done so that fields in anon structs collected by variable types don't have their variable names appended
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

static void generateParamList(FILE* out, ASTNode* parameters)
{
    ListElem* paramElem = List_Begin(parameters->paramlist.defines);
    // For each parameter in the procedure's parameter list, print it out
    for (; paramElem != List_End(parameters->paramlist.defines); paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* var = define->define.symbol;
        generateDefine(out, var, true);
        if (paramElem != List_End(parameters->paramlist.defines)->prev) {
            fprintf(out, ", ");
        }
    }
}

static void generateDefine(FILE* out, SymbolNode* var, bool param)
{
    printType(out, var->type);
    fprintf(out, " ");
    bool functionPtr = !var->type->isConst && var->type->astType == AST_FUNCTION;
    if (functionPtr) {
        fprintf(out, "(*");
    }
    printPath(out, var);
    if (functionPtr) {
        fprintf(out, ") (");
        ASTNode* params = var->type->function.domainType;
        generateParamList(out, params);
        fprintf(out, ")");
    }
    if (var->isVararg) {
        fprintf(out, ", ...");
    }
    if (!param) {
        fprintf(out, ";\n");
    }
}

static void generateStruct(FILE* out, DGraph* graphNode)
{
    if (graphNode->visited) {
        return;
    } else {
        graphNode->visited = true;
    }

    // Print out all dependencies
    ListElem* elem = List_Begin(graphNode->dependencies);
    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
        DGraph* child = elem->data;
        if (child->structDef->astType == AST_UNIONSET) {
            generateUnion(out, child);
        } else {
            generateStruct(out, child);
        }
    }

    ASTNode* _struct = graphNode->structDef;
    char* structOrdStr = myItoa(graphNode->ordinal + 1);
    fprintf(out, "struct struct_%s {\n", structOrdStr);

    ListElem* paramElem = List_Begin(_struct->paramlist.defines);
    // For each parameter in the procedure's parameter list, print it out
    for (; paramElem != List_End(_struct->paramlist.defines); paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* var = define->define.symbol;
        if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
            fprintf(out, "\t");
            generateDefine(out, var, true);
            fprintf(out, ";\n");
        }
    }
    fprintf(out, "};\n\n");
}

static void generateUnion(FILE* out, DGraph* graphNode)
{
    if (graphNode->visited) {
        return;
    } else {
        graphNode->visited = true;
    }

    // Print out all dependencies
    ListElem* elem = List_Begin(graphNode->dependencies);
    for (; elem != List_End(graphNode->dependencies); elem = elem->next) {
        DGraph* child = elem->data;
        if (child->structDef->astType == AST_UNIONSET) {
            generateUnion(out, child);
        } else {
            generateStruct(out, child);
        }
    }

    ASTNode* _union = graphNode->structDef;
    char* structOrdStr = myItoa(graphNode->ordinal + 1);
    fprintf(out, "struct struct_%s {\n\tint64_t tag;\n", structOrdStr);

    int numOfNonVoidMembers = 0;
    ListElem* paramElem = List_Begin(_union->unionset.defines);
    for (; paramElem != List_End(_union->unionset.defines); paramElem = paramElem->next) {
        ASTNode* define = paramElem->data;
        SymbolNode* var = define->define.symbol;
        if (var->type->astType != AST_VOID) {
            numOfNonVoidMembers = 1;
            break;
        }
    }

    if (numOfNonVoidMembers > 0) {
        fprintf(out, "\tunion {\n");

        paramElem = List_Begin(_union->unionset.defines);
        // For each parameter in the procedure's parameter list, print it out
        for (; paramElem != List_End(_union->unionset.defines); paramElem = paramElem->next) {
            ASTNode* define = paramElem->data;
            SymbolNode* var = define->define.symbol;
            if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst) && var->type->astType != AST_VOID) {
                fprintf(out, "\t\t");
                generateDefine(out, var, true);
                fprintf(out, ";\n");
            }
        }
        fprintf(out, "\t};\n");
    }
    fprintf(out, "};\n\n");
}

static void generateStructDefinitions(FILE* out, List* depenGraph)
{
    fprintf(out, "/* Struct definitions */\n");
    ListElem* elem = List_Begin(depenGraph);
    for (; elem != List_End(depenGraph); elem = elem->next) {
        DGraph* graphNode = elem->data;
        if (graphNode->structDef->astType == AST_UNIONSET) {
            generateUnion(out, graphNode);
        } else {
            generateStruct(out, graphNode);
        }
    }
}

static void generateForwardStrings(FILE* out, List* strings)
{
    fprintf(out, "/* Forward string declarations */\n");
    ListElem* elem = List_Begin(strings);
    int i = -1;
    for (; elem != List_End(strings); elem = elem->next) {
        i++;
        ASTNode* node = elem->data;
        printType(out, STRING_TYPE);
        fprintf(out, " string_%d;\n", i);
    }
    fprintf(out, "\n");
}

void generateForwardFunctions(FILE* out, CFG* callGraphNode)
{
    if (callGraphNode->visited) {
        return;
    }
    callGraphNode->visited = true;

    SymbolNode* symbol = callGraphNode->symbol;

    ASTNode* functionType = symbol->type;
    ASTNode* params = functionType->function.domainType;
    ASTNode* returns = functionType->function.codomainType;
    if (returns->astType != AST_PARAMLIST) {
        printType(out, functionType);
    } else {
        printType(out, returns);
    }
    fprintf(out, " ");
    printPath(out, symbol);
    fprintf(out, "(");
    generateParamList(out, params);
    fprintf(out, ");\n");

    forall(elem, callGraphNode->leaves)
    {
        generateForwardFunctions(out, elem->data);
    }
    callGraphNode->visited = false;
}

static void generateString(FILE* out, char* string)
{
    int backslashes = 0;
    for (int j = 0; j < strlen(string); j++) {
        if (string[j] == '\\') {
            backslashes++;
        }
    }
    fprintf(out, "{%d, (char[]){", strlen(string) - backslashes);
    for (int j = 0; j < strlen(string); j++) {
        char c = string[j];
        if (c == '\\') {
            fprintf(out, "'%c", c);
            j++;
            fprintf(out, "%c', ", string[j]);
        } else if (c == '\'') {
            fprintf(out, "'\\'', ");
        } else {
            fprintf(out, "'%c', ", c);
        }
    }
    fprintf(out, "'\\0'}};\n");
}

static void generateStrings(FILE* out, List* strings)
{
    fprintf(out, "/* String definitions */\n");
    ListElem* elem = List_Begin(strings);
    int i = -1;
    for (; elem != List_End(strings); elem = elem->next) {
        i++;
        ASTNode* node = elem->data;

        printType(out, STRING_TYPE);
        fprintf(out, " string_%d = ", i);
        generateString(out, node->string.data);
    }
    fprintf(out, "\n");
}

void printVarDef(FILE* out, SymbolVersion* version)
{
    fprintf(out, "\tregister ");
    printType(out, version->type);
    fprintf(out, " ");
    if (version->symbol->name[0] != '$') {
        printPath(out, version->symbol);
    }
    if (!version->symbol->isVolatile) {
        fprintf(out, "_%d;\n", version->version);
    } else {
        fprintf(out, ";\n");
        version->symbol->visited = true;
    }
}

void printVarAssign(FILE* out, SymbolVersion* version)
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

void printVar(FILE* out, SymbolVersion* version)
{
    if (version->symbol->name[0] != '$') {
        printPath(out, version->symbol);
    }
    if (!version->symbol->isVolatile) {
        fprintf(out, "_%d", version->version);
    }
}

static void generateIR(FILE* out, CFG* cfg, IR* ir)
{
    switch (ir->irType) {
    case IR_LOAD_INT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "%d;\n", (int)ir->intData);
        break;
    }
    case IR_LOAD_REAL: {
        printVarAssign(out, ir->dest);
        fprintf(out, "%f;\n", ir->doubleData);
        break;
    }
    case IR_LOAD_ARRAY_LITERAL: {
        printVarAssign(out, ir->dest);
        fprintf(out, "(");
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
    case IR_LOAD_ARGLIST: {
        printVarAssign(out, ir->dest);
        fprintf(out, "(");
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
    case IR_COPY: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_DECLARE_LABEL: // Just don't do anything... these instructions are generated at the end of a basic block
    case IR_JUMP:
    case IR_BRANCH_IF_FALSE: {
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
        printVar(out, ir->dest);
        fprintf(out, ".data[");
        printVar(out, ir->src1);
        fprintf(out, "] = ");
        printVar(out, ir->src2);
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
        printVar(out, ir->dest);
        fprintf(out, ".%s = ", ir->strData);
        printVar(out, ir->src1);
        fprintf(out, ";\n");
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
    case IR_NOT: {
        printVarAssign(out, ir->dest);
        fprintf(out, "!");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_NEGATE: {
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
    case IR_DEREF: {
        printVarAssign(out, ir->dest);
        fprintf(out, "*");
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_DEREF_COPY: {
        fprintf(out, "\t*");
        printVar(out, ir->src1);
        fprintf(out, " = ");
        printVar(out, ir->src2);
        fprintf(out, ";\n");
        break;
    }
    case IR_CONVERT: {
        printVarAssign(out, ir->dest);
        printVar(out, ir->src1);
        fprintf(out, ";\n");
        break;
    }
    case IR_PHONY: {
        break;
    }
    default: {
        PANIC("unknown IR");
    }
    }
}

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
        } else {
        }
    }
}

static void generateBasicBlock(FILE* out, CFG* cfg, BasicBlock* bb)
{
    if (bb->visited) {
        return;
    }
    bb->visited = true;
    fprintf(out, "L%d:; // incoming:%d\n", bb->id, bb->incoming);
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        generateIR(out, cfg, ir);
    }

    if (bb->hasBranch) {
        fprintf(out, "\tif (!");
        printVar(out, bb->condition);
        fprintf(out, ") {\n");
        generatePhi(out, bb->branchArguments, bb->branch, true);
        fprintf(out, "\t\tgoto L%d;\n\t} else {\n", (int)bb->branch->id);
        generatePhi(out, bb->nextArguments, bb->next, true);
        fprintf(out, "\t\tgoto L%d;\n\t}\n", (int)bb->next->id);
        generateBasicBlock(out, cfg, bb->next);
        generateBasicBlock(out, cfg, bb->branch);
    } else if (bb->next) {
        generatePhi(out, bb->nextArguments, bb->next, false);
        fprintf(out, "\tgoto L%d;\n", (int)bb->next->id);
        generateBasicBlock(out, cfg, bb->next);
    } else {
        fprintf(out, "\tgoto end;\n");
    }
}

void generateFunctionDefinitions(FILE* out, CFG* callGraphNode)
{
    if (callGraphNode->visited) {
        return;
    }
    callGraphNode->visited = true;

    SymbolNode* symbol = callGraphNode->symbol;

    ASTNode* functionType = symbol->type;
    ASTNode* params = functionType->function.domainType;
    ASTNode* returns = functionType->function.codomainType;
    if (returns->astType != AST_PARAMLIST) {
        printType(out, functionType);
    } else {
        printType(out, returns);
    }
    fprintf(out, " ");
    printPath(out, symbol);
    fprintf(out, "(");
    generateParamList(out, params);
    fprintf(out, ")\n{\n\t");
    printType(out, returns);
    fprintf(out, " retval;\n");
    forall(elem, callGraphNode->symbolVersions)
    {
        SymbolVersion* symbver = elem->data;
        if (!symbver->used || symbver->symbol->visited) {
            continue;
        }
        printVarDef(out, symbver);
    }
    clearBBVisitedFlags(callGraphNode);
    generateBasicBlock(out, callGraphNode, callGraphNode->blockGraph);
    fprintf(out, "end:;\n\treturn retval;\n}\n\n");

    forall(elem, callGraphNode->leaves)
    {
        generateFunctionDefinitions(out, elem->data);
    }
    callGraphNode->visited = false;
}

void generateMainFunction(FILE* out, CFG* callGraph)
{
    fprintf(out, "\int main(int argc, char** argv)\n");

    fprintf(out, "{\n");

    fprintf(out, "\t");
    printType(out, STRING_ARR_TYPE);
    fprintf(out, " args = {argc, calloc(sizeof(");
    printType(out, STRING_TYPE);
    fprintf(out, ") * argc, 1)};\n");

    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");

    fprintf(out, "\t\tint length = strlen(argv[i]);\n");

    fprintf(out, "\t\targs.data[i] = (");
    printType(out, STRING_TYPE);
    fprintf(out, "){length, calloc(sizeof(char) * length, 1)};\n");

    fprintf(out, "\t\tmemcpy(args.data[i].data, argv[i], length);\n");

    fprintf(out, "\t}\n");

    fprintf(out, "\tint64_t retval = ");
    printPath(out, callGraph->symbol);
    fprintf(out, "(args);\n");

    fprintf(out, "\tfor (int  i = 0; i < argc; i++) {\n");

    fprintf(out, "\t\tfree(args.data[i].data);\n");

    fprintf(out, "\t}\n");

    fprintf(out, "\tfree(args.data);\n");

    fprintf(out, "\tsystem(\"pause\");\n\treturn retval;\n");

    fprintf(out, "}\n");
}

void Generator_Generate(FILE* out, Program _program)
{
    program = _program;

    srand(time(0));
    int randID = rand();
    fprintf(out, "/* Code generated using Orange Translator http://josephs-projects.com */\n\n");
    generateIncludes(out, program.includes);
    generateStructDefinitions(out, program.structDependencyGraph);
    generateForwardStrings(out, program.strings);
    generateForwardFunctions(out, program.callGraph);
    fprintf(out, "\n#ifndef ORANGE_PROGRAM_%s\n#define ORANGE_PROGRAM_%s\n\n", myItoa(randID), myItoa(randID));
    generateStrings(out, program.strings);
    generateFunctionDefinitions(out, program.callGraph);
    generateMainFunction(out, program.callGraph);

    fprintf(out, "#endif\n");
}