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
Token* prevToken;
static List* tokens;
// The next unique identifier used for indexing blocks
int blockUID = 1;
static int arrayUID = 1;

static Token* accept(_TokenType type)
{
    while (true) {
        if (List_IsEmpty(tokens)) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        Token* top = List_Peek(tokens);
        if (top->type == type) {
            List_Pop(tokens);
            prevToken = top;
            return top;
        } else if (top->type == TOKEN_NEWLINE) {
            List_Pop(tokens);
        } else {
            return NULL;
        }
    }
}

static bool nextIsDef()
{
    int i = 0;
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        Token* token = List_Get(tokens, i);
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
        Token* token = List_Get(tokens, i);
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

static Token* nextToken()
{
    int i = 0;
    while (true) {
        if (List_IsEmpty(tokens) || i >= tokens->size) {
            List_Append(tokens, Lexer_GetNextToken(in));
        }
        Token* token = List_Get(tokens, i);
        i++;
        if (token->type == TOKEN_NEWLINE) {
            continue;
        } else {
            return token;
        }
    }
}

static Token* nextTokenMaybeNewline()
{
    if (List_IsEmpty(tokens)) {
        List_Append(tokens, Lexer_GetNextToken(in));
    }
    return List_Peek(tokens);
}

static Token* expect(_TokenType type)
{
    Token* token;
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
ASTNode* parseDefine(SymbolNode* scope, bool isPublic);
ASTNode* parseExpr(SymbolNode* scope);

static ASTNode* parseArgList(SymbolNode* scope)
{
    ASTNode* arglist = AST_Create_arglist(scope, prevToken->pos);
    while (!accept(TOKEN_RPAREN)) {
        List_Append(arglist->arglist.args, parseExpr(scope));
        accept(TOKEN_COMMA);
    }
    if (arglist->arglist.args->size != 1) {
        arglist->astType = AST_ARGLIST;
    }
    return arglist;
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
            } else {
                accept(TOKEN_SEMICOLON);
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
    ASTNode* pre = NULL;
    if (!accept(TOKEN_SEMICOLON)) {
        pre = parseStatement(NULL);
    }
    ASTNode* condition = NULL;
    ASTNode* post = NULL;
    SymbolNode* bodySymbol = Symbol_Create(myItoa(blockUID++), SYMBOL_BLOCK, scope, prevToken->pos);
    ASTNode* body = NULL;
    ASTNode* elseBlock = NULL;

    if (pre && accept(TOKEN_LBRACE)) {
        body = parseBlock(bodySymbol);
        bodySymbol->isLoop = true;
    } else {
        if (pre) {
            expect(TOKEN_SEMICOLON);
        }
        if (!accept(TOKEN_SEMICOLON)) {
            condition = parseStatement(NULL);
            expect(TOKEN_SEMICOLON);
        }
        post = NULL;
        if (!accept(TOKEN_LBRACE)) {
            post = parseStatement(NULL);
            expect(TOKEN_LBRACE);
        }

        body = parseBlock(bodySymbol);
        bodySymbol->isLoop = true;
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
        elseBlock = parseBlock(scope);
    } else {
        elseBlock = AST_Create_undef(scope, prevToken->pos);
    }

    return AST_Create_for(pre, condition, post, body, elseBlock, scope, prevToken->pos, false);
}

static ASTNode* parseMapping(SymbolNode* scope)
{
    List* exprs = List_Create();
    Token* token = NULL;
    if (!accept(TOKEN_LBRACE)) {
        List_Append(exprs, parseExpr(scope));
        while (accept(TOKEN_COMMA)) {
            List_Append(exprs, parseExpr(scope));
        }
        expect(TOKEN_ARROW);
    }
    ASTNode* expr = parseExpr(scope);
    return AST_Create_mapping(expr, exprs, scope, prevToken->pos);
}

static ASTNode* parseCase(SymbolNode* scope)
{
    ASTNode* switchNode = AST_Create_case(parseExpr(scope), scope, prevToken->pos);

    expect(TOKEN_LBRACE);
    Token* token = NULL;
    while (!accept(TOKEN_RBRACE)) {
        List_Append(switchNode->_case.mappings, parseMapping(scope));
    }
    return switchNode;
}

static ASTNode* parseFactor(SymbolNode* scope)
{
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
    } else if ((token = accept(TOKEN_NOTHING)) != NULL) {
        child = AST_Create_null(scope, token->pos);
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
        Token* ident = expect(TOKEN_IDENT);
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
    Token* token = NULL;
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
        } else {
            break;
        }
    }
    return child;
}

static ASTNode* parsePrefix(SymbolNode* scope)
{
    Token* token = NULL;
    ASTNode* prefix = NULL;
    if ((token = accept(TOKEN_EMARK)) != NULL) {
        prefix = AST_Create_not(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_AMPERSAND)) != NULL) {
        prefix = AST_Create_addr(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_STAR)) != NULL) {
        prefix = AST_Create_deref(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_MINUS)) != NULL) {
        prefix = AST_Create_neg(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_TILDE)) != NULL) {
        prefix = AST_Create_bitNot(parsePrefix(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_BAR)) != NULL) {
        prefix = AST_Create_sizeof(parseType(scope, false), scope, token->pos);
        expect(TOKEN_BAR);
    } else {
        prefix = parsePostfix(scope);
    }
    return prefix;
}

static ASTNode* parseTerm(SymbolNode* scope)
{
    ASTNode* term = parsePrefix(scope);
    Token* token = NULL;
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
    Token* token = NULL;
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
    Token* token = NULL;
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
    Token* token = NULL;
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
    Token* token = NULL;
    if ((token = accept(TOKEN_NEQ)) != NULL) {
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
            child = AST_Create_or(child, parseAndExpr(scope), scope, token->pos);
        } else {
            return child;
        }
    }
}

static ASTNode* parseExpr(SymbolNode* scope)
{
    Token* token = NULL;
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
    } else if ((token = accept(TOKEN_AMPERSAND_ASSIGN)) != NULL) {
        child = AST_Create_andAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_BAR_ASSIGN)) != NULL) {
        child = AST_Create_orAssign(child, parseOrExpr(scope), scope, token->pos);
    } else if ((token = accept(TOKEN_CARET_ASSIGN)) != NULL) {
        child = AST_Create_xorAssign(child, parseOrExpr(scope), scope, token->pos);
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
    List_Append(scope->defers, deferStatement);
    return AST_Create_defer(deferStatement, scope, prevToken->pos);
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
ASTNode* parseDefine(SymbolNode* scope, bool isPublic)
{
    Token* doc = NULL;
    Token* temp = NULL;
    bool hasDesc = false;

    if (doc = accept(TOKEN_DOC)) {
        hasDesc = true;
    }

    Token* name = expect(TOKEN_IDENT);
    SymbolNode* symbol = Symbol_Create(name->data, SYMBOL_VARIABLE, scope, name->pos);
    ASTNode* define = AST_Create_define(symbol, scope, prevToken->pos);

    if (temp = accept(TOKEN_QMARK)) {
        symbol->isExtern = true;
        if (accept(TOKEN_LSQUARE)) {
            Token* externName = expect(TOKEN_IDENT);
            strcpy_s(symbol->externName, 255, externName->data);
            expect(TOKEN_RSQUARE);
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
        } else if (type->astType == AST_IDENT && !strcmp(type->ident.data, "Enum")) {
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
        while (!accept(TOKEN_RPAREN)) {
            List_Append(child->paramlist.defines, parseDefine(scope, isPublic));
            accept(TOKEN_COMMA);
        }
        child->pos = merge(child->pos, token->pos);
        if (child->paramlist.defines->size == 0) {
            child->astType = AST_VOID;
        }
    } else {
        error(prevToken->pos, "expected type, got '%s'", Token_GetErrorMsgRepr(nextToken()->type));
    }
    return child;
}

static ASTNode* parseTypeDot(SymbolNode* scope, bool isPublic)
{
    ASTNode* factor = parseTypeAtom(scope, isPublic);
    Token* token = NULL;
    while (true) {
        if ((token = accept(TOKEN_DOT)) != NULL) {
            factor = AST_Create_dot(factor, parseTypeAtom(scope, isPublic), scope, token->pos);
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
        lengthSymbol->type->isConst = true;

        SymbolNode* dataSymbol = Symbol_Create("data", SYMBOL_VARIABLE, NULL, arrStruct->pos);
        ASTNode* dataDefine = AST_Create_define(dataSymbol, scope, token->pos);
        ASTNode* dataType = AST_Create_addr(parseType(scope, isPublic), scope, token->pos);
        arrStruct->pos = merge(arrStruct->pos, dataType->pos);

        ASTNode* dataCode = AST_Create_undef(scope, token->pos);
        dataSymbol->def = dataCode;
        dataSymbol->type = dataType;

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
    tokens = List_Create();

    ASTNode* module = parseDefine(program, true);
    expect(TOKEN_EOF);
    List_Destroy(tokens);

    return module;
}