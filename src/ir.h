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
Can do borrow checking semantics if you want
Register values are never reassigned. Memory can be reassigned, not registers.
*/

typedef enum ir_type {
    // Instruction				data in register	type of data			Description
    // Psuedo-instructions
    IR_LOAD_IDENT, //			value of ident		type of ident			Loads an identifier
    IR_LOAD_SIZEOF, //			size of type		Int						Loads the number of bytes to a type
    IR_DECLARE_VAR, //			nothing				()						Declares a symbol
    IR_DECLARE_TEMP, //			nothing				()						Declares a temporary variable
    IR_DECLARE_DEFER, //		nothing				()						Declares a defer flag
    IR_ASSIGN_VAR, //			nothing				()						Assigns the value of a register to a variable
    IR_ASSIGN_TEMP, //			nothing				()						Assigns the value of a register to a temporary variable
    IR_SET_DEFER, //			nothing				()						Sets a defer flag to true
	IR_GET_DEFER, //	
    IR_INDEX, //				value at index		type of array			Indexes an array
    IR_SLICE, //				slice				array					Creates a slice
    IR_DOT, //					value at dot		type of field			Gets the field of a struct
    IR_CAST, //					casts

    // Constants and literals
    IR_LOAD_INT, //				integer value		Int						Loads an integer constant
    IR_LOAD_REAL, //			real value			Real					Loads a real constant
    IR_LOAD_STRING, //			addr of string(?)	String					Loads a string constant. Likely stored somewhere in .data
    IR_LOAD_CHAR, //			char value			Char					Loads a char constant
    IR_LOAD_NOTHING, //			0 (for now)			()						Loads a 'nothing' constant
    IR_LOAD_TRUE, //			1					Bool					Loads a 'true' constant
    IR_LOAD_FALSE, //			0					Bool					Loads a 'false' constant
    IR_LOAD_ARRAY_LITERAL, //	array struct		[_]*					Loads an array literal
    IR_LOAD_STRUCT_LITERAL, //	struct				(_:* ...)				Loads a struct literal

    // Variables and assigning
    IR_ALLOCATE_STACK, //		addr on stack		&*						Allocates a specified number of bytes on the stack. Uninitialized
    IR_ALLOCATE_HEAP, //		addr in heap		&*						Allocates a specified number of bytes on the heap. Uninitialized
    IR_LOAD, //					data at addr		<type at addr>			Loads the data at an address in memory with offset
    IR_STORE, //				nothing				()						Stores the data of another register to an address in memory with offset

    // Branching
    IR_DECLARE_LABEL, //		nothing				()						Declares a label in the instruction list
    IR_BRANCH_IF_ZERO, //		nothing				()						Branch to label if specified register is zero
    IR_JUMP, //					nothing				()						Unconditional jump to label
    IR_CALL, //					retval of fn		<return type of fn>		Jump to function
    IR_RETURN, //				nothing				()						Return to caller
    IR_CASE, // idk, here because we will likely compile to C

    // Two parameter instructions
    IR_AND, //					a && b				Bool					Boolean and
    IR_OR, //					a || b				Bool					Boolean or
    IR_BIT_AND, //				a & b				Int						Bitwise and
    IR_BIT_XOR, //				a ^ b				Int						Bitwise xor
    IR_BIT_OR, //				a | b				Int						Bitwise or
    IR_LSHIFT, //				a << b				Int						Left shift
    IR_RSHIFT, //				a >> b				Int						Right shift
    IR_EQ, //					a == b				Bool					Equals
    IR_NEQ, //					a != b				Bool					Not equals
    IR_GTR, //					a > b				Bool					Greater than
    IR_LSR, //					a < b				Bool					Less than
    IR_GTE, //					a >= b				Bool					Greater than or equal to
    IR_LTE, //					a <= b				Bool					Less than or equal to
    IR_ADD, //					a + b				Real					Addition
    IR_SUBTRACT, //				a - b				Real					Subtraction
    IR_MULTIPLY, //				a * b				Real					Multiplication
    IR_DIVIDE, //				a / b				Real					Division
    IR_MODULUS, //				a % b				Int						Modulus

    // One parameter instructions
    IR_NEGATE, //				-a					Real					Negation
    IR_NOT, //					!a					Bool					Boolean not
    IR_BIT_NOT, //				~a					Int						Bitwise not
    IR_ADDR_OF, //				addr of a			&*						Address of identifier
} ir_type;

typedef int ir_id;

enum labelType {
    LABEL_BEGIN,
    LABEL_ELSE,
    LABEL_END,
    LABEL_CONTINUE,
    LABEL_BREAK,
    LABEL_RETURN,
    LABEL_SHORT_CIRCUIT
};

struct label {
    enum labelType labelType;
    char* labelID;
};

typedef struct IR_loadIdent {
    char* name;
    struct symbolNode* scope;
} IR_loadIdent;

typedef struct IR_loadInt {
    int64_t data;
} IR_loadInt;

typedef struct IR_loadReal {
    double data;
} IR_loadReal;

typedef struct IR_loadString {
    char* data;
} IR_loadString;

typedef struct IR_loadChar {
    char data;
} IR_loadChar;

typedef struct IR_loadNothing {
    int no_data;
} IR_loadNothing;

typedef struct IR_loadTrue {
    int no_data;
} IR_loadTrue;

typedef struct IR_loadFalse {
    int no_data;
} IR_loadFalse;

typedef struct IR_loadSizeof {
    struct astNode* type;
} IR_loadSizeof;

typedef struct IR_loadArrayLiteral {
    List* members;
} IR_loadArrayLiteral;

typedef struct IR_loadStructLiteral {
    List* args;
} IR_loadStructLiteral;

typedef struct IR_declareVar {
    struct symbolNode* symbol;
} IR_declareVar;

typedef struct IR_declareTemp {
    int no_data;
} IR_declareTemp;

typedef struct IR_declareDefer {
    int deferID;
    char* symbolName;
} IR_declareDefer;

typedef struct IR_assignVar {
    // idk what to put here yet
    int no_data;
} IR_assignVar;

typedef struct IR_assignTemp {
    ir_id dst;
    ir_id src;
} IR_assignTemp;

typedef struct IR_return {
    ir_id expr;
} IR_return;

typedef struct IR_setDefer {
    int deferID;
    char* symbolName;
} IR_setDefer;

typedef struct IR_getDefer {
    int deferID;
    char* symbolName;
} IR_getDefer;

typedef struct IR_index {
    ir_id arrExprID;
    ir_id subscriptID;
} IR_index;

typedef struct IR_slice {
    ir_id arrExprID;
    ir_id lowerBoundID;
    ir_id upperBoundID;
} IR_slice;

typedef struct IR_dot {
    struct astNode* dotExpr;
} IR_dot;

typedef struct IR_declareLabel {
    struct label label;
} IR_declareLabel;

typedef struct IR_branchIfZero {
    ir_id condition;
    struct label label;
} IR_branchIfZero;

typedef struct IR_jump {
    struct label label;
} IR_jump;

typedef struct IR_case {
    int no_data;
} IR_case;

typedef struct IR_and {
    ir_id left;
    ir_id right;
} IR_and;

typedef struct IR_or {
    ir_id left;
    ir_id right;
} IR_or;

typedef struct IR_bitAnd {
    ir_id left;
    ir_id right;
} IR_bitAnd;

typedef struct IR_bitXor {
    ir_id left;
    ir_id right;
} IR_bitXor;

typedef struct IR_bitOr {
    ir_id left;
    ir_id right;
} IR_bitOr;

typedef struct IR_lshift {
    ir_id left;
    ir_id right;
} IR_lshift;

typedef struct IR_rshift {
    ir_id left;
    ir_id right;
} IR_rshift;

typedef struct IR_eq {
    ir_id left;
    ir_id right;
} IR_eq;

typedef struct IR_neq {
    ir_id left;
    ir_id right;
} IR_neq;

typedef struct IR_gtr {
    ir_id left;
    ir_id right;
} IR_gtr;

typedef struct IR_lsr {
    ir_id left;
    ir_id right;
} IR_lsr;

typedef struct IR_gte {
    ir_id left;
    ir_id right;
} IR_gte;

typedef struct IR_lte {
    ir_id left;
    ir_id right;
} IR_lte;

typedef struct IR_add {
    ir_id left;
    ir_id right;
} IR_add;

typedef struct IR_subtract {
    ir_id left;
    ir_id right;
} IR_subtract;

typedef struct IR_multiply {
    ir_id left;
    ir_id right;
} IR_multiply;

typedef struct IR_divide {
    ir_id left;
    ir_id right;
} IR_divide;

typedef struct IR_modulus {
    ir_id left;
    ir_id right;
} IR_modulus;

typedef struct IR_negate {
    ir_id expr;
} IR_negate;

typedef struct IR_bitNot {
    ir_id expr;
} IR_bitNot;

typedef struct IR_addrOf {
    ir_id expr;
} IR_addrOf;

typedef struct IR_deref {
    ir_id expr;
} IR_deref;

typedef struct IR_cast {
    int no_data;
} IR_cast;

typedef struct IR_call {
    int no_data;
} IR_call;

typedef struct IR {
    ir_type type;
    struct position pos;
    union {
        IR_loadIdent loadIdent;
        IR_loadInt loadInt;
        IR_loadReal loadReal;
        IR_loadString loadString;
        IR_loadChar loadChar;
        IR_loadNothing loadNothing;
        IR_loadTrue loadTrue;
        IR_loadFalse loadFalse;
        IR_loadSizeof loadSizeof;
        IR_loadArrayLiteral loadArrayLiteral;
        IR_loadStructLiteral loadStructLiteral;
        IR_declareVar declaredVar;
        IR_declareTemp declareTemp;
        IR_declareDefer declareDefer;
        IR_assignVar assignVar;
        IR_assignTemp assignTemp;
        IR_return _return;
        IR_setDefer setDefer;
        IR_getDefer getDefer;
        IR_index index;
        IR_slice slice;
        IR_dot dot;
        IR_declareLabel declareLabel;
        IR_branchIfZero branchIfZero;
        IR_jump jump;
        IR_case _case;
        IR_and _and;
        IR_or _or;
        IR_bitAnd bitAnd;
        IR_bitXor bitXor;
        IR_bitOr bitOr;
        IR_lshift lshift;
        IR_rshift rshift;
        IR_eq eq;
        IR_neq neq;
        IR_gtr gtr;
        IR_lsr lsr;
        IR_gte gte;
        IR_lte lte;
        IR_add add;
        IR_subtract subtract;
        IR_multiply multiply;
        IR_divide divide;
        IR_modulus modulus;
        IR_negate negate;
        IR_bitNot bitNot;
        IR_addrOf addrOf;
        IR_deref deref;
        IR_cast cast;
        IR_call call;
    };
} IR;

// takes a list and an ast and adds an instruction representing the ast to the list, returns id of the instruction for reference
ir_id flatten(struct list* instructions, struct astNode* node);
void printInstructionList(struct list* instructions);
#endif