#pragma once
#include "../util/list.h"
#include <stdint.h>

typedef enum ir_type {
    // Constants and literals
    // These are all temporary variables that load in the constant values
    IR_INT,
    IR_REAL,
    IR_STRING,
    IR_CHAR,
    IR_NULL,
    IR_TRUE,
    IR_FALSE,
    IR_SIZEOF, // types only
    IR_ARRAY_LITERAL,
    IR_STRUCT_LITERAL,

    // Variables and assigning
    IR_DECLARE_NAMED, // declare a variable with a name
    IR_DECLARE_TEMP, // declare a temporary variable
    IR_ASSIGN_VAR, // assign var to var
    IR_ASSIGN_INDEX, // assign var to index
    IR_ASSIGN_DOT, // assign var to dot
    IR_INDEX, // evaluate index
    IR_DOT, // evaluate dot

    // Branching
    IR_DECLARE_LABEL, // declare a label with a name (possibly split to begin, end, else, return, break, continue, etc?)
    IR_JUMP,
    IR_BRANCH, // branch if condition is zero
    IR_SWITCH,
    IR_RETURN,

    // Two parameter instructions
    IR_AND,
    IR_OR,
    IR_BIT_AND,
    IR_BIT_XOR,
    IR_BIT_OR,
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
    IR_NEGATE,
    IR_BIT_NOT,
    IR_ADDR_OF,
    IR_DEREF,

    // Misc.
    IR_CAST,
    IR_CALL
} ir_type;

typedef struct codeLowered_int {
    int64_t data;
} codeLowered_int;

typedef struct codeLowered_real {
    double data;
} codeLowered_real;

typedef struct codeLowered_string {
    char* data;
} codeLowered_string;

typedef struct codeLowered_char {
    char data;
} codeLowered_char;

typedef struct codeLowered_null {
    int no_data;
} codeLowered_null;

typedef struct codeLowered_true {
    int no_data;
} codeLowered_true;

typedef struct codeLowered_false {
    int no_data;
} codeLowered_false;

typedef struct codeLowered_sizeof {
    struct astNode* type;
} codeLowered_sizeof;

typedef struct codeLowered_arrayLiteral {
    List* members;
} codeLowered_arrayLiteral;

typedef struct codeLowered_structLiteral {
    List* args;
} codeLowered_structLiteral;

typedef struct codeLowered_declareNamed {
    char* name;
} codeLowered_declareNamed;

typedef struct codeLowered_declareTemp {
    int no_data;
} codeLowered_declareTemp;

typedef struct codeLowered_assignVar {
    // idk what to put here yet
    int no_data;
} codeLowered_assignVar;

typedef struct codeLowered_assignIndex {
    int no_data;
} codeLowered_assignIndex;

typedef struct codeLowered_assignDot {
    int no_data;
} codeLowered_assignDot;

typedef struct codeLowered_index {
    int no_data;
} codeLowered_index;

typedef struct codeLowered_dot {
    int no_data;
} codeLowered_dot;

typedef struct codeLowered_declareLabel {
    int no_data;
} codeLowered_declareLabel;

typedef struct codeLowered_jump {
    int no_data;
} codeLowered_jump;

typedef struct codeLowered_branch {
    int no_data;
} codeLowered_branch;

typedef struct codeLowered_switch {
    int no_data;
} codeLowered_switch;

typedef struct codeLowered_return {
    int no_data;
} codeLowered_return;

typedef struct codeLowered_and {
    int no_data;
} codeLowered_and;

typedef struct codeLowered_or {
    int no_data;
} codeLowered_or;

typedef struct codeLowered_bitAnd {
    int no_data;
} codeLowered_bitAnd;

typedef struct codeLowered_bitXor {
    int no_data;
} codeLowered_bitXor;

typedef struct codeLowered_bitOr {
    int no_data;
} codeLowered_bitOr;

typedef struct codeLowered_lshift {
    int no_data;
} codeLowered_lshift;

typedef struct codeLowered_rshift {
    int no_data;
} codeLowered_rshift;

typedef struct codeLowered_eq {
    int no_data;
} codeLowered_eq;

typedef struct codeLowered_neq {
    int no_data;
} codeLowered_neq;

typedef struct codeLowered_gtr {
    int no_data;
} codeLowered_gtr;

typedef struct codeLowered_lsr {
    int no_data;
} codeLowered_lsr;

typedef struct codeLowered_gte {
    int no_data;
} codeLowered_gte;

typedef struct codeLowered_lte {
    int no_data;
} codeLowered_lte;

typedef struct codeLowered_add {
    int no_data;
} codeLowered_add;

typedef struct codeLowered_subtract {
    int no_data;
} codeLowered_subtract;

typedef struct codeLowered_multiply {
    int no_data;
} codeLowered_multiply;

typedef struct codeLowered_divide {
    int no_data;
} codeLowered_divide;

typedef struct codeLowered_modulus {
    int no_data;
} codeLowered_modulus;

typedef struct codeLowered_negate {
    int no_data;
} codeLowered_negate;

typedef struct codeLowered_bitNot {
    int no_data;
} codeLowered_bitNot;

typedef struct codeLowered_addrOf {
    int no_data;
} codeLowered_addrOf;

typedef struct codeLowered_cast {
    int no_data;
} codeLowered_cast;

typedef struct codeLowered_call {
    int no_data;
} codeLowered_call;

typedef struct code_lowered {
    ir_type type;
    union {
        codeLowered_int _int;
        codeLowered_real real;
        codeLowered_string string;
        codeLowered_char _char;
        codeLowered_null null;
        codeLowered_true _true;
        codeLowered_false _false;
        codeLowered_sizeof _sizeof;
        codeLowered_arrayLiteral arrayLiteral;
        codeLowered_structLiteral structLiteral;
        codeLowered_declareNamed declaredNamed;
        codeLowered_declareTemp declareTemp;
        codeLowered_assignVar assignVar;
        codeLowered_assignIndex assignIndex;
        codeLowered_assignDot assignDot;
        codeLowered_index index;
        codeLowered_dot dot;
        codeLowered_declareLabel declareLabel;
        codeLowered_jump jump;
        codeLowered_branch branch;
        codeLowered_switch _switch;
        codeLowered_return _return;
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
        codeLowered_cast cast;
        codeLowered_call call;
    };
} code_lowered;