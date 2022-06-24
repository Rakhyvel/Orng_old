#include "ir.h"
#include "../util/debug.h"
#include "../util/list.h"
#include "ast.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

int blockUID = 1;

ir_id getID(struct list* instructions)
{
    return instructions->size;
}

struct label createLabel(enum labelType labelType, char* name)
{
    struct label retval = {
        labelType,
        name
    };
    return retval;
}

ir_id add_loadIdent(List* instructions, char* name, struct symbolNode* scope, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_IDENT;
    retval->pos = pos;
    retval->loadIdent.name = name;
    retval->loadIdent.scope = scope;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadInt(List* instructions, int64_t data, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_INT;
    retval->pos = pos;
    retval->loadInt.data = data;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadString(List* instructions, char* data, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_STRING;
    retval->pos = pos;
    retval->loadString.data = data;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadChar(List* instructions, char data, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_CHAR;
    retval->pos = pos;
    retval->loadChar.data = data;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadReal(List* instructions, char data, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_REAL;
    retval->pos = pos;
    retval->loadChar.data = data;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadNothing(List* instructions, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_NOTHING;
    retval->pos = pos;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadTrue(List* instructions, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_TRUE;
    retval->pos = pos;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadFalse(List* instructions, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_FALSE;
    retval->pos = pos;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadSizeOf(List* instructions, struct astNode* type, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_SIZEOF;
    retval->pos = pos;
    retval->loadSizeof.type = type;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadArrayLiteral(List* instructions, List* members, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_ARRAY_LITERAL;
    retval->pos = pos;
    retval->loadArrayLiteral.members = members;
    List_Append(instructions, retval);
    return id;
}

ir_id add_loadStructLiteral(List* instructions, List* args, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LOAD_STRUCT_LITERAL;
    retval->pos = pos;
    retval->loadStructLiteral.args = args;
    List_Append(instructions, retval);
    return id;
}

ir_id add_declareTemp(List* instructions, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_DECLARE_TEMP;
    retval->pos = pos;
    List_Append(instructions, retval);
    return id;
}

ir_id add_declareDefer(List* instructions, int deferID, char* symbolName, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_DECLARE_DEFER;
    retval->pos = pos;
    retval->declareDefer.deferID = deferID;
    retval->declareDefer.symbolName = symbolName;
    List_Append(instructions, retval);
    return id;
}

ir_id add_assignTemp(List* instructions, ir_id dst, ir_id src, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_ASSIGN_TEMP;
    retval->pos = pos;
    retval->assignTemp.dst = dst;
    retval->assignTemp.src = src;
    List_Append(instructions, retval);
    return id;
}

ir_id add_return(List* instructions, ir_id expr, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_RETURN;
    retval->pos = pos;
    retval->_return.expr = expr;
    List_Append(instructions, retval);
    return id;
}

ir_id add_setDefer(List* instructions, int deferID, char* symbolName, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_SET_DEFER;
    retval->pos = pos;
    retval->setDefer.deferID = deferID;
    retval->setDefer.symbolName = symbolName;
    List_Append(instructions, retval);
    return id;
}

ir_id add_getDefer(List* instructions, int deferID, char* symbolName, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_SET_DEFER;
    retval->pos = pos;
    retval->setDefer.deferID = deferID;
    retval->setDefer.symbolName = symbolName;
    List_Append(instructions, retval);
    return id;
}

ir_id add_index(List* instructions, ir_id arrExprID, ir_id subscriptID, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_INDEX;
    retval->pos = pos;
    retval->index.arrExprID = arrExprID;
    retval->index.subscriptID = subscriptID;
    List_Append(instructions, retval);
    return id;
}

ir_id add_slice(List* instructions, ir_id arrExprID, ir_id lowerBoundID, ir_id upperBoundID, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_SLICE;
    retval->pos = pos;
    retval->slice.arrExprID = arrExprID;
    retval->slice.lowerBoundID = lowerBoundID;
    retval->slice.upperBoundID = upperBoundID;
    List_Append(instructions, retval);
    return id;
}

ir_id add_dot(List* instructions, ASTNode* dotExpr, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_DOT;
    retval->pos = pos;
    retval->dot.dotExpr = dotExpr;
    List_Append(instructions, retval);
    return id;
}

ir_id add_declareLabel(List* instructions, struct label label, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_DECLARE_LABEL;
    retval->pos = pos;
    retval->declareLabel.label = label;
    List_Append(instructions, retval);
    return id;
}

ir_id add_branchIfZero(List* instructions, ir_id condition, struct label label, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_BRANCH_IF_ZERO;
    retval->pos = pos;
    retval->branchIfZero.condition = condition;
    retval->branchIfZero.label = label;
    List_Append(instructions, retval);
    return id;
}

ir_id add_jump(List* instructions, struct label label, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_JUMP;
    retval->pos = pos;
    retval->jump.label = label;
    List_Append(instructions, retval);
    return id;
}

ir_id add_and(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_AND;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_or(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_OR;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_bitAnd(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_BIT_AND;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_bitXor(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_BIT_XOR;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_bitOr(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_BIT_OR;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_lshift(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LSHIFT;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_rshift(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_RSHIFT;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_eq(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_EQ;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_neq(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_NEQ;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_gtr(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_GTR;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_lsr(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LSR;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_gte(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_GTE;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_lte(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_LTE;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_add(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_ADD;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_subtract(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_SUBTRACT;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_multiply(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_MULTIPLY;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_divide(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_DIVIDE;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id add_modulus(List* instructions, ir_id left, ir_id right, struct position pos)
{
    ir_id id = getID(instructions);
    IR* retval = (IR*)calloc(sizeof(IR), 1);
    retval->type = IR_MODULUS;
    retval->pos = pos;
    retval->add.left = left;
    retval->add.right = right;
    List_Append(instructions, retval);
    return id;
}

ir_id flatten(struct list* instructions, struct astNode* node)
{
    static List* blockStack = NULL;
    if (!blockStack) {
        blockStack = List_Create();
    }

    switch (node->astType) {
    case AST_BLOCK: {
        List_Push(blockStack, node);
        SymbolNode* symbolTree = node->block.symbol;
        strncpy(symbolTree->name, myItoa(blockUID++), 255);

        for (int i = 0; i < symbolTree->defers->size; i++) {
            add_declareDefer(instructions, i, symbolTree->name, node->pos);
        }

        ir_id lastID = -1;
        ListElem* elem = List_Begin(node->block.children);
        for (; elem != List_End(node->block.children); elem = elem->next) {
            ASTNode* statement = (ASTNode*)elem->data;
            lastID = flatten(instructions, statement);
        }
        List_Pop(blockStack);

        struct label returnLabel = createLabel(LABEL_RETURN, symbolTree->name);
        struct label breakLabel = createLabel(LABEL_BREAK, symbolTree->name);
        struct label continueLabel = createLabel(LABEL_CONTINUE, symbolTree->name);
        struct label endLabel = createLabel(LABEL_END, symbolTree->name);
        if (!List_IsEmpty(blockStack) && (node->containsReturn || node->containsContinue || node->containsBreak) && symbolTree->defers->size > 0) {
            add_jump(instructions, continueLabel, node->pos);
            if (node->containsReturn) {
                add_declareLabel(instructions, returnLabel, node->pos);
                // TODO: generate defers
                ASTNode* parentBlock = List_Peek(blockStack);
                SymbolNode* parentSymbol = parentBlock->block.symbol;
                struct label parentReturnLabel = createLabel(LABEL_RETURN, parentSymbol);
                add_jump(instructions, parentReturnLabel, node->pos);
            }

            if (node->containsBreak) {
                add_declareLabel(instructions, breakLabel, node->pos);
                // TODO: generate defers
                add_jump(instructions, endLabel, node->pos);
            }
            add_declareLabel(instructions, continueLabel, node->pos);
            // TODO: generate defers
        }

        return lastID;
    }
    case AST_IF: {
        ASTNode* condition = node->_if.condition;
        ASTNode* bodyBlock = node->_if.bodyBlock;
        ASTNode* elseBlock = node->_if.elseBlock;

        struct label endLabel = createLabel(LABEL_END, bodyBlock->block.symbol->name);
        struct label elseLabel = createLabel(LABEL_ELSE, bodyBlock->block.symbol->name);

        ir_id id = add_declareTemp(instructions, node->pos);

        ir_id conditionID = flatten(instructions, condition);
        if (elseBlock->astType != AST_UNDEF) {
            add_branchIfZero(instructions, conditionID, elseLabel, node->pos);
        } else {
            add_branchIfZero(instructions, conditionID, endLabel, node->pos);
        }
        ir_id bodyBlockID = flatten(instructions, bodyBlock);

        if (elseBlock->astType != AST_UNDEF) {
            add_assignTemp(instructions, id, bodyBlockID, node->pos);
            add_jump(instructions, endLabel, node->pos);
            add_declareLabel(instructions, elseLabel, node->pos);
            ir_id elseBlockID = flatten(instructions, elseBlock);
            add_assignTemp(instructions, id, elseBlockID, node->pos);
        }

        add_declareLabel(instructions, endLabel, node->pos);
        return id;
    }
    case AST_FOR: {
        ASTNode* precondtiton = node->_for.pre;
        ASTNode* condition = node->_for.condition;
        ASTNode* postcondition = node->_for.post;
        ASTNode* bodyBlock = node->_for.bodyBlock;

        struct label beginLabel = createLabel(LABEL_BEGIN, bodyBlock->block.symbol->name);
        struct label endLabel = createLabel(LABEL_END, bodyBlock->block.symbol->name);

        flatten(instructions, precondtiton);
        add_declareLabel(instructions, beginLabel, node->pos);
        ir_id conditionID = flatten(instructions, condition);
        add_branchIfZero(instructions, conditionID, endLabel, node->pos);
        flatten(instructions, bodyBlock);
        flatten(instructions, postcondition);
        add_jump(instructions, beginLabel, node->pos);
        add_declareLabel(instructions, endLabel, node->pos);
        return -1; // What is the value if it never enters the loop?
    }
    case AST_RETURN: {
        ASTNode* expr = node->unop.expr;
        ir_id exprID = flatten(instructions, expr);
        add_return(instructions, exprID, node->pos);

        ASTNode* parentBlock = (ASTNode*)List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->block.symbol;
        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK) {
            parentSymbol = parentSymbol->parent;
        }
        struct label returnLabel = createLabel(LABEL_RETURN, parentSymbol->name);
        add_jump(instructions, returnLabel, node->pos);
        return -1;
    }
    case AST_BREAK: {
        ASTNode* parentBlock = (ASTNode*)List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->block.symbol;
        while (parentSymbol->defers->size == 0 && parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
            parentSymbol = parentSymbol->parent;
        }
        struct label endLabel;
        if (parentSymbol->defers->size == 0) {
            endLabel = createLabel(LABEL_END, parentSymbol->name);
        } else {
            endLabel = createLabel(LABEL_BREAK, parentSymbol->name);
        }
        add_jump(instructions, endLabel, node->pos);
        return -1;
    }
    case AST_CONTINUE: {
        ASTNode* parentBlock = (ASTNode*)List_Peek(blockStack);
        SymbolNode* parentSymbol = parentBlock->block.symbol;
        while (parentSymbol->parent->symbolType == SYMBOL_BLOCK && !parentSymbol->isLoop) {
            parentSymbol = parentSymbol->parent;
        }
        struct label continueLabel = createLabel(LABEL_CONTINUE, parentSymbol->name);
        add_jump(instructions, continueLabel, node->pos);
        return -1;
    }
    case AST_DEFINE: {

	}
    case AST_DEFER: {
        return add_setDefer(instructions, node->defer.deferID, node->scope->name, node->pos);
    }
    case AST_IDENT: {
        return add_loadIdent(instructions, node->ident.data, node->scope, node->pos);
    }
    case AST_INT: {
        return add_loadInt(instructions, node->_int.data, node->pos);
    }
    case AST_STRING: {
        return add_loadString(instructions, node->string.data, node->pos);
    }
    case AST_CHAR: {
        return add_loadChar(instructions, node->_char.data, node->pos);
    }
    case AST_REAL: {
        return add_loadReal(instructions, node->real.data, node->pos);
    }
    case AST_NOTHING: {
        return add_loadNothing(instructions, node->pos);
    }
    case AST_TRUE: {
        return add_loadTrue(instructions, node->pos);
    }
    case AST_FALSE: {
        return add_loadFalse(instructions, node->pos);
    }
    case AST_SIZEOF: {
        return add_loadSizeOf(instructions, node->unop.expr, node->pos);
    }
    case AST_ARRAY_LITERAL: {
        List* members = List_Create();
        for (ListElem* elem = List_Begin(node->arrayLiteral.members); elem != List_End(node->arrayLiteral.members); elem = elem->next) {
            ASTNode* child = (ASTNode*)elem->data;
            List_Append(members, (void*)flatten(instructions, child));
        }

        return add_loadArrayLiteral(instructions, members, node->pos);
    }
    case AST_ARGLIST: {
        List* args = List_Create();
        for (ListElem* elem = List_Begin(node->arglist.args); elem != List_End(node->arglist.args); elem = elem->next) {
            ASTNode* child = (ASTNode*)elem->data;
            List_Append(args, (void*)flatten(instructions, child));
        }

        return add_loadStructLiteral(instructions, args, node->pos);
    }
    case AST_PAREN: {
        ASTNode* expr = List_Get(node->arglist.args, 0);
        return flatten(instructions, expr);
    }
    case AST_INDEX: {
        ASTNode* arrExpr = node->binop.left;
        ASTNode* subscript = node->binop.right;

        ir_id arrExprID = flatten(instructions, arrExpr);
        ir_id subscriptID = flatten(instructions, subscript);

        return add_index(instructions, arrExprID, subscriptID, node->pos);
    }
    case AST_SLICE: {
        ASTNode* arrExpr = node->slice.arrayExpr;
        ASTNode* lowerBound = node->slice.lowerBound;
        ASTNode* upperBound = node->slice.upperBound;

        ir_id arrExprID = flatten(instructions, arrExpr);
        ir_id lowerBoundID = -1;
        ir_id upperBoundID = -1;

        if (lowerBound->astType != AST_UNDEF) {
            lowerBoundID = flatten(instructions, lowerBound);
        }
        if (upperBound->astType != AST_UNDEF) {
            upperBoundID = flatten(instructions, upperBound);
        }

        return add_slice(instructions, arrExprID, lowerBoundID, upperBoundID, node->pos);
    }
    case AST_DOT: {
        return add_dot(instructions, node, node->pos);
    }
    case AST_AND: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_and(instructions, leftID, rightID, node->pos);
    }
    case AST_OR: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_or(instructions, leftID, rightID, node->pos);
    }
    case AST_BIT_AND: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_bitAnd(instructions, leftID, rightID, node->pos);
    }
    case AST_BIT_XOR: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_bitXor(instructions, leftID, rightID, node->pos);
    }
    case AST_BIT_OR: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_bitOr(instructions, leftID, rightID, node->pos);
    }
    case AST_LSHIFT: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_lshift(instructions, leftID, rightID, node->pos);
    }
    case AST_RSHIFT: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_rshift(instructions, leftID, rightID, node->pos);
    }
    case AST_EQ: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_eq(instructions, leftID, rightID, node->pos);
    }
    case AST_NEQ: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_neq(instructions, leftID, rightID, node->pos);
    }
    case AST_GTR: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_gtr(instructions, leftID, rightID, node->pos);
    }
    case AST_LSR: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_lsr(instructions, leftID, rightID, node->pos);
    }
    case AST_GTE: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_gte(instructions, leftID, rightID, node->pos);
    }
    case AST_LTE: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_lte(instructions, leftID, rightID, node->pos);
    }
    case AST_ADD: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_add(instructions, leftID, rightID, node->pos);
    }
    case AST_SUBTRACT: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_subtract(instructions, leftID, rightID, node->pos);
    }
    case AST_MULTIPLY: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_multiply(instructions, leftID, rightID, node->pos);
    }
    case AST_DIVIDE: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_divide(instructions, leftID, rightID, node->pos);
    }
    case AST_MODULUS: {
        ASTNode* left = node->binop.left;
        ASTNode* right = node->binop.right;
        ir_id leftID = flatten(instructions, left);
        ir_id rightID = flatten(instructions, right);
        return add_modulus(instructions, leftID, rightID, node->pos);
    }
    }
}

char* labelTypeToString(enum labelType type)
{
    switch (type) {
    case LABEL_BEGIN:
        return "begin";
    case LABEL_ELSE:
        return "else";
    case LABEL_END:
        return "end";
    case LABEL_CONTINUE:
        return "continue";
    case LABEL_BREAK:
        return "break";
    case LABEL_RETURN:
        return "return";
    case LABEL_SHORT_CIRCUIT:
        return "short_circuit";
    }
}

void printInstructionList(struct list* instructions)
{
    ListElem* elem = List_Begin(instructions);
    int i = 0;
    for (; elem != List_End(instructions); elem = elem->next, i++) {
        IR* instruction = (IR*)elem->data;
        printf("%d ", i);
        switch (instruction->type) {
        case IR_LOAD_IDENT: {
            printf("IR_LOAD_IDENT %s", instruction->loadIdent.name);
            break;
        }
        case IR_LOAD_INT: {
            printf("IR_LOAD_INT %d", (int)instruction->loadInt.data);
            break;
        }
        case IR_LOAD_REAL: {
            printf("IR_LOAD_REAL %f", instruction->loadReal.data);
            break;
        }
        case IR_LOAD_STRING: {
            printf("IR_LOAD_STRING %s", instruction->loadString.data);
            break;
        }
        case IR_LOAD_CHAR: {
            printf("IR_LOAD_CHAR %c", instruction->loadChar.data);
            break;
        }
        case IR_LOAD_NOTHING: {
            printf("IR_LOAD_NOTHING");
            break;
        }
        case IR_LOAD_TRUE: {
            printf("IR_LOAD_TRUE");
            break;
        }
        case IR_LOAD_FALSE: {
            printf("IR_LOAD_FALSE");
            break;
        }
        case IR_LOAD_SIZEOF: {
            printf("IR_LOAD_SIZEOF");
            break;
        }
        case IR_LOAD_ARRAY_LITERAL: {
            printf("IR_LOAD_ARRAY_LITERAL");
            break;
        }
        case IR_LOAD_STRUCT_LITERAL: {
            printf("IR_LOAD_STRUCT_LITERAL");
            break;
        }
        case IR_DECLARE_VAR: {
            printf("IR_DECLARE_VAR");
            break;
        }
        case IR_DECLARE_TEMP: {
            printf("IR_DELCARE_TEMP");
            break;
        }
        case IR_DECLARE_DEFER: {
            printf("IR_DELCARE_DEFER %s_%d", instruction->declareDefer.symbolName, instruction->declareDefer.deferID);
            break;
        }
        case IR_ASSIGN_VAR: {
            printf("IR_ASSIGN_VAR");
            break;
        }
        case IR_ASSIGN_TEMP: {
            printf("IR_ASSIGN_TEMP %d %d", instruction->assignTemp.dst, instruction->assignTemp.src);
            break;
        }
        case IR_RETURN: {
            printf("IR_RETURN %d", instruction->_return.expr);
            break;
        }
        case IR_SET_DEFER: {
            printf("IR_SET_DEFER %s_%d", instruction->setDefer.symbolName, instruction->setDefer.deferID);
            break;
        }
        case IR_INDEX: {
            printf("IR_INDEX %d[%d]", instruction->index.arrExprID, instruction->index.subscriptID);
            break;
        }
        case IR_SLICE: {
            printf("IR_SLICE %d[%d;%d]", instruction->slice.arrExprID, instruction->slice.lowerBoundID, instruction->slice.upperBoundID);
            break;
        }
        case IR_DOT: {
            printf("IR_DOT");
            break;
        }
        case IR_DECLARE_LABEL: {
            printf("IR_DELCARE_LABEL %s_%s", labelTypeToString(instruction->declareLabel.label.labelType), instruction->declareLabel.label.labelID);
            break;
        }
        case IR_BRANCH_IF_ZERO: {
            printf("IR_BRANCH_IF_ZERO %d %s_%s", instruction->branchIfZero.condition, labelTypeToString(instruction->branchIfZero.label.labelType), instruction->branchIfZero.label.labelID);
            break;
        }
        case IR_JUMP: {
            printf("IR_JUMP %s_%s", labelTypeToString(instruction->jump.label.labelType), instruction->jump.label.labelID);
            break;
        }
        case IR_CASE: {
            printf("IR_CASE");
            break;
        }
        case IR_AND: {
            printf("IR_AND %d %d", instruction->_and.left, instruction->_and.right);
            break;
        }
        case IR_OR: {
            printf("IR_OR %d %d", instruction->_or.left, instruction->_or.right);
            break;
        }
        case IR_BIT_AND: {
            printf("IR_BIT_AND %d %d", instruction->bitAnd.left, instruction->bitAnd.right);
            break;
        }
        case IR_BIT_XOR: {
            printf("IR_BIT_XOR %d %d", instruction->bitXor.left, instruction->bitXor.right);
            break;
        }
        case IR_BIT_OR: {
            printf("IR_BIT_OR %d %d", instruction->bitOr.left, instruction->bitOr.right);
            break;
        }
        case IR_LSHIFT: {
            printf("IR_LSHIFT %d %d", instruction->lshift.left, instruction->lshift.right);
            break;
        }
        case IR_RSHIFT: {
            printf("IR_RSHIFT %d %d", instruction->rshift.left, instruction->rshift.right);
            break;
        }
        case IR_EQ: {
            printf("IR_EQ %d %d", instruction->eq.left, instruction->eq.right);
            break;
        }
        case IR_NEQ: {
            printf("IR_NEQ %d %d", instruction->neq.left, instruction->neq.right);
            break;
        }
        case IR_GTR: {
            printf("IR_GTR %d %d", instruction->gtr.left, instruction->gtr.right);
            break;
        }
        case IR_LSR: {
            printf("IR_LSR %d %d", instruction->lsr.left, instruction->lsr.right);
            break;
        }
        case IR_GTE: {
            printf("IR_GTE %d %d", instruction->gte.left, instruction->gte.right);
            break;
        }
        case IR_LTE: {
            printf("IR_LTE %d %d", instruction->lte.left, instruction->lte.right);
            break;
        }
        case IR_ADD: {
            printf("IR_ADD %d %d", instruction->add.left, instruction->add.right);
            break;
        }
        case IR_SUBTRACT: {
            printf("IR_SUBTRACT %d %d", instruction->subtract.left, instruction->subtract.right);
            break;
        }
        case IR_MULTIPLY: {
            printf("IR_MULTIPLY %d %d", instruction->multiply.left, instruction->multiply.right);
            break;
        }
        case IR_DIVIDE: {
            printf("IR_DIVIDE %d %d", instruction->divide.left, instruction->divide.right);
            break;
        }
        case IR_MODULUS: {
            printf("IR_MODULUS %d %d", instruction->modulus.left, instruction->modulus.right);
            break;
        }
        case IR_NEGATE: {
            printf("IR_NEGATE");
            break;
        }
        case IR_BIT_NOT: {
            printf("IR_BIT_NOT");
            break;
        }
        case IR_ADDR_OF: {
            printf("IR_ADDR_OF");
            break;
        }
        case IR_LOAD: {
            printf("IR_LOAD");
            break;
        }
        case IR_CAST: {
            printf("IR_CAST");
            break;
        }
        case IR_CALL: {
            printf("IR_CALL");
            break;
        }
        default: {
            PANIC("not set");
        }
        }
        printf("\n");
    }
}