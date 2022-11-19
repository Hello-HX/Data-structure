#include <stdio.h>
#include <stdlib.h>

//链表基础上改为尾插法就可以实现简单的队列

//队列前面有一个节点当头节点使用
//其data用来存当前的结点数
///难点实现，尾插法
//双向队列就改为如下结构，核心差不多
/*
typedef struct Node2
{
    int data;
    struct Node2* next;
    struct Node2* pre;
}Node2;
*/

//结点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

//初始化
Node* initQueue() {
    Node* Q = (Node*)malloc(sizeof(Node));
    Q->data = 0;
    Q->next = NULL;
    return Q;
}

//判断是否为空队列
int isEmpty(Node* Q) {
    if (Q->next == NULL ) {
        return 1;
    } else {
        return 0;
    }
}

//出队列
int deQueue(Node* Q) {
    if (isEmpty(Q)) {
        return 0;
    } else {
        Node* node = Q->next;
        int data = node->data;
        Q->next = Q->next->next;
        Q->data --;
        free(node);//要在完成所有结点操作后才删除，否则会断连接
        return data;
    }
}

//入队
void enQueue(Node* Q, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    Node* p = Q;
    while(p->next != NULL) {
        p = p->next;
    }
    p -> next = node;
    Q->data++;
}

//打印队列
void printQueue(Node* Q) {
    Node* node = Q -> next;
    while (node != NULL) {
        printf("%d -> ", node -> data);
        node = node -> next;
    }
    printf("NULL\n");
}

//主函数
int main() {
    Node* Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    printf("dequeue = %d\n", deQueue(Q));
    printf("dequeue = %d\n", deQueue(Q));
    printQueue(Q);
    return 0;
}