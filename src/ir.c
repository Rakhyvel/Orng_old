#include "./ir.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./main.h"
#include "./symbol.h"
#include "./validator.h"
#include <stdio.h>
#include <stdlib.h>

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
    case IR_LOAD:
        return "IR_LOAD";
    case IR_STORE:
        return "IR_STORE";
    case IR_CALL:
        return "IR_CALL";
    case IR_DECLARE_LABEL:
        return "IR_DECLARE_LABEL";
    case IR_JUMP:
        return "IR_JUMO";
    case IR_BRANCH_IF_FALSE:
        return "IR_BRANCH_IF_FALSE";
    case IR_RET:
        return "IR_RET";
    case IR_AND:
        return "IR_AND";
    case IR_OR:
        return "IR_OR";
    case IR_XOR:
        return "IR_XOR";
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
    case IR_ADDR_OF:
        return "IR_ADDR_OF";
    }
}

BasicBlock* createBasicBlock(CFG* cfg)
{
    static int blockID = 0;
    BasicBlock* retval = calloc(sizeof(BasicBlock), 1);
    retval->id = blockID;
    retval->parameters = List_Create();
    retval->arguments = List_Create();
    blockID++;
    List_Append(cfg->basicBlocks, retval);
    return retval;
}

IR* createIR(ir_type type, SymbolVersion* dest, IR* src1, IR* src2)
{
    IR* retval = calloc(sizeof(IR), 1);
    if (!retval) {
        gen_error("out of memory");
    }
    retval->type = type;
    retval->dest = dest;
    retval->src1 = src1;
    retval->src2 = src2;
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

SymbolVersion* unversionedSymbolVersion(CFG* cfg, SymbolNode* symbol, int typeSize)
{
    SymbolVersion* retval = calloc(sizeof(SymbolVersion), 1);
    if (typeSize == 0) {
        printf("bad!\n");
    }
    retval->symbol = symbol;
    retval->version = -1;
    retval->startpoint = -1;
    retval->endpoint = -1;
    retval->reg = -1;
    retval->typeSize = typeSize;
    List_Append(cfg->symbolVersions, retval);
    return retval;
}

void makeSymbolVersionUnique(SymbolVersion* symbver)
{
    symbver->version = symbver->symbol->versions->size;
    List_Append(symbver->symbol->versions, symbver);
}

SymbolVersion* tempSymbolVersion(CFG* cfg, int typeSize)
{
    SymbolVersion* retval = unversionedSymbolVersion(cfg, cfg->tempSymbol, typeSize);
    makeSymbolVersionUnique(retval);
    return retval;
}

SymbolVersion* findVersion(SymbolVersion* symbver, IR* ir, IR* stop)
{
    SymbolVersion* retval = symbver;
    for (; ir != NULL && ir != stop && ir->type != IR_PHI; ir = ir->next) {
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

void appendInstructionBasicBlock(BasicBlock* bb, IR* ir)
{
    IR* elem;
    for (elem = bb->entry; elem->next != NULL; elem = elem->next) { }
    elem->next = ir;
    ir->prev = elem;
}

void removeInstruction(BasicBlock* bb, IR* ir)
{
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

// Adds IR instructions to a list of ir instructions, returns instructions that assign a term
// When converting to SSA, the dest of each instruction will be set to a unique symbol version
//                         each source will be filled with a pointer to the most recent symbol version
// Just fill the dest with the current version now, temporary or not
SymbolVersion* flattenAST(CFG* cfg, ASTNode* node)
{
    switch (node->astType) {
    case AST_IDENT: { // the symbol version for the ident needs to be unversioned, and not shared with any other IR
        SymbolNode* symbol = Symbol_Find(node->ident.data, node->scope);

        SymbolVersion* var = unversionedSymbolVersion(cfg, symbol, symbol->typeSize);
        return var;
    }
    case AST_INT: {
        SymbolVersion* temp = tempSymbolVersion(cfg, getTypeSize(node->type));

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, node->_int.data);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_TRUE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, getTypeSize(node->type));

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 1);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_FALSE: {
        SymbolVersion* temp = tempSymbolVersion(cfg, getTypeSize(node->type));

        IR* ir = createIR_int(IR_LOAD_INT, temp, NULL, NULL, 0);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_BLOCK: {
        for (ListElem* elem = List_Begin(node->block.children); elem != List_End(node->block.children); elem = elem->next) {
            ASTNode* child = elem->data;
            flattenAST(cfg, child);
        }
        return NULL;
    }
    case AST_IF: {
        SymbolVersion* condition = flattenAST(cfg, node->_if.condition);

        IR* elseLabel = createIR_label();
        IR* endLabel = createIR_label();

        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, elseLabel));
        flattenAST(cfg, node->_if.bodyBlock);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, endLabel));
        appendInstruction(cfg, elseLabel);
        flattenAST(cfg, node->_if.elseBlock);
        appendInstruction(cfg, endLabel);
        return NULL;
    }
    case AST_FOR: {
        IR* beginLabel = createIR_label();
        IR* endLabel = createIR_label();

        flattenAST(cfg, node->_for.pre);
        appendInstruction(cfg, beginLabel);
        SymbolVersion* condition = flattenAST(cfg, node->_for.condition);
        appendInstruction(cfg, createIR_branch(IR_BRANCH_IF_FALSE, NULL, condition, NULL, endLabel));
        flattenAST(cfg, node->_for.bodyBlock);
        flattenAST(cfg, node->_for.post);
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, beginLabel));
        appendInstruction(cfg, endLabel);
        return NULL;
    }
    case AST_RETURN: {
        SymbolVersion* retval = flattenAST(cfg, node->unop.expr);

        appendInstruction(cfg, createIR(IR_RET, NULL, retval, NULL));
        appendInstruction(cfg, createIR_branch(IR_JUMP, NULL, NULL, NULL, NULL));
        return NULL;
    }
    case AST_DEFINE: {
        SymbolVersion* var = unversionedSymbolVersion(cfg, node->define.symbol, node->define.symbol->typeSize);
        SymbolVersion* def = flattenAST(cfg, node->define.symbol->def);

        IR* ir = createIR(IR_COPY, var, def, NULL);
        var->def = ir;
        appendInstruction(cfg, ir);
        return var;
    }
    case AST_ADD: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left);
        SymbolVersion* right = flattenAST(cfg, node->binop.right);
        SymbolVersion* temp = tempSymbolVersion(cfg, getTypeSize(node->type));

        IR* ir = createIR(IR_ADD, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_LSR: {
        SymbolVersion* left = flattenAST(cfg, node->binop.left);
        SymbolVersion* right = flattenAST(cfg, node->binop.right);
        SymbolVersion* temp = tempSymbolVersion(cfg, getTypeSize(node->type));

        IR* ir = createIR(IR_LSR, temp, left, right);
        temp->def = ir;
        appendInstruction(cfg, ir);
        return temp;
    }
    case AST_ASSIGN: {
        SymbolVersion* var = NULL;
        if (node->binop.left->astType == AST_IDENT) {
            SymbolNode* symbol = Symbol_Find(node->binop.left->ident.data, node->scope);
            var = unversionedSymbolVersion(cfg, symbol, symbol->typeSize);
        } else {
            PANIC("not an l-value\n");
        }
        SymbolVersion* right = flattenAST(cfg, node->binop.right);

        IR* ir = createIR(IR_COPY, var, right, NULL);
        var->def = ir;
        appendInstruction(cfg, ir);
        return var;
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
        return List_Get(cfg->basicBlocks, 0);
    } else if (ir->inBlock) {
        retval = ir->inBlock;
    } else {
        retval = createBasicBlock(cfg);
        retval->entry = ir;
        for (; ir != NULL; ir = ir->next, instruction++) {
            ir->inBlock = retval;
            if (ir->type == IR_DECLARE_LABEL) {
                // if you find a label declaration, fall through to the new basic block
                retval->hasBranch = false;
                retval->next = convertToBasicBlock(cfg, ir->next, retval);
                // retval.next might require versions of some symbols, provide those versions, if cannot find a version defined in this basic block, require it
                if (ir->next) {
                    ir->next->prev = NULL;
                    ir->next = NULL;
                }
                break;
            } else if (ir->type == IR_JUMP) {
                // if you find a jump, end this block and start new block
                retval->hasBranch = false;
                if (ir->branch) {
                    retval->next = convertToBasicBlock(cfg, ir->branch->next, retval);
                } else {
                    retval->next = List_Get(cfg->basicBlocks, 0);
                }
                if (ir->next) {
                    ir->next->prev = NULL;
                    ir->next = NULL;
                }
                break;
            } else if (ir->type == IR_BRANCH_IF_FALSE) {
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
            } else { // I have the power to make someones day just by a random act of kindness, wow!
                // for each def, create a new version of the symbol
                // for each src, use the most up to date in the IR. if none exists, add symbol version parameter
                if (ir->dest != NULL) {
                    ir->dest->startpoint = instruction;
                    ir->dest->endpoint = instruction;
                    if (ir->dest->symbol != cfg->tempSymbol) {
                        makeSymbolVersionUnique(ir->dest);
                    }
                }
                if (ir->src1 != NULL) {
                    ir->src1->endpoint = instruction;
                    if (ir->src1->symbol != cfg->tempSymbol) {
                        ir->src1 = findVersion(ir->src1, retval->entry, ir);
                        if (ir->src1->version == -1) {
                            putSymbolVersionSet(retval->parameters, ir->src1);
                        }
                    }
                }
                if (ir->src2 != NULL) {
                    ir->src2->endpoint = instruction;
                    if (ir->src2->symbol != cfg->tempSymbol) {
                        ir->src2 = findVersion(ir->src2, retval->entry, ir);
                        if (ir->src2->version == -1) {
                            putSymbolVersionSet(retval->parameters, ir->src2);
                        }
                    }
                }
                continue;
            }
        }
    }
    if (retval->next == NULL) {
        retval->next = List_Get(cfg->basicBlocks, 0);
    }
    return retval;
}

// Check imm. desc. params. If not defined in this block, add to params. If defined, in this block, add to arg set.
// Repeat until none found
bool addArgs(BasicBlock* bb)
{
    bool retval = false;
    if (bb->visited) {
        return false;
    }
    bb->visited = true;

    if (bb->next) {
        retval |= addArgs(bb->next);
        forall(elem, bb->next->parameters)
        {
            SymbolVersion* param = elem->data;
            SymbolVersion* symbver = findVersion(param, bb->entry, NULL);
            if (symbver->version == -1) {
                retval |= putSymbolVersionSet(bb->parameters, symbver);
            } else {
                retval |= putSymbolVersionSet(bb->arguments, symbver);
            }
        }
    }
    if (bb->branch) {
        retval |= addArgs(bb->branch);
        forall(elem, bb->branch->parameters)
        {
            SymbolVersion* param = elem->data;
            SymbolVersion* symbver = findVersion(param, bb->entry, NULL);
            if (symbver->version == -1) {
                retval |= putSymbolVersionSet(bb->parameters, symbver);
            } else {
                retval |= putSymbolVersionSet(bb->arguments, symbver);
            }
        }
    }

    bb->visited = false;
    return retval;
}

// Phi nodes keep symbols alive, so they aren't removed during optimization
void addPhiNodes(CFG* cfg)
{
    while (addArgs(cfg->blockGraph)) { } // First, find which args are even needed for this basic block

    // Go through each basic block, add phi node for each symbol
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        forall(elem2, bb->arguments)
        {
            SymbolVersion* var = elem2->data;
            IR* phi = createIR(IR_PHI, NULL, var, NULL);
            appendInstructionBasicBlock(bb, phi);
        }
    }
}

bool copyPropagation(CFG* cfg)
{
    bool retval = false;
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            switch (def->type) {
            case IR_COPY:
                if (def->src1->def && def->src1->def->type == IR_LOAD_INT) {
                    def->type = IR_LOAD_INT;
                    def->intData = def->src1->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                } else if (def->src1->def && def->src1->def->type == IR_COPY) {
                    def->src1 = def->src1->def->src1;
                    retval = true;
                } else if (def->src1->def && def->src1->def->type == IR_ADD) {
                    def->src1->def->dest = def->dest;
                    removeInstruction(def->inBlock, def);
                    retval = true;
                }
                break;
            case IR_ADD:
                if (def->src1->def && def->src2->def && def->src1->def->type == IR_LOAD_INT && def->src2->def->type == IR_LOAD_INT) {
                    def->type = IR_LOAD_INT;
                    def->intData = def->src1->def->intData + def->src2->def->intData;
                    def->src1 = NULL;
                    def->src2 = NULL;
                    retval = true;
                }
                break;
            default:
                break;
            }
        }
    }
    return retval;
}

// Removes code that has no effect
bool deadCode(CFG* cfg)
{
    bool retval = false;

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
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->type == IR_PHI) {
                SymbolVersion* symbver = findVersion(def->src1, bb->entry, NULL);
                symbver->used = true;
            }
            if (def->src1) {
                def->src1->used = true;
            }
            if (def->src2) {
                def->src2->used = true;
            }
        }
    }

    // Remove any symbols that aren't used
    forall(elem, cfg->basicBlocks)
    {
        BasicBlock* bb = elem->data;
        for (IR* def = bb->entry; def != NULL; def = def->next) {
            if (def->dest && !def->dest->removed && !def->dest->used) {
                removeInstruction(def->inBlock, def);
                def->dest->removed = true;
                retval = true;
            }
        }
    }

    return retval;
}

void allocateRegisters(CFG* cfg)
{
    // Given the lifetimes of symbols, can then allocate registers to each one
    int R = 12; // Number of registers
    List* freeRegisters = List_Create();
    for (int i = 0; i < R; i++) {
        List_Append(freeRegisters, i);
    }

    int offset = 0;

    List* active = List_Create();
    for (ListElem* elem = List_Begin(cfg->symbolVersions); elem != List_End(cfg->symbolVersions); elem = elem->next) {
        SymbolVersion* i = elem->data;

        // temporaries get put as registers, variables get put as memory offsets on the stack
        if (i->symbol == cfg->tempSymbol) {
            i->isReg = true;
            // Expire old intervals
            for (ListElem* elem2 = List_Begin(active); elem2 != List_End(active); elem2 = elem2->next) {
                SymbolVersion* j = elem2->data;
                if (i->def->inBlock == j->def->inBlock && j->endpoint >= i->startpoint) {
                    break;
                } else {
                    // j endpoint is before i start point
                    List_Remove(elem2);
                    List_Push(freeRegisters, j->reg);
                }
            }

            if (freeRegisters->size <= 0) {
                // spill at interval i into memory
                printf("spill");
            } else {
                // allocate a free register to i
                i->reg = List_Pop(freeRegisters);
                // add i to active sorted by increasing end points
                ListElem* elem2 = List_Begin(active);
                for (; elem2 != List_End(active); elem2 = elem2->next) {
                    SymbolVersion* symver = elem2->data;
                    if (symver->endpoint > i->endpoint) {
                        List_Insert(active, elem2, i);
                        break;
                    }
                }
                if (elem2 == List_End(active)) {
                    List_Append(active, i);
                }
            }
        } else if (!i->removed) {
            i->isReg = false;
            // each variable gets assigned to the same offset in memory, regardless of its version
            if (i->symbol->offset == 0) {
                // find next multiple of type size, lmao theres probably a closed form of this but idk this was the easiest way i could think
                // optimizer probably finds the closed form anyway
                while (offset % i->typeSize != 0) {
                    offset++;
                }
                offset += i->typeSize;
                i->offset = offset;
                i->symbol->offset = offset;
            } else {
                i->offset = i->symbol->offset;
            }
        }
    }
}

List* createCFG(SymbolNode* functionSymbol)
{
    CFG* cfg = calloc(sizeof(CFG), 1);
    if (!cfg) {
        gen_error("out of memory");
    }

    cfg->symbol = functionSymbol;
    cfg->tempSymbol = Symbol_Create("$", SYMBOL_VARIABLE, functionSymbol, (Position) { NULL, 0, 0, 0, 0 });
    cfg->head = NULL;
    cfg->tail = NULL;
    cfg->basicBlocks = List_Create();
    cfg->symbolVersions = List_Create();

    // Convert function definition AST to quadruple list
    flattenAST(cfg, functionSymbol->def);

    // Convert quadruple list to CFG of basic blocks, find versions!
    BasicBlock* returnBlock = createBasicBlock(cfg);
    cfg->blockGraph = convertToBasicBlock(cfg, cfg->head, NULL);
    addPhiNodes(cfg);

    // Optimize
    while (copyPropagation(cfg) | deadCode(cfg)) { }

    // Allocate registers using graph coloring algorithm
    allocateRegisters(cfg);
    //naiveAllocateRegisters(cfg);

    // Write out assembly based on CFG

    return cfg;
}