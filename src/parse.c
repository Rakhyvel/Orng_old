/*
Reads in two tokens at a time from the token queue (see lexer.c) and creates one
symbol tree that points to many abstract syntax trees
*/

#define _CRT_SECURE_NO_WARNINGS
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
int blockUID = 1;
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
        error(prevToken->pos, "expected '%s', got '%s'", Token_GetErrorMsgRepr(type), Token_GetErrorMsgRepr(nextToken->type));
        return NULL;
    }
}

static Token* expect2(_TokenType type, _TokenType type2)
{
    Token* token;
    if ((token = accept2(type, type2)) != NULL) {
        return token;
    } else {
        error(prevToken->pos, "expected '%s', got '%s'", Token_GetErrorMsgRepr(type), Token_GetErrorMsgRepr(nextToken->type));
        return NULL;
    }
}

void rebaseScope(ASTNode* node, SymbolNode* newScope)
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

ASTNode* parseType(SymbolNode* scope);
ASTNode* parseTypeAtom(SymbolNode* scope);
ASTNode* parseStatement(SymbolNode* scope);
ASTNode* parseDefine(SymbolNode* scope, bool isPublic);
ASTNode* parseExpr(SymbolNode* scope);

static ASTNode* parseArgList(SymbolNode* scope)
{
    ASTNode* arglist = AST_Create_arglist(scope, prevToken->pos);
    while (accept(TOKEN_NEWLINE))
        ;
    while (!accept(TOKEN_RPAREN)) {
        while (accept(TOKEN_NEWLINE))
            ;
        // accept dot? perhaps
        List_Append(arglist->arglist.args, parseExpr(scope));
        if (!accept(TOKEN_NEWLINE)) {
            if (!accept(TOKEN_COMMA)) {
                while (accept(TOKEN_NEWLINE))
                    ;
                arglist->pos = merge(arglist->pos, expect(TOKEN_RPAREN)->pos);
                break;
            }
        } else {
            while (accept(TOKEN_NEWLINE))
                ;
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
        child = AST_Create_ident(text, scope, token->pos);
    } else if ((token = accept(TOKEN_INT)) != NULL) {
        int data = strtol(token->data, NULL, 10);
        child = AST_Create_int(data, scope, token->pos);
    } else if ((token = accept(TOKEN_HEX)) != NULL) {
        int data = strtol(token->data + 2, NULL, 16);
        child = AST_Create_int(data, scope, token->pos);
    } else if ((token = accept(TOKEN_BIN)) != NULL) {
        int data = strtol(token->data + 2, NULL, 2);
        child = AST_Create_int(data, scope, token->pos);
    } else if ((token = accept(TOKEN_NULL)) != NULL) {
        child = AST_Create_null(scope, token->pos);
    } else if ((token = accept(TOKEN_REAL)) != NULL) {
        float data = atof(token->data);
        child = AST_Create_real(data, scope, token->pos);
    } else if ((token = accept(TOKEN_STR)) != NULL) {
        child = AST_Create_string(token->data, scope, token->pos);
        while (accept(TOKEN_DPLUS)) {
            while (accept(TOKEN_NEWLINE))
                ;
            token = expect(TOKEN_STR);
            strcat(child->data, token->data);
        }
    } else if ((token = accept(TOKEN_CHAR)) != NULL) {
        child = AST_Create_char(token->data, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = parseArgList(scope);
    } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
        child = AST_Create_arrayLiteral(scope, token->pos);
        while (!(token = accept(TOKEN_RSQUARE))) {
            while (accept(TOKEN_NEWLINE))
                ;
            List_Append(child->arrayLiteral.members, parseExpr(scope));
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
        child = AST_Create_true(scope, token->pos);
    } else if ((token = accept(TOKEN_FALSE)) != NULL) {
        child = AST_Create_false(scope, token->pos);
    } else if ((token = accept(TOKEN_NEW)) != NULL) {
        char* str = calloc(255, 1);
        strcat_s(str, 255, myItoa(arrayUID++));
        strcat_s(str, 255, "arr");
        SymbolNode* dumbyScope = Symbol_Create(str, SYMBOL_VARIABLE, scope, token->pos);
        ASTNode* type = parseType(dumbyScope, false);
        ASTNode* init = NULL;
        if (nextToken->type == TOKEN_LSQUARE || nextToken->type == TOKEN_LPAREN) {
            init = parseFactor(scope);
        } else {
            init = AST_Create_undef(scope, child->pos);
        }
        child = AST_Create_new(type, init, scope, token->pos);
    } else if ((token = accept(TOKEN_FREE)) != NULL) {
        child = AST_Create_free(parseExpr(scope), scope, prevToken->pos);
    } else if ((token = accept(TOKEN_DOT)) != NULL) {
        Token* ident = expect(TOKEN_IDENT);
        expect(TOKEN_ASSIGN);
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, ident->data, 254);
        child = AST_Create_namedArg(text, parseExpr(scope), scope, token->pos);
    } else {
        error(prevToken->pos, "expected expression, got '%s'", Token_GetErrorMsgRepr(nextToken->type));
    }
    return child;
}

static ASTNode* parsePostfix(SymbolNode* scope)
{
    ASTNode* child = parseFactor(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_LPAREN)) != NULL) {
            child = AST_Create_call(child, parseArgList(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
            // [ <expr>? :? <expr>? ]
            ASTNode* parent = NULL;
            ASTNode* arrayExpr = child;
            ASTNode* subscriptOrLowerBound = NULL;
            ASTNode* upperBound = NULL;
            bool isSlice = false;
            if (accept(TOKEN_SEMICOLON)) { // no lower bound
                subscriptOrLowerBound = AST_Create_undef(scope, token->pos); // lowerbound
                isSlice = true;
                if (!accept(TOKEN_RSQUARE)) { // upper bound
                    upperBound = parseExpr(scope);
                    token = expect(TOKEN_RSQUARE);
                } else {
                    upperBound = AST_Create_undef(scope, token->pos); // upperbound
                }
            } else { // a lowerbound or subscript
                subscriptOrLowerBound = parseExpr(scope); // either lowerbound or subscript
                if (!accept(TOKEN_RSQUARE)) { // there is an upper bound
                    isSlice = true;
                    expect(TOKEN_SEMICOLON);
                    if (!accept(TOKEN_RSQUARE)) { // upper bound
                        upperBound = parseExpr(scope);
                        token = expect(TOKEN_RSQUARE);
                    } else {
                        upperBound = AST_Create_undef(scope, token->pos); // upperbound
                    }
                }
            }
            if (isSlice) {
                parent = AST_Create_slice(arrayExpr, subscriptOrLowerBound, upperBound, scope, token->pos);
            } else {
                parent = AST_Create_index(arrayExpr, subscriptOrLowerBound, scope, token->pos);
            }
            parent->pos = merge(parent->pos, token->pos);
            child = parent;
        } else if ((token = accept(TOKEN_COLON)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_cast(child, parseType(scope, false), scope, token->pos);
        } else if ((token = accept(TOKEN_DOT)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            token = expect(TOKEN_IDENT);
            char* text = malloc(sizeof(char) * 255);
            strncpy_s(text, 255, token->data, 254);
            ASTNode* ident = AST_Create_ident(text, scope, token->pos);
            child = AST_Create_dot(child, ident, scope, token->pos, false);
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
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_not(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_addrOf(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_STAR)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_deref(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_MINUS)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_neg(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_TILDE)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_bitNot(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_BAR)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        prefix = AST_Create_sizeof(parseType(scope, false), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            term = AST_Create_multiply(term, parsePrefix(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_SLASH)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            term = AST_Create_divide(term, parsePrefix(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_PERCENT)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            term = AST_Create_modulus(term, parsePrefix(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_add(child, parseTerm(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_MINUS)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_subtract(child, parseTerm(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_lshift(child, parseIntExpr(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_DGTR)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_rshift(child, parseIntExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

// Returns the first conditional, or the first integer expression if none can be found
// <shiftExpr> (<condition-token> <shiftExpr>)*
static ASTNode* parseConditional(SymbolNode* scope)
{
    ASTNode* child = parseShiftExpr(scope);
    Token* token = NULL;
    if ((token = accept(TOKEN_DEQ)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_eq(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_GTR)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_gtr(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_LSR)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_lsr(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_GTE)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_gte(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_LTE)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_lte(child, parseShiftExpr(scope), scope, token->pos);
    } else {
        return child;
    }
}

// Returns the first equal-sign expression, or the next conditional if none can be found
static ASTNode* parseNeqExpr(SymbolNode* scope)
{
    ASTNode* child = parseConditional(scope);
    Token* token = NULL;
    if ((token = accept(TOKEN_NEQ)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        return AST_Create_neq(child, parseConditional(scope), scope, token->pos);
    } else {
        return child;
    }
}

static ASTNode* parseBitAndExpr(SymbolNode* scope)
{
    ASTNode* child = parseNeqExpr(scope);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_bitAnd(child, parseNeqExpr(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_bitXor(child, parseBitAndExpr(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_bitOr(child, parseBitXorExpr(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_and(child, parseBitOrExpr(scope), scope, token->pos);
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
            while (accept(TOKEN_NEWLINE))
                ;
            child = AST_Create_or(child, parseAndExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}
ASTNode* parseBlock(SymbolNode* scope)
{
    SymbolNode* blockScope = Symbol_Create(myItoa(blockUID++), SYMBOL_BLOCK, scope, prevToken->pos);
    ASTNode* block = AST_Create_block(blockScope, scope, prevToken->pos);
    blockScope->def = block;

    while (!accept(TOKEN_RBRACE)) {
        ASTNode* child = parseStatement(blockScope);
        if (child != NULL) {
            List_Append(block->block.children, child);
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

    ASTNode* condition = parseExpr(scope);
    expect(TOKEN_LBRACE);
    ASTNode* body = parseBlock(scope);
    ASTNode* elseBlock = NULL;

    if (accept(TOKEN_ELSE)) {
        if (accept(TOKEN_IF)) {
            elseBlock = parseIf(scope);
        } else {
            expect(TOKEN_LBRACE);
            elseBlock = parseBlock(scope);
        }
    } else {
        elseBlock = AST_Create_undef(scope, prevToken->pos);
    }
    return AST_Create_if(condition, body, elseBlock, scope, prevToken->pos);
}

static ASTNode* parseFor(SymbolNode* scope)
{
    while (accept(TOKEN_NEWLINE))
        ;
    ASTNode* pre = parseStatement(NULL);
    ASTNode* condition = NULL;
    ASTNode* post = NULL;
    SymbolNode* bodySymbol = NULL;
    ASTNode* body = NULL;
    ASTNode* elseBlock = NULL;

    if (pre && !accept(TOKEN_NEWLINE) && accept(TOKEN_LBRACE)) {
        body = parseBlock(scope);
        bodySymbol = body->data;
        bodySymbol->isLoop = true;
    } else {
        expect(TOKEN_SEMICOLON);
        while (accept(TOKEN_NEWLINE))
            ;
        ASTNode* condition = parseStatement(NULL);
        if (condition && !accept(TOKEN_NEWLINE)) {
            expect(TOKEN_SEMICOLON);
        }
        while (accept(TOKEN_NEWLINE))
            ;
        ASTNode* post = NULL;
        if (!accept(TOKEN_LBRACE)) {
            post = parseStatement(NULL);
            while (accept(TOKEN_NEWLINE))
                ;
            expect(TOKEN_LBRACE);
        }

        ASTNode* body = parseBlock(scope);
        SymbolNode* bodySymbol = body->data;
        bodySymbol->isLoop = true;
    }

    if (pre) {
        rebaseScope(pre, bodySymbol);
    } else {
        pre = AST_Create_undef(scope, prevToken->pos);
    }
    if (condition) {
        rebaseScope(condition, bodySymbol);
    } else {
        condition = AST_Create_undef(scope, prevToken->pos);
    }
    if (post) {
        rebaseScope(post, bodySymbol);
    } else {
        post = AST_Create_undef(scope, prevToken->pos);
    }

    if (accept(TOKEN_ELSE)) {
        expect(TOKEN_LBRACE);
        elseBlock = parseBlock(scope);
    } else {
        elseBlock = AST_Create_undef(scope, prevToken->pos);
    }

    return AST_Create_for(pre, condition, post, body, elseBlock, scope, prevToken->pos, false);
}

static ASTNode* parseCase(SymbolNode* scope)
{
    List* exprs = List_Create();
    Token* token = NULL;
    if (!accept(TOKEN_LBRACE)) {
        while (accept(TOKEN_NEWLINE))
            ;
        List_Append(exprs, parseExpr(scope));
        while (accept(TOKEN_COMMA)) {
            while (accept(TOKEN_NEWLINE))
                ;
            List_Append(exprs, parseExpr(scope));
        }
        expect(TOKEN_LBRACE);
    }
    ASTNode* block = parseBlock(scope);
    SymbolNode* blockSymbol = block->data;
    blockSymbol->isLoop = true;
    return AST_Create_case(block, exprs, scope, prevToken->pos);
}

static ASTNode* parseSwitch(SymbolNode* scope)
{
    ASTNode* switchNode = AST_Create_switch(parseExpr(scope), scope, prevToken->pos);

    expect(TOKEN_LBRACE);
    Token* token = NULL;
    while (!accept(TOKEN_RBRACE)) {
        while (accept(TOKEN_NEWLINE))
            ;
        if (((token = accept(TOKEN_CASE)) != NULL) || ((token = accept(TOKEN_ELSE)) != NULL)) {
            List_Append(switchNode->_switch.cases, parseCase(scope));
        } else {
            break;
        }
        while (accept(TOKEN_NEWLINE))
            ;
    }
    return switchNode;
}

static ASTNode* parseRestrict(SymbolNode* scope)
{
    Map* restrictionExpr = Map_Create();
    while (accept(TOKEN_NEWLINE))
        ;
    restrictionExpr = List_Create();
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
    while (accept(TOKEN_NEWLINE))
        ;

    expect(TOKEN_LBRACE);
    ASTNode* block = parseBlock(scope);
    SymbolNode* blockSymbol = block->data;
    blockSymbol->restrictionExpr = restrictionExpr;
    blockSymbol->isRestricted = true;
    return block;
}

// For statements that blur the line between statement and expression
static ASTNode* parseStatementExpr(SymbolNode* scope)
{
    if (accept(TOKEN_LBRACE)) { // Evaluates to last evaluated expression in the block
        return parseBlock(scope);
    } else if (accept(TOKEN_IF)) { // Evaluates to to block evaluated
        return parseIf(scope);
    } else if (accept(TOKEN_FOR)) { // Evaluates to to block evaluated
        return parseFor(scope);
    } else if (accept(TOKEN_SWITCH)) { // Evaluates to to block evaluated
        return parseSwitch(scope);
    } else if (accept(TOKEN_RESTRICT)) { // Evaluates to to block evaluated
        return parseRestrict(scope);
    } else {
        return parseOrExpr(scope); // plain expression, evals to itself
    }
}

static ASTNode* parseExpr(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* child = parseStatementExpr(scope);
    if ((token = accept(TOKEN_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_assign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_PLUS_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_addAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_MINUS_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_subAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_STAR_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_multAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_SLASH_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_divAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_PERCENT_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_modAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_AMPERSAND_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_andAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_BAR_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_orAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_CARET_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_xorAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DLSR_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_lshiftAssign(child, parseStatementExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DGTR_ASSIGN)) != NULL) {
        while (accept(TOKEN_NEWLINE))
            ;
        child = AST_Create_rshiftAssign(child, parseStatementExpr(scope), scope, token->pos);
    }
    return child;
}

static ASTNode* parseReturn(SymbolNode* scope)
{
    ASTNode* expr = NULL;
    if (!accept(TOKEN_NEWLINE)) {
        expr = parseExpr(scope);
    } else {
        expr = AST_Create_undef(scope, prevToken->pos);
    }
    return AST_Create_return(expr, scope, expr->pos);
}

static ASTNode* parseDefer(SymbolNode* scope)
{
    ASTNode* deferStatement = parseStatement(scope);
    if (deferStatement == NULL) {
        error(prevToken->pos, "expected statement after defer");
    }
    List_Append(scope->defers, deferStatement);
    return AST_Create_defer(deferStatement, scope, prevToken->pos);
}

static ASTNode* parseStatement(SymbolNode* scope)
{
    if (accept(TOKEN_CONTINUE)) { // not expr
        return AST_Create_continue(scope, prevToken->pos);
    } else if (accept(TOKEN_BREAK)) { // not expr
        return AST_Create_break(scope, prevToken->pos);
    } else if (accept(TOKEN_RETURN)) { // not expr
        return parseReturn(scope);
    } else if (accept(TOKEN_NEWLINE) || accept(TOKEN_SEMICOLON)) { // not expr
        return NULL;
    } else if ((nextToken->type == TOKEN_IDENT && nextNextToken->type == TOKEN_COLON) || (nextToken->type == TOKEN_IDENT && nextNextToken->type == TOKEN_RESTRICT)) { // not expr
        return parseDefine(scope, false);
    } else if (accept(TOKEN_DEFER)) { // not expr
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
            ASTNode* expr = parseFactor(scope);
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
    ASTNode* define = AST_Create_define(symbol, scope, prevToken->pos);
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
    bool isConst = accept(TOKEN_COLON) != NULL;
    while (accept(TOKEN_NEWLINE))
        ;

    ASTNode* type = NULL;
    ASTNode* def = NULL;
    bool inferType = accept(TOKEN_ASSIGN);
    while (accept(TOKEN_NEWLINE))
        ;

    if (!inferType) {
        type = parseType(symbol, false);
        type->isConst |= isConst;
        if (type->astType == AST_IDENT && !strcmp(type->data, "Package")) {
            symbol->symbolType = SYMBOL_PACKAGE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Module")) {
            symbol->symbolType = SYMBOL_MODULE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Type")) {
            symbol->symbolType = SYMBOL_TYPE;
        } else if (type->astType == AST_IDENT && !strcmp(type->data, "Enum")) {
            symbol->symbolType = SYMBOL_ENUM;
        } else if (type->astType == AST_FUNCTION && type->isConst) {
            symbol->symbolType = SYMBOL_FUNCTION;
        } else {
            symbol->symbolType = SYMBOL_VARIABLE;
        }
        if (accept(TOKEN_ELLIPSES)) {
            symbol->isVararg = true;
        }
        symbol->pos = merge(symbol->pos, type->pos);
    } else {
        type = AST_Create_undef(scope, prevToken->pos);
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
        } else {
            def = parseExpr(symbol);
        }
    } else {
        def = AST_Create_undef(scope, prevToken->pos);
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
        child = AST_Create_ident(text, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = AST_Create_paramlist(scope, token->pos);
        while (accept(TOKEN_NEWLINE))
            ;
        while (!accept(TOKEN_RPAREN)) {
            while (accept(TOKEN_NEWLINE))
                ;
            List_Append(child, parseDefine(scope, isPublic));
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
        child->pos = merge(child->pos, token->pos);
        if (child->children->size == 0) {
            child->astType = AST_VOID;
        }
    } else {
        error(prevToken->pos, "expected type, got '%s'", Token_GetErrorMsgRepr(nextToken->type));
    }
    return child;
}

static ASTNode* parseTypeDot(SymbolNode* scope, bool isPublic)
{
    ASTNode* factor = parseTypeAtom(scope, isPublic);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DOT)) != NULL) {
            factor = AST_Create_dot(factor, parseTypeAtom(scope, isPublic) ,scope, token->pos);
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
            SymbolNode* hiddenSymbol = Symbol_Create("", SYMBOL_BLOCK, scope, child->pos); // So that paramlist members are not visible in function
            ASTNode* right = parseType(hiddenSymbol, isPublic);
            ASTNode* parent = AST_Create_function(child, right, scope, token->pos);
            child = parent;
        } else {
            return child;
        }
    }
}

ASTNode* parseTypeNonConst(SymbolNode* scope, bool isPublic)
{
    //ASTNode* child = parseTypeFunction(scope, isPublic);
    Token* token = NULL;
    if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        return AST_Create_addr(parseType(scope, isPublic), scope, token->pos);
    } else if ((token = accept(TOKEN_DAMPERSAND)) != NULL) {
        ASTNode* type = AST_Create_addr(parseType(scope, isPublic), scope, token->pos);
        return AST_Create_addr(type, scope, token->pos);
    } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
        ASTNode* arrStruct = AST_Create_array(scope, token->pos);

        SymbolNode* lengthSymbol = Symbol_Create("length", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* lengthDefine = AST_Create_define(lengthSymbol, scope, token->pos);
        ASTNode* lengthType = AST_Create_ident("Int", scope, token->pos);
        ASTNode* lengthCode;
        if (!(token = accept(TOKEN_RSQUARE))) {
            lengthCode = parseExpr(scope);
            token = expect(TOKEN_RSQUARE);
        } else {
            lengthCode = AST_Create_undef(scope, token->pos);
        }
        arrStruct->pos = merge(arrStruct->pos, token->pos);
        lengthSymbol->def = lengthCode;
        lengthSymbol->type = lengthType;
        lengthSymbol->isPublic = true;
        lengthSymbol->type->isConst = true;

        SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* dataDefine = AST_Create_define(dataSymbol, scope, token->pos);
        ASTNode* dataType = AST_Create_addr(parseType(scope, isPublic), scope, token->pos);
        arrStruct->pos = merge(arrStruct->pos, dataType->pos);

        ASTNode* dataCode = AST_Create_undef(scope, token->pos);
        dataSymbol->def = dataCode;
        dataSymbol->type = dataType;
        dataSymbol->isPublic = true;

        List_Append(arrStruct->paramlist.defines, lengthDefine);
        List_Append(arrStruct->paramlist.defines, dataDefine);

        return arrStruct;
    } else {
        return parseTypeFunction(scope, isPublic);
    }
}

ASTNode* parseType(SymbolNode* scope, bool isPublic)
{
    Token* token;
    if ((token = accept(TOKEN_COLON)) != NULL) {
        ASTNode* type = parseTypeNonConst(scope, isPublic);
        type->isConst = true;
        return type;
    } else {
        return parseTypeNonConst(scope, isPublic);
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