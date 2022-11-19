#include <stdio.h>
#include <stdlib.h>
#define MAX 65535

/*顶点是事件
  弧段是活动
  最早求工期
  然后逆向求不拖延工期的情况下的最晚
  对比时间余量
  余量为0说明是关键活动，
  行程安排得满当，要想提升效率，得从这里下手*/

//关键路径思路
//拓扑排序
//求事件指标 
//顺推过去，逆推回来
//x是i的前驱节点
/*事件最早开始时间，Vi(e) = MAX{Vx(e) + weight(x,i)} 选择最大的*/
//x是i的后继节点
/*事件最晚开始时间，Vx(l) = MIN{Vxi(e) - weight(i,x)} 选择最小的*/
//求活动指标
/*活动最早开始时间，li(e) = Vstart(e)*/
/*活动最晚开始时间，li(l) = Vend(l) - weight*/
//求时间余量
/*l(l) - l(e) = 0,再是关键活动，安排得满满的*/


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
    Node* stack = (Node*)malloc(sizeof(Node));
    stack -> data = 0;
    stack -> next = NULL;
    return stack;
}

int isEmpty(Node* stack) {
    if (stack -> next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(Node* stack, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack -> next;
    stack -> next = node;
    stack -> data ++;
}

int pop(Node* stack) {
    if (!isEmpty(stack)) {
        Node* node = stack -> next;
        stack -> next = node -> next;
        return node -> data;
    }
    else {
        return -1;
    }
}

//进行拓扑排序
int* findInDegrees(Graph* G) {
    int* inDegress = (int*)malloc(sizeof(int)*G->vexNum);
    //记得初始化数组！！！！！！！！！！！2
    for(int i = 0; i<G->vexNum; i++) {
        inDegress[i] = 0;
    }
    for (int i = 0; i < G->vexNum; i++) {
        for (int j = 0; j < G->vexNum; j++) {
            if(G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
               inDegress[j] = inDegress[j] + 1;
        }
    } 
    return inDegress;
}

int* topologicalSort(Graph* G) {  
    int index = 0;
    int* top = (int*)malloc(sizeof(int)*G->vexNum);
    int* inDegress = findInDegrees(G);
    Node* stack = initStack();
    for (int i = 0; i < G->vexNum; i++) {
        if(inDegress[i]==0) push(stack,i);
    }
    while(!isEmpty(stack)) {
        int vex = pop(stack);
        top[index++] = vex;
        for (int i = 0; i < G->vexNum; i++) {
            if(G->arcs[vex][i] > 0 && G->arcs[vex][i] != MAX) {
                inDegress[i] = inDegress[i] - 1;
                if(inDegress[i] == 0) push(stack,i);
            }
        }
    }
    for (int i = 0; i < index; i++) {
        printf("%c ",G->vexs[top[i]]);
    }
    printf("\n");
    return top;
}


//获取拓扑序列的指标
int getIndex(int* top,Graph* G, int i) {
    int j = 0;
    for(j = 0; j < G->vexNum; j++) {
        if(top[j] == i) return j;
    }
}

/*流程 
  获得拓扑序列
  计算事件最早指标
  逆向计算事件最晚指标
  计算活动指标
  计算时间余量 */



//求事件指标和活动指标

void criticalPath(Graph* G) {
    int* top = topologicalSort(G);
    int* early = (int*)malloc(sizeof(int)*G->vexNum);
    int* late = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0; i < G->vexNum; i++) {
        early[i] = 0;
        late[i] = 0;
    }
    //计算事件最早发生时间
    //i是目标顶点，j是到i的前继续
    //记得获得拓扑序列的索引进行访问
    for (int i = 0; i < G->vexNum; i++) {
        int max = 0;
        for (int j = 0; j < G->vexNum; j++) {
            //动态规划思想，注意是取top[i];
            if(G->arcs[j][top[i]] > 0 && G->arcs[j][top[i]] != MAX) {
                int index = getIndex(top, G, j);
                if (early[index] + G->arcs[j][top[i]] >max)
                    max = early[index] + G ->arcs[j][top[i]];
            }
        }
        early[i] = max;
    }
    for (int i = 0; i < G->vexNum; i++) {
        printf("%d ",early[i]);
    }
    printf("\n"); 
    //计算活动最晚发生事件
    //最后一个不用，工期已经内定了
    //i依旧是j的前继续
    late[(G->vexNum)- 1] = early[(G->vexNum) - 1];
    for (int i = (G->vexNum) -2 ; i >= 0; i--) {//从-2的位置开始
        int min = MAX;
        for(int j = 0; j < G->vexNum; j++) {
            if(G->arcs[top[i]][j] > 0 && G->arcs[top[i]][j] != MAX) {
                int index = getIndex(top, G, j);//获得前节点在拓扑序列的位置
                if(late[index] - G->arcs[top[i]][j] < min) {
                    min = late[index] - G->arcs[top[i]][j];
                }
            }
        }
        late[i] = min;
    }
    for (int i = 0; i < G->vexNum; i++) {
        printf("%d ",late[i]);
    }
    printf("\n"); 
    //计算活动指标并计算时间余量，直接穷举图就欧克
    //有边就可以算时间余量，注意要访问获取拓扑索引才能获得正确的指标
    for(int i = 0; i < G->vexNum; i++) {
        for (int j = 0; j < G->vexNum; j++) {
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != MAX) {
                //获取索引，记得获取索引！！！！
                int start = getIndex(top, G, i);
                int end = getIndex(top,G,j);
                //把计算事件指标混在里面了
                if((late[end] - G->arcs[i][j]) - early[start] == 0) {
                    printf("start = %d end = %d\n",i,j);
                }
            }
        }
    }
}


void createGraph(Graph* G, char* vexs, int* arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] > 0 && G -> arcs[i][j] != MAX)
                G -> arcNum ++;
        }
    }
}

void DFS(Graph* G, int* visited, int index) {
    printf("%c ", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G, visited, i);
        }
    }
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


int main() {
    Graph* G = initGraph(9);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[9][9] = {
        0, 6, 4, 5, MAX, MAX, MAX, MAX, MAX,
        MAX, 0, MAX, MAX, 1, MAX, MAX, MAX, MAX,
        MAX, MAX, 0, MAX, 1, MAX, MAX, MAX, MAX,
        MAX, MAX, MAX, 0, MAX, 2, MAX, MAX, MAX,
        MAX, MAX, MAX, MAX, 0, MAX, 9, 7, MAX,
        MAX, MAX, MAX, MAX, MAX, 0, MAX, 4, MAX,
        MAX, MAX, MAX, MAX, MAX, MAX, 0, MAX, 2,
        MAX, MAX, MAX, MAX, MAX, MAX, MAX, 0, 4,
        MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX, 0
    };
    createGraph(G, "012345678", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    criticalPath(G);
    return 0;
}