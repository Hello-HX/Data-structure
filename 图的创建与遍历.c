#include<stdio.h>
#include<stdlib.h>

//引入循环队列完成BFS
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



//下面是一些操作

#define MAXSIZE 5

//顶点，边数，顶点数组，边数组（邻接矩阵）
typedef struct Graph {
    char* vexs;
    int ** arcs;
    int vexNum;
    int arcNum;
}Graph;


Graph* initGraph(int vexNum) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G -> vexs = (char*)malloc(sizeof(char)* vexNum);
    G -> arcs = (int**)malloc(sizeof(int*) * vexNum);
    for (int i = 0; i < vexNum; i++) {
        G->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

void createGraph(Graph* G, char* vexs, int* arcs) {
    for (int i = 0; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            //地址漂移
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0) {
                G -> arcNum ++;
            }
        }
    }
    //除以2才是边数
    G -> arcNum /= 2;
}

//递归实现深度搜索
//标记，进入踩
void DFS(Graph* G, int* visited, int index) {
    printf("%c\t",G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; i++) {
        if (G->arcs[index][i] == 1 && !visited [i]) {
            DFS(G,visited,i);
        }
    }
}

//队列实现广度搜索
void BFS(Graph* G, int* visited, int index) {
    Node* Q = initQueue();
    enQueue(Q,index);
    visited[index] = 1;
    printf("%c\t",G->vexs[index]);
    while(!isEmpty(Q)) {
      int i = deQueue(Q);
      for (int j = 0; j < G->vexNum; j++) {
        if (G -> arcs[i][j] == 1 && !visited[j]) {
            printf("%c\t", G->vexs[j]);
            visited[j] = 1;
            enQueue(Q,j);
        }
      }
    }
}


//对标记图进行复原
void revisited(Graph* G, int * visited) {
    for (int i = 0; i < G -> vexNum; i++) {
        visited[i] = 0;
    }
}

int main() {
    Graph* G = initGraph(5);

    //这里我不开二维的数组，因为我是一个单方向的图，便利完所有节点即可
    int * visited = (int*)malloc(sizeof(int) * G->vexNum);
    revisited(G, visited);
    int arcs[5][5] = {
        0,1,1,1,0,
        1,0,1,1,1,
        1,1,0,0,0,
        1,1,0,0,1,
        0,1,0,1,0
    };
    createGraph(G, "ABCDE", (int*)arcs);//数组还可以这样搞进去的，传值嘛
    DFS(G, visited, 0);
    printf("\n");
    /*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++ ) {
            printf("%d",G->arcs[i][j]);
        }
        printf("\n");
    }
    */
    revisited(G, visited);
    BFS(G,visited,0);
    return 0;
}

