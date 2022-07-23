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
struct token* prevToken;
static List* tokens;
// The next unique identifier used for indexing blocks
static int arrayUID = 1;

static struct token* accept(_TokenType type)
{
    struct token* token;
    int i = 0;
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        token = List_Get(tokens, i);
        if (token->type == type) {
            break;
        } else if (token->type != TOKEN_NEWLINE) {
            return NULL;
        }
        i++;
    }
    for (; i >= 0; i--) {
        List_Pop(tokens);
    }
    prevToken = token;
    return token;
}

static bool nextIsDef()
{
    int i = 0;
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        struct token* token = List_Get(tokens, i);
        i++;
        if (token->type == TOKEN_NEWLINE) {
            continue;
        } else if (token->type == TOKEN_IDENT) {
            break;
        } else {
            return false;
        }
    }
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        struct token* token = List_Get(tokens, i);
        i++;
        if (token->type == TOKEN_NEWLINE) {
            continue;
        } else if (token->type == TOKEN_COLON) {
            return true;
        } else {
            return false;
        }
    }
}

static struct token* nextToken()
{
    int i = 0;
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        struct token* token = List_Get(tokens, i);
        i++;
        if (token->type == TOKEN_NEWLINE) {
            continue;
        } else {
            return token;
        }
    }
}

static struct token* nextTokenMaybeNewline()
{
    if (List_IsEmpty(tokens)) {
        List_Append(tokens, Lexer_GetNextToken(in));
    }
    return List_Peek(tokens);
}

static struct token* expect(_TokenType type)
{
    struct token* token;
    if ((token = accept(type)) != NULL) {
        return token;
    } else {
        error(nextToken()->pos, "expected '%s', got '%s'", Token_GetErrorMsgRepr(type), Token_GetErrorMsgRepr(nextToken()->type));
        return NULL;
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
ASTNode* parseDefine(SymbolNode* scope);
ASTNode* parseExpr(SymbolNode* scope);

static ASTNode* parseArgList(SymbolNode* scope)
{
    ASTNode* arglist = AST_Create_arglist(scope, prevToken->pos);
    while (!accept(TOKEN_RPAREN)) {
        List_Append(arglist->arglist.args, parseExpr(scope));
        accept(TOKEN_COMMA);
    }
    if (arglist->arglist.args->size == 1) {
        arglist->astType = AST_PAREN;
    } else if (arglist->arglist.args->size > 1) {
        arglist->astType = AST_ARGLIST;
    }
    return arglist;
}

static int blockUID = 1;
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
            } else if (accept(TOKEN_SEMICOLON)) {
                if (nextTokenMaybeNewline()->type == TOKEN_NEWLINE) {
                    error(nextTokenMaybeNewline()->pos, "unexpected newline");
                }
            } else {
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
    // Create a new scope so that pre is visible
    SymbolNode* blockScope = Symbol_Create(myItoa(blockUID++), SYMBOL_BLOCK, scope, prevToken->pos);
    ASTNode* block = AST_Create_block(blockScope, scope, prevToken->pos);
    blockScope->def = block;

    ASTNode* pre = NULL;
    if (!accept(TOKEN_SEMICOLON)) {
        pre = parseStatement(blockScope);
    }
    ASTNode* condition = NULL;
    ASTNode* post = NULL;
    ASTNode* body = NULL;
    ASTNode* elseBlock = NULL;

    if (pre && accept(TOKEN_LBRACE)) {
        body = parseBlock(blockScope);
        body->block.symbol->isLoop = true;
        condition = pre;
        pre = NULL;
    } else {
        if (pre) {
            expect(TOKEN_SEMICOLON);
        }
        if (!accept(TOKEN_SEMICOLON)) {
            condition = parseStatement(blockScope);
            expect(TOKEN_SEMICOLON);
        }
        post = NULL;
        if (!accept(TOKEN_LBRACE)) {
            post = parseStatement(blockScope);
            expect(TOKEN_LBRACE);
        }

        body = parseBlock(blockScope);
        body->block.symbol->isLoop = true;
    }

    if (!pre) {
        pre = AST_Create_undef(scope, prevToken->pos);
    }
    if (!condition) {
        condition = AST_Create_undef(scope, prevToken->pos);
    }
    if (!post) {
        post = AST_Create_undef(scope, prevToken->pos);
    }

    if (accept(TOKEN_ELSE)) {
        expect(TOKEN_LBRACE);
        elseBlock = parseBlock(blockScope);
    } else {
        elseBlock = AST_Create_undef(scope, prevToken->pos);
    }

    return AST_Create_for(pre, condition, post, body, elseBlock, scope, prevToken->pos, false);
}

static ASTNode* parseMapping(SymbolNode* scope)
{
    List* exprs = List_Create();
    struct token* token = NULL;
    if (accept(TOKEN_ELSE)) {
        expect(TOKEN_ARROW);
    } else {
        List_Append(exprs, parseExpr(scope));
        while (accept(TOKEN_COMMA)) {
            List_Append(exprs, parseExpr(scope));
        }
        expect(TOKEN_ARROW);
    }
    ASTNode* expr = parseExpr(scope);
    return AST_Create_mapping(expr, exprs, scope, prevToken->pos);
}

static ASTNode* parseFieldMapping(SymbolNode* scope)
{
    List* exprs = List_Create();
    struct token* token = NULL;
    if (accept(TOKEN_ELSE)) {
        expect(TOKEN_ARROW);
    } else {
        expect(TOKEN_DOT);
        char* text = malloc(sizeof(char) * 255);
        if (token = accept(TOKEN_IDENT)) {
            strncpy_s(text, 255, token->data, 254);
        } else {
            token = expect(TOKEN_NOTHING);
            strncpy_s(text, 255, "nothing", 254);
        }
        List_Append(exprs, AST_Create_ident(text, scope, token->pos));
        expect(TOKEN_ARROW);
    }
    ASTNode* expr = parseExpr(scope);

    ASTNode* retval = AST_Create_fieldMapping(expr, exprs, scope, prevToken->pos);
    retval->astType = AST_FIELD_MAPPING;
    return retval;
}

static ASTNode* parseCase(SymbolNode* scope)
{
    ASTNode* caseNode = AST_Create_case(parseExpr(scope), scope, prevToken->pos);

    expect(TOKEN_LBRACE);
    struct token* token = NULL;
    if (nextToken()->type == TOKEN_DOT) {
        caseNode->astType = AST_FIELD_CASE;
        while (!accept(TOKEN_RBRACE)) {
            ASTNode* mapping = parseFieldMapping(scope);
            List_Append(caseNode->_case.mappings, mapping);
            if (accept(TOKEN_RBRACE)) {
                break;
            } else if (!accept(TOKEN_SEMICOLON)) {
                expect(TOKEN_NEWLINE);
            }
        }
    } else {
        while (!accept(TOKEN_RBRACE)) {
            List_Append(caseNode->_case.mappings, parseMapping(scope));
            if (accept(TOKEN_RBRACE)) {
                break;
            } else if (!accept(TOKEN_SEMICOLON)) {
                expect(TOKEN_NEWLINE);
            }
        }
    }
    return caseNode;
}

static ASTNode* parseFactor(SymbolNode* scope)
{
    ASTNode* child = NULL;
    struct token* token = NULL;
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
    } else if ((token = accept(TOKEN_NOTHING)) != NULL) {
        child = AST_Create_nothing(scope, token->pos);
    } else if ((token = accept(TOKEN_REAL)) != NULL) {
        float data = atof(token->data);
        child = AST_Create_real(data, scope, token->pos);
    } else if ((token = accept(TOKEN_STR)) != NULL) {
        child = AST_Create_string(token->data, scope, token->pos);
        while (accept(TOKEN_DPLUS)) {
            token = expect(TOKEN_STR);
            strcat(child->string.data, token->data);
        }
    } else if ((token = accept(TOKEN_CHAR)) != NULL) {
        child = AST_Create_char(token->data, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = parseArgList(scope);
    } else if ((token = accept(TOKEN_LSQUARE)) != NULL) {
        child = AST_Create_arrayLiteral(scope, token->pos);
        while (!(token = accept(TOKEN_RSQUARE))) {
            List_Append(child->arrayLiteral.members, parseExpr(scope));
            accept(TOKEN_COMMA);
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
        if (nextToken()->type == TOKEN_LSQUARE || nextToken()->type == TOKEN_LPAREN) {
            init = parseFactor(scope);
        } else {
            init = AST_Create_undef(scope, nextToken()->pos);
        }
        child = AST_Create_new(type, init, scope, token->pos);
    } else if ((token = accept(TOKEN_DOT)) != NULL) {
        struct token* ident = expect(TOKEN_IDENT);
        expect(TOKEN_ASSIGN);
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, ident->data, 254);
        child = AST_Create_namedArg(text, parseExpr(scope), scope, token->pos);
    } else if (accept(TOKEN_LBRACE)) {
        return parseBlock(scope);
    } else if (accept(TOKEN_IF)) {
        return parseIf(scope);
    } else if (accept(TOKEN_FOR)) {
        return parseFor(scope);
    } else if (accept(TOKEN_CASE)) {
        return parseCase(scope);
    } else {
        error(prevToken->pos, "expected expression, got '%s'", Token_GetErrorMsgRepr(nextToken()->type));
    }
    return child;
}

static ASTNode* parsePostfix(SymbolNode* scope)
{
    ASTNode* child = parseFactor(scope);
    struct token* token = NULL;
    while (true) {
        if (nextTokenMaybeNewline()->type != TOKEN_NEWLINE && (token = accept(TOKEN_LPAREN)) != NULL) {
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
            child = AST_Create_cast(child, parseType(scope, false), scope, token->pos);
        } else if ((token = accept(TOKEN_DOT)) != NULL) {
            token = expect(TOKEN_IDENT);
            char* text = malloc(sizeof(char) * 255);
            strncpy_s(text, 255, token->data, 254);
            ASTNode* ident = AST_Create_ident(text, scope, token->pos);
            child = AST_Create_dot(child, ident, scope, token->pos, false);
        } else if ((token = accept(TOKEN_QMARK)) != NULL) {
            child = AST_Create_maybe(child, scope, token->pos);
        } else if ((token = accept(TOKEN_ORELSE)) != NULL) {
            child = AST_Create_orelse(-1, child, parseStatement(scope), scope, token->pos);
        } else {
            break;
        }
    }
    return child;
}

static ASTNode* parsePrefix(SymbolNode* scope)
{
    struct token* token = NULL;
    ASTNode* prefix = NULL;
    if ((token = accept(TOKEN_EMARK)) != NULL) {
        prefix = AST_Create_not(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        prefix = AST_Create_addrOf(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_STAR)) != NULL) {
        prefix = AST_Create_deref(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_MINUS)) != NULL) {
        prefix = AST_Create_neg(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_TILDE)) != NULL) {
        prefix = AST_Create_bitNot(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_SIZEOF)) != NULL) {
        prefix = AST_Create_sizeof(parseType(scope, false), scope, token->pos);
    } else {
        prefix = parsePostfix(scope);
    }
    return prefix;
}

static ASTNode* parseTerm(SymbolNode* scope)
{
    ASTNode* term = parsePrefix(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_STAR)) != NULL) {
            term = AST_Create_multiply(term, parsePrefix(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_SLASH)) != NULL) {
            term = AST_Create_divide(term, parsePrefix(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_PERCENT)) != NULL) {
            term = AST_Create_modulus(term, parsePrefix(scope), scope, token->pos);
        } else {
            return term;
        }
    }
}

static ASTNode* parseIntExpr(SymbolNode* scope)
{
    struct token* token = NULL;
    ASTNode* child = parseTerm(scope);
    while (true) {
        if ((token = accept(TOKEN_PLUS)) != NULL) {
            child = AST_Create_add(child, parseTerm(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_MINUS)) != NULL) {
            child = AST_Create_subtract(child, parseTerm(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

static ASTNode* parseShiftExpr(SymbolNode* scope)
{
    struct token* token = NULL;
    ASTNode* child = parseIntExpr(scope);
    while (true) {
        if ((token = accept(TOKEN_DLSR)) != NULL) {
            child = AST_Create_lshift(child, parseIntExpr(scope), scope, token->pos);
        } else if ((token = accept(TOKEN_DGTR)) != NULL) {
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
    struct token* token = NULL;
    if ((token = accept(TOKEN_DEQ)) != NULL) {
        return AST_Create_eq(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_GTR)) != NULL) {
        return AST_Create_gtr(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_LSR)) != NULL) {
        return AST_Create_lsr(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_GTE)) != NULL) {
        return AST_Create_gte(child, parseShiftExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_LTE)) != NULL) {
        return AST_Create_lte(child, parseShiftExpr(scope), scope, token->pos);
    } else {
        return child;
    }
}

// Returns the first equal-sign expression, or the next conditional if none can be found
static ASTNode* parseNeqExpr(SymbolNode* scope)
{
    ASTNode* child = parseConditional(scope);
    struct token* token = NULL;
    if ((token = accept(TOKEN_NEQ)) != NULL) {
        return AST_Create_neq(child, parseConditional(scope), scope, token->pos);
    } else {
        return child;
    }
}

static ASTNode* parseBitAndExpr(SymbolNode* scope)
{
    ASTNode* child = parseNeqExpr(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
            child = AST_Create_bitAnd(child, parseNeqExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

static ASTNode* parseBitXorExpr(SymbolNode* scope)
{
    ASTNode* child = parseBitAndExpr(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_CARET)) != NULL) {
            child = AST_Create_bitXor(child, parseBitAndExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

static ASTNode* parseBitOrExpr(SymbolNode* scope)
{
    ASTNode* child = parseBitXorExpr(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_BAR)) != NULL) {
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
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DAMPERSAND)) != NULL) {
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
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DBAR)) != NULL) {
            child = AST_Create_or(child, parseAndExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

static ASTNode* parseExpr(SymbolNode* scope)
{
    struct token* token = NULL;
    ASTNode* child = parseOrExpr(scope);
    if ((token = accept(TOKEN_ASSIGN)) != NULL) {
        child = AST_Create_assign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_PLUS_ASSIGN)) != NULL) {
        child = AST_Create_addAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_MINUS_ASSIGN)) != NULL) {
        child = AST_Create_subAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_STAR_ASSIGN)) != NULL) {
        child = AST_Create_multAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_SLASH_ASSIGN)) != NULL) {
        child = AST_Create_divAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_PERCENT_ASSIGN)) != NULL) {
        child = AST_Create_modAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DAMPERSAND_ASSIGN)) != NULL) {
        child = AST_Create_andAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DBAR_ASSIGN)) != NULL) {
        child = AST_Create_orAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_AMPERSAND_ASSIGN)) != NULL) {
        child = AST_Create_bitAndAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_BAR_ASSIGN)) != NULL) {
        child = AST_Create_bitOrAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_CARET_ASSIGN)) != NULL) {
        child = AST_Create_bitXorAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DLSR_ASSIGN)) != NULL) {
        child = AST_Create_lshiftAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DGTR_ASSIGN)) != NULL) {
        child = AST_Create_rshiftAssign(child, parseOrExpr(scope), scope, token->pos);
    }
    return child;
}

static ASTNode* parseReturn(SymbolNode* scope)
{
    return AST_Create_return(parseExpr(scope), scope, prevToken->pos);
}

static ASTNode* parseDefer(SymbolNode* scope)
{
    ASTNode* deferStatement = parseStatement(scope);
    if (deferStatement == NULL) {
        error(prevToken->pos, "expected statement after defer");
    }
    ASTNode* retval = AST_Create_defer(deferStatement, scope, prevToken->pos);
    List_Append(scope->defers, deferStatement);
    return retval;
}

static ASTNode* parseStatement(SymbolNode* scope)
{
    // TODO: Detect def by ident followed by newlines followed by : -[ ? or @
    if (nextIsDef()) {
        return parseDefine(scope, false);
    } else if (accept(TOKEN_FREE)) {
        return AST_Create_free(parseExpr(scope), scope, prevToken->pos);
    } else if (accept(TOKEN_RETURN)) {
        return parseReturn(scope);
    } else if (accept(TOKEN_DEFER)) {
        return parseDefer(scope);
    } else if (accept(TOKEN_CONTINUE)) {
        return AST_Create_continue(scope, prevToken->pos);
    } else if (accept(TOKEN_BREAK)) {
        return AST_Create_break(scope, prevToken->pos);
    } else {
        return parseExpr(scope);
    }
}

// isPublic is passed in as true to make parameters and return types always public
ASTNode* parseDefine(SymbolNode* scope)
{
    struct token* doc = NULL;
    struct token* temp = NULL;
    bool hasDesc = false;

    if (doc = accept(TOKEN_DOC)) {
        hasDesc = true;
    }

    struct token* name = expect(TOKEN_IDENT);
    SymbolNode* symbol = Symbol_Create(name->data, SYMBOL_VARIABLE, scope, name->pos);
    ASTNode* define = AST_Create_define(symbol, scope, prevToken->pos);

    if (temp = accept(TOKEN_QMARK)) {
        symbol->isExtern = true;
        if (accept(TOKEN_LSQUARE)) {
            struct token* externName = expect(TOKEN_IDENT);
            strcpy_s(symbol->externName, 255, externName->data);
            expect(TOKEN_RSQUARE);
        } else {
            strcpy_s(symbol->externName, 255, symbol->name);
        }
    } else {
        strcpy_s(symbol->externName, 255, symbol->name);
    }

    if (temp = accept(TOKEN_RESTRICT)) {
        List* restrictionExpr = List_Create();
        symbol->isRestricted = true;
        symbol->restrictionExpr = restrictionExpr;
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

    if (hasDesc) {
        strncpy_s(symbol->desc, 255, doc->data, 255);
    }

    expect(TOKEN_COLON);
    bool isConst = accept(TOKEN_COLON) != NULL;

    ASTNode* type = NULL;
    ASTNode* def = NULL;
    bool inferType = accept(TOKEN_ASSIGN);

    if (!inferType) {
        type = parseType(symbol, false);
        type->isConst |= isConst;
        if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Package")) {
            symbol->symbolType = SYMBOL_PACKAGE;
        } else if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Module")) {
            symbol->symbolType = SYMBOL_MODULE;
        } else if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Type")) {
            symbol->symbolType = SYMBOL_TYPE;
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
        type->isConst |= isConst;
    }

    if (symbol->symbolType == SYMBOL_TYPE && symbol->name[0] >= 'a' && symbol->name[0] <= 'z') {
        error(symbol->pos, "type symbol not capitalized");
    }

    if (inferType || accept(TOKEN_ASSIGN)) {
        if (symbol->symbolType == SYMBOL_MODULE || symbol->symbolType == SYMBOL_PACKAGE) {
            def = parseType(symbol, false);
        } else if (symbol->symbolType == SYMBOL_MODULE) {
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
    return define;
}

ASTNode* parseEnumDefine(SymbolNode* scope)
{
    struct token* name = expect(TOKEN_IDENT);
    SymbolNode* symbol = Symbol_Create(name->data, SYMBOL_VARIABLE, scope, name->pos);
    ASTNode* define = AST_Create_define(symbol, scope, prevToken->pos);
    strcpy_s(symbol->externName, 255, symbol->name);

    if (accept(TOKEN_COLON)) {
        ASTNode* type = NULL;
        type = parseType(symbol, false);
        if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Package")) {
            symbol->symbolType = SYMBOL_PACKAGE;
        } else if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Module")) {
            symbol->symbolType = SYMBOL_MODULE;
        } else if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Type")) {
            symbol->symbolType = SYMBOL_TYPE;
        } else if (type->astType == AST_FUNCTION && type->isConst) {
            symbol->symbolType = SYMBOL_FUNCTION;
        } else {
            symbol->symbolType = SYMBOL_VARIABLE;
        }
        if (accept(TOKEN_ELLIPSES)) {
            symbol->isVararg = true;
        }
        symbol->pos = merge(symbol->pos, type->pos);
        symbol->type = type;
    } else {
        symbol->type = AST_Create_void(scope, symbol->pos);
    }
    return define;
}

ASTNode* parseTypeAtom(SymbolNode* scope)
{
    struct token* token = NULL;
    ASTNode* child = NULL;
    if ((token = accept(TOKEN_IDENT)) != NULL) {
        char* text = malloc(sizeof(char) * 255);
        strncpy_s(text, 255, token->data, 254);
        child = AST_Create_ident(text, scope, token->pos);
    } else if ((token = accept(TOKEN_LPAREN)) != NULL) {
        child = AST_Create_paramlist(scope, token->pos);
        while (!accept(TOKEN_RPAREN)) {
            List_Append(child->paramlist.defines, parseDefine(scope));
            if (accept(TOKEN_COMMA)) {
                if (nextTokenMaybeNewline()->type == TOKEN_NEWLINE) {
                    error(nextTokenMaybeNewline()->pos, "unexpected newline");
                }
            }
        }
        child->pos = merge(child->pos, token->pos);
        if (child->paramlist.defines->size == 0) {
            child->astType = AST_VOID;
        }
    } else if ((token = accept(TOKEN_ENUM)) != NULL) {
        child = AST_Create_enum(scope, token->pos);
        while (!accept(TOKEN_RPAREN)) {
            List_Append(child->_enum.defines, parseEnumDefine(scope));
            if (accept(TOKEN_COMMA)) {
                if (nextTokenMaybeNewline()->type == TOKEN_NEWLINE) {
                    error(nextTokenMaybeNewline()->pos, "unexpected newline");
                }
            }
        }
        child->pos = merge(child->pos, token->pos);
        if (child->_enum.defines->size == 0) {
            error(token->pos, "empty enum");
        }
    } else {
        error(prevToken->pos, "expected type, got '%s'", Token_GetErrorMsgRepr(nextToken()->type));
    }
    return child;
}

static ASTNode* parseTypeDot(SymbolNode* scope)
{
    ASTNode* factor = parseTypeAtom(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DOT)) != NULL) {
            factor = AST_Create_dot(factor, parseTypeAtom(scope), scope, token->pos);
        } else {
            break;
        }
    }
    return factor;
}

static ASTNode* parseTypeUnion(SymbolNode* scope)
{
    ASTNode* factor = parseTypeDot(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DBAR)) != NULL) {
            factor = AST_Create_union(factor, parseTypeDot(scope), scope, token->pos);
        } else {
            break;
        }
    }
    return factor;
}

ASTNode* parseTypeFunction(SymbolNode* scope)
{
    ASTNode* child = parseTypeUnion(scope);
    struct token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_ARROW)) != NULL) {
            if (child->astType != AST_FUNCTION && child->astType != AST_PARAMLIST && child->astType != AST_VOID) {
                error(child->pos, "expected parameter list or function");
            }
            SymbolNode* hiddenSymbol = Symbol_Create("", SYMBOL_BLOCK, scope, child->pos); // So that paramlist members are not visible in function
            ASTNode* right = parseType(hiddenSymbol);
            ASTNode* parent = AST_Create_function(child, right, scope, token->pos);
            child = parent;
        } else {
            return child;
        }
    }
}

ASTNode* parseTypeNonConst(SymbolNode* scope)
{
    //ASTNode* child = parseTypeFunction(scope, isPublic);
    struct token* token = NULL;
    if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        return AST_Create_addr(parseType(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_DAMPERSAND)) != NULL) {
        ASTNode* type = AST_Create_addr(parseType(scope), scope, token->pos);
        return AST_Create_addr(type, scope, token->pos);
    } else if ((token = accept(TOKEN_QMARK)) != NULL) {
        ASTNode* maybeEnum = AST_Create_enum(scope, token->pos);

        SymbolNode* nothingSymbol = Symbol_Create("nothing", SYMBOL_VARIABLE, NULL, maybeEnum->pos);
        ASTNode* nothingDefine = AST_Create_define(nothingSymbol, scope, token->pos);
        ASTNode* nothingType = AST_Create_void(scope, token->pos);
        nothingSymbol->type = nothingType;

        SymbolNode* somethingSymbol = Symbol_Create("something", SYMBOL_VARIABLE, NULL, maybeEnum->pos);
        ASTNode* somethingDefine = AST_Create_define(somethingSymbol, scope, token->pos);
        ASTNode* somethingType = parseType(scope);
        somethingSymbol->type = somethingType;

        List_Append(maybeEnum->_enum.defines, nothingDefine);
        List_Append(maybeEnum->_enum.defines, somethingDefine);
        return maybeEnum;
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
        lengthSymbol->type->isConst = true;

        SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* dataDefine = AST_Create_define(dataSymbol, scope, token->pos);
        ASTNode* dataType = AST_Create_addr(parseType(scope), scope, token->pos);
        arrStruct->pos = merge(arrStruct->pos, dataType->pos);
        ASTNode* dataCode = AST_Create_undef(scope, token->pos);
        dataSymbol->def = dataCode;
        dataSymbol->type = dataType;

        List_Append(arrStruct->paramlist.defines, lengthDefine);
        List_Append(arrStruct->paramlist.defines, dataDefine);
        return arrStruct;
    } else {
        return parseTypeFunction(scope);
    }
}

ASTNode* parseType(SymbolNode* scope)
{
    struct token* token;
    if ((token = accept(TOKEN_COLON)) != NULL) {
        ASTNode* type = parseTypeNonConst(scope);
        type->isConst = true;
        return type;
    } else {
        return parseTypeNonConst(scope);
    }
}

// Parses the token queue into a symbol tree
ASTNode* Parser_Parse(FILE* _in, SymbolNode* program)
{
    in = _in;
    tokens = List_Create();

    ASTNode* module = parseDefine(program, true);
    expect(TOKEN_EOF);
    List_Destroy(tokens);

    return module;
}