/*
Reads in two tokens at a time from the token queue (see lexer.c) and creates one
symbol tree that points to many abstract syntax trees
*/

#include "parse.h"
#include "../util/debug.h"
#include "./ast.h"
#include "./lexer.h"
#include "./main.h"
#include "./position.h"
#include "./token.h"
#include <stdlib.h>
#include <string.h>

// File handle for the input file
static FILE* in;
// Pointer to the previous token for taking a look at the span
static Token* prevToken;
// Pointer to the token that is at the front of the token queue
static Token* nextToken;
// Pointer to the token that is just after the front of the token queue
static Token* nextNextToken;
// The next unique identifier used for indexing blocks
static int blockUID = 1;
static int arrayUID = 1;

/*
Takes in a token type. If that type matches the token type of the token at the
front of the token queue, pops the token from the stack and returns it. Otherwise,
returns null
*/
static Token* accept(_TokenType type)
{
    if (nextToken->type == type) {
        Token* temp = nextToken;
        prevToken = nextToken;
        nextToken = nextNextToken;
        nextNextToken = Lexer_GetNextToken(in);
        return temp;
    } else {
        return NULL;
    }
}

static Token* accept2(_TokenType type, _TokenType type2)
{
    if (nextToken->type == type && nextNextToken->type == type2) {
        Token* temp = nextToken;
        prevToken = nextToken;
        nextNextToken = Lexer_GetNextToken(in);
        nextToken = Lexer_GetNextToken(in);
        return temp;
    } else {
        return NULL;
    }
}

/*
Takes in a token type. If that type matches the token type of the token at the
front of the token queue, pops the token off the stack and returns it. Otherwise,
crashes program with a syntax error.
*/
static Token* expect(_TokenType type)
{
    Token* token;
    if ((token = accept(type)) != NULL) {
        return token;
    } else {
        error(prevToken->pos, "expected %s, got %s", Token_GetString(type), Token_GetString(nextToken->type));
        return NULL;
    }
}

static Token* expect2(_TokenType type, _TokenType type2)
{
    Token* token;
    if ((token = accept2(type, type2)) != NULL) {
        return token;
    } else {
        error(prevToken->pos, "expected %s, got %s", Token_GetString(type), Token_GetString(nextToken->type));
        return NULL;
    }
}

static void rebaseScope(ASTNode* node, SymbolNode* newScope)
{
    node->scope = newScope;
    if (node->astType == AST_DEFINE) {
        SymbolNode* def = node->data;
        def->parent = newScope;
        Map_Put(newScope->children, def->name, def);
    }

    ListElem* elem = List_Begin(node->children);
    for (; elem != List_End(node->children); elem = elem->next) {
        rebaseScope(elem->data, newScope);
    }
}

/*
Converts integers to base 10 ascii. Used for text representation of UID's 
*/
char* myItoa(int val)
{
    char* buf = (char*)calloc(1, 32);
    int i = 30;
    for (; val && i; --i, val /= 10)
        buf[i] = "0123456789"[val % 10];
    return &buf[i + 1];
}

void appendAndMerge(ASTNode* node, ASTNode* child)
{
    List_Append(node->children, child);
    node->pos = merge(node->pos, child->pos);
}

ASTNode* parseType(SymbolNode* scope);
ASTNode* parseTypeAtom(SymbolNode* scope);
ASTNode* parseStatement(SymbolNode* scope);
ASTNode* parseDefine(SymbolNode* scope, bool isPublic);
ASTNode* parseExpr(SymbolNode* scope);

static ASTNode* parseArgList(SymbolNode* scope)
{
    ASTNode* arglist = AST_Create(AST_PAREN, 0, scope, prevToken->pos);
    if (!accept(TOKEN_RPAREN)) {
        while (true) {
            while (accept(TOKEN_NEWLINE))
                ;
            // accept dot? perhaps
            appendAndMerge(arglist, parseExpr(scope));
            while (accept(TOKEN_NEWLINE))
                ;
            if (!accept(TOKEN_COMMA)) {
                arglist->pos = merge(arglist->pos, expect(TOKEN_RPAREN)->pos);
                break;
            }
        }
    }
    if (arglist->children->size != 1) {
        arglist->astType = AST_ARGLIST;
    }
    return arglist;
}

// Returns the first factor (identifier, literals), or null if none can be found
static ASTNode* parseFactor(SymbolNode* scope)
{
    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* child = NULL;
    Token* token = NULL;
    if ((token = accept(TOKEN_IDENT)) != NULL) {
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, token->data, 254);
        child = AST_Create(AST_IDENT, text, scope, token->pos);
    } else if ((token = accept(TOKEN_INT)) != NULL) {
        int data = strtol(token->data, NULL, 10);
        child = AST_Create(AST_INT, data, scope, token->pos);
    } else if ((token = accept(TOKEN_HEX)) != NULL) {
        int data = strtol(token->data + 2, NULL, 16);
        child = AST_Create(AST_INT, data, scope, token->pos);
    } else if ((token = accept(TOKEN_BIN)) != NULL) {
        int data = strtol(token->data + 2, NULL, 2);
        child = AST_Create(AST_INT, data, scope, token->pos);
    } else if ((token = accept(TOKEN_NULL)) != NULL) {
        child = AST_Create(AST_NULL, 0, scope, token->pos);
    } else if ((token = accept(TOKEN_REAL)) != NULL) {
        float data = atof(token->data);
        child = AST_Create(AST_REAL, data, scope, token->pos);
    } else if ((token = accept(TOKEN_STR)) != NULL) {
        child = AST_Create(AST_STRING, token->data, scope, token->pos);
    } else if ((token = accept(TOKEN_CHAR)) != NULL) {
        child = AST_Create(AST_CHAR, token->data, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = parseArgList(scope);
    } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
        child = AST_Create(AST_ARRAY_LITERAL, 0, scope, token->pos);
        while (!(token = accept(TOKEN_RSQUARE))) {
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(child, parseExpr(scope));
            if (!accept(TOKEN_NEWLINE)) {
                if (!accept(TOKEN_COMMA)) {
                    while (accept(TOKEN_NEWLINE))
                        ;
                    token = expect(TOKEN_RSQUARE);
                    child->pos = merge(child->pos, token->pos);
                    break;
                }
            } else {
                while (accept(TOKEN_NEWLINE))
                    ;
            }
        }
        child->pos = merge(child->pos, token->pos);
    } else if ((token = accept(TOKEN_TRUE)) != NULL) {
        child = AST_Create(AST_TRUE, 1, scope, token->pos);
    } else if ((token = accept(TOKEN_FALSE)) != NULL) {
        child = AST_Create(AST_FALSE, 0, scope, token->pos);
    } else if ((token = accept(TOKEN_NEW)) != NULL) {
        child = AST_Create(AST_NEW, NULL, scope, token->pos);
        char* str = calloc(255, 1);
        strcat_s(str, 255, myItoa(arrayUID++));
        strcat_s(str, 255, "arr");
        SymbolNode* dumbyScope = Symbol_Create(str, SYMBOL_VARIABLE, scope, child->pos);
        appendAndMerge(child, parseType(dumbyScope, false));
    } else if ((token = accept(TOKEN_FREE)) != NULL) {
        child = AST_Create(AST_FREE, NULL, scope, prevToken->pos);
        appendAndMerge(child, parseExpr(scope));
    } else if ((token = accept(TOKEN_DOT)) != NULL) {
        Token* ident = expect(TOKEN_IDENT);
        expect(TOKEN_ASSIGN);
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, ident->data, 254);
        child = AST_Create(AST_NAMED_ARG, text, scope, token->pos);
        appendAndMerge(child, parseExpr(scope));
    } else {
        error(prevToken->pos, "expected expression, got %s", Token_GetString(nextToken->type));
    }
    return child;
}

static ASTNode* parsePostfix(SymbolNode* scope)
{
    ASTNode* child = parseFactor(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_LPAREN)) != NULL) {
            ASTNode* parent = AST_Create(AST_CALL, 0, scope, token->pos);
            appendAndMerge(parent, child);
            appendAndMerge(parent, parseArgList(scope));
            child = parent;
        } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
            ASTNode* parent = AST_Create(AST_INDEX, 0, scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseExpr(scope));
            while (accept(TOKEN_NEWLINE))
                ;
            expect(TOKEN_RSQUARE);
            child = parent;
        } else if ((token = accept(TOKEN_COLON)) != NULL) {
            ASTNode* parent = AST_Create(AST_CAST, 0, scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseType(scope, false));
            child = parent;
        } else if ((token = accept(TOKEN_DOT)) != NULL) {
            ASTNode* parent = AST_Create(AST_DOT, NULL, scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            token = expect(TOKEN_IDENT);
            char* text = malloc(sizeof(char) * 255);
            strncpy_s(text, 255, token->data, 254);
            child = AST_Create(AST_IDENT, text, scope, token->pos);
            appendAndMerge(parent, child);
            child = parent;
        } else {
            break;
        }
    }
    return child;
}

// Returns the first prefix, or the first factor if none can be found
static ASTNode* parsePrefix(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* prefix = NULL;
    if ((token = accept(TOKEN_EMARK)) != NULL) {
        prefix = AST_Create(AST_NOT, "!", scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parsePrefix(scope));
    } else if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        prefix = AST_Create(AST_ADDROF, "&", scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parsePrefix(scope));
    } else if ((token = accept(TOKEN_STAR)) != NULL) {
        prefix = AST_Create(AST_DEREF, "*", scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parsePrefix(scope));
    } else if ((token = accept(TOKEN_MINUS)) != NULL) {
        prefix = AST_Create(AST_NEG, "-", scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parsePrefix(scope));
    } else if ((token = accept(TOKEN_TILDE)) != NULL) {
        prefix = AST_Create(AST_BIT_NOT, "~", scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parsePrefix(scope));
    } else if ((token = accept(TOKEN_BAR)) != NULL) {
        prefix = AST_Create(AST_SIZEOF, NULL, scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(prefix, parseType(scope, false));
        while (accept(TOKEN_NEWLINE))
            ;
        expect(TOKEN_BAR);
    } else {
        prefix = parsePostfix(scope);
    }
    return prefix;
}

// Returns the first term, or the first term if none can be found
static ASTNode* parseTerm(SymbolNode* scope)
{
    ASTNode* term = parsePrefix(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_STAR)) != NULL) {
            ASTNode* multiply = AST_Create(AST_MULTIPLY, "*", scope, token->pos);
            appendAndMerge(multiply, term);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(multiply, parsePrefix(scope));
            term = multiply;
        } else if ((token = accept(TOKEN_SLASH)) != NULL) {
            ASTNode* divide = AST_Create(AST_DIVIDE, "/", scope, token->pos);
            appendAndMerge(divide, term);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(divide, parsePrefix(scope));
            term = divide;
        } else if ((token = accept(TOKEN_PERCENT)) != NULL) {
            ASTNode* modulus = AST_Create(AST_MODULUS, "%", scope, token->pos);
            appendAndMerge(modulus, term);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(modulus, parsePrefix(scope));
            term = modulus;
        } else {
            return term;
        }
    }
}

// Returns the first integer expression, or the first term if none can be found
static ASTNode* parseIntExpr(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* child = parseTerm(scope);
    while (true) {
        if ((token = accept(TOKEN_PLUS)) != NULL) {
            ASTNode* parent = AST_Create(AST_ADD, "+", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseTerm(scope));
            child = parent;
        } else if ((token = accept(TOKEN_MINUS)) != NULL) {
            ASTNode* parent = AST_Create(AST_SUBTRACT, "-", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseTerm(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

static ASTNode* parseShiftExpr(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* child = parseIntExpr(scope);
    while (true) {
        if ((token = accept(TOKEN_DLSR)) != NULL) {
            ASTNode* parent = AST_Create(AST_LSHIFT, "<<", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseIntExpr(scope));
            child = parent;
        } else if ((token = accept(TOKEN_DGTR)) != NULL) {
            ASTNode* parent = AST_Create(AST_RSHIFT, ">>", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseIntExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

// Returns the first conditional, or the first integer expression if none can be found
static ASTNode* parseConditional(SymbolNode* scope)
{
    ASTNode* child = parseShiftExpr(scope);
    Token* token = NULL;
    if ((token = accept(TOKEN_GTR)) != NULL) {
        ASTNode* parent = AST_Create(AST_GTR, ">", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseShiftExpr(scope));
        return parent;
    } else if ((token = accept(TOKEN_LSR)) != NULL) {
        ASTNode* parent = AST_Create(AST_LSR, "<", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseShiftExpr(scope));
        return parent;
    } else if ((token = accept(TOKEN_GTE)) != NULL) {
        ASTNode* parent = AST_Create(AST_GTE, ">=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseShiftExpr(scope));
        return parent;
    } else if ((token = accept(TOKEN_LTE)) != NULL) {
        ASTNode* parent = AST_Create(AST_LTE, "<=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseShiftExpr(scope));
        return parent;
    } else {
        return child;
    }
}

// Returns the first equal-sign expression, or the next conditional if none can be found
static ASTNode* parseEqExpr(SymbolNode* scope)
{
    ASTNode* child = parseConditional(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DEQ)) != NULL) {
            ASTNode* parent = AST_Create(AST_EQ, "==", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseConditional(scope));
            return parent;
        } else if ((token = accept(TOKEN_NEQ)) != NULL) {
            ASTNode* parent = AST_Create(AST_NEQ, "!=", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseConditional(scope));
            return parent;
        } else {
            return child;
        }
    }
}

static ASTNode* parseBitAndExpr(SymbolNode* scope)
{
    ASTNode* child = parseEqExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
            ASTNode* parent = AST_Create(AST_BIT_AND, "&", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseEqExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

static ASTNode* parseBitXorExpr(SymbolNode* scope)
{
    ASTNode* child = parseBitAndExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_CARET)) != NULL) {
            ASTNode* parent = AST_Create(AST_BIT_XOR, "^", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseBitAndExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

static ASTNode* parseBitOrExpr(SymbolNode* scope)
{
    ASTNode* child = parseBitXorExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_BAR)) != NULL) {
            ASTNode* parent = AST_Create(AST_BIT_OR, "|", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseBitXorExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

// Returns the first and expression, or the next equal-sign expression if none can be found
static ASTNode* parseAndExpr(SymbolNode* scope)
{
    ASTNode* child = parseBitOrExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DAMPERSAND)) != NULL) {
            ASTNode* parent = AST_Create(AST_AND, "&&", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseBitOrExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

// Returns the first or expression, or the next and expression if none can be found
ASTNode* parseOrExpr(SymbolNode* scope)
{
    ASTNode* child = parseAndExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DBAR)) != NULL) {
            ASTNode* parent = AST_Create(AST_OR, "||", scope, token->pos);
            appendAndMerge(parent, child);
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(parent, parseAndExpr(scope));
            child = parent;
        } else {
            return child;
        }
    }
}

ASTNode* parseTernaryExpr(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* child = parseOrExpr(scope);
    if ((token = accept(TOKEN_QMARK)) != NULL) {
        ASTNode* parent = AST_Create(AST_TERNARY, 0, scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseExpr(scope));
        expect(TOKEN_SEMICOLON);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseExpr(scope));
        return parent;
    } else {
        return child;
    }
}

static ASTNode* parseExpr(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* child = parseTernaryExpr(scope);
    if ((token = accept(TOKEN_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_ASSIGN, "=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_PLUS_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_ADD_ASSIGN, "+=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_MINUS_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_SUB_ASSIGN, "-=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_STAR_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_MULT_ASSIGN, "*=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_SLASH_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_DIV_ASSIGN, "/=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_PERCENT_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_MOD_ASSIGN, "%=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_AMPERSAND_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_AND_ASSIGN, "&=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_BAR_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_OR_ASSIGN, "|=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_CARET_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_XOR_ASSIGN, "^=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_DLSR_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_LSHIFT_ASSIGN, "<<=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    } else if ((token = accept(TOKEN_DGTR_ASSIGN)) != NULL) {
        ASTNode* parent = AST_Create(AST_RSHIFT_ASSIGN, ">>=", scope, token->pos);
        appendAndMerge(parent, child);
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(parent, parseTernaryExpr(scope));
        child = parent;
    }
    return child;
}

ASTNode* parseBlock(SymbolNode* scope)
{
    SymbolNode* blockScope = Symbol_Create(myItoa(blockUID++), SYMBOL_BLOCK, scope, prevToken->pos);
    ASTNode* block = AST_Create(AST_BLOCK, blockScope, scope, prevToken->pos);
    blockScope->def = block;

    while (!accept(TOKEN_RBRACE)) {
        ASTNode* child = parseStatement(blockScope);
        if (child != NULL) {
            appendAndMerge(block, child);
            if (accept(TOKEN_RBRACE)) {
                break;
            } else if (!accept(TOKEN_SEMICOLON)) {
                expect(TOKEN_NEWLINE);
            }
        }
    }
    return block;
}

// Parses out the first if-statement from the token queue
static ASTNode* parseIf(SymbolNode* scope)
{
    ASTNode* ifNode = AST_Create(AST_IF, 0, scope, prevToken->pos);

    ASTNode* condition = parseExpr(scope);
    expect(TOKEN_LBRACE);
    ASTNode* body = parseBlock(scope);

    appendAndMerge(ifNode, condition);
    appendAndMerge(ifNode, body);

    if (accept(TOKEN_ELSE)) {
        ifNode->astType = AST_IFELSE;
        if (accept(TOKEN_IF)) {
            appendAndMerge(ifNode, parseIf(scope));
        } else {
            expect(TOKEN_LBRACE);
            appendAndMerge(ifNode, parseBlock(scope));
        }
    }

    return ifNode;
}

static ASTNode* parseFor(SymbolNode* scope)
{
    ASTNode* forNode = AST_Create(AST_FOR, 0, scope, prevToken->pos);

    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* pre = parseStatement(NULL);
    if (pre && !accept(TOKEN_NEWLINE)) {
        if (accept(TOKEN_LBRACE)) {
            // For loop acts as while loop
            forNode->astType = AST_WHILE;
            ASTNode* body = parseBlock(scope);
            SymbolNode* blockSymbol = body->data;
            blockSymbol->isLoop = true;

            rebaseScope(pre, blockSymbol);
            appendAndMerge(forNode, pre);
            appendAndMerge(forNode, body);
            return forNode;
        } else {
            expect(TOKEN_SEMICOLON);
        }
    }
    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* condition = parseStatement(NULL);
    if (condition && !accept(TOKEN_NEWLINE)) {
        expect(TOKEN_SEMICOLON);
    }
    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* loopExpr = NULL;
    if (!accept(TOKEN_LBRACE)) {
        loopExpr = parseStatement(NULL);
        while (accept(TOKEN_NEWLINE))
            ;
        expect(TOKEN_LBRACE);
    }

    ASTNode* body = parseBlock(scope);
    SymbolNode* bodySymbol = body->data;
    bodySymbol->isLoop = true;

    if (pre) {
        rebaseScope(pre, bodySymbol);
        appendAndMerge(forNode, pre);
    } else {
        appendAndMerge(forNode, AST_Create(AST_UNDEF, NULL, scope, forNode->pos));
    }
    if (condition) {
        rebaseScope(condition, bodySymbol);
        appendAndMerge(forNode, condition);
    } else {
        appendAndMerge(forNode, AST_Create(AST_UNDEF, NULL, scope, forNode->pos));
    }
    if (loopExpr) {
        rebaseScope(loopExpr, bodySymbol);
        appendAndMerge(forNode, loopExpr);
    } else {
        appendAndMerge(forNode, AST_Create(AST_UNDEF, NULL, scope, forNode->pos));
    }
    appendAndMerge(forNode, body);

    return forNode;
}

static ASTNode* parseCase(SymbolNode* scope)
{
    ASTNode* caseNode = AST_Create(AST_CASE, 0, scope, prevToken->pos);
    Token* token = NULL;
    if (!accept(TOKEN_LBRACE)) {
        while (accept(TOKEN_NEWLINE))
            ;
        appendAndMerge(caseNode, parseExpr(scope));
        while (accept(TOKEN_COMMA)) {
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(caseNode, parseExpr(scope));
        }
        expect(TOKEN_LBRACE);
    }
    appendAndMerge(caseNode, parseBlock(scope));
    return caseNode;
}

static ASTNode* parseSwitch(SymbolNode* scope)
{
    ASTNode* switchNode = AST_Create(AST_SWITCH, 0, scope, prevToken->pos);

    ASTNode* expr = parseExpr(scope);
    appendAndMerge(switchNode, expr);
    expect(TOKEN_LBRACE);
    Token* token = NULL;
    while (!accept(TOKEN_RBRACE)) {
        while (accept(TOKEN_NEWLINE))
            ;
        if (((token = accept(TOKEN_CASE)) != NULL) || ((token = accept(TOKEN_ELSE)) != NULL)) {
            appendAndMerge(switchNode, parseCase(scope));
        } else {
            break;
        }
        while (accept(TOKEN_NEWLINE))
            ;
    }
    return switchNode;
}

static ASTNode* parseReturn(SymbolNode* scope)
{
    ASTNode* returnNode = AST_Create(AST_RETURN, NULL, scope, prevToken->pos);

    if (!accept(TOKEN_NEWLINE)) {
        appendAndMerge(returnNode, parseExpr(scope));
    } else {
        appendAndMerge(returnNode, AST_Create(AST_VOID, NULL, scope, prevToken->pos));
    }
    return returnNode;
}

static ASTNode* parseRestrict(SymbolNode* scope)
{
    Map* restrictionExpr = Map_Create();
    while (accept(TOKEN_NEWLINE))
        ;
    while (!accept(TOKEN_RSQUARE)) {
        while (accept(TOKEN_NEWLINE))
            ;
        Token* token = expect(TOKEN_IDENT);
        if (accept(TOKEN_ASSIGN)) {
            Map_Put(restrictionExpr, token->data, parseExpr(scope));
        } else {
            Map_Put(restrictionExpr, token->data, AST_Create(AST_IDENT, token->data, scope, token->pos));
        }
        if (!accept(TOKEN_NEWLINE)) {
            if (!accept(TOKEN_COMMA)) {
                while (accept(TOKEN_NEWLINE))
                    ;
                expect(TOKEN_RSQUARE);
                break;
            }
        } else {
            while (accept(TOKEN_NEWLINE))
                ;
        }
    }
    while (accept(TOKEN_NEWLINE))
        ;

    expect(TOKEN_LBRACE);
    ASTNode* block = parseBlock(scope);
    SymbolNode* blockSymbol = block->data;
    blockSymbol->restrictionExpr = restrictionExpr;
    blockSymbol->isRestricted = true;
    return block;
}

static ASTNode* parseDefer(SymbolNode* scope)
{
    ASTNode* defer = AST_Create(AST_DEFER, scope->defers->size, scope, prevToken->pos);
    ASTNode* deferStatement = parseStatement(scope);
    List_Append(scope->defers, deferStatement);
    appendAndMerge(defer, deferStatement);
    return defer;
}

static ASTNode* parseStatement(SymbolNode* scope)
{
    if (accept(TOKEN_LBRACE)) {
        return parseBlock(scope);
    } else if (accept(TOKEN_IF)) {
        return parseIf(scope);
    } else if (accept(TOKEN_FOR)) {
        return parseFor(scope);
    } else if (accept(TOKEN_CONTINUE)) {
        return AST_Create(AST_CONTINUE, "continue", scope, prevToken->pos);
    } else if (accept(TOKEN_BREAK)) {
        return AST_Create(AST_BREAK, "break", scope, prevToken->pos);
    } else if (accept(TOKEN_SWITCH)) {
        return parseSwitch(scope);
    } else if (accept(TOKEN_RETURN)) {
        return parseReturn(scope);
    } else if (accept(TOKEN_RESTRICT)) {
        return parseRestrict(scope);
    } else if (accept(TOKEN_NEWLINE) || accept(TOKEN_SEMICOLON)) {
        return NULL;
    } else if ((nextToken->type == TOKEN_IDENT && nextNextToken->type == TOKEN_COLON) || (nextToken->type == TOKEN_IDENT && nextNextToken->type == TOKEN_RESTRICT)) {
        return parseDefine(scope, false);
    } else if (accept(TOKEN_DEFER)) {
        return parseDefer(scope);
    } else {
        return parseExpr(scope);
    }
}

// isPublic is passed in as true to make parameters and return types always public
ASTNode* parseDefine(SymbolNode* scope, bool isPublic)
{
    Token* doc = NULL;
    Token* temp = NULL;
    Token* firstToken = NULL;
    bool isExtern = false;
    bool isRestricted = false;
    bool hasDesc = false;
    List* restrictionExpr = NULL;

    if (doc = accept(TOKEN_DOC)) {
        hasDesc = true;
    }
    while (accept(TOKEN_NEWLINE))
        ;
    if (temp = accept(TOKEN_RESTRICT)) {
        if (!firstToken) {
            firstToken = temp;
        }
        restrictionExpr = List_Create();
        isRestricted = true;
        while (accept(TOKEN_NEWLINE))
            ;
        while (!accept(TOKEN_RSQUARE)) {
            while (accept(TOKEN_NEWLINE))
                ;
            ASTNode* expr = parseExpr(scope);
            List_Append(restrictionExpr, expr);
            if (!accept(TOKEN_NEWLINE)) {
                if (!accept(TOKEN_COMMA)) {
                    while (accept(TOKEN_NEWLINE))
                        ;
                    expect(TOKEN_RSQUARE);
                    break;
                }
            } else {
                while (accept(TOKEN_NEWLINE))
                    ;
            }
        }
    }
    while (accept(TOKEN_NEWLINE))
        ;

    Token* externNameToken = NULL;
    if (temp = accept(TOKEN_QMARK)) {
        if (!firstToken) {
            firstToken = temp;
        }
        isExtern = true;
        if (accept(TOKEN_LSQUARE)) {
            externNameToken = expect(TOKEN_IDENT);
            expect(TOKEN_RSQUARE);
        }
    }
    while (accept(TOKEN_NEWLINE))
        ;

    if (temp = accept(TOKEN_PLUS)) {
        if (!firstToken) {
            firstToken = temp;
        }
        isPublic = true;
    }
    while (accept(TOKEN_NEWLINE))
        ;

    Token* name = expect(TOKEN_IDENT);
    while (accept(TOKEN_NEWLINE))
        ;
    if (!firstToken) {
        firstToken = name;
    }
    SymbolNode* symbol = Symbol_Create(name->data, SYMBOL_VARIABLE, scope, merge(firstToken->pos, name->pos));
    ASTNode* define = AST_Create(AST_DEFINE, symbol, scope, prevToken->pos);
    if (isExtern) {
        if (externNameToken == NULL) {
            strcpy_s(symbol->externName, 255, name->data);
        } else {
            strcpy_s(symbol->externName, 255, externNameToken->data);
        }
    }
    if (isRestricted) {
        symbol->isRestricted = true;
        symbol->restrictionExpr = restrictionExpr;
    }
    if (hasDesc) {
        strncpy_s(symbol->desc, 255, doc->data, 255);
    }

    expect(TOKEN_COLON);
    if (accept(TOKEN_COLON)) {
        symbol->isCompTime = true;
    }
    while (accept(TOKEN_NEWLINE))
        ;

    ASTNode* type = NULL;
    ASTNode* def = NULL;
    bool inferType = accept(TOKEN_ASSIGN);
    while (accept(TOKEN_NEWLINE))
        ;

    if (!inferType) {
        type = parseType(symbol, false);
        if (type->astType == AST_IDENT && !strcmp(type->data, "Package")) {
            symbol->symbolType = SYMBOL_PACKAGE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Module")) {
            symbol->symbolType = SYMBOL_MODULE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Type")) {
            symbol->symbolType = SYMBOL_TYPE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Enum")) {
            symbol->symbolType = SYMBOL_ENUM;
        } else if (type->astType == AST_FUNCTION && symbol->isCompTime) {
            symbol->symbolType = SYMBOL_FUNCTION;
        } else {
            symbol->symbolType = SYMBOL_VARIABLE;
        }
        if (accept(TOKEN_ELLIPSES)) {
            symbol->isVararg = true;
        }
        symbol->pos = merge(symbol->pos, type->pos);
    } else {
        type = AST_Create(AST_UNDEF, 0, scope, prevToken->pos);
    }

    if (symbol->symbolType == SYMBOL_TYPE && symbol->name[0] >= 'a' && symbol->name[0] <= 'z') {
        error(symbol->pos, "type symbol not capitalized");
    }

    if (inferType || accept(TOKEN_ASSIGN)) {
        while (accept(TOKEN_NEWLINE))
            ;
        if (symbol->symbolType == SYMBOL_MODULE || symbol->symbolType == SYMBOL_PACKAGE) {
            def = parseType(symbol, false);
        } else if (symbol->symbolType == SYMBOL_TYPE) {
            def = parseType(symbol, true);
        } else if (symbol->symbolType == SYMBOL_FUNCTION) {
            if (nextToken->type != TOKEN_LBRACE) { // Wrap non-block statements in blocks
                SymbolNode* blockScope = Symbol_Create(myItoa(blockUID++), SYMBOL_BLOCK, symbol, prevToken->pos);
                def = AST_Create(AST_BLOCK, blockScope, symbol, prevToken->pos);
                blockScope->def = def;
                appendAndMerge(def, parseStatement(blockScope));
            } else {
                def = parseStatement(symbol);
            }
        } else {
            def = parseExpr(symbol);
        }
    } else if (symbol->isCompTime && !isExtern && type->astType != AST_ARRAY) {
        error(name->pos, "constant expression for symbol '%s' expected", symbol->name);
    } else {
        def = AST_Create(AST_UNDEF, 0, scope, prevToken->pos);
    }

    if (symbol->symbolType == SYMBOL_ENUM) {
        def->astType = AST_ENUM;
    }

    symbol->def = def;
    symbol->type = type;
    symbol->isPublic = isPublic;
    symbol->isExtern = isExtern;
    return define;
}

ASTNode* parseTypeAtom(SymbolNode* scope, bool isPublic)
{
    Token* token = NULL;
    ASTNode* child = NULL;
    if ((token = accept(TOKEN_IDENT)) != NULL) {
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, token->data, 254);
        child = AST_Create(AST_IDENT, text, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = AST_Create(AST_PARAMLIST, 0, scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        while (!accept(TOKEN_RPAREN)) {
            while (accept(TOKEN_NEWLINE))
                ;
            appendAndMerge(child, parseDefine(scope, isPublic));
            if (!accept(TOKEN_NEWLINE)) {
                if (!accept(TOKEN_COMMA)) {
                    while (accept(TOKEN_NEWLINE))
                        ;
                    expect(TOKEN_RPAREN);
                    break;
                }
            } else {
                while (accept(TOKEN_NEWLINE))
                    ;
            }
        }
        if (child->children->size == 0) {
            child->astType = AST_VOID;
        }
    } else {
        error(prevToken->pos, "expected type, got %s", Token_GetString(nextToken->type));
    }
    return child;
}

static ASTNode* parseTypeDot(SymbolNode* scope, bool isPublic)
{
    ASTNode* factor = parseTypeAtom(scope, isPublic);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DOT)) != NULL) {
            ASTNode* dot = AST_Create(AST_DOT, ".", scope, token->pos);
            appendAndMerge(dot, factor);
            appendAndMerge(dot, parseTypeAtom(scope, isPublic));
            factor = dot;
        } else {
            break;
        }
    }
    return factor;
}

ASTNode* parseTypeFunction(SymbolNode* scope, bool isPublic)
{
    ASTNode* child = parseTypeDot(scope, isPublic);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_ARROW)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            if (child->astType != AST_FUNCTION && child->astType != AST_PARAMLIST && child->astType != AST_VOID) {
                error(child->pos, "expected parameter list or function");
            }
            ASTNode* parent = AST_Create(AST_FUNCTION, 0, scope, token->pos);
            SymbolNode* hiddenSymbol = Symbol_Create("", SYMBOL_BLOCK, scope, parent->pos); // So that paramlist members are not visible in function
            ASTNode* right = parseType(hiddenSymbol, isPublic);
            appendAndMerge(parent, child);
            appendAndMerge(parent, right);
            child = parent;
        } else {
            return child;
        }
    }
}

ASTNode* parseType(SymbolNode* scope, bool isPublic)
{
    //ASTNode* child = parseTypeFunction(scope, isPublic);
    Token* token = NULL;
    if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        ASTNode* type = AST_Create(AST_ADDR, 0, scope, token->pos);
        appendAndMerge(type, parseType(scope, isPublic));
        return type;
    } else if ((token = accept(TOKEN_DAMPERSAND)) != NULL) {
        ASTNode* type1 = AST_Create(AST_ADDR, 0, scope, token->pos);
        ASTNode* type2 = AST_Create(AST_ADDR, 0, scope, token->pos);
        appendAndMerge(type1, type2);
        appendAndMerge(type2, parseType(scope, isPublic));
        return type1;
    } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
        ASTNode* arrStruct = AST_Create(AST_ARRAY, 0, scope, token->pos);

        SymbolNode* lengthSymbol = Symbol_Create("length", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* lengthDefine = AST_Create(AST_DEFINE, lengthSymbol, scope, token->pos);
        ASTNode* lengthType = AST_Create(AST_IDENT, "Int", scope, token->pos);
        ASTNode* lengthCode;
        if (!(token = accept(TOKEN_RSQUARE))) {
            lengthCode = parseExpr(scope);
            token = expect(TOKEN_RSQUARE);
        } else {
            lengthCode = AST_Create(AST_UNDEF, 0, scope, token->pos);
        }
        arrStruct->pos = merge(arrStruct->pos, token->pos);
        lengthSymbol->def = lengthCode;
        lengthSymbol->type = lengthType;
        lengthSymbol->isPublic = true;
        lengthSymbol->isCompTime = true;

        SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* dataDefine = AST_Create(AST_DEFINE, dataSymbol, scope, token->pos);
        ASTNode* dataType = AST_Create(AST_C_ARRAY, NULL, scope, token->pos);
        appendAndMerge(dataType, parseType(scope, isPublic));
        arrStruct->pos = merge(arrStruct->pos, dataType->pos);
        if (lengthCode->astType != AST_UNDEF) {
            appendAndMerge(dataType, lengthCode);
        } else {
            appendAndMerge(dataType, AST_Create(AST_UNDEF, 0, scope, token->pos));
        }
        ASTNode* dataCode = AST_Create(AST_UNDEF, 0, scope, token->pos);
        dataSymbol->def = dataCode;
        dataSymbol->type = dataType;
        dataSymbol->isPublic = true;
        dataSymbol->isCompTime = false;

        appendAndMerge(arrStruct, lengthDefine);
        appendAndMerge(arrStruct, dataDefine);

        if (lengthCode->astType == AST_UNDEF) {
            ASTNode* addr = AST_Create(AST_ADDR, 0, scope, arrStruct->pos);
            appendAndMerge(addr, arrStruct);
            return addr;
        } else {
            return arrStruct;
        }
    } else {
        return parseTypeFunction(scope, isPublic);
    }
}

// Parses the token queue into a symbol tree
ASTNode* Parser_Parse(FILE* _in, SymbolNode* program)
{
    in = _in;
    nextToken = Lexer_GetNextToken(in);
    nextNextToken = Lexer_GetNextToken(in);

    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* module = parseDefine(program, true);
    while (accept(TOKEN_NEWLINE))
        ;
    expect(TOKEN_EOF);
    //AST_Print(module, "", "");

    return module;
}