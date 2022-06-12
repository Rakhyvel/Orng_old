#ifndef IR_H
#define IR_H
#include "../util/list.h"
#include "./position.h"
#include <stdint.h>

// var = var   -- assign var
// var = temp  -- assign temp
// temp = var  -- load ident
// temp = temp -- for if/else and for loops

/*
IR	- contains psuedo instructions until types are resolved
				- like store

code_typed		- all types are known
				- code is validated to be correct
				- compile time execution is performed
				- psuedo-instructions like assign_dot, assign_index, are resolved to stores with computed offsets

Then optimizations can be made!
*/

typedef enum reg {
    A,
    B,
    C,
    D,
    DI,
    SI,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
    XMM0,
    XMM1,
    XMM2,
    XMM3,
    XMM4,
    XMM5,
    XMM6,
    XMM7,
} reg;

typedef enum ir_type {
    // Constants and literals
    IR_LOAD_IDENT,
    IR_LOAD_INT, //				integer value		Int						Loads an integer constant
    IR_LOAD_REAL, //			real value			Real					Loads a real constant
    IR_LOAD_STR, //															Loads a string literal from .data
    IR_PHONY,

    // Variables and assigning
    IR_COPY, //																Copies one symbol to another
    IR_LOAD, //					data at addr		<type at addr>			Loads the data at an address in memory with offset relative to base pointer
    IR_STORE, //				nothing				()						Stores the data of another register to an address in memory with offset relative to base pointer
    IR_CALL, //					retval of fn		<return type of fn>		Jump to function
    IR_RET, // copy src1 into rax

    IR_DECLARE_LABEL,
    IR_JUMP,
    IR_BRANCH_IF_FALSE,

    // Two parameter instructions
    IR_AND, //					a && b				Bool					Bitwise and
    IR_OR, //					a || b				Bool					Bitwise or
    IR_XOR, //					a ^ b				Int						Bitwise xor
    IR_LSHIFT, //				a << b				Int						Left shift
    IR_RSHIFT, //				a >> b				Int						Right shift
    IR_EQ, //					a == b				Bool					Equals
    IR_NEQ, //					a != b				Bool					Not equals
    IR_GTR, //					a > b				Bool					Greater than
    IR_LSR, //					a < b				Bool					Less than
    IR_GTE, //					a >= b				Bool					Greater than or equal to
    IR_LTE, //					a <= b				Bool					Less than or equal to
    IR_ADD, //					a + b				Real					Addition
    IR_ADDI,
    IR_SUBTRACT, //				a - b				Real					Subtraction
    IR_MULTIPLY, //				a * b				Real					Multiplication
    IR_DIVIDE, //				a / b				Real					Division
    IR_MODULUS, //				a % b				Int						Modulus

    // One parameter instructions
    IR_NEGATE, //				-a					Real					Negation
    IR_NOT, //					!a					Bool					Boolean not
    IR_BIT_NOT, //				~a					Int						Bitwise not
    IR_ADDR_OF, //				addr of a			&*						Address of identifier
    IR_CONVERT,
} ir_type;

/*
typedef struct symVer {
    struct symbolNode* symbol; // the actual symbol node for this symbol
    int version; // the version of this symbol
    struct IR* assign; // where in the CFG this SymbolVersion was assigned
} SymbolVersion;
*/

enum terminatorType {
    TERM_JUMP,
    TERM_BRANCH,
    TERM_RET
};

typedef struct SymbolVersion {
    struct symbolNode* symbol;
    int version;

    struct astNode* type;
    int typeSize;

    struct IR* def;
    int startpoint;
    int endpoint;

    bool removed;
    bool used;

    int isReg;
    union {
        reg reg;
        int offset;
    };
} SymbolVersion;

typedef struct IR {
    ir_type irType;

    SymbolVersion* dest;
    SymbolVersion* src1;
    SymbolVersion* src2;
    union {
        int64_t intData;
        double doubleData;
        struct IR* branch;
        struct SymbolVersion* symbver;
        struct {
            struct astNode* fromType;
            struct astNode* toType;
        };
    };

    struct BasicBlock* inBlock;
    struct IR* next;
    struct IR* prev;
} IR;

typedef struct BasicBlock {
    struct IR* entry;
    bool hasBranch;
    int id;
    struct SymbolVersion* condition; // Used for conditional jumps
    struct BasicBlock* next; // Used by jump, and branch if condition is true
    struct BasicBlock* branch; // Used by branch if condition is false
    struct List* parameters; // These symbols are needed to be phi-noded. They are defined somewhere in this BB, and are used by children BB
    struct List* arguments;
    bool visited;
} BasicBlock;

typedef struct CFG {
    // Quadruple list
    IR* head;
    IR* tail;

    // Basic block graph
    BasicBlock* blockGraph;
    List* basicBlocks; // flat list of all basic block

    List* symbolVersions;
    struct symbolNode* symbol; // Symbol table for function
    struct symbolNode* tempSymbol; // Temporary symbol (could be several different types!!!)
    List* real32; // Set of all 32 bit real numbers
    List* real64; // Set of all 64 bit real numbers
} CFG;

List* createCFG(struct symbolNode* functionSymbol);

#endif