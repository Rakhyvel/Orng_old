// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef IR_H
#define IR_H
#include "../util/list.h"
#include "./position.h"
#include <stdint.h>

// Enum of all the types an IR instruction can be
typedef enum ir_type {
    // Constants and literals
	IR_LOAD_SYMBOL,
	IR_LOAD_EXTERN,
    IR_LOAD_INT,
    IR_LOAD_REAL,
    IR_LOAD_ARGLIST,
    IR_LOAD_ARRAY_LITERAL,
	IR_LOAD_DEFAULT_ARRAY,
	IR_LOAD_STRING,

    // Two parameter instructions
    IR_COPY,
    IR_BIT_OR,
    IR_BIT_XOR,
    IR_BIT_AND,
    IR_EQ,
    IR_NEQ,
    IR_GTR,
    IR_LSR,
    IR_GTE,
    IR_LTE,
    IR_LSHIFT,
    IR_RSHIFT,
    IR_ADD,
    IR_SUBTRACT,
    IR_MULTIPLY,
    IR_DIVIDE,
    IR_MODULUS,
    IR_EXPONENT,
    IR_NOT,
    IR_NEG,
    IR_BIT_NOT,
    IR_ADDR_OF,
    IR_SIZEOF,
    IR_DEREF,
    IR_DEREF_COPY,
    IR_INDEX,
    IR_INDEX_COPY,
	IR_SLICE,
    IR_DOT,
    IR_DOT_COPY,
    IR_CAST,
    IR_NEW,
    IR_NEW_ARR,
    IR_FREE,
    IR_PHONY,

    // Control flow
    IR_DECLARE_LABEL,
    IR_JUMP,
    IR_BRANCH_IF_FALSE,
    IR_CALL,

	// Errors
	IR_PUSH_STACK_TRACE,
	IR_CLEAR_STACK_TRACE,
	IR_ERROR,
} ir_type;

// Keeps track of the version of a symbol. A new version is created every time a symbol is reassigned. Used for optimization and SSA
typedef struct symbolVersion {
    struct symbolNode* symbol; // The original symbol for this symbol version
    int version; // The version of this symbol version
    struct IR* def; // The IR instruction that defines this symbol version

    struct astNode* type; // Type of symbol version. NOTE! Temporary symbol versions use same symbol, cannot use type of symbol in most cases!

    bool removed; // Whether or not this symbol version has been removed for optimization
    bool used; // Whether or not this symbol version is used in an expressions
    bool lvalue; // Whether or not this symbol version is an L value
} SymbolVersion;

// The Intermediate Representation (IR) allows for better optimization and compile-time evaluation than an AST
typedef struct IR {
    ir_type irType; // Type of this IR instruction
    int id; // ID of this IR instruction. Each IR has a unique ID throughout the program

    SymbolVersion* dest; // Where the result of this instruction will be saved
    SymbolVersion* src1;
    SymbolVersion* src2; 
    SymbolVersion* src3;

	// Data used by IRs
    union {
        int64_t intData;
        double doubleData;
        char* strData;
        struct IR* branch;
        List* listData;
        struct symbolNode* symbol;
        struct {
            struct astNode* fromType;
            struct astNode* toType;
        };
        struct {
            struct SymbolVersion* lowerBound;
            struct SymbolVersion* upperBound;
        };
    };

    struct BasicBlock* inBlock; // The basic block this IR instruction is apart of
    struct IR* next; // The next IR instruction in the IR instruction list
    struct IR* prev; // The previous IR instruction in the IR instruction list
    struct position pos; // Position this IR instruction can be found in the source text
    bool removed; // Whether or not this IR instruction has been removed for optimization
} IR;

// A basic block is a unit of control flow that consists of a list of IR instructions. Each function has a graph of basic blocks
typedef struct BasicBlock {
    struct IR* entry; // The first IR instruction in the basic block's IR instruction linked list
    bool hasBranch; // Whether or not this basic block has a conditional branch or is just a jump
    int id; // The unique ID for this basic block
    int incoming; // TODO: rename to 'numberOfPredecessors' // The number of basic blocks that jump to this block

    struct list* parameters; // List of symbol versions that are used somewhere in an IR in the BB, but are not defined anywhere in the BB up to the IR in question

    struct BasicBlock* next; // Used by jumps, and branch if condition is true
    struct list* nextArguments; // These symbols are copied to the parameters of the next BB

    struct symbolVersion* condition; // Used for conditional jumps
    struct BasicBlock* branch; // Used by branch if condition is false
    struct list* branchArguments; // These symbols are copied to the parameters of the branch BB

    bool visited; // Used for traversal of a graph of basic blocks
} BasicBlock;

// Control Flow Graphs represent an entire function in the IR
typedef struct CFG {
    IR* head; // Head of the IR instruction linked list
    IR* tail; // Tail of the IR instruction linked list

    BasicBlock* blockGraph; // The first basic block in the CFGs basic block graph
    List* basicBlocks; // flat list of all basic block

    struct symbolNode* symbol; // Symbol of function this CFG represents
    struct symbolNode* tempSymbol; // Temporary symbol (could be several different types!!!)
    struct symbolNode* returnSymbol; // Used to store the function return value in

    List* leaves; // Set of other CFG nodes loaded by this CFG (as an symbol expr in some fashion, to be called or not)

    bool visited; // For graph traversal
} CFG;

List* createCFG(struct symbolNode* functionSymbol, CFG* caller);

#endif