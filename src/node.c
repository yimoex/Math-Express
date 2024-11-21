#define MAX_CHIDREN_SIZE 16

#define PRIORITY_ROOT -1
#define PRIORITY_ADD 1
#define PRIORITY_SUB 1
#define PRIORITY_DIV 2
#define PRIORITY_MUL 2
#define PRIORITY_REM 2
#define PRIORITY_POW 3
#define PRIORITY_VAL 10

#ifndef NULL
#define NULL (void *)0
#endif

typedef union {
    int value;
} NodeValue;

typedef enum {
    OP_ROOT = 0,
    OP_ADD  = 1, // +
    OP_SUB  = 2, // -
    OP_DIV  = 3, // /
    OP_MUL  = 4, //x
    OP_REM  = 5, //%
    OP_POW  = 6, //%
    OP_VAL  = 7, //Value
} NodeOperator;

typedef struct AstNode {
    int id;
    NodeOperator op;
    NodeValue value;
    int priority;
    struct AstNode* chidrens[MAX_CHIDREN_SIZE];
    int size;
    struct AstNode* father;
} AstNode;

AstNode* astnode_create(NodeOperator op, int priority){
    AstNode* node = (AstNode *)malloc(sizeof(AstNode));
    node -> op = op;
    node -> priority = priority;
    node -> size = 0;
    node -> father = NULL;
    node -> id = 0;
    return node;
}

void astnode_chidrens_add(AstNode* root, AstNode* new){
    root -> chidrens[root -> size] = new;
    new -> father = root;
    new -> id = root -> size;
    root -> size++;
}

AstNode* astnode_find(AstNode* node, int priority){
    if(node -> father == NULL || priority == node -> priority) return node;
    while(node -> father -> priority > priority){
        if(node -> father == 0) printError("遇到意外错误无法运行!");
        node = node -> father;
    }
    return node;
}

void astnode_delete(AstNode* node, int id){
    int i;
    AstNode* p;
    for(i = id + 1;i < node -> size;i++){
        p = node -> chidrens[i];
        node -> chidrens[i - 1] = node -> chidrens[i];
        p -> id = i - 1;
    }
    node -> size--;
}

AstNode* astnode_add(AstNode* node, NodeOperator op, int priority){
    AstNode* tmp = astnode_create(op, priority);
    node = astnode_find(node, priority);
    AstNode* father;
    if(priority > node -> priority){
        astnode_chidrens_add(node, tmp);
    }else{
        father = node -> father;
        astnode_delete(node -> father, node -> id);
        astnode_chidrens_add(tmp, node);
        astnode_chidrens_add(father, tmp);
    }
    return tmp;
}

AstNode* astnode_add_value(AstNode* node, int val){
    AstNode* tmp = astnode_create(OP_VAL, PRIORITY_VAL);
    tmp -> value.value = val;
    astnode_chidrens_add(node, tmp);
    return tmp;
}

int astnode_resolve(AstNode* node){
    NodeOperator op = node -> op;
    int i;
    if(op == OP_ADD){
        int res = 0;
        for(i = 0;i < node -> size;i++){
            res += astnode_resolve(node -> chidrens[i]);
        }
        return res;
    }
    if(op == OP_MUL){
        int res = 1;
        for(i = 0;i < node -> size;i++){
            res *= astnode_resolve(node -> chidrens[i]);
        }
        return res;
    }
    if(op == OP_SUB){
        int res = astnode_resolve(node -> chidrens[0]);
        for(i = 1;i < node -> size;i++){
            res -= astnode_resolve(node -> chidrens[i]);
        }
        return res;
    }
    if(op == OP_DIV){
        int res = astnode_resolve(node -> chidrens[0]);
        for(i = 1;i < node -> size;i++){
            res += astnode_resolve(node -> chidrens[i]);
        }
        return res;
    }
    if(op == OP_REM){
        int n1 = astnode_resolve(node -> chidrens[0]);
        int n2 = astnode_resolve(node -> chidrens[0]);
        if(n2 == 0) printError("无法将0作为取余的数!");
        return n1 % n2;
    }
    if(op == OP_POW){
        int n1 = astnode_resolve(node -> chidrens[0]);
        int n2 = astnode_resolve(node -> chidrens[0]);
        return pow(n1, n2);
    }
    if(op == OP_VAL){
        return node -> value.value;
    }
    if(op == OP_ROOT){
        return astnode_resolve(node -> chidrens[0]);
    }
}
