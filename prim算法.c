#include <stdio.h>
#include <stdlib.h>
//prime：找点法，从小到大，由MST性质，权值最小必在里面，UV集合
#define MAX  32767
/**
 * 图顶点之前不通，那么邻接矩阵的值为MAX
 * 如果顶点是自己本身，那么值为0
 */

//带权重的图，加些数字进去
typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

//我定义的U集合
typedef struct Edge{
    char vex;//记录U集合到最小边的起始节点
    int weight;//记录最小边
}Edge;

/**
 * 当edge.weight = 0时，代表顶点加入到U集合中
 */ 


//实现prime
/*
记录当前U集合状态
选择最小边以及顶点加入到U集合中
*/

//当weight为0的时候，代表顶点加入到U集合中
//和一开始定义有权图时关联起来了
//初始化，把选择的起点全部拷贝进来，而这个时候如果是0，就是起点本身了
Edge* initEdge(Graph* G, int index) {
    //开辟一个U集合数组
    //用一维的点访问来滚动维护整个算法
    Edge* edge = (Edge*)malloc(sizeof(Edge)*G->vexNum);
    for (int i = 0; i < G->vexNum; i++) {
        edge[i].vex = G->vexs[index];
        edge[i].weight = G->arcs[index][i];//最小的边的权值
    }
    return edge;
}


int getMinEdge(Edge* edge, Graph* G) {
    int index;
    int min = MAX;
    //去遍历节点，寻找当前的最小边
    for (int i = 0; i < G->vexNum; i++) {
        //不是结点本身且小的边
        //每个index角标是和Graph图的点是对应起来的
        if(edge[i].weight != 0 && min > edge[i].weight) {
            min = edge[i].weight;
            index = i;
        }
    }
    return index;
}


void prim(Graph* G, int index) {
    int min;
    Edge* edge = initEdge(G, index);//用索引点初始化图
    for (int i = 0; i<G->vexNum-1;i++) {//还有G->vexNum-1个点没有访问过
        //min也是一个点的坐标，用G可以得到
        min = getMinEdge(edge,G);//获得最小的边
        printf("v%c-->v%c,weight = %d\n",edge[min].vex,G->vexs[min],edge[min].weight);//节点是什么我用G来显示
        edge[min].weight = 0;//这个点访问过了，踩掉
        
        //权值更新，从一开始的索引开始，由从权值小到大，一层层去更新，直到全部踩为0
        for (int j = 0; j < G ->vexNum; j++) {
            if(G->arcs[min][j] < edge[j].weight) { //规避0的问题了，如果有小的，覆盖掉大的
                edge[j].weight = G->arcs[min][j];
                edge[j].vex = G -> vexs[min];
                //没有更新的后面还可以选
            }
        }
    }
}


//初始化图
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

//创建图
void createGraph(Graph* G, char* vexs, int* arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX)  //算边的时候加条件
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

//遍历图
void DFS(Graph* G, int* visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

//主函数
int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
        0, 6, 1, 5, MAX, MAX,
        6, 0, 5, MAX, 3, MAX,
        1, 5, 0, 5, 6, 4,
        5, MAX, 5, 0, MAX, 2,
        MAX, 3, 6, MAX, 0, 6,
        MAX, MAX, 4, 2, 6, 0
    };
    createGraph(G, "123456", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    prim(G, 0);
    return 0;
}