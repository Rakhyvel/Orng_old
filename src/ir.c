// © 2021-2022 Joseph Shimel. All rights reserved.

#define _CRT_SECURE_NO_WARNINGS
#include "./ir.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./main.h"
#include "./parse.h"
#include "./symbol.h"
#include "./validator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolVersion* flattenAST(CFG* cfg, ASTNode* node, IR* returnLabel, IR* breakLabel, IR* continueLabel, IR* errorLabel, bool lvalue);

char* IR_ToString(ir_type type)
{
    switch (type) {
    case IR_LOAD_SYMBOL:
        return "IR_LOAD_SYMBOL";
    case IR_LOAD_EXTERN:
        return "IR_LOAD_EXTERN";
    case IR_LOAD_INT:
        return "IR_LOAD_INT";
    case IR_LOAD_REAL:
        return "IR_LOAD_REAL";
    case IR_LOAD_ARGLIST:
        return "IR_LOAD_ARGLIST";
    case IR_LOAD_ARRAY_LITERAL:
        return "IR_LOAD_ARRAY_LITERAL";
    case IR_LOAD_DEFAULT_ARRAY:
        return "IR_LOAD_DEFAULT_ARRAY";
    case IR_LOAD_STRING:
        return "IR_LOAD_STRING";
    case IR_COPY:
        return "IR_COPY";
    case IR_BIT_OR:
        return "IR_BIT_OR";
    case IR_BIT_XOR:
        return "IR_BIT_XOR";
    case IR_BIT_AND:
        return "IR_BIT_AND";
    case IR_EQ:
        return "IR_EQ";
    case IR_NEQ:
        return "IR_NEQ";
    case IR_GTR:
        return "IR_GTR";
    case IR_LSR:
        return "IR_LSR";
    case IR_GTE:
        return "IR_GTE";
    case IR_LTE:
        return "IR_LTE";
    case IR_LSHIFT:
        return "IR_LSHIFT";
    case IR_RSHIFT:
        return "IR_RSHIFT";
    case IR_ADD:
        return "IR_ADD";
    case IR_SUBTRACT:
        return "IR_SUB";
    case IR_MULTIPLY:
        return "IR_MULTIPLY";
    case IR_DIVIDE:
        return "IR_DIVIDE";
    case IR_MODULUS:
        return "IR_MODULUS";
    case IR_EXPONENT:
        return "IR_EXPONENT";
    case IR_NOT:
        return "IR_NOT";
    case IR_NEG:
        return "IR_NEG";
    case IR_BIT_NOT:
        return "IR_BIT_NOT";
    case IR_ADDR_OF:
        return "IR_ADDR_OF";
    case IR_SIZEOF:
        return "IR_SIZEOF";
    case IR_DEREF:
        return "IR_DEREF";
    case IR_DEREF_COPY:
        return "IR_DEREF_COPY";
    case IR_INDEX:
        return "IR_INDEX";
    case IR_INDEX_COPY:
        return "IR_INDEX_COPY";
    case IR_SLICE:
        return "IR_SLICE";
    case IR_DOT:
        return "IR_DOT";
    case IR_DOT_COPY:
        return "IR_DOT_COPY";
    case IR_CAST:
        return "IR_CAST";
    case IR_NEW:
        return "IR_NEW";
    case IR_NEW_ARR:
        return "IR_NEW_ARR";
    case IR_FREE:
        return "IR_FREE";
    case IR_PHONY:
        return "IR_PHONY";
    case IR_DECLARE_LABEL:
        return "IR_DECLARE_LABEL";
    case IR_JUMP:
        return "IR_JUMP";
    case IR_BRANCH_IF_FALSE:
        return "IR_BRANCH_IF_FALSE";
    case IR_CALL:
        return "IR_CALL";
    case IR_PUSH_STACK_TRACE:
        return "IR_PUSH_STACK_TRACE";
    case IR_CLEAR_STACK_TRACE:
        return "IR_CLEAR_STACK_TRACE";
    case IR_ERROR:
        return "IR_ERROR";
    }
}

void printSymbver(SymbolVersion* symbver)
{
    if (symbver) {
        if (symbver->symbol->isVolatile) {
            printf("V");
        }
        printf("%s_%d\t", symbver->symbol->name, symbver->version);
    } else {
        printf("<NULL>\t");
    }
}

void printIR(IR* ir)
{
    if (!ir) {
        printf("<NULL>\n");
    } else if (ir->irType == IR_DECLARE_LABEL) {
        printf("L%d:\n", ir->id);
    } else {
        char* mnemonic = IR_ToString(ir->irType);
        int length = strlen(mnemonic);
        printf("%d\t%s", ir->id, mnemonic);
        for (int i = 20 - length; i >= 0; i--) {
            printf(" ");
        }
        printSymbver(ir->dest);
        printSymbver(ir->src1);
        printSymbver(ir->src2);
        printf("\trem:%d", ir->removed);
        printf("\tin L%d", ir->inBlock ? ir->inBlock->id : 0);
        if (ir->irType == IR_BRANCH_IF_FALSE && ir->branch) {
            printf("\tL%d", ir->branch->id);
        } else if (ir->irType == IR_JUMP && ir->branch) {
            printf("\tL%d", ir->branch->id);
        } else if (ir->irType == IR_LOAD_INT) {
            printf("\tint:%d", (int)ir->intData);
        } else if (ir->irType == IR_LOAD_REAL) {
            printf("\treal:%f", ir->doubleData);
        } else if (ir->irType == IR_PHONY) {
            printf("\tsize:%d", ir->listData->size);
        }
        printf("\n");
    }
}

void printInstructionList(CFG* cfg)
{
    for (IR* ir = cfg->head; ir != NULL; ir = ir->next) {
        printIR(ir);
    }
}

void printSymbverList(List* list)
{
    printf("(");
    forall(elem, list)
    {
        SymbolVersion* symbver = elem->data;
        printf("%s_%d", symbver->symbol->name, symbver->version);
        if (elem->next != List_End(list)) {
            printf(", ");
        }
    }
    printf(")\n");
}

void printBlockGraph(BasicBlock* bb)
{
    if (!bb || bb->visited) {
        return;
    }
    bb->visited = true;
    printf("Basic Block L%d", bb->id);
    printSymbverList(bb->parameters);
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        printIR(ir);
    }
    if (bb->hasBranch) {
        if (bb->branch) {
            printf("if (!%s_%d) goto %d", bb->condition->symbol->name, bb->condition->version, bb->branch->id);
        } else {
            printf("if (!%s_%d) goto <END>", bb->condition->symbol->name, bb->condition->version);
        }
        printSymbverList(bb->branchArguments);
    }
    if (bb->next) {
        printf("goto %d", bb->next->id);
        printSymbverList(bb->nextArguments);
        printf("\n");
    } else {
        printf("goto <END>");
        printSymbverList(bb->nextArguments);
        printf("\n");
    }
    if (bb->hasBranch) {
        printBlockGraph(bb->branch);
    }
    printBlockGraph(bb->next);
}

BasicBlock* createBasicBlock(CFG* cfg)
{
    static int blockID = 0;
    BasicBlock* retval = calloc(sizeof(BasicBlock), 1);
    retval->id = blockID;
    retval->parameters = List_Create();
    retval->nextArguments = List_Create();
    retval->branchArguments = List_Create();
    blockID++;
    List_Append(cfg->basicBlocks, retval);
    return retval;
}

IR* createIR(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, struct position pos)
{
    static int id = 0;
    IR* retval = calloc(sizeof(IR), 1);
    if (!retval) {
        gen_error("out of memory");
    }
    retval->irType = type;
    retval->pos = pos;
    retval->dest = dest;
    retval->src1 = src1;
    retval->src2 = src2;
    retval->id = id++;
    return retval;
}

IR* createIR_int(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, int64_t data, struct position pos)
{
    IR* retval = createIR(type, dest, src1, src2, pos);
    retval->intData = data;
    return retval;
}

IR* createIR_double(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, double data, struct position pos)
{
    IR* retval = createIR(type, dest, src1, src2, pos);
    retval->doubleData = data;
    return retval;
}

IR* createIR_branch(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, IR* data, struct position pos)
{
    IR* retval = createIR(type, dest, src1, src2, pos);
    retval->branch = data;
    return retval;
}

IR* createIR_symbol(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, SymbolVersion* data, struct position pos)
{
    IR* retval = createIR(type, dest, src1, src2, pos);
    retval->symbver = data;
    return retval;
}

IR* createIR_ast(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, ASTNode* from, ASTNode* to, struct position pos)
{
    IR* retval = createIR(type, dest, src1, src2, pos);
    retval->fromType = from;
    retval->toType = to;
    return retval;
}

IR* createIR_label(struct position pos)
{
    IR* retval = createIR(IR_DECLARE_LABEL, NULL, NULL, NULL, pos);
    return retval;
}

void putSymbolVersion(List* symbolVersions, SymbolVersion* symver)
{
    forall(elem, symbolVersions)
    {
        SymbolVersion* data = elem->data;
        if (data->symbol == symver->symbol && data->version == symver->version) {
            return;
        }
    }
    List_Append(symbolVersions, symver);
}

SymbolVersion* unversionedSymbolVersion(CFG* cfg, SymbolNode* symbol, ASTNode* type)
{
    SymbolVersion* retval = calloc(sizeof(SymbolVersion), 1);
    retval->symbol = symbol;
    retval->version = -1;
    retval->type = type;
    retval->used = false;
    return retval;
}

void makeSymbolVersionUnique(SymbolVersion* symbver)
{
    if (symbver->version != -1) {
        return;
    } else {
        symbver->version = symbver->symbol->versions->size;
        List_Append(symbver->symbol->versions, symbver);
    }
}

SymbolVersion* tempSymbolVersion(CFG* cfg, ASTNode* type)
{
    SymbolVersion* retval = unversionedSymbolVersion(cfg, cfg->tempSymbol, type);
    makeSymbolVersionUnique(retval);
    return retval;
}

/*
Starts at the given IR, goes until the given stop IR. Finds the first symbol version with the same symbol that is defined in the block
*/
SymbolVersion* findVersion(SymbolVersion* symbver, IR* ir, IR* stop)
{
    SymbolVersion* retval = symbver;
    for (; ir != NULL && ir != stop; ir = ir->next) {
        if (ir->dest != NULL && ir->dest->symbol == symbver->symbol) {
            retval = ir->dest;
        }
    }
    return retval;
}

// Finds the first def and version
SymbolVersion* findDef(SymbolVersion* symbver, IR* ir, IR* stop)
{
    SymbolVersion* retval = symbver;
    for (; ir != NULL && ir != stop; ir = ir->next) {
        if (ir->dest != NULL && ir->dest->symbol == symbver->symbol && ir->dest->version == symbver->version) {
            retval = ir->dest;
        }
    }
    return NULL;
}

bool putSymbolVersionSet(List* set, SymbolVersion* symbver)
{
    forall(elem, set)
    {
        SymbolVersion* var = elem->data;
        if (var->symbol == symbver->symbol) {
            return false;
        }
    }
    List_Append(set, symbver);
    return true;
}

SymbolVersion* findSymbolVersionSet(List* set, SymbolVersion* symbver)
{
    forall(elem, set)
    {
        SymbolVersion* var = elem->data;
        if (var->symbol == symbver->symbol) {
            return var;
        }
    }
    return NULL;
}

void appendInstruction(CFG* cfg, IR* ir)
{
    if (cfg->head == NULL) {
        cfg->head = ir;
    } else if (cfg->tail == NULL) {
        cfg->head->next = ir;
        cfg->tail = ir;
        cfg->tail->prev = cfg->head;
    } else {
        cfg->tail->next = ir;
        ir->prev = cfg->tail;
        cfg->tail = ir;
    }
}

IR* getTail(IR* head)
{
    for (; head->next != NULL; head = head->next) { }
    return head;
}

IR* appendInstructionBasicBlock(BasicBlock* bb, IR* ir)
{
    if (bb->entry == NULL) {
        bb->entry = ir;
    } else {
        ir->inBlock = bb;
        IR* elem = getTail(bb->entry);
        elem->next = ir;
        ir->prev = elem;
    }
    return ir;
}

void removeInstruction(BasicBlock* bb, IR* ir)
{
    //printf("removed instruction %d\n", ir->id);
    ir->removed = true;
    if (bb->entry == ir) {
        bb->entry = ir->next;
    }
    if (ir->prev) {
        ir->prev->next = ir->next;
    }
    if (ir->next) {
        ir->next->prev = ir->prev;
    }
}

void removeBasicBlock(CFG* cfg, BasicBlock* bb, bool wipeIR)
{
    //printf("removed block %d\n", bb->id);
    List_Remove(cfg->basicBlocks, bb);
    if (wipeIR) {
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            ir->removed = true;
        }
    }
}

void clearBBVisitedFlags(CFG* cfg)
{
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        bb->visited = false;
    }
}

// Whenever execution exits a block, run the defers in reverse order
// If execution reaches end of block, run all defers
// If continue, jump to defer needed to run, go to end of block
// If break, jump to defer needed to run, go to break label
// If return, jump to defer needed to run, go to return label
void generateDefers(CFG* cfg, List* defers, List* deferLabels)
{
    for (int i = defers->size - 1; i >= 0; i--) {
        appendInstruction(cfg, List_Get(deferLabels, i));
        flattenAST(cfg, List_Get(defers, i), NULL, NULL, NULL, NULL, false);
    }
}

SymbolVersion* defaultValue(CFG* cfg, ASTNode* type)
{
    switch (type->astType) {
    default: {
        SymbolVersion* temp = tempSymbolVersion(cfg, type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 0, type->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_VOID: {
        return NULL;
    }
    case AST_PARAMLIST: {
        SymbolVersion* temp = tempSymbolVersion(cfg, type);

        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, type->pos);
        temp->def = ir;
        ir->listData = List_Create();

        forall(elem, type->paramlist.defines)
        {
            ASTNode* define = elem->data;
            SymbolNode* var = define->define.symbol;
            if (var->def->astType == AST_UNDEF) {
                List_Append(ir->listData, defaultValue(cfg, var->type));
            } else if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
                List_Append(ir->listData, flattenAST(cfg, var->def, NULL, NULL, NULL, NULL, false));
            }
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARRAY: {
        ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
        SymbolNode* lengthSymbol = lengthDefine->define.symbol;
        ASTNode* lengthCode = lengthSymbol->def;
        ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
        SymbolNode* dataSymbol = dataDefine->define.symbol;
        ASTNode* dataAddrType = dataSymbol->type;
        ASTNode* dataType = dataAddrType->unop.expr;

        SymbolVersion* temp = tempSymbolVersion(cfg, type);
        IR* ir = NULL;
        if (dataType->astType == AST_ARRAY) {
            if (lengthCode->astType == AST_INT) {
                ir = createIR(IR_LOAD_ARRAY_LITERAL, temp, NULL, NULL, type->pos);
                temp->def = ir;
                ir->listData = List_Create();
                for (int i = 0; i < lengthCode->_int.data; i++) {
                    SymbolVersion* member = defaultValue(cfg, dataType);
                    List_Append(ir->listData, member);
                }
            } else {
                ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, type->pos);
                temp->def = ir;
                ir->listData = List_Create();

                SymbolVersion* lengthSymbver = tempSymbolVersion(cfg, INT64_TYPE);
                IR* lengthIR = createIR_int(IR_LOAD_INT, lengthSymbver, NULL, NULL, 0, type->pos);
                lengthSymbver->def = lengthIR;
                appendInstruction(cfg, lengthIR);

                List_Append(ir->listData, lengthSymbver);
                List_Append(ir->listData, defaultValue(cfg, dataAddrType));
            }
        } else {
            if (lengthCode->astType == AST_INT) {
                ir = createIR(IR_LOAD_ARRAY_LITERAL, temp, NULL, NULL, type->pos);
                temp->def = ir;
                ir->listData = List_Create();
                SymbolVersion* member = defaultValue(cfg, dataType);
                for (int i = 0; i < lengthCode->_int.data; i++) {
                    List_Append(ir->listData, member);
                }
            } else {
                ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, type->pos);
                temp->def = ir;
                ir->listData = List_Create();

                SymbolVersion* lengthSymbver = tempSymbolVersion(cfg, INT64_TYPE);
                IR* lengthIR = createIR_int(IR_LOAD_INT, lengthSymbver, NULL, NULL, 0, type->pos);
                lengthSymbver->def = lengthIR;
                appendInstruction(cfg, lengthIR);

                List_Append(ir->listData, lengthSymbver);
                List_Append(ir->listData, defaultValue(cfg, dataAddrType));
            }
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ENUM: {
        ASTNode* firstDefine = List_Get(type->_enum.defines, 0);
        SymbolNode* firstVar = firstDefine->define.symbol;
        int tagID = getTag(firstVar->name, firstVar->type);

        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, tagID, type->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* expr = defaultValue(cfg, firstVar->type);

        SymbolVersion* temp = tempSymbolVersion(cfg, type);
        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, type->pos);
        temp->def = ir;
        ir->listData = List_Create();
        List_Append(ir->listData, tag);
        if (expr) {
            List_Append(ir->listData, expr);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    }
}

// Adds IR instructions to a list of ir instructions, returns instructions that assign a term
// When converting to SSA, the dest of each instruction will be set to a unique symbol version
//                         each source will be filled with a pointer to the most recent symbol version
// Just fill the dest with the current version now, temporary or not
SymbolVersion* flattenAST(CFG* cfg, ASTNode* node, IR* returnLabel, IR* breakLabel, IR* continueLabel, IR* errorLabel, bool lvalue)
{
    switch (node->astType) {
    case AST_IDENT: { // the symbol version for the ident needs to be unversioned, and not shared with any other IR
        SymbolNode* symbol = Symbol_Find(node->ident.data, node->scope);
        if (symbol->isExtern) {
            SymbolVersion* temp = tempSymbolVersion(cfg, symbol->type);
            IR* ir = createIR(IR_LOAD_EXTERN, temp, NULL, NULL, node->pos);
            ir->symbol = symbol;
            temp->def = ir;
            appendInstruction(cfg, ir);
            return temp;
        } else if (symbol->symbolType == SYMBOL_FUNCTION) {
            createCFG(symbol, cfg);
            SymbolVersion* temp = tempSymbolVersion(cfg, symbol->type);

            IR* ir = createIR(IR_LOAD_SYMBOL, temp, NULL, NULL, node->pos);
            ir->symbol = symbol;
            temp->def = ir;
            appendInstruction(cfg, ir);
            return temp;
        } else {
            SymbolVersion* var = unversionedSymbolVersion(cfg, symbol, symbol->type);
            var->lvalue = lvalue;
            return var;
        }
    }
    case AST_INT: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, node->_int.data, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_CHAR: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        int64_t data = node->_char.data[0];
        if (node->_char.data[0] == '\\') {
            if (node->_char.data[1] == '0') {
                data = '\0';
            } else if (node->_char.data[1] == 'a') {
                data = '\a';
            } else if (node->_char.data[1] == 'b') {
                data = '\b';
            } else if (node->_char.data[1] == 'f') {
                data = '\f';
            } else if (node->_char.data[1] == 'n') {
                data = '\n';
            } else if (node->_char.data[1] == 't') {
                data = '\t';
            } else if (node->_char.data[1] == 'r') {
                data = '\r';
            } else if (node->_char.data[1] == 'v') {
                data = '\v';
            } else if (node->_char.data[1] == '\\') {
                data = '\\';
            } else if (node->_char.data[1] == '\'') {
                data = '\'';
            } else if (node->_char.data[1] == '"') {
                data = '"';
            } else if (node->_char.data[1] == 'r') {
                data = '\r';
            } else if (node->_char.data[1] == '?') {
                data = '?';
            } else if (node->_char.data[1] == '0') {
                data = '\0';
            }
        }
        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, data, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_TRUE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 1, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_FALSE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 0, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_REAL: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_double(IR_LOAD_REAL, temp, NULL, NULL, node->real.data, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARGLIST: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, node->pos);
        temp->def = ir;
        ir->listData = List_Create();
        forall(elem, node->arglist.args)
        {
            SymbolVersion* member = flattenAST(cfg, elem->data, returnLabel, breakLabel, continueLabel, errorLabel, false);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ENUM_LITERAL: {
        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, node->enumLiteral.tag, node->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* expr = NULL;
        if (node->enumLiteral.expr) {
            expr = flattenAST(cfg, node->enumLiteral.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        }

        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);
        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, node->pos);
        temp->def = ir;
        ir->listData = List_Create();
        List_Append(ir->listData, tag);
        if (expr && expr->type->astType != AST_VOID && getTypeEnum(node->enumLiteral.tag, node->type)->astType != AST_VOID) {
            List_Append(ir->listData, expr);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NOTHING: {
        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, getTag("nothing", VOID_TYPE), node->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* expr = NULL;
        if (node->enumLiteral.expr) {
            expr = flattenAST(cfg, node->enumLiteral.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        }

        SymbolVersion* temp = tempSymbolVersion(cfg, MAYBE_VOID_TYPE);
        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL, node->pos);
        temp->def = ir;
        ir->listData = List_Create();
        List_Append(ir->listData, tag);
        if (expr) {
            List_Append(ir->listData, expr);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARRAY_LITERAL: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LOAD_ARRAY_LITERAL, temp, NULL, NULL, node->pos);
        temp->def = ir;
        ir->listData = List_Create();
        forall(elem, node->arrayLiteral.members)
        {
            SymbolVersion* member = flattenAST(cfg, elem->data, returnLabel, breakLabel, continueLabel, errorLabel, false);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_STRING: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LOAD_STRING, temp, NULL, NULL, node->pos);
        temp->def = ir;
        ir->strData = node->string.data;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_UNDEF: {
        return NULL;
    }
    case AST_ASSIGN: {
        if (node->binop.left->astType == AST_IDENT) {
            SymbolNode* symbol = Symbol_Find(node->binop.left->ident.data, node->scope);
            SymbolVersion* var = unversionedSymbolVersion(cfg, symbol, symbol->type);
            var->lvalue = true;
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);

            IR* ir = createIR(IR_COPY, var, right, NULL, node->pos);
            var->def = ir;
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_INDEX) {
            SymbolVersion* arr = flattenAST(cfg, node->binop.left->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, true);
            arr->lvalue = true;
            SymbolVersion* index = flattenAST(cfg, node->binop.left->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);

            IR* ir = createIR(IR_INDEX_COPY, NULL, arr, index, node->pos);
            ir->src3 = right;
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_DOT) {
            SymbolVersion* left = flattenAST(cfg, node->binop.left->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, true);
            left->lvalue = true;
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            IR* ir = createIR(IR_DOT_COPY, NULL, left, right, node->pos);
            ir->strData = node->binop.left->binop.right->ident.data;
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_DEREF) {
            SymbolVersion* left = flattenAST(cfg, node->binop.left->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, true);
            left->lvalue = true;
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            IR* ir = createIR(IR_DEREF_COPY, NULL, left, right, node->pos);
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_PAREN) {
            node->binop.left = List_Get(node->binop.left->arglist.args, 0);
            flattenAST(cfg, node, returnLabel, breakLabel, continueLabel, errorLabel, true);
        } else {
            PANIC("not an l-value\n");
        }
        // TODO: go through each L value IR and set an L value flag
        // TODO: generate L value IR's inline
        return NULL;
    }
    case AST_OR: {
        SymbolVersion* var = tempSymbolVersion(cfg, INT8_TYPE);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, left, NULL, elseLabel, node->pos));
        IR* loadTrue = createIR_int(IR_LOAD_INT, var, NULL, NULL, 1, node->pos);
        List_Append(phony->listData, loadTrue);
        appendInstruction(cfg, loadTrue);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        IR* copyRight = createIR(IR_COPY, var, right, NULL, node->pos);
        List_Append(phony->listData, copyRight);
        appendInstruction(cfg, copyRight);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_AND: {
        SymbolVersion* var = tempSymbolVersion(cfg, INT8_TYPE);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, left, NULL, elseLabel, node->pos));
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        IR* copyRight = createIR(IR_COPY, var, right, NULL, node->pos);
        List_Append(phony->listData, copyRight);
        appendInstruction(cfg, copyRight);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, elseLabel);
        IR* loadFalse = createIR_int(IR_LOAD_INT, var, NULL, NULL, 0, node->pos);
        List_Append(phony->listData, loadFalse);
        appendInstruction(cfg, loadFalse);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_BIT_OR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_OR, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_XOR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_XOR, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_AND: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_AND, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_EQ: {
        SymbolVersion* left = NULL;
        SymbolVersion* right = NULL;
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        if (node->binop.left->type->astType == AST_ENUM) {
            SymbolVersion* leftEnum = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
            left = tempSymbolVersion(cfg, INT64_TYPE);
            IR* leftIR = createIR(IR_DOT, left, leftEnum, NULL, node->pos);
            leftIR->strData = "tag";
            left->def = leftIR;
            appendInstruction(cfg, leftIR);

            SymbolVersion* rightEnum = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            right = tempSymbolVersion(cfg, INT64_TYPE);
            IR* rightIR = createIR(IR_DOT, right, rightEnum, NULL, node->pos);
            rightIR->strData = "tag";
            right->def = rightIR;
            appendInstruction(cfg, rightIR);
        } else {
            left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
            right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        }

        IR* ir = createIR(IR_EQ, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NEQ: {
        SymbolVersion* left = NULL;
        SymbolVersion* right = NULL;
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        if (node->binop.left->type->astType == AST_ENUM) {
            SymbolVersion* leftEnum = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
            left = tempSymbolVersion(cfg, INT64_TYPE);
            IR* leftIR = createIR(IR_DOT, left, leftEnum, NULL, node->pos);
            leftIR->strData = "tag";
            left->def = leftIR;
            appendInstruction(cfg, leftIR);

            SymbolVersion* rightEnum = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            right = tempSymbolVersion(cfg, INT64_TYPE);
            IR* rightIR = createIR(IR_DOT, right, rightEnum, NULL, node->pos);
            rightIR->strData = "tag";
            right->def = rightIR;
            appendInstruction(cfg, rightIR);
        } else {
            left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
            right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        }

        IR* ir = createIR(IR_NEQ, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_GTR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_GTR, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LSR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LSR, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_GTE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_GTE, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LTE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LTE, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LSHIFT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LSHIFT, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_RSHIFT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_RSHIFT, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ADD: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_ADD, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_SUBTRACT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_SUBTRACT, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_MULTIPLY: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_MULTIPLY, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DIVIDE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_DIVIDE, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_MODULUS: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_MODULUS, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_EXPONENT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_EXPONENT, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NOT: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_NOT, temp, expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NEG: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_NEG, temp, expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_NOT: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_NOT, temp, expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ADDR_OF: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);
        temp->lvalue = lvalue;

        IR* ir = createIR(IR_ADDR_OF, temp, expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_SIZEOF: {
        SymbolVersion* temp = tempSymbolVersion(cfg, INT64_TYPE);

        IR* ir = createIR_ast(IR_SIZEOF, temp, NULL, NULL, node->unop.expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DEREF: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);
        temp->lvalue = lvalue;

        IR* ir = createIR(IR_DEREF, temp, expr, NULL, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_TRY: {
        SymbolVersion* var = tempSymbolVersion(cfg, node->type);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        // Get tag of expr
        SymbolVersion* left = flattenAST(cfg, node->taggedUnop.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* enumIR = createIR(IR_DOT, enumDot, left, NULL, node->pos);
        enumIR->strData = "tag";
        enumDot->def = enumIR;
        appendInstruction(cfg, enumIR);

        // Get tag of success type
        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, node->taggedUnop.tag, node->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        // Compare success tag with expr tag
        SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
        IR* conditionIR = createIR(IR_EQ, condition, enumDot, tag, node->pos);
        condition->def = conditionIR;
        appendInstruction(cfg, conditionIR);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        // Success branch
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel, node->pos));
        SymbolVersion* somethingDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* somethingIR = createIR(IR_DOT, somethingDot, left, NULL, node->pos);
        somethingIR->strData = "success";
        somethingDot->def = somethingIR;
        appendInstruction(cfg, somethingIR);

        IR* copy = createIR(IR_COPY, var, somethingDot, NULL, node->pos);
        List_Append(phony->listData, copy);
        appendInstruction(cfg, copy);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));

        // Error branch, set retval to error message
        appendInstruction(cfg, elseLabel);
        SymbolVersion* returnSymbolVersion = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);
        appendInstruction(cfg, createIR_ast(IR_CAST, returnSymbolVersion, left, NULL, NULL, returnSymbolVersion->type, node->pos)); // Do this rather than a simple copy, may be !() error type, which must be converted
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, errorLabel, node->pos));
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_CATCH: {
        SymbolVersion* var = tempSymbolVersion(cfg, node->type);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        SymbolVersion* left = flattenAST(cfg, node->taggedBinop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* enumIR = createIR(IR_DOT, enumDot, left, NULL, node->pos);
        enumIR->strData = "tag";
        enumDot->def = enumIR;
        appendInstruction(cfg, enumIR);

        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, node->taggedBinop.tag, node->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
        IR* conditionIR = createIR(IR_EQ, condition, enumDot, tag, node->pos);
        condition->def = conditionIR;
        appendInstruction(cfg, conditionIR);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel, node->pos));
        SymbolVersion* somethingDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* somethingIR = createIR(IR_DOT, somethingDot, left, NULL, node->pos);
        somethingIR->strData = "success";
        somethingDot->def = somethingIR;
        appendInstruction(cfg, somethingIR);

        IR* copy = createIR(IR_COPY, var, somethingDot, NULL, node->pos);
        List_Append(phony->listData, copy);
        appendInstruction(cfg, copy);

        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* elseSymbver = flattenAST(cfg, node->taggedBinop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        if (elseSymbver) {
            IR* copy = createIR(IR_COPY, var, elseSymbver, NULL, node->pos);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_ORELSE: {
        SymbolVersion* var = tempSymbolVersion(cfg, node->type);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        SymbolVersion* left = flattenAST(cfg, node->taggedBinop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* enumIR = createIR(IR_DOT, enumDot, left, NULL, node->pos);
        enumIR->strData = "tag";
        enumDot->def = enumIR;
        appendInstruction(cfg, enumIR);

        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, node->taggedBinop.tag, node->pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
        IR* conditionIR = createIR(IR_NEQ, condition, enumDot, tag, node->pos);
        condition->def = conditionIR;
        appendInstruction(cfg, conditionIR);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel, node->pos));
        SymbolVersion* somethingDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* somethingIR = createIR(IR_DOT, somethingDot, left, NULL, node->pos);
        somethingIR->strData = "something";
        somethingDot->def = somethingIR;
        appendInstruction(cfg, somethingIR);

        IR* copy = createIR(IR_COPY, var, somethingDot, NULL, node->pos);
        List_Append(phony->listData, copy);
        appendInstruction(cfg, copy);

        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* elseSymbver = flattenAST(cfg, node->taggedBinop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        if (elseSymbver) {
            IR* copy = createIR(IR_COPY, var, elseSymbver, NULL, node->pos);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_CALL: {
        SymbolVersion* left = flattenAST(cfg, node->call.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_CALL, temp, left, NULL, node->pos);
        temp->def = ir;
        ir->listData = List_Create();
        forall(elem, node->call.right->arglist.args)
        {
            SymbolVersion* member = flattenAST(cfg, elem->data, returnLabel, breakLabel, continueLabel, errorLabel, false);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        if (node->type->astType == AST_ENUM) {
            ASTNode* successType = NULL;
            forall(elem, node->type->_enum.defines)
            {
                ASTNode* define = elem->data;
                SymbolNode* var = define->define.symbol;
                if (!strcmp(var->name, "success")) {
                    successType = var->type;
                    break;
                }
            }
            // if not successful then push pos str to stack, else clear stack
            if (successType) {
                SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
                IR* enumIR = createIR(IR_DOT, enumDot, temp, NULL, node->pos);
                enumIR->strData = "tag";
                enumDot->def = enumIR;
                appendInstruction(cfg, enumIR);

                // Get tag of success type
                SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
                IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, getTag("success", successType), node->pos);
                tag->def = tagIR;
                appendInstruction(cfg, tagIR);

                // Compare success tag with expr tag
                SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
                IR* conditionIR = createIR(IR_NEQ, condition, enumDot, tag, node->pos);
                condition->def = conditionIR;
                appendInstruction(cfg, conditionIR);

                IR* elseLabel = createIR_label(node->pos);
                IR* endLabel = createIR_label(node->pos);

                // Success branch
                appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel, node->pos));
                IR* pushStackTraceIR = createIR(IR_PUSH_STACK_TRACE, NULL, NULL, NULL, node->pos);
                appendInstruction(cfg, pushStackTraceIR);
                appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));

                // Error branch, set retval to error message
                appendInstruction(cfg, elseLabel);
                IR* clearStackTraceIR = createIR(IR_CLEAR_STACK_TRACE, NULL, NULL, NULL, node->pos);
                appendInstruction(cfg, clearStackTraceIR);
                appendInstruction(cfg, endLabel);
            }
        }
        return temp;
    }
    case AST_INDEX: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
        left->lvalue = lvalue;
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        if (isDebug) {
            // Done so that versioning is correct. Would version array symbol in this BB and other BB as same version, duplicate code
            SymbolVersion* arrayCopy = NULL;
            if (left->symbol == cfg->tempSymbol) {
                arrayCopy = tempSymbolVersion(cfg, left->type);
                IR* arrayExprCopyIR = createIR(IR_COPY, arrayCopy, left, NULL, node->pos);
                arrayCopy->def = arrayExprCopyIR;
                appendInstruction(cfg, arrayExprCopyIR);
            } else {
                arrayCopy = unversionedSymbolVersion(cfg, left->symbol, left->type);
            }
            SymbolVersion* indexCopy = NULL;
            if (right->symbol == cfg->tempSymbol) {
                indexCopy = tempSymbolVersion(cfg, right->type);
                IR* indexExprCopyIR = createIR(IR_COPY, indexCopy, right, NULL, node->pos);
                indexCopy->def = indexExprCopyIR;
                appendInstruction(cfg, indexExprCopyIR);
            } else {
                indexCopy = unversionedSymbolVersion(cfg, right->symbol, right->type);
            }

            IR* tooHighLabel = createIR_label(node->pos);
            IR* tooLowLabel = createIR_label(node->pos);
            IR* end = createIR_label(node->pos);

            // 0
            SymbolVersion* zero = tempSymbolVersion(cfg, INT64_TYPE);
            IR* zeroIR = createIR_int(IR_LOAD_INT, zero, NULL, NULL, 0, node->pos);
            zero->def = zeroIR;
            appendInstruction(cfg, zeroIR);

            // Get array length
            SymbolVersion* arrayLength = tempSymbolVersion(cfg, INT64_TYPE);
            IR* lengthIR = createIR(IR_DOT, arrayLength, arrayCopy, NULL, node->pos);
            lengthIR->strData = "length";
            arrayLength->def = lengthIR;
            appendInstruction(cfg, lengthIR);

            // If index >= array length, goto branch error
            SymbolVersion* upperBound = tempSymbolVersion(cfg, BOOL_TYPE);
            IR* upperIR = createIR(IR_LSR, upperBound, indexCopy, arrayLength, node->pos);
            upperBound->def = upperIR;
            appendInstruction(cfg, upperIR);

            // If index < 0, branch to error
            SymbolVersion* lowerBound = tempSymbolVersion(cfg, BOOL_TYPE);
            IR* lowerIR = createIR(IR_GTE, lowerBound, indexCopy, zero, node->pos);
            lowerBound->def = lowerIR;
            appendInstruction(cfg, lowerIR);

            appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, upperBound, NULL, tooHighLabel, node->pos));
            appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, lowerBound, NULL, tooLowLabel, node->pos));
            appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, end, node->pos));
            appendInstruction(cfg, tooHighLabel);
            IR* tooHighError = createIR(IR_ERROR, NULL, NULL, NULL, node->pos);
            tooHighError->strData = "array index greater than array length";
            appendInstruction(cfg, tooHighError);
            appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, end, node->pos));

            appendInstruction(cfg, tooLowLabel);
            IR* tooLowError = createIR(IR_ERROR, NULL, NULL, NULL, node->pos);
            tooLowError->strData = "array index is negative";
            appendInstruction(cfg, tooLowError);
            appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, end, node->pos));

            appendInstruction(cfg, end);
        }

        IR* ir = createIR(IR_INDEX, temp, left, right, node->pos);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_SLICE: {
        SymbolVersion* arr = flattenAST(cfg, node->slice.arrayExpr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* lowerBound;
        if (node->slice.lowerBound->astType != AST_UNDEF) {
            lowerBound = flattenAST(cfg, node->slice.lowerBound, returnLabel, breakLabel, continueLabel, errorLabel, false);
            if (lowerBound->def && lowerBound->def->irType == IR_LOAD_INT && lowerBound->def->intData < 0) {
                error(lowerBound->def->pos, "lower bound is negative");
            }
        } else {
            lowerBound = tempSymbolVersion(cfg, INT64_TYPE);
            IR* loadLowerBoundIR = createIR_int(IR_LOAD_INT, lowerBound, NULL, NULL, 0, node->pos);
            lowerBound->def = loadLowerBoundIR;
            appendInstruction(cfg, loadLowerBoundIR);
        }
        SymbolVersion* upperBound;
        if (node->slice.upperBound->astType != AST_UNDEF) {
            upperBound = flattenAST(cfg, node->slice.upperBound, returnLabel, breakLabel, continueLabel, errorLabel, false);
        } else {
            upperBound = tempSymbolVersion(cfg, INT64_TYPE);
            IR* arrDataIR = createIR(IR_DOT, upperBound, arr, NULL, node->pos);
            arrDataIR->strData = "length";
            upperBound->def = arrDataIR;
            appendInstruction(cfg, arrDataIR);
        }

        SymbolVersion* newSizeSymbver = tempSymbolVersion(cfg, INT64_TYPE);
        IR* newSizeIR = createIR(IR_SUBTRACT, newSizeSymbver, upperBound, lowerBound, node->pos);
        newSizeSymbver->def = newSizeIR;
        appendInstruction(cfg, newSizeIR);

        ASTNode* dataAddrType = getArrayDataTypeAddr(node->slice.arrayExpr->type);
        SymbolVersion* arrDataSymbver = tempSymbolVersion(cfg, dataAddrType);
        IR* arrDataIR = createIR(IR_DOT, arrDataSymbver, arr, NULL, node->pos);
        arrDataIR->strData = "data";
        arrDataSymbver->def = arrDataIR;
        appendInstruction(cfg, arrDataIR);

        SymbolVersion* newPtrSymbver = tempSymbolVersion(cfg, dataAddrType);
        IR* newPtrIR = createIR(IR_ADD, newPtrSymbver, arrDataSymbver, lowerBound, node->pos);
        newPtrSymbver->def = newPtrIR;
        appendInstruction(cfg, newPtrIR);

        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);
        IR* ir = createIR(IR_SLICE, temp, arr, NULL, node->pos);
        ir->listData = List_Create();
        temp->def = ir;
        List_Append(ir->listData, newSizeSymbver);
        List_Append(ir->listData, newPtrSymbver);
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DOT: {
        if ((node->dot.left->type->astType == AST_IDENT && (!strcmp(node->dot.left->type->ident.data, "Module") || !strcmp(node->dot.left->type->ident.data, "Type")))
            || (node->dot.symbol && node->dot.symbol->symbolType == SYMBOL_FUNCTION)) {
            if (node->dot.symbol->symbolType == SYMBOL_FUNCTION) {
                createCFG(node->dot.symbol, cfg);
            }
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            IR* ir = createIR(IR_LOAD_SYMBOL, temp, NULL, NULL, node->pos);
            ir->symbol = node->dot.symbol;
            temp->def = ir;
            appendInstruction(cfg, ir);
            return temp;
        } else {
            SymbolVersion* left = flattenAST(cfg, node->dot.left, returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
            left->lvalue = lvalue;
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            if (node->dot.left->type->astType == AST_ENUM && isDebug) {
                SymbolVersion* enumLiteralExpr = NULL;
                if (left->symbol == cfg->tempSymbol) {
                    enumLiteralExpr = tempSymbolVersion(cfg, left->type);
                    IR* enumExprCopyIR = createIR(IR_COPY, enumLiteralExpr, left, NULL, node->pos);
                    enumLiteralExpr->def = enumExprCopyIR;
                    appendInstruction(cfg, enumExprCopyIR);
                } else {
                    enumLiteralExpr = unversionedSymbolVersion(cfg, left->symbol, left->type);
                }

                IR* endLabel = createIR_label(node->pos);
                // Get tag of expr
                SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
                IR* enumIR = createIR(IR_DOT, enumDot, enumLiteralExpr, NULL, node->pos);
                enumIR->strData = "tag";
                enumDot->def = enumIR;
                appendInstruction(cfg, enumIR);

                // Get tag of enum
                SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
                IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, getTagEnum(node->dot.right->ident.data, node->dot.left->type), node->pos);
                tag->def = tagIR;
                appendInstruction(cfg, tagIR);

                // Compare success tag with expr tag
                SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
                IR* conditionIR = createIR(IR_NEQ, condition, enumDot, tag, node->pos);
                condition->def = conditionIR;
                appendInstruction(cfg, conditionIR);

                appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, endLabel, node->pos));
                IR* fieldError = createIR(IR_ERROR, NULL, NULL, NULL, node->pos);
                char* fieldStr = calloc(255, sizeof(char));
                sprintf(fieldStr, "field '%s' not active", node->dot.right->ident.data);
                fieldError->strData = fieldStr;
                appendInstruction(cfg, fieldError);
                appendInstruction(cfg, endLabel);
            }
            IR* ir = createIR(IR_DOT, temp, left, NULL, node->pos);
            ir->strData = node->dot.right->ident.data;
            temp->def = ir;
            appendInstruction(cfg, ir);
            return temp;
        }
    }
    case AST_CAST: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->binop.right);

        IR* ir = NULL;
        if (node->binop.right->astType == AST_PARAMLIST) { // C doesn't allow explicit casts to structs, but does allow implicit copies
            ir = createIR(IR_COPY, temp, left, NULL, node->pos);
        } else {
            ir = createIR_ast(IR_CAST, temp, left, NULL, node->binop.left->type, node->binop.right, node->pos);
        }
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NEW: {
        SymbolVersion* addr = tempSymbolVersion(cfg, node->type);
        SymbolVersion* init = NULL;

        if (node->binop.left->astType == AST_ARRAY) {
            // List of array type length symbol versions flattened from array type
            List* lengthCodeSymbvers = List_Create();
            ASTNode* arrType = node->binop.left;
            while (arrType->astType == AST_ARRAY) {
                SymbolVersion* lengthCodeSymbver = flattenAST(cfg, getArrayLengthAST(arrType), NULL, NULL, NULL, NULL, false);
                if (lengthCodeSymbver) { // If getArrayLengthAST(arrType) is undef, this is NULL, ruins things when iterating over the ir's listData
                    List_Append(lengthCodeSymbvers, lengthCodeSymbver);
                }
                if (getArrayDataType(arrType)->astType == AST_ARRAY && getArrayLengthAST(getArrayDataType(arrType))->astType == AST_UNDEF) {
                    break;
                }
                arrType = getArrayDataType(arrType);
            }

            IR* ir = NULL;
            if (node->binop.right->astType != AST_UNDEF) {
                init = flattenAST(cfg, node->binop.right, NULL, NULL, NULL, NULL, false);
                ir = createIR(IR_NEW_ARR, addr, NULL, init, node->pos);
            } else if (arrType->astType == AST_ARRAY) {
                init = defaultValue(cfg, getArrayDataType(arrType));
                ir = createIR(IR_NEW_ARR, addr, init, NULL, node->pos);
            } else {
                init = defaultValue(cfg, arrType);
                ir = createIR(IR_NEW_ARR, addr, init, NULL, node->pos);
            }
            addr->def = ir;
            ir->listData = lengthCodeSymbvers;
            appendInstruction(cfg, ir);
        } else {
            if (node->binop.right->astType != AST_UNDEF) {
                init = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel, errorLabel, false);
            } else {
                init = defaultValue(cfg, node->binop.left);
            }
            IR* ir = createIR_ast(IR_NEW, addr, init, NULL, node->binop.left, node->binop.right, node->pos);
            addr->def = ir;
            appendInstruction(cfg, ir);
        }
        return addr;
    }
    case AST_FREE: {
        SymbolVersion* expr = NULL;

        if (node->unop.expr->type->astType == AST_ARRAY) {
            SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel, errorLabel, false);
            expr = tempSymbolVersion(cfg, getArrayDataTypeAddr(node->unop.expr->type));

            IR* dotIR = createIR(IR_DOT, expr, left, NULL, node->pos);
            dotIR->strData = "data";
            expr->def = dotIR;
            appendInstruction(cfg, dotIR);
        } else {
            expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        }

        IR* ir = createIR(IR_FREE, NULL, expr, NULL, node->pos);
        appendInstruction(cfg, ir);
        return NULL;
    }
    case AST_PAREN: {
        return flattenAST(cfg, List_Get(node->arglist.args, 0), returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
    }
    case AST_DEFINE: {
        if (node->define.symbol->type->isConst) {
            return NULL;
        }

        SymbolVersion* var = unversionedSymbolVersion(cfg, node->define.symbol, node->define.symbol->type);
        SymbolVersion* def = NULL;
        if (node->define.symbol->def->astType != AST_UNDEF) {
            def = flattenAST(cfg, node->define.symbol->def, returnLabel, breakLabel, continueLabel, errorLabel, lvalue);
        } else {
            def = defaultValue(cfg, node->define.symbol->type);
        }

        IR* ir = createIR(IR_COPY, var, def, NULL, node->pos);
        var->def = ir;
        appendInstruction(cfg, ir);
        return var;
    }
    case AST_BLOCK: {
        // Each defer has 3 labels, continue, break, return
        // Start off with the given continue, break, return (-1)
        // Every time a defer is encountered in the block, increase number by 1
        // When passing continue, break, return, check the number and use those labels
        List* continueLabels = List_Create();
        List* breakLabels = List_Create();
        List* returnLabels = List_Create();
        List* errorLabels = List_Create();
        forall(elem, node->block.symbol->defers)
        {
            List_Append(continueLabels, createIR_label(node->pos));
            List_Append(breakLabels, createIR_label(node->pos));
            List_Append(returnLabels, createIR_label(node->pos));
        }
        forall(elem, node->block.symbol->errdefers)
        {
            List_Append(errorLabels, createIR_label(node->pos));
        }
        IR* end = createIR_label(node->pos);

        IR* thisContinueLabel = continueLabel ? continueLabel : end;
        IR* thisBreakLabel = breakLabel;
        IR* thisReturnLabel = returnLabel;
        IR* thisErrorLabel = errorLabel;
        int deferLabelIndex = 0;
        int errDeferLabelIndex = 0;

        SymbolVersion* var = NULL;
        forall(elem, node->block.children)
        {
            ASTNode* child = elem->data;
            var = flattenAST(cfg, child, thisReturnLabel, thisBreakLabel, thisContinueLabel, thisErrorLabel, false);
            if (child->astType == AST_DEFER) {
                thisContinueLabel = List_Get(continueLabels, deferLabelIndex);
                thisBreakLabel = List_Get(breakLabels, deferLabelIndex);
                thisReturnLabel = List_Get(returnLabels, deferLabelIndex);
                thisErrorLabel = List_Get(errorLabels, errDeferLabelIndex);
                deferLabelIndex++;
                errDeferLabelIndex++;
            }
            if (child->astType == AST_ERRDEFER) {
                thisErrorLabel = List_Get(errorLabels, errDeferLabelIndex);
                errDeferLabelIndex++;
            }
        }

        SymbolVersion* evalSymbolVersion = NULL;
        bool noReturnVar = false; // Don't return var to copied to the return value, already done here before running errdefers
        if (node->type->astType != AST_UNDEF && var) {
            evalSymbolVersion = tempSymbolVersion(cfg, node->type);
            IR* ir = createIR(IR_COPY, evalSymbolVersion, var, NULL, node->pos);
            evalSymbolVersion->def = ir;
            appendInstruction(cfg, ir);

            // If eval type is an error enum, and symbol returns an error (create field), AND this block is a return block, add runtime check for tag. If not success tag, branch to error label
            SymbolNode* parent = node->block.symbol;
            while (parent->symbolType == SYMBOL_BLOCK) {
                parent = parent->parent;
            }
            if (parent->isError && var->type->astType == AST_ENUM && thisErrorLabel && node->block.returnEval && !enumContainsField(var->type, "success", VOID_TYPE)) {
                noReturnVar = true;
                SymbolVersion* returnVersion = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);
                appendInstruction(cfg, createIR(IR_COPY, returnVersion, var, NULL, invalid_pos));

                // Get tag of expr
                SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
                IR* enumIR = createIR(IR_DOT, enumDot, var, NULL, node->pos);
                enumIR->strData = "tag";
                enumDot->def = enumIR;
                appendInstruction(cfg, enumIR);

                // Get tag of success type
                SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
                int tagID = getTagEnum("success", var->type);
                IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, tagID, node->pos);
                tag->def = tagIR;
                appendInstruction(cfg, tagIR);

                // Compare success tag with expr tag
                SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
                IR* conditionIR = createIR(IR_EQ, condition, enumDot, tag, node->pos);
                condition->def = conditionIR;
                appendInstruction(cfg, conditionIR);

                // branch to error label if not equal to success
                appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, thisErrorLabel, node->pos));
            }
        }

        generateDefers(cfg, node->block.symbol->defers, continueLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, end, node->pos));

        generateDefers(cfg, node->block.symbol->defers, breakLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, breakLabel, node->pos));

        generateDefers(cfg, node->block.symbol->defers, returnLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, returnLabel, node->pos));

        generateDefers(cfg, node->block.symbol->errdefers, errorLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, errorLabel, node->pos));
        appendInstruction(cfg, end);

        if (noReturnVar) {
            return NULL;
        } else {
            return evalSymbolVersion;
        }
    }
    case AST_IF: {
        SymbolVersion* var = NULL;
        IR* phony = NULL;
        if (node->type->astType != AST_UNDEF) {
            var = tempSymbolVersion(cfg, node->type);
            phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
            phony->listData = List_Create();
            var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
            appendInstruction(cfg, phony);
        }
        SymbolVersion* condition = flattenAST(cfg, node->_if.condition, returnLabel, breakLabel, continueLabel, errorLabel, false);

        IR* elseLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel, node->pos));
        SymbolVersion* bodySymbver = flattenAST(cfg, node->_if.bodyBlock, returnLabel, breakLabel, continueLabel, errorLabel, false);
        if (var && bodySymbver) {
            IR* copy = createIR(IR_COPY, var, bodySymbver, NULL, node->pos);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* elseSymbver = flattenAST(cfg, node->_if.elseBlock, returnLabel, breakLabel, continueLabel, errorLabel, false);
        if (var && elseSymbver) {
            IR* copy = createIR(IR_COPY, var, elseSymbver, NULL, node->pos);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_FOR: {
        IR* beginLabel = createIR_label(node->pos);
        IR* thisContinueLabel = createIR_label(node->pos);
        IR* endLabel = createIR_label(node->pos);

        flattenAST(cfg, node->_for.pre, returnLabel, breakLabel, continueLabel, errorLabel, false);
        appendInstruction(cfg, beginLabel);
        SymbolVersion* condition = flattenAST(cfg, node->_for.condition, returnLabel, endLabel, thisContinueLabel, errorLabel, false);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, endLabel, node->pos));
        flattenAST(cfg, node->_for.bodyBlock, returnLabel, endLabel, thisContinueLabel, errorLabel, false);
        appendInstruction(cfg, thisContinueLabel);
        flattenAST(cfg, node->_for.post, returnLabel, endLabel, continueLabel, errorLabel, false);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, beginLabel, node->pos));
        appendInstruction(cfg, endLabel);
        return NULL;
    }
    case AST_CASE: {
        SymbolVersion* var = NULL;
        IR* phony = NULL;
        if (node->type->astType != AST_UNDEF) {
            var = tempSymbolVersion(cfg, node->type);
            phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
            phony->listData = List_Create();
            var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
            appendInstruction(cfg, phony);
        }

        // Generate a list of labels for each mapping, and an else label if there is one
        List* mappingLabels = List_Create();
        for (int i = 0; i < node->_case.mappings->size; i++) {
            List_Append(mappingLabels, createIR_label(node->pos));
        }
        IR* endLabel = createIR_label(node->pos);

        // TODO: if case expr is enum type, make a set of tags. Add each mapping expr's tag to the set. Afterwards, go through enum defines and get tag, remove tag. If tag not found, error (field not in enum), if set is empty before done with enum type defines, error (some fields not handled)

        // For each expr in each mapping, branch if false to the mapping's label if caseExpr does not equal mapping expr
        SymbolVersion* caseExpr = flattenAST(cfg, node->_case.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        int i = 0;
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            IR* mappingLabel = List_Get(mappingLabels, i);
            forall(elem2, mapping->mapping.exprs)
            {
                SymbolVersion* mappingExpr = flattenAST(cfg, elem2->data, returnLabel, breakLabel, continueLabel, errorLabel, false);
                SymbolVersion* notEqualSymbol = tempSymbolVersion(cfg, BOOL_TYPE);
                // Done so that versioning is correct. Would version array symbol in this BB and other BB as same version, duplicate code
                SymbolVersion* caseExprCopy = NULL;
                if (caseExpr->symbol == cfg->tempSymbol) {
                    caseExprCopy = tempSymbolVersion(cfg, caseExpr->type);
                    IR* caseExprCopyIR = createIR(IR_COPY, caseExprCopy, caseExpr, NULL, node->pos);
                    caseExprCopy->def = caseExprCopyIR;
                    appendInstruction(cfg, caseExprCopyIR);
                } else {
                    caseExprCopy = unversionedSymbolVersion(cfg, caseExpr->symbol, caseExpr->type);
                }
                IR* notEqualIR = createIR(IR_NEQ, notEqualSymbol, caseExprCopy, mappingExpr, node->pos);
                notEqualSymbol->def = notEqualIR;
                appendInstruction(cfg, notEqualIR);
                appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, notEqualSymbol, NULL, mappingLabel, node->pos));
            }
            i++;
        }
        // Append else label, append else block if there is one, with a jump to the end label
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            if (mapping->mapping.exprs->size == 0) {
                SymbolVersion* bodySymbver = flattenAST(cfg, mapping->mapping.expr, returnLabel, endLabel, continueLabel, errorLabel, false);
                if (var && bodySymbver) {
                    IR* copy = createIR(IR_COPY, var, bodySymbver, NULL, node->pos);
                    List_Append(phony->listData, copy);
                    appendInstruction(cfg, copy);
                }
                appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
                break;
            }
        }
        // For each mapping, append mapping label and flatten mapping code, with a jump to the end label
        i = 0;
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            IR* mappingLabel = List_Get(mappingLabels, i);
            if (mapping->mapping.exprs->size != 0) {
                appendInstruction(cfg, mappingLabel);
                SymbolVersion* bodySymbver = flattenAST(cfg, mapping->mapping.expr, returnLabel, endLabel, continueLabel, errorLabel, false);
                if (var && bodySymbver) {
                    IR* copy = createIR(IR_COPY, var, bodySymbver, NULL, node->pos);
                    List_Append(phony->listData, copy);
                    appendInstruction(cfg, copy);
                }
                appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
            }
            i++;
        }
        // Append end label
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_FIELD_CASE: {
        SymbolVersion* var = NULL;
        IR* phony = NULL;
        if (node->type->astType != AST_UNDEF) {
            var = tempSymbolVersion(cfg, node->type);
            phony = createIR(IR_PHONY, var, NULL, NULL, node->pos);
            phony->listData = List_Create();
            var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
            appendInstruction(cfg, phony);
        }
        SymbolVersion* caseExpr = flattenAST(cfg, node->_case.expr, returnLabel, breakLabel, continueLabel, errorLabel, false);
        SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
        IR* enumIR = createIR(IR_DOT, enumDot, caseExpr, NULL, node->pos);
        enumIR->strData = "tag";
        enumDot->def = enumIR;
        appendInstruction(cfg, enumIR);

        // Generate a list of labels for each mapping, and an else label if there is one
        List* mappingLabels = List_Create();
        for (int i = 0; i < node->_case.mappings->size; i++) {
            List_Append(mappingLabels, createIR_label(node->pos));
        }
        IR* endLabel = createIR_label(node->pos);

        // For each expr in each mapping, branch if false to the mapping's label if caseExpr does not equal mapping expr
        int i = 0;
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            IR* mappingLabel = List_Get(mappingLabels, i);

            SymbolVersion* right = tempSymbolVersion(cfg, INT64_TYPE);
            IR* tagIR = createIR_int(IR_LOAD_INT, right, NULL, NULL, mapping->fieldMapping.tag, node->pos);
            right->def = tagIR;
            appendInstruction(cfg, tagIR);

            SymbolVersion* notEqualSymbol = tempSymbolVersion(cfg, BOOL_TYPE);
            IR* notEqualIR = createIR(IR_NEQ, notEqualSymbol, enumDot, right, node->pos);
            notEqualSymbol->def = notEqualIR;
            appendInstruction(cfg, notEqualIR);
            appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, notEqualSymbol, NULL, mappingLabel, node->pos));
            i++;
        }
        // For each mapping, append mapping label and flatten mapping code, with a jump to the end label
        i = 0;
        forall(elem, node->_case.mappings)
        {
            ASTNode* mapping = elem->data;
            IR* mappingLabel = List_Get(mappingLabels, i);
            appendInstruction(cfg, mappingLabel);
            SymbolVersion* bodySymbver = flattenAST(cfg, mapping->fieldMapping.expr, returnLabel, endLabel, continueLabel, errorLabel, false);
            if (var && bodySymbver) {
                IR* copy = createIR(IR_COPY, var, bodySymbver, NULL, node->pos);
                List_Append(phony->listData, copy);
                appendInstruction(cfg, copy);
            }
            appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel, node->pos));
            i++;
        }
        // Append end label
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_RETURN: {
        // The error path for the expression in a return is just the return path. Ex: myFunc::()->!Int = {return if true {AnError} else {4}} -- if true clause shouldn't take error path
        SymbolVersion* retval = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel, returnLabel, false);
        SymbolVersion* var = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);

        if (retval) {
            appendInstruction(cfg, createIR(IR_COPY, var, retval, NULL, node->pos));
        }

        // Choose whether to return to return path or error path
        SymbolNode* parent = node->scope;
        while (parent->symbolType == SYMBOL_BLOCK) {
            parent = parent->parent;
        }
        if (parent->isError && var->type->astType == AST_ENUM && errorLabel) {
            // Get tag of expr
            SymbolVersion* enumDot = tempSymbolVersion(cfg, INT64_TYPE);
            IR* enumIR = createIR(IR_DOT, enumDot, retval, NULL, node->pos);
            enumIR->strData = "tag";
            enumDot->def = enumIR;
            appendInstruction(cfg, enumIR);

            // Get tag of success type
            SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
            int tagID = getTagEnum("success", var->type);
            IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, tagID, node->pos);
            tag->def = tagIR;
            appendInstruction(cfg, tagIR);

            // Compare success tag with expr tag
            SymbolVersion* condition = tempSymbolVersion(cfg, BOOL_TYPE);
            IR* conditionIR = createIR(IR_EQ, condition, enumDot, tag, node->pos);
            condition->def = conditionIR;
            appendInstruction(cfg, conditionIR);

            // branch to error label if not equal to success
            appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, errorLabel, node->pos));
        }
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, returnLabel, node->pos));
        return NULL;
    }
    case AST_BREAK: {
        IR* ir = createIR_branch(IR_JUMP, NULL, NULL, NULL, breakLabel, node->pos);
        appendInstruction(cfg, ir);
        return NULL;
    }
    case AST_CONTINUE: {
        IR* ir = createIR_branch(IR_JUMP, NULL, NULL, NULL, continueLabel, node->pos);
        appendInstruction(cfg, ir);
        return NULL;
    }
    case AST_UNREACHABLE: {
        if (isDebug) {
            IR* error = createIR(IR_ERROR, NULL, NULL, NULL, node->pos);
            error->strData = "unreachable";
            appendInstruction(cfg, error);
        }
        return NULL;
    }
    case AST_DEFER: {
        return NULL;
    }
    case AST_ERRDEFER: {
        return NULL;
    }
    default: {
        PANIC("unimplemented\n");
    }
    }
}

BasicBlock* convertToBasicBlock(CFG* cfg, IR* ir, BasicBlock* predecessor)
{
    BasicBlock* retval;
    int instruction = 0;
    if (ir == NULL) {
        return NULL;
    } else if (ir->inBlock) {
        retval = ir->inBlock;
    } else {
        retval = createBasicBlock(cfg);
        retval->entry = ir;
        for (; ir != NULL; ir = ir->next, instruction++) {
            ir->inBlock = retval;
            if (ir->dest != NULL && ir->dest->symbol != cfg->tempSymbol) {
                makeSymbolVersionUnique(ir->dest);
            }

            if (ir->irType == IR_DECLARE_LABEL) {
                // if you find a label declaration, end this block and jump to new block
                retval->hasBranch = false;
                retval->next = convertToBasicBlock(cfg, ir->next, retval);
                if (ir->next) {
                    ir->next->prev = NULL;
                    ir->next = NULL;
                }
                break;
            } else if (ir->irType == IR_JUMP) {
                // if you find a jump, end this block and start new block
                retval->hasBranch = false;
                if (ir->branch) {
                    retval->next = convertToBasicBlock(cfg, ir->branch->next, retval);
                } else {
                    retval->next = NULL;
                }
                if (ir->next) {
                    ir->next->prev = NULL;
                    ir->next = NULL;
                }
                break;
            } else if (ir->irType == IR_BRANCH_IF_FALSE) {
                // if you find a branch, end this block, start both blocks
                retval->hasBranch = true;
                IR* branchNext = ir->branch->next; // Since ir->branch->next may get nullified by calling convertToBasicBlock on ir->next
                retval->next = convertToBasicBlock(cfg, ir->next, retval);
                retval->branch = convertToBasicBlock(cfg, branchNext, retval);
                retval->condition = ir->src1;
                if (ir->next) {
                    ir->next->prev = NULL;
                    ir->next = NULL;
                }
                break;
            }
        }
    }
    return retval;
}

// Cannot do this during basic block conversion because the ir.next pointers are needed
void removeBasicBlockInstructions(CFG* cfg)
{
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        if (bb->entry == NULL) {
            continue;
        } else if (bb->entry->next == NULL) {
            bb->entry = NULL;
        } else {
            IR* ir = bb->entry;
            for (; ir->next != NULL; ir = ir->next) { }
            ir->prev->next = NULL;
        }
    }
}

bool copyAndConstantPropagation(CFG* cfg)
{
    bool retval = false;
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            switch (def->irType) {
            case IR_COPY:
                // Self copy (should remove)
                if (def->dest->symbol == def->src1->symbol && def->dest->version == def->src1->version) {
                    break;
                }
                // Integer constant propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                    LOG("int copy\n");
                }
                // Real constant propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_REAL && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                    LOG("real copy\n");
                }
                // Array literal propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_ARRAY_LITERAL && !def->src1->symbol->isVolatile && def->dest->symbol != cfg->tempSymbol) {
                    def->irType = IR_LOAD_ARRAY_LITERAL;
                    def->listData = def->src1->def->listData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                    LOG("load array copy\n");
                }
                // Arglist literal propagation
                else if (false && def->src1->def && def->src1->def->irType == IR_LOAD_ARGLIST && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_ARGLIST;
                    def->listData = def->src1->def->listData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                    LOG("load arglist copy\n");
                }
                // Copy propagation
                else if (def->src1->def && def->src1->def->irType == IR_COPY && def->src1 != def->src1->def->src1 && !def->src1->symbol->isVolatile) {
                    LOG("IR%d = IR%d\n", def->id, def->src1->def->id);
                    def->src1 = def->src1->def->src1;
                    retval = true;
                }
                break;
            case IR_INDEX:
                if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData < 0) {
                    error(def->pos, "array index is negative");
                } else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && getArrayLength(def->src1->type) != -1 && def->src2->def->intData >= getArrayLength(def->src1->type)) {
                    error(def->pos, "array index greater than array length");
                } else if (def->src1->def && def->src2 && def->src1->def->irType == IR_LOAD_ARRAY_LITERAL && def->src2->def->irType == IR_LOAD_INT && List_Get(def->src1->def->listData, def->src2->def->intData) != NULL) {
                    def->irType = IR_COPY;
                    def->src1 = List_Get(def->src1->def->listData, def->src2->def->intData);
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_SLICE: {
                SymbolVersion* length = List_Get(def->listData, 0);
                if (length->def && length->def->irType == IR_LOAD_INT && length->def->intData <= 0) {
                    error(length->def->pos, "array with non-positive length");
                }
                break;
            }
            case IR_EQ:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData == def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData == def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData == def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData == def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_NEQ:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData != def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData != def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData != def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData != def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_GTR:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData > def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData > def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData > def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData > def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_LSR:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData < def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData < def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData < def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData < def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_GTE:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData >= def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData >= def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData >= def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData >= def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_LTE:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData <= def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData <= def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = def->src1->def->intData <= def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->doubleData <= def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_ADD:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData + def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData + def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->intData + def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData + def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left identity
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src1 = def->src2;
                    def->src2 = NULL;
                    retval = true;
                }
                // Right identity
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_SUBTRACT:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData - def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData - def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->intData - def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData - def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left identity
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src1 = def->src2;
                    def->src2 = NULL;
                    retval = true;
                }
                // Right identity
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_MULTIPLY:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData * def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData * def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->intData * def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData * def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left identity
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 1) {
                    def->irType = IR_COPY;
                    def->src1 = def->src2;
                    def->src2 = NULL;
                    retval = true;
                }
                // Right identity
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 1) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left zero
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_LOAD_INT;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    def->intData = 0;
                    retval = true;
                }
                // Right zero
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_LOAD_INT;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    def->intData = 0;
                    retval = true;
                }
                break;
            case IR_DIVIDE:
                // Cannot divide by int zero
                if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    error(def->pos, "division by zero");
                }
                // Cannot divide by real zero
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_REAL && def->src2->def->doubleData == 0.0) {
                    error(def->pos, "division by zero");
                }
                // Known int value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData / def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData / def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known int/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->intData / def->src2->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real/real value
                else if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_REAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData / def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left identity
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 1) {
                    def->irType = IR_COPY;
                    def->src1 = def->src2;
                    def->src2 = NULL;
                    retval = true;
                }
                // Right identity
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 1) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_BIT_OR:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData | def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left identity
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src1 = def->src2;
                    def->src2 = NULL;
                    retval = true;
                }
                // Right identity
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_BIT_XOR:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData ^ def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_BIT_AND:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData & def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_LSHIFT:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData << def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left known value
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_LOAD_INT;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    def->intData = 0;
                    retval = true;
                }
                // Right known value
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_RSHIFT:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData >> def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left known value
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_LOAD_INT;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    def->intData = 0;
                    retval = true;
                }
                // Right known value
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_MODULUS:
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = def->src1->def->intData % def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Left known value
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_INT && def->src1->def->intData == 0) {
                    def->irType = IR_LOAD_INT;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    def->intData = 0;
                    retval = true;
                }
                // Right known value
                else if (def->src2->def && def->src2->def->irType == IR_LOAD_INT && def->src2->def->intData == 0) {
                    def->irType = IR_COPY;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_NOT:
                // Known int value
                if (def->src1->def && def->src1->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = !def->src1->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_NEG:
                // Known int value
                if (def->src1->def && def->src1->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = -def->src1->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Known real value
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_REAL) {
                    def->irType = IR_LOAD_INT;
                    def->doubleData = -def->src1->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_BIT_NOT:
                // Known int value
                if (def->src1->def && def->src1->def->irType == IR_LOAD_INT) {
                    def->irType = IR_LOAD_INT;
                    def->intData = ~def->src1->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            case IR_PHONY:
                // Phony IRs with only one def should be that single def
                if (def && def->irType == IR_PHONY) { // Make sure this is consistent, does necessarily have to be
                    forall(elem, def->listData)
                    {
                        IR* phonyDef = elem->data;
                        if (phonyDef->removed) {
                            List_Remove(def->listData, phonyDef);
                            retval = true;
                            LOG("phony def removed\n");
                            break;
                        }
                    }
                    if (def->listData->size == 1) {
                        IR* newDef = List_Get(def->listData, 0);
                        def->dest->def = newDef;
                        newDef->dest = def->dest;
                        removeInstruction(def->inBlock, def);
                        List_Remove(def->listData, newDef);
                        retval = true;
                        LOG("phony has one def\n");
                    }
                    if (def->listData->size == 0) {
                        removeInstruction(def->inBlock, def);
                        retval = true;
                        LOG("phony has one def\n");
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    return retval;
}

bool addArgs(CFG* cfg, BasicBlock* bb)
{
    bool retval = false;
    if (bb->visited) {
        return false;
    }
    bb->visited = true;

    if (bb->next) {
        retval |= addArgs(cfg, bb->next);
        forall(elem, bb->next->parameters)
        {
            SymbolVersion* param = elem->data; // parameter symbol for next block
            SymbolVersion* symbver = findVersion(param, bb->entry, NULL);
            if (symbver == param) { // Could not find param def in this block, require it as a parameter for this own block
                SymbolVersion* myParam = findSymbolVersionSet(bb->parameters, param);
                if (myParam) {
                    symbver = myParam;
                } else {
                    symbver = unversionedSymbolVersion(cfg, param->symbol, param->type);
                    putSymbolVersionSet(bb->parameters, symbver); // When you add symbol versions to the parameters, you need to go through IR and see if any dest/src are unversioned
                }
            } // else found in this block already, add it to the arguments
            retval |= putSymbolVersionSet(bb->nextArguments, symbver);
            if (retval) {
                LOG("Added %s_%d to L%d nextArgs\n", symbver->symbol->name, symbver->version, bb->id);
            }
        }
    }

    if (bb->branch && bb->hasBranch) {
        retval |= addArgs(cfg, bb->branch);
        forall(elem, bb->branch->parameters)
        {
            SymbolVersion* param = elem->data;
            SymbolVersion* symbver = findVersion(param, bb->entry, NULL);
            if (symbver == param) { // Could not find param def in this block, require it as a parameter for this own block
                SymbolVersion* myParam = findSymbolVersionSet(bb->parameters, param);
                if (myParam) {
                    symbver = myParam;
                } else {
                    symbver = unversionedSymbolVersion(cfg, param->symbol, param->type);
                    putSymbolVersionSet(bb->parameters, symbver);
                }
            }
            retval |= putSymbolVersionSet(bb->branchArguments, symbver);
            if (retval) {
                LOG("Added %s_%d to L%d branchArgs\n", symbver->symbol->name, symbver->version, bb->id);
            }
        }
    }

    return retval;
}

void calculateArgs(CFG* cfg)
{
    // Clear arguments
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        List_Clear(bb->parameters);
        List_Clear(bb->nextArguments);
        List_Clear(bb->branchArguments);

        // Parameters are symbols used by IR without a definition for the symbol before the IR
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            // If src1 version is undefined, and is not defined in this BB, request it as parameter
            if (ir->src1 != NULL && ir->src1->symbol != cfg->tempSymbol && ir->src1->version == -1) {
                ir->src1 = findVersion(ir->src1, bb->entry, ir);
                if (ir->src1->version == -1) {
                    putSymbolVersionSet(bb->parameters, ir->src1);
                }
            }
            // If src2 version is undefined, and is not defined in this BB, request it as parameter
            if (ir->src2 != NULL && ir->src2->symbol != cfg->tempSymbol && ir->src2->version == -1) {
                ir->src2 = findVersion(ir->src2, bb->entry, ir);
                if (ir->src2->version == -1) {
                    putSymbolVersionSet(bb->parameters, ir->src2);
                }
            }
            // If src3 version is undefined, and is not defined in this BB, request it as parameter
            if (ir->src3 != NULL && ir->src3->symbol != cfg->tempSymbol && ir->src3->version == -1) {
                ir->src3 = findVersion(ir->src3, bb->entry, ir);
                if (ir->src3->version == -1) {
                    putSymbolVersionSet(bb->parameters, ir->src3);
                }
            }

            if (ir->irType == IR_CALL || ir->irType == IR_LOAD_ARGLIST || ir->irType == IR_LOAD_ARRAY_LITERAL || ir->irType == IR_NEW_ARR) {
                forall(elem, ir->listData)
                {
                    if (!elem->data) {
                        PANIC("WHOA!\n");
                    }
                    if (((SymbolVersion*)elem->data)->symbol != cfg->tempSymbol && ((SymbolVersion*)elem->data)->version == -1) {
                        elem->data = findVersion(((SymbolVersion*)elem->data), bb->entry, ir);
                        if (((SymbolVersion*)elem->data)->version == -1) {
                            putSymbolVersionSet(bb->parameters, ((SymbolVersion*)elem->data));
                        }
                    }
                }
            }
        }
        // Do the same for the condition of a branch, if there is one
        if (bb->hasBranch && bb->condition != NULL && bb->condition->symbol != cfg->tempSymbol && bb->condition->version == -1) {
            bb->condition = findVersion(bb->condition, bb->entry, NULL);
            if (bb->condition->version == -1) {
                putSymbolVersionSet(bb->parameters, bb->condition);
            }
        }
    }

    // Add function parameters as basic block symbol version parameters
    forall(elem, cfg->symbol->type->function.domainType->paramlist.defines)
    {
        ASTNode* define = elem->data;
        SymbolNode* param = define->define.symbol;
        SymbolVersion* symbver = unversionedSymbolVersion(cfg, param, param->type);
        putSymbolVersionSet(cfg->blockGraph->parameters, symbver);
    }

    // Find phi arguments
    do {
        clearBBVisitedFlags(cfg);
    } while (addArgs(cfg, cfg->blockGraph));
}

void findUnusedSymbolVersions(CFG* cfg)
{
    // Find out which symbols are used
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        // Clear all used flags
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            if (ir->dest) {
                ir->dest->used = false;
            }
        }

        // Arguments are default used
        forall(elem2, bb->nextArguments)
        {
            SymbolVersion* symbver = elem2->data;
            symbver->used = true;
        }
        forall(elem2, bb->branchArguments)
        {
            SymbolVersion* symbver = elem2->data;
            symbver->used = true;
        }

        // Go through and see if each symbol is used
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->dest && (def->irType == IR_DOT_COPY || def->irType == IR_DEREF_COPY || def->irType == IR_FREE || def->irType == IR_CALL || (def->dest->def && def->dest->def->irType == IR_PHONY))) {
                def->dest->used = true;
            }
            if (def->src1) {
                def->src1->used = true;
            }
            if (def->src2) {
                def->src2->used = true;
            }
            if (def->src3) {
                def->src3->used = true;
            }
            if (def->irType == IR_LOAD_ARRAY_LITERAL || def->irType == IR_LOAD_ARGLIST || def->irType == IR_SLICE || def->irType == IR_CALL || def->irType == IR_NEW_ARR) {
                forall(elem, def->listData)
                {
                    SymbolVersion* symbver = elem->data;
                    symbver->used = true;
                }
            }
        }

        // Conditions are always used
        if (bb->hasBranch) {
            bb->condition->used = true;
        }
    }
}

void calculateIncomingNode(BasicBlock* bb)
{
    bb->incoming++;
    if (bb->visited) {
        return;
    }
    bb->visited = true;
    if (bb->next) {
        calculateIncomingNode(bb->next);
    }
    if (bb->hasBranch && bb->branch) {
        calculateIncomingNode(bb->branch);
    }
}

// Basic blocks with only one incoming node may be adopted into the node that calls them
void calculateIncomingNodes(CFG* cfg)
{
    // Clear incoming counters
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        bb->incoming = 0;
    }

    clearBBVisitedFlags(cfg);
    calculateIncomingNode(cfg->blockGraph);
}

/*
Volatile symbols may change unpredictably throughout the program. Some optimizations don't work on volatile symbols.
Find those symbols that are volatile.
*/
void calculateVolatility(CFG* cfg)
{
    // Clear volatility flag
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            if (ir->dest) {
                ir->dest->symbol->isVolatile = false;
            }
        }
    }

    // Go through instruction in each block. If a symbol has it's address taken, mark it as volatile
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            if (ir->irType == IR_ADDR_OF) {
                ir->src1->symbol->isVolatile = true;
            }
        }
    }
}

// Removes code that has no effect
bool deadCode(CFG* cfg)
{
    bool retval = false;
    if (!cfg->blockGraph) {
        return retval;
    }

    calculateArgs(cfg); // Needs to be recalculated each time, because args need to be counted as 'used'. So need to find what args are
    findUnusedSymbolVersions(cfg);
    calculateIncomingNodes(cfg);
    calculateVolatility(cfg);

    // Remove basic blocks with no incoming basic blocks from the list of basic blocks
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        if (bb->incoming == 0) {
            removeBasicBlock(cfg, bb, true);
            LOG("remove from L%d block list, no incoming basic blocks\n", bb->id);
            return true;
        }
    }

    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;

        // Remove any symbols that aren't used
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->dest && !def->removed && !def->dest->used && def->dest->symbol != cfg->returnSymbol && def->irType != IR_PHONY) {
                LOG("remove ir %d %s_%d %p\n", def->id, def->dest->symbol->name, def->dest->version, def->dest);
                removeInstruction(bb, def);
                retval = true;
            }
            if (def->dest && !def->removed && !def->dest->used && def->dest->symbol == cfg->returnSymbol && cfg->symbol->type->function.codomainType->astType == AST_VOID) {
                LOG("remove void ir %d %s_%d %p\n", def->id, def->dest->symbol->name, def->dest->version, def->dest);
                removeInstruction(bb, def);
                retval = true;
            }
        }

        // Adopt basic blocks with only one incoming block
        if (bb->next && bb->entry && !bb->hasBranch && bb->next->incoming == 1) {
            IR* end = getTail(bb->entry);
            LOG("block adoption of L%d\n", bb->next->id);

            forall(elem, bb->nextArguments) // no need for branch args since !bb->hasBranch
            {
                SymbolVersion* argument = elem->data;
                SymbolVersion* parameter = findSymbolVersionSet(bb->next->parameters, argument);
                if (parameter) {
                    if (parameter->version != argument->version) {
                        end = appendInstructionBasicBlock(bb, createIR(IR_COPY, parameter, argument, NULL, invalid_pos));
                        parameter->def = end;
                        makeSymbolVersionUnique(parameter);
                    } else {
                        LOG("symbol %s L%d arg is same version as L%d param \n", parameter->symbol->name, bb->id, bb->next->id);
                    }
                } else {
                    LOG("couldn't find the parameter to match the argument\n");
                }
            }

            // Join next block at the end of this block
            end->next = bb->next->entry;
            if (bb->next->entry) {
                bb->next->entry->prev = end;
            }

            // Copy basic block end conditions
            bb->hasBranch = bb->next->hasBranch;
            bb->branch = bb->next->branch;
            bb->condition = bb->next->condition;
            bb->nextArguments = bb->next->nextArguments; // Is this correct?
            bb->branchArguments = bb->next->branchArguments; // Is this correct?

            // Set inBlock to this block
            for (IR* child = bb->next->entry; child != NULL; child = child->next) {
                child->inBlock = bb;
            }

            // Remove the next block
            removeBasicBlock(cfg, bb->next, false);
            bb->next = bb->next->next;
            retval = true;
            break;
        }

        // Remove false branches
        if (bb->hasBranch && bb->condition->def && bb->condition->def->irType == IR_LOAD_INT && !bb->condition->symbol->isVolatile) {
            bb->hasBranch = false;
            if (!bb->condition->def->intData) {
                bb->next = bb->branch;
            }
            retval = true;
            LOG("false branch L%d\n", bb->id);
        }

        // Remove jump chains
        if (bb->next && !bb->next->entry && !bb->next->hasBranch) {
            bb->next = bb->next->next;
            retval = true;
            LOG("jump chain L%d\n", bb->id);
        }

        if (bb->branch && !bb->branch->entry && !bb->branch->hasBranch) {
            bb->branch = bb->branch->next;
            retval = true;
            LOG("branch chain L%d\n", bb->id);
        }

        if (bb->hasBranch && bb->branch == bb->next) {
            bb->hasBranch = false;
            LOG("same branch L%d\n", bb->id);
            retval = true;
        }
    }

    // Rebase block graph if jump chain
    if (cfg->blockGraph && !cfg->blockGraph->entry && !cfg->blockGraph->hasBranch) {
        cfg->blockGraph = cfg->blockGraph->next;
        retval = true;
        LOG("rebase cfg block graph, jump chain\n");
    }

    return retval;
}

List* createCFG(SymbolNode* functionSymbol, CFG* caller)
{
    if (functionSymbol->ir || functionSymbol->isExtern) {
        return;
    }
    CFG* cfg = calloc(sizeof(CFG), 1);
    if (!cfg) {
        gen_error("out of memory");
    }

    cfg->symbol = functionSymbol;
    cfg->tempSymbol = Symbol_Create("$", SYMBOL_VARIABLE, functionSymbol, (Position) { NULL, 0, 0, 0, 0 });
    cfg->returnSymbol = Symbol_Create("$return", SYMBOL_VARIABLE, functionSymbol, (Position) { NULL, 0, 0, 0, 0 });
    cfg->head = NULL;
    cfg->tail = NULL;
    cfg->basicBlocks = List_Create();
    cfg->leaves = List_Create();

    functionSymbol->ir = cfg;
    if (caller && !List_Contains(caller->leaves, cfg)) {
        List_Append(caller->leaves, cfg);
    }

    // Convert function definition AST to quadruple list
    SymbolVersion* eval = flattenAST(cfg, functionSymbol->def, NULL, NULL, NULL, NULL, false);
    // Implicit success return
    if (functionSymbol->type->function.codomainType->astType == AST_ENUM && enumContainsField(functionSymbol->type->function.codomainType, "success", VOID_TYPE)) {
        SymbolVersion* tag = tempSymbolVersion(cfg, INT64_TYPE);
        IR* tagIR = createIR_int(IR_LOAD_INT, tag, NULL, NULL, getTagEnum("success", functionSymbol->type->function.codomainType), invalid_pos);
        tag->def = tagIR;
        appendInstruction(cfg, tagIR);

        SymbolVersion* implcitSuccess = tempSymbolVersion(cfg, functionSymbol->type->function.codomainType);
        IR* ir = createIR(IR_LOAD_ARGLIST, implcitSuccess, NULL, NULL, invalid_pos);
        implcitSuccess->def = ir;
        ir->listData = List_Create();
        List_Append(ir->listData, tag);
        appendInstruction(cfg, ir);

        SymbolVersion* returnVersion = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);

        appendInstruction(cfg, createIR(IR_COPY, returnVersion, implcitSuccess, NULL, invalid_pos));
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, NULL, invalid_pos));
    }
    // Normal expression return
    else if (eval) {
        SymbolVersion* returnVersion = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);
        appendInstruction(cfg, createIR(IR_COPY, returnVersion, eval, NULL, invalid_pos));
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, NULL, invalid_pos));
    }
    //printf("\n%s\n", functionSymbol->name);
    //printInstructionList(cfg);

    // Convert quadruple list to CFG of basic blocks, find versions!
    cfg->blockGraph = convertToBasicBlock(cfg, cfg->head, NULL);
    removeBasicBlockInstructions(cfg);

    // Optimize
    do {
        //printf("\n\n%s\n", cfg->symbol->name);
        //clearBBVisitedFlags(cfg);
        //printBlockGraph(cfg->blockGraph);
    } while (copyAndConstantPropagation(cfg) | deadCode(cfg));

    // Parameters and the such are kept
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        forall(elem, bb->parameters)
        {
            SymbolVersion* symbver = elem->data;
            makeSymbolVersionUnique(symbver);
        }
        forall(elem, bb->nextArguments)
        {
            SymbolVersion* symbver = elem->data;
            makeSymbolVersionUnique(symbver);
        }
        forall(elem, bb->branchArguments)
        {
            SymbolVersion* symbver = elem->data;
            makeSymbolVersionUnique(symbver);
        }
    }

    // Parameters are sometimes added to a BB after the fact, symbol versions are not changed to reflect this.
    // Update undefined symbol versions to be the BB parameter symbol version
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
            if (ir->src1 && ir->src1->version == -1) {
                ir->src1 = findSymbolVersionSet(bb->parameters, ir->src1);
                if (!ir->src1 || ir->src1->version == -1) {
                    PANIC("AH\n");
                }
            }
            if (ir->src2 && ir->src2->version == -1) {
                ir->src2 = findSymbolVersionSet(bb->parameters, ir->src2);
                if (!ir->src2 || ir->src2->version == -1) {
                    PANIC("AH\n");
                }
            }
            if (ir->src3 && ir->src3->version == -1) {
                ir->src3 = findSymbolVersionSet(bb->parameters, ir->src3);
                if (!ir->src3 || ir->src3->version == -1) {
                    PANIC("AH\n");
                }
            }
            if (ir->irType == IR_CALL || ir->irType == IR_LOAD_ARGLIST || ir->irType == IR_LOAD_ARRAY_LITERAL) {
                forall(elem, ir->listData)
                {
                    if (((SymbolVersion*)elem->data)->version == -1) {
                        elem->data = findSymbolVersionSet(bb->parameters, elem->data);
                        if (((SymbolVersion*)elem->data)->version == -1) {
                            PANIC("AH\n");
                        }
                    }
                }
            }
        }
    }

    // TODO: Register allocation

    return cfg;
}