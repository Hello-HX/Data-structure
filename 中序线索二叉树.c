#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//利用没有用到的指针进行线索化
//自己画张图感受一下这段中序序列
//思考如何利用没有用到的指针进行线索化
//以及一些坑逼的条件，如果烦，直接全部都判断一下

typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag;//左右标签
    int rtag;
}TreeNode;

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
        (*T) -> ltag = 0;//标签初始化
        (*T) -> rtag = 0;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

//中序线索化
//因为要用用遍历整个树，且要改掉其指针的值，所以用二级指针
void inThreadTree(TreeNode* T, TreeNode** pre) {
    if (T) {//非空才执行
        inThreadTree(T->lchild, pre);//左子树边界条件
        //do something
        if(T->lchild == NULL) {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if(*pre != NULL && (*pre) -> rchild == NULL) {
            (*pre) -> rtag = 1;
            (*pre) -> rchild = T;
        }
        //pre是前继，代表上一次访问过的节点，保留下来。
        *pre = T;//pre不会是空的，我条件限制不访问到空
        inThreadTree(T->rchild,pre);//右子树，递归一样的逻辑
    }
}

TreeNode* getFirst(TreeNode* T) {
    while(T->ltag == 0) {
        T = T -> lchild;
    }
    //找到一个左标签非0的就是了，左边递进
    return T;
}

TreeNode* getNext(TreeNode* node) {
    if (node -> rtag == 1) return node->rchild;
    else return getFirst(node -> rchild); //，没有右标签，则访问右子树，找到一个first
}



int main( ) {
    TreeNode* T;

    TreeNode* pre = NULL;

    int index = 0;
    createTree(&T, "ABD##E##C##", &index);
    
    //最后一个自己手动操作
    inThreadTree(T, &pre);
    pre ->rtag = 1;
    pre ->rchild = NULL;
    
    //for还可以这样用的！！！！
    for (TreeNode* node = getFirst(T); node != NULL; node = getNext(node)) {
        printf("%c", node -> data);
    }
    printf("\n");
    return 0;
}