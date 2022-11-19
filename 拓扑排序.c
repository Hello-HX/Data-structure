#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* initStack() {
    //malloc是在堆上自己动态分配内存
    //所谓的释放，是变量名，内存地址依旧在
    Node* stack = (Node*)malloc(sizeof(Node));
    stack->data = 0;
    stack->next = NULL;
    return stack;
}

int isEmpty(Node* stack) {
    if(stack ->next == NULL) {
        return 1;
    }
    else return 0;
}

void push(Node* stack, int data) {
    Node * node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack->next;
    stack -> next = node;
    stack -> data++;
}

int pop(Node* stack) {
    if(isEmpty(stack)) return -1;
    else {
        Node* node = stack -> next;
        int data = node->data;
        stack->next = node->next;
        free(node);
        stack->data--;
        return data;
    }
}

//初始化入度数组
int* findInDegrees(Graph* G) {
    int* inDegrees = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0; i < G->vexNum; i++) {
        inDegrees[i] = 0;
    }
    for (int i = 0; i < G->vexNum; i++) {
        for(int j = 0; j < G->vexNum; j++) {
            if(G->arcs[i][j]) inDegrees[j] = inDegrees[j] + 1;
        }
    }
    return inDegrees;
}

//DAG，AOV 任务流程

//拓扑排序
//找入度为0的点，剪掉，继续，再剪
//直到最终的拓扑数组中看看是所有顶点都进去，如果有，就是有向无环图
//否则就不是
void topologicalSort(Graph* G) {
    int index = 0;
    //用来存拓扑数组
    int* top = (int*)malloc(sizeof(int)*G->vexNum);
    //用来存入度
    int* inDegrees = findInDegrees(G);
    //用栈来压，保证不用每一次都去扫入度为0的点
    Node* stack = initStack();
    for(int i = 0; i < G->vexNum; i++) {
        if(inDegrees[i] == 0) push(stack,i);
    }
    while (!isEmpty(stack))
    {
        int vex = pop(stack);
        top[index++]=vex;
        //减掉边，并且把入度为0的点赛进去
        for(int i = 0;  i < G->vexNum; i++) {
            if(G->arcs[vex][i]) {//有边，剪掉了，减一
                inDegrees[i] = inDegrees[i] -1;
                if(inDegrees[i] == 0) push(stack,i);
            }
        }
    }
    for(int i = 0; i < G->vexNum; i++) {
        printf("%c ",G->vexs[top[i]]);
    }
    printf("\n");  
}

Graph* initGraph(int vexNum) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G -> vexs = (char*)malloc(sizeof(char) * vexNum);
    G -> arcs = (int**)malloc(sizeof(int*) * vexNum);
    for (int i = 0 ; i < vexNum; i++) {
        G -> arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
    return G;
}

void createGraph(Graph* G, char* vexs, int* arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0)
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

// 有向无环图不一定能遍历完所有节点
void DFS(Graph* G, int* visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] == 1  && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
        0,1,1,1,0,0,
        0,0,0,0,0,0,
        0,1,0,0,1,0,
        0,0,0,0,1,0,
        0,0,0,0,0,0,
        0,0,0,1,1,0
    };
    createGraph(G, "123456", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    topologicalSort(G);
    return 0;
}