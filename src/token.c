// © 2021-2022 Joseph Shimel. All rights reserved.
// Functionality for working with tokens

#include "token.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "../util/map.h"

// Returns the name of a token type
const char* Token_GetString(_TokenType type)
{
    switch (type) {
    case TOKEN_IDENT:
        return "TOKEN_IDENT";
    case TOKEN_STR:
        return "TOKEN_STR";
    case TOKEN_CHAR:
        return "TOKEN_CHAR";
    case TOKEN_INT:
        return "TOKEN_INT";
    case TOKEN_HEX:
        return "TOKEN_HEX";
    case TOKEN_BIN:
        return "TOKEN_BIN";
    case TOKEN_NEWLINE:
        return "TOKEN_NEWLINE";
    case TOKEN_COLON:
        return "TOKEN_COLON";
    case TOKEN_COMMA:
        return "TOKEN_COMMA";
    case TOKEN_DOT:
        return "TOKEN_DOT";
    case TOKEN_DSIGN:
        return "TOKEN_DSIGN";
    case TOKEN_ELLIPSES:
        return "TOKEN_ELLIPSES";
    case TOKEN_ASSIGN:
        return "TOKEN_ASSIGN";
    case TOKEN_PLUS_ASSIGN:
        return "TOKEN_PLUS_ASSIGN";
    case TOKEN_MINUS_ASSIGN:
        return "TOKEN_MINUS_ASSIGN";
    case TOKEN_STAR_ASSIGN:
        return "TOKEN_STAR_ASSIGN";
    case TOKEN_SLASH_ASSIGN:
        return "TOKEN_SLASH_ASSIGN";
    case TOKEN_PERCENT_ASSIGN:
        return "TOKEN_PERCENT_ASSIGN";
    case TOKEN_AMPERSAND_ASSIGN:
        return "TOKEN_AMPERSAND_ASSIGN";
    case TOKEN_BAR_ASSIGN:
        return "TOKEN_BAR_ASSIGN";
    case TOKEN_CARET_ASSIGN:
        return "TOKEN_CARET_ASSIGN";
    case TOKEN_DLSR_ASSIGN:
        return "TOKEN_DLSR_ASSIGN";
    case TOKEN_DGTR_ASSIGN:
        return "TOKEN_DGTR_ASSIGN";
    case TOKEN_PLUS:
        return "TOKEN_PLUS";
    case TOKEN_DPLUS:
        return "TOKEN_DPLUS";
    case TOKEN_MINUS:
        return "TOKEN_MINUS";
    case TOKEN_STAR:
        return "TOKEN_STAR";
    case TOKEN_SLASH:
        return "TOKEN_SLASH";
    case TOKEN_PERCENT:
        return "TOKEN_PERCENT";
    case TOKEN_TILDE:
        return "TOKEN_TILDE";
    case TOKEN_BAR:
        return "TOKEN_BAR";
    case TOKEN_CARET:
        return "TOKEN_CARET";
    case TOKEN_DGTR:
        return "TOKEN_DGTR";
    case TOKEN_DLSR:
        return "TOKEN_DLSR";
    case TOKEN_EMARK:
        return "TOKEN_EMARK";
    case TOKEN_DBAR:
        return "TOKEN_DBAR";
    case TOKEN_DAMPERSAND:
        return "TOKEN_DAMPERSAND";
    case TOKEN_NEQ:
        return "TOKEN_NEQ";
    case TOKEN_DEQ:
        return "TOKEN_DEQ";
    case TOKEN_GTR:
        return "TOKEN_GTR";
    case TOKEN_GTE:
        return "TOKEN_GTE";
    case TOKEN_LSR:
        return "TOKEN_LSR";
    case TOKEN_LTE:
        return "TOKEN_LTE";
    case TOKEN_TRUE:
        return "TOKEN_TRUE";
    case TOKEN_FALSE:
        return "TOKEN_FALSE";
    case TOKEN_LPAREN:
        return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
        return "TOKEN_RPAREN";
    case TOKEN_QMARK:
        return "TOKEN_QMARK";
    case TOKEN_SEMICOLON:
        return "TOKEN_SEMICOLON";
    case TOKEN_LBRACE:
        return "TOKEN_LBRACE";
    case TOKEN_RBRACE:
        return "TOKEN_RBRACE";
    case TOKEN_LSQUARE:
        return "TOKEN_LSQUARE";
    case TOKEN_RSQUARE:
        return "TOKEN_RSQUARE";
    case TOKEN_RESTRICT:
        return "TOKEN_RESTRICT";
    case TOKEN_IF:
        return "TOKEN_IF";
    case TOKEN_ELSE:
        return "TOKEN_ELSE";
    case TOKEN_FOR:
        return "TOKEN_FOR";
    case TOKEN_BREAK:
        return "TOKEN_BREAK";
    case TOKEN_CONTINUE:
        return "TOKEN_CONTINUE";
    case TOKEN_CASE:
        return "TOKEN_CASE";
    case TOKEN_NOTHING:
        return "TOKEN_NOTHING";
    case TOKEN_RETURN:
        return "TOKEN_RETURN";
    case TOKEN_NEW:
        return "TOKEN_NEW";
    case TOKEN_FREE:
        return "TOKEN_FREE";
    case TOKEN_DEFER:
        return "TOKEN_DEFER";
    case TOKEN_ERRDEFER:
        return "TOKEN_ERRDEFER";
    case TOKEN_UNREACHABLE:
        return "TOKEN_UNREACHABLE";
    case TOKEN_ARROW:
        return "TOKEN_ARROW";
    case TOKEN_BIG_ARROW:
        return "TOKEN_BIG_ARROW";
    case TOKEN_AMPERSAND:
        return "TOKEN_AMPERSAND";
    case TOKEN_DOC:
        return "TOKEN_DOC";
    case TOKEN_EOF:
        return "TOKEN_EOF";
    case _token_count:
        PANIC("Invalid token type");
        return "";
    }
    PANIC("Invalid token type");
    return "";
}

// Returns how a token is represented textually in Orng
const char* Token_GetRepr(_TokenType type)
{
    switch (type) {
    case TOKEN_NEWLINE:
        return "\n";
    case TOKEN_COLON:
        return ":";
    case TOKEN_COMMA:
        return ",";
    case TOKEN_DOT:
        return ".";
    case TOKEN_DDOT:
        return "..";
    case TOKEN_DSIGN:
        return "$";
    case TOKEN_ELLIPSES:
        return "...";
    case TOKEN_ASSIGN:
        return "=";
    case TOKEN_PLUS_ASSIGN:
        return "+=";
    case TOKEN_MINUS_ASSIGN:
        return "-=";
    case TOKEN_STAR_ASSIGN:
        return "*=";
    case TOKEN_SLASH_ASSIGN:
        return "/=";
    case TOKEN_PERCENT_ASSIGN:
        return "%=";
    case TOKEN_CARET_ASSIGN:
        return "^=";
    case TOKEN_DAMPERSAND_ASSIGN:
        return "&&=";
    case TOKEN_DBAR_ASSIGN:
        return "||=";
    case TOKEN_AMPERSAND_ASSIGN:
        return "&=";
    case TOKEN_BAR_ASSIGN:
        return "|=";
    case TOKEN_TILDE_ASSIGN:
        return  "~=";
    case TOKEN_DLSR_ASSIGN:
        return "<<=";
    case TOKEN_DGTR_ASSIGN:
        return ">>=";
    case TOKEN_PLUS:
        return "+";
    case TOKEN_DPLUS:
        return "++";
    case TOKEN_MINUS:
        return "-";
    case TOKEN_DMINUS:
        return "--";
    case TOKEN_STAR:
        return "*";
    case TOKEN_SLASH:
        return "/";
    case TOKEN_PERCENT:
        return "%";
    case TOKEN_TILDE:
        return "~";
    case TOKEN_BAR:
        return "|";
    case TOKEN_CARET:
        return "^";
    case TOKEN_DGTR:
        return ">>";
    case TOKEN_DLSR:
        return "<<";
    case TOKEN_EMARK:
        return "!";
    case TOKEN_DBAR:
        return "||";
    case TOKEN_DAMPERSAND:
        return "&&";
    case TOKEN_NEQ:
        return "!=";
    case TOKEN_DEQ:
        return "==";
    case TOKEN_GTR:
        return ">";
    case TOKEN_GTE:
        return ">=";
    case TOKEN_LSR:
        return "<";
    case TOKEN_LTE:
        return "<=";
    case TOKEN_TRUE:
        return "true";
    case TOKEN_FALSE:
        return "false";
    case TOKEN_QMARK:
        return "?";
    case TOKEN_SEMICOLON:
        return ";";
    case TOKEN_LPAREN:
        return "(";
    case TOKEN_RPAREN:
        return ")";
    case TOKEN_LBRACE:
        return "{";
    case TOKEN_RBRACE:
        return "}";
    case TOKEN_LSQUARE:
        return "[";
    case TOKEN_RSQUARE:
        return "]";
    case TOKEN_RESTRICT:
        return "-[";
    case TOKEN_ENUM:
        return "(|";
    case TOKEN_IF:
        return "if";
    case TOKEN_ELSE:
        return "else";
    case TOKEN_FOR:
        return "for";
    case TOKEN_BREAK:
        return "break";
    case TOKEN_CONTINUE:
        return "continue";
    case TOKEN_CASE:
        return "case";
    case TOKEN_NOTHING:
        return "nothing";
    case TOKEN_RETURN:
        return "return";
    case TOKEN_NEW:
        return "new";
    case TOKEN_FREE:
        return "free";
    case TOKEN_DEFER:
        return "defer";
    case TOKEN_SIZEOF:
        return "sizeof";
    case TOKEN_ORELSE:
        return "orelse";
    case TOKEN_TRY:
        return "try";
    case TOKEN_ERRDEFER:
        return "errdefer";
    case TOKEN_CATCH:
        return "catch";
    case TOKEN_UNREACHABLE:
        return "unreachable";
    case TOKEN_ARROW:
        return "->";
    case TOKEN_BIG_ARROW:
        return "=>";
    case TOKEN_AMPERSAND:
        return "&";
    case TOKEN_DOC:
        return "#==";
    case TOKEN_EOF:
        return "123eof";
    default:
        PANIC("Unknown token type %d\n", type);
        return NULL;
    }
}

// Returns how a token is represented in an Orng syntax error message
const char* Token_GetErrorMsgRepr(_TokenType type)
{
    switch (type) {
    case TOKEN_IDENT:
        return "identifier";
    case TOKEN_STR:
        return "string literal";
    case TOKEN_CHAR:
        return "character literal";
    case TOKEN_INT:
        return "integer literal";
    case TOKEN_HEX:
        return "hexadecimal literal";
    case TOKEN_BIN:
        return "binary literal";
    case TOKEN_NEWLINE:
        return "end of line";
    case TOKEN_EOF:
        return "end of file";
    default:
        return Token_GetRepr(type);
    }
}