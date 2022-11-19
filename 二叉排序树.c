#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;


TreeNode* bstSearch(TreeNode* T, int data) {
    if(T) {
        if(T->data == data) return T;
        else if (data < T -> data) return bstSearch(T -> lchild, data);
        else if (data > T -> data) return bstSearch(T -> rchild, data);
    }
    else return NULL;
}

//其实就是在原来的基础上，有方向的进行遍历
void bstInsert(TreeNode** T, int data) {
    //找到了，分配，插入
    if(*T == NULL) {
        (*T) = (TreeNode*)malloc(sizeof(TreeNode));//二级所指的指针在这里修改了
        (*T)->data = data;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    }
    else if(data == (*T) -> data) {
        return ; //结束
    }
    else if(data < (*T) -> data) {
        bstInsert(&((*T)-> lchild), data);
    }
    else {
        bstInsert(&((*T) -> rchild), data);
    }
}


void preOrder(TreeNode* T) {
    if (T) {
        printf("%d ", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

int main() {
    TreeNode* T = NULL;
    int nums[6] = {8, 6, 10, 9, 11, 23};
    for (int i = 0; i < 6; i++) {
        bstInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
}