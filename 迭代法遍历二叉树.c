#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef struct StackNode {
    TreeNode* data;
    struct StackNode* next;
}StackNode;

void createTree(TreeNode** T, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        // 此时为空节点
        *T = NULL;
    }
    else {
        // 此时不为空
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = ch;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

StackNode* initStack() {
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

void push(TreeNode* data, StackNode* S) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

int isEmpty(StackNode* S) {
    if (S->next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

TreeNode* pop(StackNode* S) {
    if (isEmpty(S)) {
        return NULL;
    }
    else {
        StackNode* node = S->next;
        S->next = node->next;
        TreeNode* T = node->data;
        free(node);
        return T;
    }
}

//记得一开始得把节点塞进去
//对中间节点进行标记

void preOrder(TreeNode* T) {
    StackNode* S = initStack();
    if(T)push(T,S);
    while(!isEmpty(S)) {
        TreeNode* node = pop(S);
        if(node) {
            if(node->rchild) push(node->rchild,S);
            if(node->lchild) push(node->lchild,S);
            push(node,S);
            push(NULL,S);
        }
        else {
            node=pop(S);
            printf("%c",node->data);
        }
    }
}

void inOrder(TreeNode* T) {
    StackNode* S = initStack();
    if(T)push(T,S);
    while(!isEmpty(S)) {
        TreeNode* node = pop(S);
        if(node) {
            if(node->rchild) push(node->rchild,S);
            push(node,S);
            push(NULL,S);
            if(node->lchild) push(node->lchild,S);
        }
        else {
            node=pop(S);
            printf("%c",node->data);
        }
    }
}

void postOrder(TreeNode* T) {
    StackNode* S = initStack();
    if(T)push(T,S); 
    while(!isEmpty(S)) {
        TreeNode* node = pop(S);
        if(node) {
            push(node,S);
            push(NULL,S);
            if(node->rchild) push(node->rchild,S);
            if(node->lchild) push(node->lchild,S);
        }
        else {
            node=pop(S);
            printf("%c",node->data);
        }
    }
}

int main( ) {
    TreeNode* T;
    int index = 0;
    char data[7]={'A','B','#','#','C','#','#'};
    createTree(&T, data, &index);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    postOrder(T);
    printf("\n");
    return 0;
}