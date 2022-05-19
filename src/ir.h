#include "../util/list.h"
#include "./position.h"
#include <stdint.h>

// var = var   -- assign var
// var = temp  -- assign temp
// temp = var  -- load ident
// temp = temp -- for if/else and for loops

/*
code_lowered	- contains psuedo instructions until types are resolved
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

typedef struct codeLowered_loadIdent {
    char* name;
    struct symbolNode* scope;
} codeLowered_loadIdent;

typedef struct codeLowered_loadInt {
    int64_t data;
} codeLowered_loadInt;

typedef struct codeLowered_loadReal {
    double data;
} codeLowered_loadReal;

typedef struct codeLowered_loadString {
    char* data;
} codeLowered_loadString;

typedef struct codeLowered_loadChar {
    char data;
} codeLowered_loadChar;

typedef struct codeLowered_loadNothing {
    int no_data;
} codeLowered_loadNothing;

typedef struct codeLowered_loadTrue {
    int no_data;
} codeLowered_loadTrue;

typedef struct codeLowered_loadFalse {
    int no_data;
} codeLowered_loadFalse;

typedef struct codeLowered_loadSizeof {
    struct astNode* type;
} codeLowered_loadSizeof;

typedef struct codeLowered_loadArrayLiteral {
    List* members;
} codeLowered_loadArrayLiteral;

typedef struct codeLowered_loadStructLiteral {
    List* args;
} codeLowered_loadStructLiteral;

typedef struct codeLowered_declareVar {
    struct symbolNode* symbol;
} codeLowered_declareVar;

typedef struct codeLowered_declareTemp {
    int no_data;
} codeLowered_declareTemp;

typedef struct codeLowered_declareDefer {
    int deferID;
    char* symbolName;
} codeLowered_declareDefer;

typedef struct codeLowered_assignVar {
    // idk what to put here yet
    int no_data;
} codeLowered_assignVar;

typedef struct codeLowered_assignTemp {
    ir_id dst;
    ir_id src;
} codeLowered_assignTemp;

typedef struct codeLowered_return {
    ir_id expr;
} codeLowered_return;

typedef struct codeLowered_setDefer {
    int deferID;
    char* symbolName;
} codeLowered_setDefer;

typedef struct codeLowered_index {
    ir_id arrExprID;
    ir_id subscriptID;
} codeLowered_index;

typedef struct codeLowered_slice {
    ir_id arrExprID;
    ir_id lowerBoundID;
    ir_id upperBoundID;
} codeLowered_slice;

typedef struct codeLowered_dot {
    ir_id leftID;
    char* identifier;
} codeLowered_dot;

typedef struct codeLowered_declareLabel {
    struct label label;
} codeLowered_declareLabel;

typedef struct codeLowered_branchIfZero {
    ir_id condition;
    struct label label;
} codeLowered_branchIfZero;

typedef struct codeLowered_jump {
    struct label label;
} codeLowered_jump;

typedef struct codeLowered_case {
    int no_data;
} codeLowered_case;

typedef struct codeLowered_and {
    ir_id left;
    ir_id right;
} codeLowered_and;

typedef struct codeLowered_or {
    ir_id left;
    ir_id right;
} codeLowered_or;

typedef struct codeLowered_bitAnd {
    ir_id left;
    ir_id right;
} codeLowered_bitAnd;

typedef struct codeLowered_bitXor {
    ir_id left;
    ir_id right;
} codeLowered_bitXor;

typedef struct codeLowered_bitOr {
    ir_id left;
    ir_id right;
} codeLowered_bitOr;

typedef struct codeLowered_lshift {
    ir_id left;
    ir_id right;
} codeLowered_lshift;

typedef struct codeLowered_rshift {
    ir_id left;
    ir_id right;
} codeLowered_rshift;

typedef struct codeLowered_eq {
    ir_id left;
    ir_id right;
} codeLowered_eq;

typedef struct codeLowered_neq {
    ir_id left;
    ir_id right;
} codeLowered_neq;

typedef struct codeLowered_gtr {
    ir_id left;
    ir_id right;
} codeLowered_gtr;

typedef struct codeLowered_lsr {
    ir_id left;
    ir_id right;
} codeLowered_lsr;

typedef struct codeLowered_gte {
    ir_id left;
    ir_id right;
} codeLowered_gte;

typedef struct codeLowered_lte {
    ir_id left;
    ir_id right;
} codeLowered_lte;

typedef struct codeLowered_add {
    ir_id left;
    ir_id right;
} codeLowered_add;

typedef struct codeLowered_subtract {
    ir_id left;
    ir_id right;
} codeLowered_subtract;

typedef struct codeLowered_multiply {
    ir_id left;
    ir_id right;
} codeLowered_multiply;

typedef struct codeLowered_divide {
    ir_id left;
    ir_id right;
} codeLowered_divide;

typedef struct codeLowered_modulus {
    ir_id left;
    ir_id right;
} codeLowered_modulus;

typedef struct codeLowered_negate {
    ir_id expr;
} codeLowered_negate;

typedef struct codeLowered_bitNot {
    ir_id expr;
} codeLowered_bitNot;

typedef struct codeLowered_addrOf {
    ir_id expr;
} codeLowered_addrOf;

typedef struct codeLowered_deref {
    ir_id expr;
} codeLowered_deref;

typedef struct codeLowered_cast {
    int no_data;
} codeLowered_cast;

typedef struct codeLowered_call {
    int no_data;
} codeLowered_call;

typedef struct code_lowered {
    ir_type type;
    struct position pos;
    union {
        codeLowered_loadIdent loadIdent;
        codeLowered_loadInt loadInt;
        codeLowered_loadReal loadReal;
        codeLowered_loadString loadString;
        codeLowered_loadChar loadChar;
        codeLowered_loadNothing loadNothing;
        codeLowered_loadTrue loadTrue;
        codeLowered_loadFalse loadFalse;
        codeLowered_loadSizeof loadSizeof;
        codeLowered_loadArrayLiteral loadArrayLiteral;
        codeLowered_loadStructLiteral loadStructLiteral;
        codeLowered_declareVar declaredVar;
        codeLowered_declareTemp declareTemp;
        codeLowered_declareDefer declareDefer;
        codeLowered_assignVar assignVar;
        codeLowered_assignTemp assignTemp;
        codeLowered_return _return;
        codeLowered_setDefer setDefer;
        codeLowered_index index;
        codeLowered_slice slice;
        codeLowered_dot dot;
        codeLowered_declareLabel declareLabel;
        codeLowered_branchIfZero branchIfZero;
        codeLowered_jump jump;
        codeLowered_case _case;
        codeLowered_and _and;
        codeLowered_or _or;
        codeLowered_bitAnd bitAnd;
        codeLowered_bitXor bitXor;
        codeLowered_bitOr bitOr;
        codeLowered_lshift lshift;
        codeLowered_rshift rshift;
        codeLowered_eq eq;
        codeLowered_neq neq;
        codeLowered_gtr gtr;
        codeLowered_lsr lsr;
        codeLowered_gte gte;
        codeLowered_lte lte;
        codeLowered_add add;
        codeLowered_subtract subtract;
        codeLowered_multiply multiply;
        codeLowered_divide divide;
        codeLowered_modulus modulus;
        codeLowered_negate negate;
        codeLowered_bitNot bitNot;
        codeLowered_addrOf addrOf;
        codeLowered_deref deref;
        codeLowered_cast cast;
        codeLowered_call call;
    };
} code_lowered;

// takes a list and an ast and adds an instruction representing the ast to the list, returns id of the instruction for reference
ir_id flatten(struct list* instructions, struct astNode* node);
void printInstructionList(struct list* instructions);