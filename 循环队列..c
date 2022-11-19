#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

//循环队列的关键在于如何计算好这些下角标
//循环队列用数组来实现，因为方便，刚好构成一圈


//define the struct of circular queue
typedef struct Queue {
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

//初始化队列
Queue* initQueue() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}

//打印队列
void printQueue(Queue* Q) {
    // 要知道队列当前有多少个元素
    int length = (Q->rear - Q->front + MAXSIZE) % MAXSIZE;//这里是关键
    int index = Q->front;
    for (int i = 0; i < length; i++) {
        printf("%d -> ", Q->data[index]);
        index = (index + 1) % MAXSIZE;//也是关键
    }
    printf("NULL\n");
}

//judge queue is or not full
int isFull(Queue* Q) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return 1;
    } else {
        return 0;
    }
}

//judge queue is or not empty
int isEmpty(Queue* Q) {
    if (Q->front == Q->rear) {
        return 1;
    } else {
        return 0;
    }
}

//入队
int enQueue(Queue* Q, int data) {
    if (isFull(Q)) {
        return 0;
    } else {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    }
}

//出队
int deQueue(Queue* Q) {
    if (isEmpty(Q)) {
        return -1;
    } else {
        int data = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return data;
    }
}

//主函数
int main() {
    Queue* Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    deQueue(Q);
    printQueue(Q);
    return 0;
}