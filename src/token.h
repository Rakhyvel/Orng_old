// © 2021-2022 Joseph Shimel. All rights reserved.

#ifndef TOKEN_H
#define TOKEN_H

#include "./main.h"

/*
    Token operators are ordered by precedence, this makes it easy to compare
    when creating an AST for an expression */
typedef enum {
    // Literals
    TOKEN_IDENT,
    TOKEN_STR,
    TOKEN_CHAR,
    TOKEN_INT,
    TOKEN_HEX,
    TOKEN_BIN,
    TOKEN_REAL,
    TOKEN_DOC_DATA,
    // Punctuation
    TOKEN_NEWLINE,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_DSIGN,
    TOKEN_ELLIPSES,
    // Math
    TOKEN_ASSIGN,
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,
    TOKEN_STAR_ASSIGN,
    TOKEN_SLASH_ASSIGN,
    TOKEN_PERCENT_ASSIGN,
    TOKEN_CARET_ASSIGN,
    TOKEN_DAMPERSAND_ASSIGN,
    TOKEN_DBAR_ASSIGN,
    TOKEN_AMPERSAND_ASSIGN,
    TOKEN_BAR_ASSIGN,
    TOKEN_TILDE_ASSIGN,
    TOKEN_DLSR_ASSIGN,
    TOKEN_DGTR_ASSIGN,
    TOKEN_PLUS,
	TOKEN_DPLUS,
    TOKEN_MINUS,
    TOKEN_DMINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    // Bitwise
    TOKEN_TILDE,
    TOKEN_BAR,
    TOKEN_CARET,
    TOKEN_DGTR,
    TOKEN_DLSR,
    // Boolean
    TOKEN_EMARK,
    TOKEN_DBAR,
    TOKEN_DAMPERSAND,
    TOKEN_NEQ,
    TOKEN_DEQ,
    TOKEN_GTR,
    TOKEN_GTE,
    TOKEN_LSR,
    TOKEN_LTE,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_QMARK,
    TOKEN_SEMICOLON,
    // Open and closing
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LSQUARE,
    TOKEN_RSQUARE,
    TOKEN_RESTRICT,
	TOKEN_ENUM,
    // Keywords
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_CASE,
    TOKEN_NOTHING,
    TOKEN_RETURN,
    TOKEN_DEFER,
    TOKEN_NEW,
    TOKEN_FREE,
	TOKEN_SIZEOF,
	TOKEN_ORELSE,
	TOKEN_CATCH,
	TOKEN_TRY,
	TOKEN_ERRDEFER,
	TOKEN_UNREACHABLE,
    // Types
    TOKEN_ARROW,
	TOKEN_BIG_ARROW,
    TOKEN_AMPERSAND,
    // Comments
    TOKEN_DOC,
    // Meta
    TOKEN_EOF,
    _token_count // Used to tell how many tokens there are
} _TokenType; // winnt.h uses TokenType as an enum >:(

// Used to break up lexicographical meaning
struct token {
    _TokenType type;
    char data[500];
    Position pos;
};
typedef struct token Token;

const char* Token_GetString(_TokenType type);
const char* Token_GetRepr(_TokenType type);
const char* Token_GetErrorMsgRepr(_TokenType type);

#endif