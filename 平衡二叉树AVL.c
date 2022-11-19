#include<stdio.h>
#include<stdlib.h>

//树的结点结构
typedef struct TreeNode {
    int data;
    int height;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

void preOrder(TreeNode* T);
int max(int a, int b);
int getHeight(TreeNode* node);
//创建，修改调整需要改变指针的值，所以要用二级指针
void rrRotation(TreeNode* node, TreeNode** root);
void llRotation(TreeNode* node, TreeNode** root);
void avlInsert(TreeNode** T, int data);

//前序打印
void preOrder(TreeNode* T) {
    if(T) {
        printf("%d ", T->data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

//求最大最小
int max(int a, int b) {
    return a > b ? a:b;
}

//左旋转
void llRotation(TreeNode* node,TreeNode **root) {
    TreeNode* temp = node -> lchild;//左孩子，中间点
    //注意切割的顺序，优先对父亲结点进行操作

    node -> lchild = temp -> rchild;
    //父亲的左孩子为中间结点的右孩子
    temp -> rchild = node;
    //中间结点的右孩子为原来的父亲结点

    //注意先后顺序，自顶向下，子树再调整过程中是没有影响高度的
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) +1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) +1;

    *root = temp;
    //把root指针指向的地址改了，也就是为什么要用二级指针对的原因
}

//右旋转
void rrRotation(TreeNode* node,TreeNode **root) {
    TreeNode* temp = node -> rchild;//右孩子，中间点
    //注意切割的顺序，优先对父亲结点进行操作

    node -> rchild = temp -> lchild;
    //父亲的右孩子为中间结点的左孩子
    temp -> lchild = node;
    //中间结点的左孩子为原来的父亲结点

    //注意先后顺序，自顶向下，子树再调整过程中是没有影响高度的
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) +1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) +1;

    *root = temp;
    //把root指针指向的地址改了，也就是为什么要用二级指针对的原因
}

//获取当前的高度
int getHeight(TreeNode *node) {
    return node? node -> height : 0;
}

//进入平衡树的创建
void avlInsert(TreeNode** T, int data) {//传入二级指针才可以改变一级指针所存的地址
    if(*T == NULL) {
        //空结点，找到头了，对其进行创建
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = data;
        (*T) -> height = 0;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    }
    else if(data < (*T) -> data) {//在左边进行搜索
        avlInsert(&(*T) -> lchild, data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        //判断高度差
        if (lHeight - rHeight == 2) {//左边失衡
            if (data < (*T) -> lchild -> data) {
                //LL调整
                llRotation(*T, T);
            }
            else {
            //LR调整
            rrRotation((*T) -> lchild,&(*T) -> lchild);
            llRotation(*T, T);
            }
        }
    }
    else if (data > (*T) -> data ) {//在右边进行搜索
        avlInsert(&(*T) -> rchild, data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        if (rHeight - lHeight == 2) {//右边失衡
            if (data > (*T) -> rchild -> data) {
                //RR调整
                rrRotation(*T, T);
            }
            else {
                //RL调整
                llRotation((*T) -> rchild, &(*T) -> rchild);
                rrRotation(*T, T);
            }
        }
    }
    //回溯进行高度计算
    (*T) -> height = max(getHeight((*T) -> lchild),getHeight((*T) -> rchild)) +1; //回溯算法，对高度进行计算
}

//主函数
int main() {
    TreeNode* T = NULL;
    int RLnums[5] = {1, 8, 6, 7, 10};//要构建的平衡二叉树序列
    int RRnums[5] = {1, 2, 3, 4, 5};
    int LRnums[5] = {8, 7, 9, 5, 6};
    int LLnums[5] = {5, 4, 3, 2, 1};
    for (int i = 0; i < 5; i++) {
        avlInsert(&T, LLnums[i]);//插入
    }
    preOrder(T);//前序打印
    printf("\n平衡树创建成功！！！");
    return 0;
}