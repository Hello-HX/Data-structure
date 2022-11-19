#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//---------------------------------------------------------------
//---------------------------------------------------------------
//引入队列完成层序遍历操作,记得改参数
typedef struct QueueNode {
    TreeNode* data; //改为指针，指向树的节点
    struct QueueNode* pre;
    struct QueueNode* next;
}QueueNode;

QueueNode* initQueue() {
    QueueNode* Q = (QueueNode*)malloc(sizeof(QueueNode));
    Q->data = NULL;
    Q->next = Q;
    Q->pre = Q;
    return Q;
}

void enQueue(TreeNode* data, QueueNode* Q) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = data;
    node->pre = Q;
    node->next = Q;
    Q->pre->next = node;
    Q->pre = node;
}

int isEmpty(QueueNode* Q) {
    if (Q->next == Q) {
        return 1;
    }
    else {
        return 0;
    }
}

QueueNode* deQueue(QueueNode* Q) {
    if (isEmpty(Q)) {
        return NULL;
    }
    else {
        QueueNode* node = Q->next;
        Q->next->next->pre = Q;
        Q->next = Q->next->next;
        return node;
    }
}

//----------------------------------------------------------------
//----------------------------------------------------------------

//传建过程就是遍历过程

//创建二叉树
//二级指针因为我要改掉指针所指的内容
//先序创建
void createTree(TreeNode** T, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index+=1;//索引
    if (ch == '#') {
        //此时节点为空
        *T = NULL;
    }
    else {
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = ch;
        //左右两边都是树，递归处理
        createTree(&(*T)->lchild, data, index);
        createTree(&(*T)->rchild, data, index);

    }
}

//前序遍历
void preOrder(TreeNode* T) {
    if (T == NULL) {
        return ;
    }
    else {
        printf("%c", T->data);//先办事
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

//中序遍历
void inOrder(TreeNode* T) {
    if (T == NULL) {
        return ;
    }
    else {
        preOrder(T->lchild);
        printf("%c", T->data);
        preOrder(T->rchild);
    }
}

//后序遍历
void postOrder(TreeNode* T) {
    if (T == NULL) {
        return ;
    }
    else {
        preOrder(T->rchild);
        preOrder(T->lchild);
        printf("%c", T->data);
    }
}

//层序遍历，用队列
void levelTraverse(QueueNode* Q, TreeNode* T) {
    enQueue(T, Q);
    while (!isEmpty(Q)) {
        QueueNode* node = deQueue(Q);
        printf("%c ", node->data->data);
        if (node->data->lchild) {
            enQueue(node->data->lchild, Q);
        }
        if (node->data->rchild) {
            enQueue(node->data->rchild, Q);
        }
    }
}


int main() {
    TreeNode* T;
    QueueNode* Q = initQueue();
    int index = 0;
    char data[7]={'A','B','#','#','C','#','#'};
    createTree(&T, data, &index);

    preOrder(T);
    printf("\n");

    inOrder(T);
    printf("\n");

    postOrder(T);
    printf("\n");

    levelTraverse(Q, T);
    printf("\n");
    return 0;
}