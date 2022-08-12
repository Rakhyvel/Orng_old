#ifndef IR_H
#define IR_H
#include "../util/list.h"
#include "./position.h"
#include <stdint.h>

typedef enum ir_type {
    // Constants and literals
	IR_LOAD_SYMBOL,
    IR_LOAD_INT,
    IR_LOAD_REAL,
    IR_LOAD_ARGLIST,
    IR_LOAD_ARRAY_LITERAL,
	IR_LOAD_DEFAULT_ARRAY,
	IR_LOAD_STRING,

    // Control flow
    IR_DECLARE_LABEL,
    IR_JUMP,
    IR_BRANCH_IF_FALSE,
    IR_CALL,

    // Two parameter instructions
    IR_INDEX,
    IR_INDEX_COPY,
	IR_SLICE,
    IR_DOT,
    IR_DOT_COPY,
    IR_BIT_AND,
    IR_BIT_OR,
    IR_BIT_XOR,
    IR_LSHIFT,
    IR_RSHIFT,
    IR_EQ,
    IR_NEQ,
    IR_GTR,
    IR_LSR,
    IR_GTE,
    IR_LTE,
    IR_ADD,
    IR_SUBTRACT,
    IR_MULTIPLY,
    IR_DIVIDE,
    IR_MODULUS,

    // One parameter instructions
    IR_PHONY,
    IR_COPY,
    IR_NOT,
    IR_NEGATE,
    IR_BIT_NOT,
    IR_ADDR_OF,
    IR_DEREF,
	IR_DEREF_COPY,

	// Type IRs
    IR_CONVERT,
	IR_SIZEOF,
	IR_NEW, 
	IR_NEW_ARR,
	IR_FREE,

	IR_PUSH_STACK_TRACE,
	IR_CLEAR_STACK_TRACE
} ir_type;

typedef struct symbolVersion {
    struct symbolNode* symbol;
    struct IR* def;
    int version;

    struct astNode* type;

    bool removed;
    bool used;
    bool lvalue;
} SymbolVersion;

typedef struct IR {
    ir_type irType;
    int id;

    SymbolVersion* dest;
    SymbolVersion* src1;
    SymbolVersion* src2;
    SymbolVersion* src3;
    union {
        int64_t intData;
        double doubleData;
        char* strData;
        struct IR* branch;
        struct SymbolVersion* symbver;
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

    struct BasicBlock* inBlock;
    struct IR* next;
    struct IR* prev;
    struct position pos;
    bool removed;
} IR;

typedef struct BasicBlock {
    struct IR* entry;
    bool hasBranch;
    int id;
    int incoming;
    struct list* parameters; // List of symbol versions that are used somewhere in an IR in the BB, but are not defined anywhere in the BB up to the IR in question
    struct BasicBlock* next; // Used by jump, and branch if condition is true
    struct list* nextArguments; // These symbols are copied to the parameters of the next BB
    struct BasicBlock* branch; // Used by branch if condition is false
    struct symbolVersion* condition; // Used for conditional jumps
    struct list* branchArguments; // These symbols are copied to the parameters of the branch BB
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
    //List* symbolVersions;
    struct symbolNode* symbol; // Symbol table for function
    struct symbolNode* tempSymbol; // Temporary symbol (could be several different types!!!)
    struct symbolNode* returnSymbol; // Used to store the return value in
    int phonies;

    // Call graph
    List* leaves; // Set of other CFG nodes loaded by this CFG (as an symbol expr in some fashion, to be called or not)

    bool visited; // For traversal
} CFG;

List* createCFG(struct symbolNode* functionSymbol, CFG* caller);
void clearBBVisitedFlags(CFG* cfg);

#endif