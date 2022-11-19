//MST 性质
//选边，最小权值边必在
//连通分量

#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

// 连通记录数组，难点
typedef struct Edge {
    int start;
    int end;
    int weight;
}Edge;

//初始化连通数组
Edge* initEdge(Graph* G) {
    int index = 0;
    Edge* edge = (Edge*)malloc(sizeof(Edge)*G->arcNum);
    //直接对角线矩阵截半保存，学到了
    //关键点
    for (int i = 0; i < G->vexNum; i++) {//行数
        for (int j = i+1; j<G->vexNum; j++) {//截取位置
            if(G->arcs[i][j] != MAX) {
                edge[index].start = i;
                edge[index].end =j;
                edge[index].weight = G->arcs[i][j];
                index++;
            }
        }
    }
    return edge;
}

//冒泡排序
//因为我要从里面选择最小边，所以要对edge数组进行排序
void sortEdge(Edge* edge, Graph* G) {
    Edge temp;
    for (int i = 0; i < G -> arcNum-1; i++ ) {
        for (int j = 0; j < G->arcNum-1-i; i++ ) {
            if(edge[j].weight > edge[j+1].weight) {
                temp = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = temp;
            }
        }
    }
}

//克鲁斯卡算法
/*思路
  构建连通边的数组
  对连通边的数组进行排序
  构建最小分量数组
  选择连通边数组，依旧是否构建成为环进行执行判断
  如果可以选择，打印并且再次遍历修改最小分量数组
   */
void kruskal(Graph* G) {

    //用来判断所选内容是否构成了一个环
    //最小连通分量记录，一开始都为自己
    int * connected = (int*)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; i++) {
        connected[i] = i;
    }

    Edge* edge = initEdge(G);
    sortEdge(edge,G);

    for (int i = 0; i < G-> vexNum; i++) {
        //用edge取出索引
        int start = connected[edge[i].start];
        int end = connected[edge[i].end];
        
        //没有构成环
        //访问G坐标不能用start和end，因为这里是连通分量的起始
        if(start != end) {
            //可以选择的
            printf("v%c --> v%c weight = %d\n",G->vexs[edge[i].start],
            G->vexs[edge[i].end],edge[i].weight);
            //遍历连通数组，
            for(int j = 0; j < G->vexNum; j++) {
                //连通标记，终点相同，则指为同一个祖宗
                if(connected[j] == end) {
                   connected[j] ==start;
                }
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
            //更改数边的条件
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX)
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

//深度遍历图
void DFS(Graph* G, int* visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            //更改遍历的条件
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
    kruskal(G);
    return 0;
}