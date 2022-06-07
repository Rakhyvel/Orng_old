#include "generator.h"
#include "../util/debug.h"
#include "./ir.h"
#include "symbol.h"

const char* getReg(int i, int typeSize)
{
    switch (typeSize) {
    case 1:
        switch (i) {
        case 0:
            return "cl";
        case 1:
            return "dl";
        case 2:
            return "dil";
        case 3:
            return "sil";
        case 4:
            return "r8b";
        case 5:
            return "r9b";
        case 6:
            return "r10b";
        case 7:
            return "r11b";
        case 8:
            return "r12b";
        case 9:
            return "r13b";
        case 10:
            return "r14b";
        case 11:
            return "r15b";
        default:
            return "<spilled into main memory>";
        }
    case 2:
        switch (i) {
        case 0:
            return "cx";
        case 1:
            return "dx";
        case 2:
            return "di";
        case 3:
            return "si";
        case 4:
            return "r8w";
        case 5:
            return "r9w";
        case 6:
            return "r10w";
        case 7:
            return "r11w";
        case 8:
            return "r12w";
        case 9:
            return "r13w";
        case 10:
            return "r14w";
        case 11:
            return "r15w";
        default:
            return "<spilled into main memory>";
        }
    case 4:
        switch (i) {
        case 0:
            return "ecx";
        case 1:
            return "edx";
        case 2:
            return "edi";
        case 3:
            return "esi";
        case 4:
            return "r8d";
        case 5:
            return "r9d";
        case 6:
            return "r10d";
        case 7:
            return "r11d";
        case 8:
            return "r12d";
        case 9:
            return "r13d";
        case 10:
            return "r14d";
        case 11:
            return "r15d";
        default:
            return "<spilled into main memory>";
        }
    case 8:
        switch (i) {
        case 0:
            return "rcx";
        case 1:
            return "rdx";
        case 2:
            return "rdi";
        case 3:
            return "rsi";
        case 4:
            return "r8";
        case 5:
            return "r9";
        case 6:
            return "r10";
        case 7:
            return "r11";
        case 8:
            return "r12";
        case 9:
            return "r13";
        case 10:
            return "r14";
        case 11:
            return "r15";
        default:
            return "<spilled into main memory>";
        }
    default:
        PANIC("bad size!\n");
    }
}

static char* getSize(int typeSize)
{
    switch (typeSize) {
    case 1:
        return "BYTE";
    case 2:
        return "WORD";
    case 4:
        return "DWORD";
    case 8:
        return "QWORD";
    default:
        PANIC("");
    }
}

static void generateAddress(FILE* out, SymbolVersion* symbver)
{
    if (symbver->isReg) {
        fprintf(out, "%s", getReg(symbver->reg, symbver->typeSize));
    } else {
        fprintf(out, "%s [rbp-%d]", getSize(symbver->typeSize), symbver->symbol->offset);
    }
}

static bool addressesAreEqual(SymbolVersion* dest, SymbolVersion* src)
{
    if (dest->isReg != src->isReg) {
        return false;
    } else if (dest->isReg && src->isReg) {
        return dest->reg == src->reg;
    } else {
        return dest->offset == src->offset;
    }
}

static void generateSingle(FILE* out, char* mnemonic, SymbolVersion* dest)
{
    fprintf(out, "\t%s ", mnemonic);
    generateAddress(out, dest);
    fprintf(out, "\n");
}

static void generateDouble(FILE* out, char* mnemonic, SymbolVersion* dest, SymbolVersion* src)
{
    if (!strcmp(mnemonic, "mov") && addressesAreEqual(dest, src)) {
        return;
    } else if (!dest->isReg && !src->isReg) {
        fprintf(out, "\tmov rbx, [rbp-%d]\n", src->offset);
        fprintf(out, "\t%s [rbp-%d], rbx\n", mnemonic, dest->offset);
    } else {
        fprintf(out, "\t%s ", mnemonic);
        generateAddress(out, dest);
        fprintf(out, ", ");
        generateAddress(out, src);
        fprintf(out, "\n");
    }
}

static void generateImmediate(FILE* out, char* mnemonic, SymbolVersion* dest, int data)
{
    if (dest->isReg) {
        fprintf(out, "\t%s %s, %d\n", mnemonic, getReg(dest->reg, dest->typeSize), data);
    } else {
        fprintf(out, "\t%s %s [rbp-%d], %d\n", mnemonic, getSize(dest->typeSize), dest->offset, data);
    }
}

static void generateRetMov(FILE* out, SymbolVersion* src)
{
    if (src->isReg) {
        fprintf(out, "\tmov rax, %s\n", getReg(src->reg, src->typeSize));
    } else {
        fprintf(out, "\tmov rax, %s [rbp-%d]\n", getSize(src->typeSize), src->offset);
    }
}

static void generateIR(FILE* out, IR* ir)
{
    switch (ir->type) {
    case IR_LOAD_IDENT: {
        fprintf(out, "\t; load ident\n");
        generateDouble(out, "mov", ir->dest, ir->symbver);
        break;
    }
    case IR_LOAD_INT: {
        fprintf(out, "\t; load int\n");
        generateImmediate(out, "mov", ir->dest, (int)ir->intData);
        break;
    }
    case IR_COPY: {
        fprintf(out, "\t; copy\n");
        generateDouble(out, "mov", ir->dest, ir->src1);
        break;
    }
    case IR_DECLARE_LABEL: // Just don't do anything... these instructions are generated at the end of a basic block
    case IR_JUMP:
    case IR_BRANCH_IF_FALSE: {
        break;
    }
    case IR_RET: {
        fprintf(out, "\t; return\n");
        generateRetMov(out, ir->src1);
        break;
    }
    case IR_ADD: {
        fprintf(out, "\t; add\n");
        generateDouble(out, "mov", ir->dest, ir->src1);
        generateDouble(out, "add", ir->dest, ir->src2);
        break;
    }
    case IR_LSR: {
        fprintf(out, "\t; lt\n");
        generateDouble(out, "cmp", ir->src1, ir->src2);
        generateSingle(out, "setl", ir->dest);
        break;
    }
    case IR_PHI: {
        fprintf(out, ";%d", ir->src1->version);
        generateSingle(out, "phi", ir->src1);
        break;
    }
    default: {
        PANIC("unknown IR");
    }
    }
}

static void generateBasicBlock(FILE* out, BasicBlock* bb)
{
    if (bb->visited) {
        return;
    }
    bb->visited = true;
    fprintf(out, ".L%d:\n", bb->id);
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        generateIR(out, ir);
    }

    if (bb->hasBranch) {
        generateImmediate(out, "cmp", bb->condition, 0);
        fprintf(out, "\tje .L%d\n", (int)bb->branch->id);
        if (bb->next->visited) { // will likely be generated now, chill!
        }
        fprintf(out, "\tjmp .L%d\n", (int)bb->next->id);
        generateBasicBlock(out, bb->next);
        generateBasicBlock(out, bb->branch);
    } else {
        if (!bb->next->visited) { // will likely be generated now, chill!
        }
        fprintf(out, "\tjmp .L%d\n", (int)bb->next->id);
        if (bb->next->id != 0) {
            generateBasicBlock(out, bb->next);
        }
    }
}

void Generator_Generate(FILE* out, CFG* cfg)
{
    fprintf(out, "[bits 64]\nglobal _start\n\nsection .data\ndummy\tdb 0\n\nsection .bss\n\nsection .code\n_start:\n%s:\n", cfg->symbol->name);
    fprintf(out, "\tpush rbp\n\tmov rbp, rsp\n\tadd rsp, 128\n");
    generateBasicBlock(out, cfg->blockGraph);
    fprintf(out, ".L0:\n\tsub rsp, 128\n\tpop rbp\n\tret\n");
}