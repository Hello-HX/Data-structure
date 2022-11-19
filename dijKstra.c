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

//单源最短路径
//从一个点开始，四射，选min出来，再四射，这样就能把一个点到其他点的min求出来

//分治加贪心，局部最优解到达全局最优解，不走回头路
// S 记录是否求得到目标顶点的最短路径 -- 除了开始其他都是0
// P 记录目标顶点到其他顶点最短路径的前驱顶点 -- 自己
// D 记录了目标顶点到其他顶点的最短路径长度 --开始0，其他MAX
//初始化，选n-1次，第一个不用选
//无边无穷大，自己则赋值为0

//思路就是每一次循环寻找出一个最小节点，并进行标记，然后再用这个最小节点去遍历保证其他点min，然后再选出最小的，继续来，不能回头

int getMin(int* d, int*s, Graph* G)
{
    int min = MAX;
    int index;
    for (int i = 0; i < G->vexNum; i++) {
        //还没有求得且是最小的
        if(!s[i] && d[i] < min) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(Graph* G, int index) {
    int* s = (int*)malloc(sizeof(int)* G->vexNum);
    int* p = (int*)malloc(sizeof(int)* G->vexNum);
    int* d = (int*)malloc(sizeof(int)* G->vexNum);

    //初始化,三个合并了，也可以分开，多到少逻辑合并
    for(int i = 0; i < G->vexNum; i++) {
        if(G->arcs[index][i]!=MAX && G->arcs[index]>0) {
            d[i] = G->arcs[index][i];
            p[i] = index;
        }
        else{
            d[i] = MAX;
            p[i] = -1;//NULL
        }
        if(i == index) {
            s[i] = 1;
            d[i] = 0;
        }
        else s[i] = 0;
    }
    //run count == vexNUm-1;少了一个起始点
    for(int i = 0; i < G->vexNum-1; i++) {
        int index = getMin(d,s,G);
        s[index] = 1;
        for(int j = 0; j < G->vexNum; j++) {
            //去更新dijkstra图
            if( !s[j] && G->arcs[index][j] + d[index] < d[j])
            {
                d[j] = G->arcs[index][j] + d[index];
                p[j] = index ;
            }
        }
    }

    for (int i = 0 ; i < G ->vexNum; i++) {
        printf("%d %d %d\n",s[i],p[i],d[i]);
    }
}



int main() {
    Graph* G = initGraph(7);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[7][7] = {
        0, 12, MAX, MAX, MAX, 16, 14,
        12, 0, 10, MAX, MAX, 7, MAX,
        MAX, 10, 0, 3, 5, 6, MAX,
        MAX, MAX, 3, 0, 4, MAX, MAX,
        MAX, MAX, 5, 4, 0, 2, 8,
        16, 7, 6, MAX, 2, 0, 9,
        14, MAX, MAX, MAX, 8, 9, 0
    };
    createGraph(G, "1234567", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    dijkstra(G, 0);
    return 0;
}