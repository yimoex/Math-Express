#ifndef PRIORITY_ROOT
#include "node.c"
#endif

#define EXPR_MAX_SIZE 16

typedef int (*AstCallback)(AstNode* node);

typedef struct {
    char ch;
    NodeOperator op;
    int priority;
    AstCallback call;
} ExprNode;


typedef struct {
    int size;
    ExprNode* nodes[EXPR_MAX_SIZE];
} Expr;

Expr* express_create(){
    Expr* ex = (Expr *)malloc(sizeof(Expr));
    ex -> size = 0;
    return ex;
}

int express_register(Expr* ex, char ch, NodeOperator op, int priority, AstCallback caller){
    if(ex -> size == EXPR_MAX_SIZE) return 0;
    ExprNode* node = (ExprNode *)malloc(sizeof(ExprNode));
    node -> ch = ch;
    node -> op = op;
    node -> priority = priority;
    node -> call = caller;
    ex -> nodes[ex -> size] = node;
    ex -> size++;
    return 1;
}
