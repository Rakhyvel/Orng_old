#include "generator.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./ir.h"
#include "symbol.h"

const char* getReg(int i, int typeSize)
{
    switch (typeSize) {
    case 1:
        switch (i) {
        case A:
            return "al";
        case B:
            return "bl";
        case C:
            return "cl";
        case D:
            return "dl";
        case DI:
            return "dil";
        case SI:
            return "sil";
        case R8:
            return "r8b";
        case R9:
            return "r9b";
        case R10:
            return "r10b";
        case R11:
            return "r11b";
        case R12:
            return "r12b";
        case R13:
            return "r13b";
        case R14:
            return "r14b";
        case R15:
            return "r15b";
        default:
            return "<spilled into main memory>";
        }
    case 2:
        switch (i) {
        case A:
            return "ax";
        case B:
            return "bx";
        case C:
            return "cx";
        case D:
            return "dx";
        case DI:
            return "di";
        case SI:
            return "si";
        case R8:
            return "r8w";
        case R9:
            return "r9w";
        case R10:
            return "r10w";
        case R11:
            return "r11w";
        case R12:
            return "r12w";
        case R13:
            return "r13w";
        case R14:
            return "r14w";
        case R15:
            return "r15w";
        default:
            return "<spilled into main memory>";
        }
    case 4:
        switch (i) {
        case A:
            return "eax";
        case B:
            return "ebx";
        case C:
            return "ecx";
        case D:
            return "edx";
        case DI:
            return "edi";
        case SI:
            return "esi";
        case R8:
            return "r8d";
        case R9:
            return "r9d";
        case R10:
            return "r10d";
        case R11:
            return "r11d";
        case R12:
            return "r12d";
        case R13:
            return "r13d";
        case R14:
            return "r14d";
        case R15:
            return "r15d";
        case XMM0:
            return "xmm0";
        case XMM1:
            return "xmm1";
        case XMM2:
            return "xmm2";
        case XMM3:
            return "xmm3";
        case XMM4:
            return "xmm4";
        case XMM5:
            return "xmm5";
        case XMM6:
            return "xmm6";
        case XMM7:
            return "xmm7";
        default:
            return "<spilled into main memory>";
        }
    case 8:
        switch (i) {
        case A:
            return "rax";
        case B:
            return "rbx";
        case C:
            return "rcx";
        case D:
            return "rdx";
        case DI:
            return "rdi";
        case SI:
            return "rsi";
        case R8:
            return "r8";
        case R9:
            return "r9";
        case R10:
            return "r10";
        case R11:
            return "r11";
        case R12:
            return "r12";
        case R13:
            return "r13";
        case R14:
            return "r14";
        case R15:
            return "r15";
        case XMM0:
            return "xmm0";
        case XMM1:
            return "xmm1";
        case XMM2:
            return "xmm2";
        case XMM3:
            return "xmm3";
        case XMM4:
            return "xmm4";
        case XMM5:
            return "xmm5";
        case XMM6:
            return "xmm6";
        case XMM7:
            return "xmm7";
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
        //fprintf(out, "%s [rbp-%d]", getSize(symbver->typeSize), symbver->symbol->offset);
        // When is the size needed? Some instructions give errors if you include the size, even if it's right!
        fprintf(out, "[rbp-%d]", symbver->symbol->offset);
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
    if (!dest->isReg && !src->isReg) {
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

static void generateMov(FILE* out, SymbolVersion* dest, SymbolVersion* src)
{
    if (addressesAreEqual(dest, src)) {
        fprintf(out, "\t; self copy eliminated\n");
        return;
    }
    char* mnemonic;
    if (dest->isReg && dest->reg >= XMM0 && dest->typeSize == 8 || src->isReg && src->reg >= XMM0 && src->typeSize == 8) {
        mnemonic = "movsd";
    } else if (dest->isReg && dest->reg >= XMM0 && dest->typeSize == 4 || src->isReg && src->reg >= XMM0 && src->typeSize == 4) {
        mnemonic = "movss";
    } else if (dest->typeSize > src->typeSize) {
        mnemonic = "movsx";
    } else {
        mnemonic = "mov";
    }
    generateDouble(out, mnemonic, dest, src);
}

static void generateImmediate(FILE* out, char* mnemonic, SymbolVersion* dest, int data)
{
    if (dest->isReg) {
        fprintf(out, "\t%s %s, %d\n", mnemonic, getReg(dest->reg, dest->typeSize), data);
    } else {
        fprintf(out, "\t%s %s [rbp-%d], %d\n", mnemonic, getSize(dest->typeSize), dest->offset, data);
    }
}

static void generateLoadConstant(FILE* out, char* mnemonic, SymbolVersion* dest, char* constantClass, int constantLocation)
{
    fprintf(out, "\t%s %s, [$LC%s_%d]\n", mnemonic, getReg(dest->reg, dest->typeSize), constantClass, constantLocation);
}

static void generateRetMov(FILE* out, SymbolVersion* src)
{
    if (src->typeSize == 8) {
        if (src->isReg) {
            fprintf(out, "\tmov rax, %s\n", getReg(src->reg, src->typeSize));
        } else {
            fprintf(out, "\tmov rax, %s [rbp-%d]\n", getSize(src->typeSize), src->offset);
        }
    } else {
        if (src->isReg) {
            fprintf(out, "\tmovzx rax, %s\n", getReg(src->reg, src->typeSize));
        } else {
            fprintf(out, "\tmovzx rax, %s [rbp-%d]\n", getSize(src->typeSize), src->offset);
        }
    }
}

static void generateIR(FILE* out, CFG* cfg, IR* ir)
{
    switch (ir->irType) {
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
    case IR_LOAD_REAL: {
        fprintf(out, "\t; load real\n");
        int i = 0;
        if (ir->dest->typeSize == 8) {
            forall(elem, cfg->real64)
            {
                if (elem->doubleData == ir->doubleData) {
                    generateLoadConstant(out, "movsd", ir->dest, "R64", i);
                    break;
                }
                i++;
            }
        } else {
            forall(elem, cfg->real32)
            {
                if (elem->doubleData == ir->doubleData) {
                    generateLoadConstant(out, "movss", ir->dest, "R32", i);
                    break;
                }
                i++;
            }
        }
        break;
    }
    case IR_COPY: {
        fprintf(out, "\t; copy :)\n");
        generateMov(out, ir->dest, ir->src1);
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
        generateMov(out, ir->dest, ir->src1);
        if (ir->dest->isReg && ir->dest->reg >= XMM0 && ir->dest->typeSize == 8) {
            generateDouble(out, "addsd", ir->dest, ir->src2);
        } else if (ir->dest->isReg && ir->dest->reg >= XMM0 && ir->dest->typeSize == 4) {
            generateDouble(out, "addss", ir->dest, ir->src2);
        } else {
            generateDouble(out, "add", ir->dest, ir->src2);
        }
        break;
    }
    case IR_LSR: {
        fprintf(out, "\t; lt\n");
        if (ir->src1->isReg && ir->src1->reg >= XMM0 && ir->src1->typeSize == 8) {
            generateDouble(out, "comisd", ir->src1, ir->src2);
            generateSingle(out, "setc", ir->dest); // Carry flag is less-than in FPU
        } else if (ir->src1->isReg && ir->src1->reg >= XMM0 && ir->src1->typeSize == 4) {
            generateDouble(out, "comiss", ir->src1, ir->src2);
            generateSingle(out, "setc", ir->dest);
        } else {
            generateDouble(out, "cmp", ir->src1, ir->src2);
            generateSingle(out, "setl", ir->dest);
        }
        break;
    }
    case IR_CONVERT: {
        fprintf(out, "\t; convert\n");
        if (ir->fromType->astType == AST_IDENT && ir->toType->astType == AST_IDENT) {
            if ((!strcmp(ir->fromType->ident.data, "Real64") || !strcmp(ir->fromType->ident.data, "Real"))) {
                // Real64 -> ?
                if (!strcmp(ir->toType->ident.data, "Real32")) {
                    generateDouble(out, "cvtsd2ss", ir->dest, ir->src1);
                } else if (!strcmp(ir->toType->ident.data, "Int64") || !strcmp(ir->toType->ident.data, "Int")) {
                    generateDouble(out, "cvttsd2si", ir->dest, ir->src1);
                }
            } else if (!strcmp(ir->fromType->ident.data, "Real32")) {
                // Real32 -> ?
                if (!strcmp(ir->toType->ident.data, "Real64") || !strcmp(ir->toType->ident.data, "Real")) {
                    generateDouble(out, "cvtss2sd", ir->dest, ir->src1);
                } else if (!strcmp(ir->toType->ident.data, "Int64") || !strcmp(ir->toType->ident.data, "Int")) {
                    generateDouble(out, "cvttss2si", ir->dest, ir->src1);
                }
            } else if (!strcmp(ir->fromType->ident.data, "Int64") || !strcmp(ir->fromType->ident.data, "Int")) {
				// Int64 -> ?
                if (!strcmp(ir->toType->ident.data, "Real64") || !strcmp(ir->toType->ident.data, "Real")) {
                    generateDouble(out, "cvtsi2sd", ir->dest, ir->src1);
                } else if (!strcmp(ir->toType->ident.data, "Real32")) {
                    generateDouble(out, "cvttsi2ss", ir->dest, ir->src1);
                }
            }
        }
        break;
    }
    default: {
        PANIC("unknown IR");
    }
    }
}

static void generateReals(FILE* out, CFG* cfg)
{
    int i = 0;
    forall(elem, cfg->real64)
    {
        double y = elem->doubleData;
        fprintf(out, "\t$LCR64_%d\tdq %f\n", i, y);
        i++;
    }
    i = 0;
    forall(elem, cfg->real32)
    {
        double y = elem->doubleData;
        fprintf(out, "\t$LCR32_%d\tdd %f\n", i, y);
        i++;
    }
}

static void generateBasicBlock(FILE* out, CFG* cfg, BasicBlock* bb)
{
    if (bb->visited) {
        return;
    }
    bb->visited = true;
    fprintf(out, ".L%d:\n", bb->id);
    for (IR* ir = bb->entry; ir != NULL; ir = ir->next) {
        generateIR(out, cfg, ir);
    }

    if (bb->hasBranch) {
        fprintf(out, "\t; branch\n");
        generateImmediate(out, "cmp", bb->condition, 0);
        fprintf(out, "\tje .L%d\n", (int)bb->branch->id);
        if (bb->next->visited) { // will likely be generated now, chill!
        }
        fprintf(out, "\tjmp .L%d\n", (int)bb->next->id);
        generateBasicBlock(out, cfg, bb->next);
        generateBasicBlock(out, cfg, bb->branch);
    } else {
        if (!bb->next->visited) { // will likely be generated now, chill!
        }
        fprintf(out, "\tjmp .L%d\n", (int)bb->next->id);
        if (bb->next->id != 0) {
            generateBasicBlock(out, cfg, bb->next);
        }
    }
}

void Generator_Generate(FILE* out, CFG* cfg)
{
    fprintf(out, "[bits 64]\nglobal _start\n\nsection .data\n\tdummy\tdb 0\n");
    generateReals(out, cfg);
    fprintf(out, "\n\nsection .code\n_start:\n%s:\n", cfg->symbol->name);
    fprintf(out, "\tpush rbp\n\tmov rbp, rsp\n\tadd rsp, 128\n"); // Align stack to 128 byte intervals to be aligned with cache line (does that really matter??)
    generateBasicBlock(out, cfg, cfg->blockGraph);
    fprintf(out, ".L0:\n\tsub rsp, 128\n\tpop rbp\n\tret\n");
}