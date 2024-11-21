#ifndef PRIORITY_ROOT
#include "node.c"
#endif

char* getType(){
    ;
}

void printAllNode(AstNode* root){
    printf("Node: %d\n", root -> op);
    if(root -> size == 0) return;
    printf("==[Next Floor]==\n");
    int i;
    for(i = 0;i < root -> size;i++){
        if(root -> chidrens[i] == NULL) continue;
        printAllNode(root -> chidrens[i]);
    }
}
