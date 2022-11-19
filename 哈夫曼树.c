#include<stdio.h>
#include<stdlib.h>

//哈夫曼树就是让整个树合起来权值最小
//有点类似编码
//把出现最小的丢在树底，高的方在上面就好了，这样是最优的
//有点碰碰的思想
//只要每次从里面选最小的，一碰，就欧克，再赛回去，直到完成


//顺序存储，大数组
typedef struct TreeNode {
    int weight;
    int parent;//要有一个parent
    int lchild;
    int rchild;
}TreeNode;

typedef struct HFTree {
    TreeNode* data;
    int length;//节点数,2*length-1个
}HFTree;

HFTree* initTree(int* weight, int length) {
    //第一步肯定是开空间
    HFTree* T = (HFTree*) malloc(sizeof(HFTree));
    T -> data = (TreeNode*)malloc(sizeof(TreeNode)*(2*length-1)); //最终长度，归约
    T -> length = length;
    for (int i = 0; i < length; i++) {
        //结构体数组是点的！！！
        T -> data[i].weight = weight[i];
        T -> data[i].parent = 0;
        T -> data[i].lchild = -1;
        T -> data[i].rchild = -1; 
    }
    return T;
}

//从里面选择两个小的
int* selectMin(HFTree* T) {
    int min = 10000;
    int secondMin = 10000;
    int minIndex = 0;
    int secondIndex = 0;
    //在length前面选
    for (int i = 0; i < T->length; i++) {
        if(T->data[i].parent == 0) {
            if(T->data[i].weight< min) {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < T->length; i++) {
        if(T -> data[i].parent == 0) {
            if(T->data[i].weight < secondMin && i != minIndex) { //记得这里的下角标
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int)*2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree* T) {
    int* res;
    int min;
    int secondMin;
    //记得算好length的长度，长度为2n-1；
    int length = T -> length * 2 - 1;
    for (int i = T->length; i< length; i++) { //从T->length开始算;
        res = selectMin(T);
        min = res[0];
        secondMin = res[1];
        T -> data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T -> data[i].lchild = min;
        T -> data[i].rchild = secondMin;
        T -> data[i].parent = 0;
        T -> data[min].parent = i;
        T -> data[secondMin].parent = i;
        T -> length ++; 
    }
}

void preOrder(HFTree* T, int index) {
    if(index != -1) {
        printf("%d ", T->data[index].weight);
        preOrder(T, T->data[index].lchild);
        preOrder(T, T->data[index].rchild);
    }
}

int main() {
    int weight[7] = {5, 1, 3, 6, 11, 2, 4};
    HFTree* T = initTree(weight, 7);
    createHFTree(T);
    preOrder(T, T -> length - 1); //从开始合并的
    printf("\n");
    return 0;
}