#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "error.c"
#include "buffer.c"
#include "token.c"
#include "node.c"
#include "expr.c"

#include "debug.c"

int main(){
    char string[64] = "3^3"; //表达式

    AstNode* root = astnode_create(OP_ROOT, PRIORITY_ROOT), *node = root;
    Buffer* buf = buffer_create();
    Token* token = token_create(string, strlen(string));
    Expr* ex = express_create();
    char ch;
    while((ch = token_read(token)) != -1){
        if(ch == ' ') continue;
        if(ch == '+'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_ADD, PRIORITY_ADD);
            continue;
        }
        if(ch == '-'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_SUB, PRIORITY_SUB);
            continue;
        }
        if(ch == '/'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_DIV, PRIORITY_DIV);
            continue;
        }
        if(ch == 'x'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_MUL, PRIORITY_MUL);
            continue;
        }
        if(ch == '%'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_REM, PRIORITY_REM);
            continue;
        }
        if(ch == '^'){
            node = astnode_add_value(node, buffer2int(buf));
            buffer_clear(buf);
            node = astnode_add(node, OP_POW, PRIORITY_POW);
            continue;
        }
        buffer_add_char(buf, ch);
    }
    if(!buffer_empty(buf)){
        astnode_add_value(node, buffer2int(buf));
        buffer_clear(buf);
    }
    //printAllNode(root);
    int value = astnode_resolve(root);
    printf("%d\n", value);
}