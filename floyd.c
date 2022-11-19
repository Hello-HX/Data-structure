#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

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
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX) 
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

void DFS(Graph* G, int* visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

//是一种动态规划的思想
//我们只关心，前后状态，中间通过递推来进行穷尽枚举
//也叫为试探法，三for法,加入中转,选出最优解 （起始 中转 结点）
//两个数组，一个用来记录权值，另一个用来记录前驱节点和连通情况
//D数组用来记录权值
//P数组用来记录前驱节点,每次中j -> i -> k,我只在乎如何可以到 i -> k;


void floyd(Graph* G) {
    //初始化数组
    int d[G->vexNum][G->vexNum];
    int p[G->vexNum][G->vexNum];
    for (int i = 0; i < G->vexNum; i++) {
        for (int j = 0; j < G->vexNum; j++) {
            d[i][j] = G->arcs[i][j];
            if(G->arcs[i][j] > 0 && G->arcs[i][j] != MAX ) {
                p[i][j] = i;//前驱节点
            }
            else {
                p[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < G -> vexNum; i++) {//枚举中间点
        for (int j = 0; j < G -> vexNum; j++) {//枚举起点
            for (int k = 0; k < G -> vexNum; k++) {//枚举终点
                if(d[j][i] + d[i][k] < d[j][k]) {
                    d[j][k] = d[j][i] + d[i][k];//选择走中转
                    p[j][k] = p[i][k]; //如何到中转
                }
            }
        }
    }
    
    //打印出来
    for (int i = 0; i < G -> vexNum; i++) {
        for (int j = 0; j < G -> vexNum; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < G -> vexNum; i++) {
        for (int j = 0; j < G -> vexNum; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}



int main() {
    Graph* G = initGraph(4);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[4][4] = {
        0, 1, MAX, 3,
        1, 0, 2, 2,
        MAX, 2, 0, 8,
        3, 2, 8, 0
    };
    createGraph(G, "1234", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    floyd(G);
    return 0;
}