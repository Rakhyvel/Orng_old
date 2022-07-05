#include "./ir.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./main.h"
#include "./symbol.h"
#include "./validator.h"
#include <stdio.h>
#include <stdlib.h>

SymbolVersion* flattenAST(CFG* cfg, ASTNode* node, IR* returnLabel, IR* breakLabel, IR* continueLabel);

char* IR_ToString(ir_type type)
{
    switch (type) {
    case IR_LOAD_INT:
        return "IR_LOAD_INT";
    case IR_LOAD_REAL:
        return "IR_LOAD_REAL";
    case IR_LOAD_STR:
        return "IR_LOAD_STR";
    case IR_COPY:
        return "IR_COPY";
    case IR_CALL:
        return "IR_CALL";
    case IR_DECLARE_LABEL:
        return "IR_DECLARE_LABEL";
    case IR_JUMP:
        return "IR_JUMP";
    case IR_BRANCH_IF_FALSE:
        return "IR_BRANCH_IF_FALSE";
    case IR_RET:
        return "IR_RET";
    case IR_DOT:
        return "IR_DOT";
    case IR_BIT_AND:
        return "IR_BIT_AND";
    case IR_BIT_OR:
        return "IR_BIT_OR";
    case IR_BIT_XOR:
        return "IR_BIT_XOR";
    case IR_LSHIFT:
        return "IR_LSHIFT";
    case IR_RSHIFT:
        return "IR_RSHIFT";
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
    case IR_NEGATE:
        return "IR_NEGATE";
    case IR_NOT:
        return "IR_NOT";
    case IR_BIT_NOT:
        return "IR_BIT_NOT";
    case IR_DEREF:
        return "IR_DEREF";
    case IR_DEREF_COPY:
        return "IR_DEREF_COPY";
    case IR_ADDR_OF:
        return "IR_ADDR_OF";
    case IR_PHONY:
        return "IR_PHONY";
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
        printf("if (!%s_%d) goto %d", bb->condition->symbol->name, bb->condition->version, bb->branch->id);
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

IR* createIR(ir_type type, SymbolVersion* dest, IR* src1, IR* src2)
{
    static int id = 0;
    IR* retval = calloc(sizeof(IR), 1);
    if (!retval) {
        gen_error("out of memory");
    }
    if (id == 25) {
        printf("hehe\n");
    }
    retval->irType = type;
    retval->dest = dest;
    retval->src1 = src1;
    retval->src2 = src2;
    retval->id = id++;
    return retval;
}

IR* createIR_int(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, int64_t data)
{
    IR* retval = createIR(type, dest, src1, src2);
    retval->intData = data;
    return retval;
}

IR* createIR_double(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, double data)
{
    IR* retval = createIR(type, dest, src1, src2);
    retval->doubleData = data;
    return retval;
}

IR* createIR_branch(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, IR* data)
{
    IR* retval = createIR(type, dest, src1, src2);
    retval->branch = data;
    return retval;
}

IR* createIR_symbol(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, SymbolVersion* data)
{
    IR* retval = createIR(type, dest, src1, src2);
    retval->symbver = data;
    return retval;
}

IR* createIR_ast(ir_type type, SymbolVersion* dest, IR* src1, IR* src2, ASTNode* from, ASTNode* to)
{
    IR* retval = createIR(type, dest, src1, src2);
    retval->fromType = from;
    retval->toType = to;
    return retval;
}

IR* createIR_label()
{
    IR* retval = createIR(IR_DECLARE_LABEL, NULL, NULL, NULL);
    return retval;
}

void putSymbolVersion(List* symbolVersions, SymbolVersion* symver)
{
    for (ListElem* elem = List_Begin(symbolVersions); elem != List_End(symbolVersions); elem = elem->next) {
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
    List_Append(cfg->symbolVersions, retval);
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
        flattenAST(cfg, List_Get(defers, i), NULL, NULL, NULL);
    }
}

SymbolVersion* defaultValue(CFG* cfg, ASTNode* type)
{
    switch (type->astType) {
    default: {
        SymbolVersion* temp = tempSymbolVersion(cfg, type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 0);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARRAY: {
        ASTNode* lengthDefine = List_Get(type->paramlist.defines, 0);
        SymbolNode* lengthSymbol = lengthDefine->define.symbol;
        ASTNode* lengthCode = lengthSymbol->def;
        ASTNode* dataDefine = List_Get(type->paramlist.defines, 1);
        SymbolNode* dataSymbol = dataDefine->define.symbol;
        ASTNode* dataType = dataSymbol->type->unop.expr;

        SymbolVersion* temp = tempSymbolVersion(cfg, type);

        IR* ir = createIR(IR_LOAD_ARRAY_LITERAL, temp, NULL, NULL);
        temp->def = ir;
        ir->listData = List_Create();
        for (int i = 0; i < lengthCode->_int.data; i++) { // TODO: flatten AST and use the IR_LOAD_INT.indData instead (?)
            SymbolVersion* member = defaultValue(cfg, dataType);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_PARAMLIST: {
        SymbolVersion* temp = tempSymbolVersion(cfg, type);

        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL);
        temp->def = ir;
        ir->listData = List_Create();

        for (ListElem* elem = List_Begin(type->paramlist.defines); elem != List_End(type->paramlist.defines); elem = elem->next) {
            ASTNode* define = elem->data;
            SymbolNode* var = define->define.symbol;
            if (var->def->astType == AST_UNDEF) {
                List_Append(ir->listData, defaultValue(cfg, var->type));
            } else if (!(var->symbolType == SYMBOL_FUNCTION && var->type->isConst)) {
                List_Append(ir->listData, flattenAST(cfg, var->def, NULL, NULL, NULL));
            }
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
SymbolVersion* flattenAST(CFG* cfg, ASTNode* node, IR* returnLabel, IR* breakLabel, IR* continueLabel)
{
    switch (node->astType) {
    case AST_IDENT: { // the symbol version for the ident needs to be unversioned, and not shared with any other IR
        SymbolNode* symbol = Symbol_Find(node->ident.data, node->scope);

        SymbolVersion* var = unversionedSymbolVersion(cfg, symbol, symbol->type);
        return var;
    }
    case AST_INT: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, node->_int.data);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_TRUE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 1);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_FALSE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 0);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_CHAR: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, (int64_t)(*node->_char.data));
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_REAL: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR_double(IR_LOAD_REAL, temp, NULL, NULL, node->real.data);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARRAY_LITERAL: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LOAD_ARRAY_LITERAL, temp, NULL, NULL);
        temp->def = ir;
        ir->listData = List_Create();
        forall(elem, node->arrayLiteral.members)
        {
            SymbolVersion* member = flattenAST(cfg, elem->data, returnLabel, breakLabel, continueLabel);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ARGLIST: {
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LOAD_ARGLIST, temp, NULL, NULL);
        temp->def = ir;
        ir->listData = List_Create();
        forall(elem, node->arrayLiteral.members)
        {
            SymbolVersion* member = flattenAST(cfg, elem->data, returnLabel, breakLabel, continueLabel);
            List_Append(ir->listData, member);
        }
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_PAREN: {
        return flattenAST(cfg, List_Get(node->arglist.args, 0), returnLabel, breakLabel, continueLabel);
    }
    case AST_BLOCK: {
        // Each defer has 3 labels, continue, break, return
        // Start off with the given continue, break, return (-1)
        // Every time a defer is encountered in the block, increase number by 1
        // When passing continue, break, return, check the number and use those labels
        List* continueLabels = List_Create();
        List* breakLabels = List_Create();
        List* returnLabels = List_Create();
        forall(elem, node->block.symbol->defers)
        {
            List_Append(continueLabels, createIR_label());
            List_Append(breakLabels, createIR_label());
            List_Append(returnLabels, createIR_label());
        }
        IR* end = createIR_label();

        IR* thisContinueLabel = continueLabel ? continueLabel : end;
        IR* thisBreakLabel = breakLabel;
        IR* thisReturnLabel = returnLabel;
        int deferLabelIndex = node->block.symbol->defers->size;

        SymbolVersion* var = NULL;
        for (ListElem* elem = List_Begin(node->block.children); elem != List_End(node->block.children); elem = elem->next) {
            ASTNode* child = elem->data;
            var = flattenAST(cfg, child, thisReturnLabel, thisBreakLabel, thisContinueLabel);
            if (child->astType == AST_DEFER) {
                deferLabelIndex--;
                thisContinueLabel = List_Get(continueLabels, deferLabelIndex);
                thisBreakLabel = List_Get(breakLabels, deferLabelIndex);
                thisReturnLabel = List_Get(returnLabels, deferLabelIndex);
            }
        }

        SymbolVersion* evalSymbolVersion = NULL;
        if (node->type->astType != AST_UNDEF && var) {
            evalSymbolVersion = tempSymbolVersion(cfg, node->type);
            IR* ir = createIR(IR_COPY, evalSymbolVersion, var, NULL);
            evalSymbolVersion->def = ir;
            appendInstruction(cfg, ir);
        }

        generateDefers(cfg, node->block.symbol->defers, continueLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, end));
        generateDefers(cfg, node->block.symbol->defers, breakLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, breakLabel));
        generateDefers(cfg, node->block.symbol->defers, returnLabels);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, returnLabel));
        appendInstruction(cfg, end);
        return evalSymbolVersion;
    }
    case AST_IF: {
        SymbolVersion* var = NULL;
        IR* phony = NULL;
        if (node->type->astType != AST_UNDEF) {
            var = tempSymbolVersion(cfg, node->type);
            phony = createIR(IR_PHONY, var, NULL, NULL);
            phony->listData = List_Create();
            var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
            appendInstruction(cfg, phony);
        }
        SymbolVersion* condition = flattenAST(cfg, node->_if.condition, returnLabel, breakLabel, continueLabel);

        IR* elseLabel = createIR_label();
        IR* endLabel = createIR_label();

        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel));
        SymbolVersion* bodySymbver = flattenAST(cfg, node->_if.bodyBlock, returnLabel, breakLabel, continueLabel);
        if (var && bodySymbver) {
            IR* copy = createIR(IR_COPY, var, bodySymbver, NULL);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* elseSymbver = flattenAST(cfg, node->_if.elseBlock, returnLabel, breakLabel, continueLabel);
        if (var && elseSymbver) {
            IR* copy = createIR(IR_COPY, var, elseSymbver, NULL);
            List_Append(phony->listData, copy);
            appendInstruction(cfg, copy);
        }
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_FOR: {
        IR* beginLabel = createIR_label();
        IR* thisContinueLabel = createIR_label();
        IR* endLabel = createIR_label();

        flattenAST(cfg, node->_for.pre, returnLabel, breakLabel, continueLabel);
        appendInstruction(cfg, beginLabel);
        SymbolVersion* condition = flattenAST(cfg, node->_for.condition, returnLabel, endLabel, thisContinueLabel);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, endLabel));
        flattenAST(cfg, node->_for.bodyBlock, returnLabel, endLabel, thisContinueLabel);
        appendInstruction(cfg, thisContinueLabel);
        flattenAST(cfg, node->_for.post, returnLabel, endLabel, continueLabel);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, beginLabel));
        appendInstruction(cfg, endLabel);
        return NULL;
    }
    case AST_RETURN: {
        SymbolVersion* retval = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* var = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);

        appendInstruction(cfg, createIR(IR_COPY, var, retval, NULL));
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, returnLabel));
        return NULL;
    }
    case AST_BREAK: {
        IR* ir = createIR_branch(IR_JUMP, NULL, NULL, NULL, breakLabel);
        appendInstruction(cfg, ir);
        return NULL;
    }
    case AST_CONTINUE: {
        IR* ir = createIR_branch(IR_JUMP, NULL, NULL, NULL, continueLabel);
        appendInstruction(cfg, ir);
        return NULL;
    }
    case AST_DEFER: {
        return NULL;
    }
    case AST_DEFINE: {
        if (node->define.symbol->type->isConst) {
            return NULL;
        }

        SymbolVersion* var = unversionedSymbolVersion(cfg, node->define.symbol, node->define.symbol->type);
        SymbolVersion* def = NULL;
        if (node->define.symbol->def->astType != AST_UNDEF) {
            def = flattenAST(cfg, node->define.symbol->def, returnLabel, breakLabel, continueLabel);
        } else {
            def = defaultValue(cfg, node->define.symbol->type);
        }

        IR* ir = createIR(IR_COPY, var, def, NULL);
        var->def = ir;
        appendInstruction(cfg, ir);
        return var;
    }
    case AST_SLICE: {
        /*
		struct struct_3 _172_arr = {4, (int64_t[]){0, 0, 0, 0}}
		upperBound = 4;
		lowerBound = 2;
		newSize = upperBound - lowerBound
		arrData = arr.data
		newPtr = arrData + lowerBound
		_172_subArr = {newSize, newPtr};
		*/
        SymbolVersion* arr = flattenAST(cfg, node->slice.arrayExpr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* lowerBound;
        if (node->slice.lowerBound->astType != AST_UNDEF) {
            lowerBound = flattenAST(cfg, node->slice.lowerBound, returnLabel, breakLabel, continueLabel);
        } else {
            lowerBound = tempSymbolVersion(cfg, INT64_TYPE);
            IR* loadLowerBoundIR = createIR_int(IR_LOAD_INT, lowerBound, NULL, NULL, 0);
            lowerBound->def = loadLowerBoundIR;
            appendInstruction(cfg, loadLowerBoundIR);
        }
        SymbolVersion* upperBound;
        if (node->slice.upperBound->astType != AST_UNDEF) {
            upperBound = flattenAST(cfg, node->slice.upperBound, returnLabel, breakLabel, continueLabel);
        } else {
            upperBound = tempSymbolVersion(cfg, INT64_TYPE);
            IR* arrDataIR = createIR(IR_DOT, upperBound, arr, NULL);
            arrDataIR->strData = "length";
            upperBound->def = arrDataIR;
            appendInstruction(cfg, arrDataIR);
        }

        SymbolVersion* newSizeSymbver = tempSymbolVersion(cfg, INT64_TYPE);
        IR* newSizeIR = createIR(IR_SUBTRACT, newSizeSymbver, upperBound, lowerBound);
        newSizeSymbver->def = newSizeIR;
        appendInstruction(cfg, newSizeIR);

        ASTNode* dataDefine = List_Get(node->slice.arrayExpr->type->paramlist.defines, 1);
        SymbolNode* dataSymbol = dataDefine->define.symbol;
        ASTNode* dataType = dataSymbol->type->unop.expr;
        SymbolVersion* arrDataSymbver = tempSymbolVersion(cfg, dataType);
        IR* arrDataIR = createIR(IR_DOT, arrDataSymbver, arr, NULL);
        arrDataIR->strData = "data";
        arrDataSymbver->def = arrDataIR;
        appendInstruction(cfg, arrDataIR);

        SymbolVersion* newPtrSymbver = tempSymbolVersion(cfg, dataType);
        IR* newPtrIR = createIR(IR_ADD, newPtrSymbver, arrDataSymbver, lowerBound);
        newPtrSymbver->def = newPtrIR;
        appendInstruction(cfg, newPtrIR);

        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);
        IR* ir = createIR(IR_LOAD_ARGLIST, temp, arr, NULL);
        ir->listData = List_Create();
        temp->def = ir;
        List_Append(ir->listData, newSizeSymbver);
        List_Append(ir->listData, newPtrSymbver);
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_INDEX: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_INDEX, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DOT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_DOT, temp, left, NULL);
        ir->strData = node->binop.right->ident.data;
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_OR: {
        SymbolVersion* var = tempSymbolVersion(cfg, INT8_TYPE);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        IR* elseLabel = createIR_label();
        IR* endLabel = createIR_label();

        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, left, NULL, elseLabel));
        IR* loadTrue = createIR_int(IR_LOAD_INT, var, NULL, NULL, 1);
        List_Append(phony->listData, loadTrue);
        appendInstruction(cfg, loadTrue);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, elseLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        IR* copyRight = createIR(IR_COPY, var, right, NULL);
        List_Append(phony->listData, copyRight);
        appendInstruction(cfg, copyRight);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_AND: {
        SymbolVersion* var = tempSymbolVersion(cfg, INT8_TYPE);
        IR* phony = createIR(IR_PHONY, var, NULL, NULL);
        phony->listData = List_Create();
        var->def = phony; // Done just so that it is considered live, I think. Has no real "def", since it's run-time dependent
        appendInstruction(cfg, phony);

        IR* elseLabel = createIR_label();
        IR* endLabel = createIR_label();

        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, left, NULL, elseLabel));
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        IR* copyRight = createIR(IR_COPY, var, right, NULL);
        List_Append(phony->listData, copyRight);
        appendInstruction(cfg, copyRight);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, elseLabel);
        IR* loadFalse = createIR_int(IR_LOAD_INT, var, NULL, NULL, 0);
        List_Append(phony->listData, loadFalse);
        appendInstruction(cfg, loadFalse);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, endLabel);
        return var;
    }
    case AST_BIT_OR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_OR, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_XOR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_XOR, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_AND: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_AND, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LSHIFT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LSHIFT, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_RSHIFT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_RSHIFT, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_EQ: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_EQ, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NEQ: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_NEQ, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_GTR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_GTR, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LSR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LSR, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_GTE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_GTE, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LTE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_LTE, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ADD: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_ADD, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_SUBTRACT: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_SUBTRACT, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_MULTIPLY: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_MULTIPLY, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DIVIDE: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_DIVIDE, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_MODULUS: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_MODULUS, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ASSIGN: {
        if (node->binop.left->astType == AST_IDENT) {
            SymbolNode* symbol = Symbol_Find(node->binop.left->ident.data, node->scope);
            SymbolVersion* var = unversionedSymbolVersion(cfg, symbol, symbol->type);
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);

            IR* ir = createIR(IR_COPY, var, right, NULL);
            var->def = ir;
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_INDEX) {
            SymbolVersion* arr = flattenAST(cfg, node->binop.left->binop.left, returnLabel, breakLabel, continueLabel);
            SymbolVersion* index = flattenAST(cfg, node->binop.left->binop.right, returnLabel, breakLabel, continueLabel);
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);

            IR* ir = createIR(IR_INDEX_COPY, arr, index, right);
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_DOT) {
            SymbolVersion* left = flattenAST(cfg, node->binop.left->binop.left, returnLabel, breakLabel, continueLabel);
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            IR* ir = createIR(IR_DOT_COPY, left, right, NULL);
            ir->strData = node->binop.left->binop.right->ident.data;
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_DEREF) {
            SymbolVersion* left = flattenAST(cfg, node->binop.left->unop.expr, returnLabel, breakLabel, continueLabel);
            SymbolVersion* right = flattenAST(cfg, node->binop.right, returnLabel, breakLabel, continueLabel);
            SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

            IR* ir = createIR(IR_DEREF_COPY, NULL, left, right);
            appendInstruction(cfg, ir);
        } else if (node->binop.left->astType == AST_PAREN) {
            node->binop.left = List_Get(node->binop.left->arglist.args, 0);
            flattenAST(cfg, node, returnLabel, breakLabel, continueLabel);
        } else {
            PANIC("not an l-value\n");
        }
        return NULL;
    }
    case AST_NOT: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_NOT, temp, expr, NULL);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_NEG: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_NEGATE, temp, expr, NULL);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BIT_NOT: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_BIT_NOT, temp, expr, NULL);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ADDROF: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_ADDR_OF, temp, expr, NULL);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_DEREF: {
        SymbolVersion* expr = flattenAST(cfg, node->unop.expr, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->type);

        IR* ir = createIR(IR_DEREF, temp, expr, NULL);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_CAST: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left, returnLabel, breakLabel, continueLabel);
        SymbolVersion* temp = tempSymbolVersion(cfg, node->binop.right);

        IR* ir = createIR_ast(IR_COPY, temp, left, NULL, node->binop.left->type, node->binop.right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_UNDEF: {
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
                retval->next = convertToBasicBlock(cfg, ir->next, retval);
                retval->branch = convertToBasicBlock(cfg, ir->branch->next, retval);
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
                }
                // Real constant propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_REAL && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_REAL;
                    def->doubleData = def->src1->def->doubleData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Array literal propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_ARRAY_LITERAL && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_ARRAY_LITERAL;
                    def->listData = def->src1->def->listData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Arglist literal propagation
                else if (def->src1->def && def->src1->def->irType == IR_LOAD_ARGLIST && !def->src1->symbol->isVolatile) {
                    def->irType = IR_LOAD_ARGLIST;
                    def->listData = def->src1->def->listData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                // Copy propagation
                else if (def->src1->def && def->src1->def->irType == IR_COPY && def->src1 != def->src1->def->src1 && !def->src1->symbol->isVolatile) {
                    def->src1 = def->src1->def->src1;
                    retval = true;
                }
                break;
            case IR_INDEX:
                if (def->src1->def && def->src2 && def->src1->def->irType == IR_LOAD_ARRAY_LITERAL && def->src2->def->irType == IR_LOAD_INT) {
                    def->irType = IR_COPY;
                    def->src1 = List_Get(def->src1->def->listData, def->src2->def->intData);
                    def->src2 = NULL;
                    retval = true;
                }
                break;
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
                // Known int value
                if (def->src1->def && def->src2->def && def->src1->def->irType == IR_LOAD_INT && def->src2->def->irType == IR_LOAD_INT) {
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
            case IR_NEGATE:
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

    // Parameters are symbols used by IR without a definition for the symbol before the IR
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        if (ir->src1 != NULL) {
            if (ir->src1->symbol != cfg->tempSymbol) {
                ir->src1 = findVersion(ir->src1, bb->entry, ir);
                if (ir->src1->version == -1) {
                    putSymbolVersionSet(bb->parameters, ir->src1);
                }
            }
        }
        if (ir->src2 != NULL) {
            if (ir->src2->symbol != cfg->tempSymbol) {
                ir->src2 = findVersion(ir->src2, bb->entry, ir);
                if (ir->src2->version == -1) {
                    putSymbolVersionSet(bb->parameters, ir->src2);
                }
            }
        }
    }

    if (bb->next) {
        retval |= addArgs(cfg, bb->next);
        forall(elem, bb->next->parameters)
        {
            SymbolVersion* param = elem->data;
            SymbolVersion* symbver = findVersion(param, bb->entry, NULL);
            if (symbver == param) { // Could not find param def in this block, require it as a parameter for this own block
                SymbolVersion* myParam = findSymbolVersionSet(bb->parameters, param);
                if (myParam) {
                    symbver = myParam;
                } else {
                    symbver = unversionedSymbolVersion(cfg, param->symbol, param->type);
                    putSymbolVersionSet(bb->parameters, symbver); // When you add symbol versions to the parameters, you need to go through IR and see if any dest/src are unversioned
                }
            }
            retval |= putSymbolVersionSet(bb->nextArguments, symbver);
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
    }

    clearBBVisitedFlags(cfg);
    // Find phi arguments
    while (addArgs(cfg, cfg->blockGraph)) {
        clearBBVisitedFlags(cfg);
    }
}

void findUnusedSymbolVersions(CFG* cfg)
{
    // Clear all used flags
    forall(elem, cfg->symbolVersions)
    {
        SymbolVersion* symbver = elem->data;
        symbver->used = false;
    }

    // Find out which symbols are used
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
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
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->dest && (def->irType == IR_INDEX_COPY || def->irType == IR_DOT_COPY || def->irType == IR_DEREF_COPY)) {
                def->dest->used = true;
            }
            if (def->src1) {
                def->src1->used = true;
            }
            if (def->src2) {
                def->src2->used = true;
            }
            if (def->irType == IR_LOAD_ARRAY_LITERAL || def->irType == IR_LOAD_ARGLIST) {
                forall(elem, def->listData)
                {
                    SymbolVersion* symbver = elem->data;
                    symbver->used = true;
                }
            }
        }
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
    forall(elem, cfg->symbolVersions)
    {
        SymbolVersion* symbver = elem->data;
        symbver->symbol->isVolatile = false;
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

    calculateArgs(cfg);
    findUnusedSymbolVersions(cfg);
    calculateIncomingNodes(cfg);
    calculateVolatility(cfg);

    // Remove basic blocks with no incoming basic blocks from the list of basic blocks
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        if (bb->incoming == 0) {
            removeBasicBlock(cfg, bb, true);
            return true;
        }
    }

    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;

        // Remove any symbols that aren't used
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->dest && !def->removed && !def->dest->used && def->dest->symbol != cfg->returnSymbol && def->dest->symbol != cfg->returnSymbol) {
                removeInstruction(bb, def);
                retval = true;
            }
        }

        // Adopt basic blocks with only one incoming block
        if (bb->next && bb->entry && !bb->hasBranch && bb->next->incoming == 1) {
            IR* end = getTail(bb->entry);

            forall(elem, bb->nextArguments) // no need for branch args since !bb->hasBranch
            {
                SymbolVersion* argument = elem->data;
                SymbolVersion* parameter = findSymbolVersionSet(bb->next->parameters, argument);
                if (parameter) {
                    if (parameter->version != argument->version) {
                        end = appendInstructionBasicBlock(bb, createIR(IR_COPY, parameter, argument, NULL));
                        parameter->def = end;
                        makeSymbolVersionUnique(parameter);
                    } else {
                        printf("symbol %s L%d arg is same version as L%d param \n", parameter->symbol->name, bb->id, bb->next->id);
                    }
                } else {
                    printf("couldn't find the parameter to match the argument\n");
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
        }

        // Remove jump chains
        if (bb->next && !bb->next->entry && !bb->next->hasBranch) {
            bb->next = bb->next->next;
            retval = true;
        }

        if (bb->branch && !bb->branch->entry && !bb->branch->hasBranch) {
            bb->branch = bb->branch->next;
            retval = true;
        }
    }

    // Rebase block graph if jump chain
    if (cfg->blockGraph && !cfg->blockGraph->entry && !cfg->blockGraph->hasBranch) {
        cfg->blockGraph = cfg->blockGraph->next;
        retval = true;
    }
    calculateArgs(cfg);

    return retval;
}

List* createCFG(SymbolNode* functionSymbol)
{
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
    cfg->symbolVersions = List_Create();
    cfg->leaves = List_Create();

    // Convert function definition AST to quadruple list
    SymbolVersion* eval = flattenAST(cfg, functionSymbol->def, NULL, NULL, NULL);
    if (eval) {
        SymbolVersion* returnVersion = unversionedSymbolVersion(cfg, cfg->returnSymbol, cfg->symbol->type->function.codomainType);
        appendInstruction(cfg, createIR(IR_COPY, returnVersion, eval, NULL));
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, NULL));
    }
    printInstructionList(cfg);

    // Convert quadruple list to CFG of basic blocks, find versions!
    cfg->blockGraph = convertToBasicBlock(cfg, cfg->head, NULL);
    removeBasicBlockInstructions(cfg);

    // Optimize
    do {
        printf("\n\n");
        clearBBVisitedFlags(cfg);
        printBlockGraph(cfg->blockGraph);
        findUnusedSymbolVersions(cfg);
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
            }
            if (ir->src2 && ir->src2->version == -1) {
                ir->src2 = findSymbolVersionSet(bb->parameters, ir->src2);
            }
        }
    }
    printf("\n\n");
    clearBBVisitedFlags(cfg);
    printBlockGraph(cfg->blockGraph);
    findUnusedSymbolVersions(cfg);

    // TODO: Possibly collect strings

    return cfg;
}