/*
The lexer handles reading in from a file stream, and grouping characters 
into tokens so that they can be easily manipulated later. 
*/

#include "lexer.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "./position.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// The line number that the translator is on in the input file
int line;
int span = 1;
bool inComment = false;

// some legal identifiers in Orng are keywords in C
// should decouple Orng source from output C. Orng programmer shouldn't care about C at all
static bool cNameClash(char* str)
{
    return (!strcmp(str, "auto")
        || !strcmp(str, "char")
        || !strcmp(str, "const")
        || !strcmp(str, "default")
        || !strcmp(str, "do")
        || !strcmp(str, "double")
        || !strcmp(str, "enum")
        || !strcmp(str, "extern")
        || !strcmp(str, "float")
        || !strcmp(str, "goto")
        || !strcmp(str, "inline")
        || !strcmp(str, "int")
        || !strcmp(str, "long")
        || !strcmp(str, "register")
        || !strcmp(str, "restrict")
        || !strcmp(str, "short")
        || !strcmp(str, "signed")
        || !strcmp(str, "static")
        || !strcmp(str, "struct")
        || !strcmp(str, "switch")
        || !strcmp(str, "typedef")
        || !strcmp(str, "union")
        || !strcmp(str, "unsigned")
        || !strcmp(str, "void")
        || !strcmp(str, "volatile")
        || !strcmp(str, "while")
        || !strcmp(str, "_Alignas")
        || !strcmp(str, "_Alignof")
        || !strcmp(str, "_Atomic")
        || !strcmp(str, "_Bool")
        || !strcmp(str, "_Complex")
        || !strcmp(str, "_Generic")
        || !strcmp(str, "_Imaginary")
        || !strcmp(str, "_Noreturn")
        || !strcmp(str, "_Static_assert")
        || !strcmp(str, "_Thread_local"));
}

static bool prependWithUnderscore(char* str)
{
    int len = strlen(str);
    for (int i = len; i > 0; i--) {
        str[i] = str[i - 1];
    }
    str[0] = '_';
}

static bool strContains(char* str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}

/*
Returns what type of character the given character is. Used to split along char types
*/
static int getCharType(char c)
{
    if (isalnum(c) || c == '_') {
        return 0;
    } else if (isspace(c)) {
        return 1;
    } else {
        return 2;
    }
}

/*
Returns whether or not to split a token based on the begining character of the token, and the new character
*/
static bool shouldSplitToken(char c, char start, int length)
{
    if (start == '\n'
        || start == ')'
        || start == '{'
        || start == '}'
        || start == '['
        || start == ']'
        || start == ';'
        || start == '?'
        || start == ':'
        || start == ','
        || (start == '(' && c != '|')
        || (start == '=' && c != '=')
        || (start == '&' && c != '&' && c != '=')
        || (start == '|' && c != '|' && c != '=')
        || (start == '<' && c != '<' && c != '=')
        || (start == '>' && c != '>' && c != '=')
        || (start == '.' && c != '.')
        || (start == '+' && c != '+' && c != '=')
        || (start == '-' && c != '>' && c != '-' && c != '=' && (c != '[' || length != 1))
        || (start == '*' && c != '=')
        || (start == '/' && c != '=' && c != '/')
        || (start == '%' && c != '=')
        || (start == '!' && c != '=')) {
        return true;
    } else {
        return getCharType(c) != getCharType(start);
    }
}
/* 
Reads in a file stream, gets the data for the next token. Leaves file 
stream at the begining of next token */
Token* Lexer_GetNextToken(FILE* in)
{
    int nextChar;
    struct token* token = (struct token*)calloc(1, sizeof(struct token));
    token->pos.filename = filename;
    token->pos.start_line = line;
    token->pos.end_line = line;
    token->pos.start_span = span;

    // Append next character until end of token
    int length = 0;
    bool escaped = false;
    while ((nextChar = fgetc(in)) != EOF) {
        span++;
        if ((length != 0 && // Excempt the first character
                token->type != TOKEN_STR && // Excempt if token is a string
                token->type != TOKEN_CHAR && // Excempt if token is a char
                (token->type != TOKEN_HEX || !isdigit(nextChar))
                && shouldSplitToken(nextChar, token->data[0], length)) // Compare based on character types
            && !(isdigit(token->data[0]) && nextChar == '.')
            && !(token->data[0] == '0' && nextChar == 'x')) {
            break;
        } else if (!escaped && nextChar == '"' && token->type == TOKEN_STR) {
            break;
        } else if (!escaped && nextChar == '\'' && token->type == TOKEN_CHAR) {
            break;
        } else if (!inComment && !escaped && nextChar == '"' && token->type != TOKEN_CHAR) {
            token->type = TOKEN_STR;
        } else if (!inComment && !escaped && nextChar == '\'' && token->type != TOKEN_STR) {
            token->type = TOKEN_CHAR;
        } else {
            token->data[length++] = nextChar;
            escaped = (nextChar == '\\') && !escaped;
        }
    }
    // Replace character back into input stream
    if (token->type != TOKEN_STR && token->type != TOKEN_CHAR) {
        ungetc(nextChar, in);
        span--;
    }
    token->pos.end_span = span;

    // Skip space characters to get to begining of next token
    while (isspace(nextChar = fgetc(in)) && (nextChar == ' ' || nextChar == '\t')) {
        span++;
    }
    ungetc(nextChar, in);

    // Find the type of the token
    if (length == 0 && token->type != TOKEN_STR && token->type != TOKEN_CHAR) {
        token->type = TOKEN_EOF;
    } else if (token->type != TOKEN_STR && token->type != TOKEN_CHAR) {
        // Go through token map, assign type. If a match is found, break out of the loop
        for (token->type = TOKEN_NEWLINE;
             token->type < _token_count && strcmp(Token_GetRepr(token->type), token->data);
             token->type++)
            ;
        // If no match is found, assume literal. Numbers start with a digit
        if (token->type == _token_count) {
            if (length >= 3 && token->data[0] == '0' && token->data[1] == 'x') {
                token->type = TOKEN_HEX;
            } else if (length >= 3 && token->data[0] == '0' && token->data[1] == 'b') {
                token->type = TOKEN_BIN;
            } else if (isdigit(token->data[0])) {
                if (strContains(token->data, '.')) {
                    token->type = TOKEN_REAL;
                } else {
                    token->type = TOKEN_INT;
                }
            } else {
                token->type = TOKEN_IDENT;
                if (cNameClash(token->data)) {
                    prependWithUnderscore(token->data);
                }
            }
        }
    }
    if (token->type == TOKEN_DOC) {
        memset(token->data, 0, 255);
        while ((nextChar = fgetc(in)) != '=') {
            char str[2];
            str[0] = nextChar;
            str[1] = 0;
            strcat_s(token->data, 255, str);
        }
        fgetc(in);
    }
    // Increment line count if newline token
    else if (token->type == TOKEN_NEWLINE) {
        line++;
        span = 1;
    }
    // Ignore tokens until newline if line comment
    else if (token->type == TOKEN_DMINUS) {
        while (fgetc(in) != '\n')
            ;
        line++;
        span = 1;
        while (isspace(nextChar = fgetc(in)) && (nextChar == ' ' || nextChar == '\t')) {
            span++;
        }
        ungetc(nextChar, in);
        token->type = TOKEN_NEWLINE;
    }
    //printf("%d: [%s]:%s\n", line, token->data, Token_GetString(token->type));
    return token;
}