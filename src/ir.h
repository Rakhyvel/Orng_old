#ifndef IR_H
#define IR_H
#include "../util/list.h"
#include "./position.h"
#include <stdint.h>

typedef enum ir_type {
    // Constants and literals
    IR_LOAD_IDENT,
    IR_LOAD_INT,
    IR_LOAD_REAL,
    IR_LOAD_STR,
	// IR_LOAD_ARGLIST ?
	// IR_LOAD_ARRAY_LITERAL ?

	// Control flow
    IR_DECLARE_LABEL,
    IR_JUMP,
    IR_BRANCH_IF_FALSE,
    IR_CALL,
    IR_RET,

    // Two parameter instructions
    IR_AND,
    IR_OR,
    IR_XOR,
    IR_LSHIFT,
    IR_RSHIFT,
    IR_EQ,
    IR_NEQ,
    IR_GTR,
    IR_LSR,
    IR_GTE,
    IR_LTE,
    IR_ADD,
    IR_ADDI,
    IR_SUBTRACT,
    IR_MULTIPLY,
    IR_DIVIDE,
    IR_MODULUS,

    // One parameter instructions
	IR_PHONY,
    IR_COPY,
    IR_NEGATE,
    IR_NOT,
    IR_BIT_NOT,
    IR_ADDR_OF,
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

typedef struct symbolVersion {
    struct symbolNode* symbol;
    struct IR* def;
    int version;

    struct astNode* type;

    bool removed;
    bool used;
} SymbolVersion;

typedef struct IR {
    ir_type irType;
    int id;

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
    struct symbolVersion* condition; // Used for conditional jumps
    struct BasicBlock* next; // Used by jump, and branch if condition is true
    struct BasicBlock* branch; // Used by branch if condition is false
    struct list* parameters; // These symbols are needed to be phi-noded. They are defined somewhere in this BB, and are used by children BB
    struct list* arguments; // These symbols are 
    bool visited;
} BasicBlock;

typedef struct CFG {
    // Quadruple list
    IR* head;
    IR* tail;

    // Basic block graph
    BasicBlock* blockGraph;
    List* basicBlocks; // flat list of all basic block

    // Symbols
    List* symbolVersions;
    struct symbolNode* symbol; // Symbol table for function
    struct symbolNode* tempSymbol; // Temporary symbol (could be several different types!!!)
    struct symbolNode* returnSymbol; // Used to store the return value in
    struct symbolVersion* expr; // The last evaluated expression of the function will be put here

	// Call graph
    List* leaves; // Set of other CFG nodes loaded by this CFG (as an symbol expr in some fashion, to be called or not)

	bool visited; // For traversal
} CFG;

List* createCFG(struct symbolNode* functionSymbol);

#endif