#include <stdio.h>
#include <stdlib.h>

//没有什么难的，就是一个个对比

/*
//平均查找长度 累加PiCi (P为概率，C为长度)
//定义大数组
typedef struct List {
    int* data;
    int length;
    int num;
}List;

List* initList(int length) {
    List* list = (List*)malloc(sizeof(List));
    list -> length = length;
    list -> data = (int*)malloc(sizeof(int) * length);
    list -> num = 0;
    return list;
}

void listAdd(List* list, int data) {
    list -> data[list -> num] = data;
    list -> num = (list -> num) + 1;
}

void printList(List* list) {
    for (int i = 0; i < list -> num; i++) {
        printf("%d -> ", list -> data[i]);
    }
    printf("NULL\n");
}

//顺序就是一个个对比嘛
int search(List* list, int key) {
    //for里的越界也是一次操作
    for (int i = 0; i < list ->num; i++) {
        if (list->data[i] == key) return i;
    }
    return -1;
}

int main()
{
    List* list = initList(5);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    printList(list);
    printf("%d\n", search(list, 3));
    return 0;
}

*/

//带哨兵的操作，减少判断操作，不用判断越界，数据大有用
//从最后一个开始遍历
//牺牲第一个元素，什么都不干。

typedef struct List
{
    int *data;
    int length;
    int num;
} List;

List *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->length = length;
    list->data = (int *)malloc(sizeof(int) * (length + 1));
    list->num = 1;
    return list;
}

void listAdd(List *list, int data)
{
    list->data[list->num] = data;
    list->num++;
}

void printList(List *list)
{
    for (int i = 1; i < list->num; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

//哨兵优化
int search(List *list, int key)
{
    int i;
    list->data[0] = key;
    //注意这样不用在中间判断是否越界！！！！
    for (i = (list->num) - 1; list->data[i] != key; i--)
        ;
    return i;
}

int main()
{
    List *list = initList(5);
    listAdd(list, 4);
    listAdd(list, 5);
    listAdd(list, 6);
    listAdd(list, 7);
    printList(list);
    printf("%d\n", search(list, 8));
    return 0;
}
