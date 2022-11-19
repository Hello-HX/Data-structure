#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* data;
    int length;
    int num;
} List;

List* initList(int length) {
    List* list = (List*)malloc(sizeof(List));
    list -> data = (int*)malloc(sizeof(int) * length);
    list -> length = length;
    list -> num = 0;
    return list;
}

void listAdd(int data, List* list) {
    list -> data[list -> num] = data;
    list -> num = list -> num + 1;
}

void printList(List* list) {
    for (int i = 0; i < list -> num; i++) {
        printf("%d ", list -> data[i]);
    }
    printf("\n");
}

//迭代写法
int binarySearch(int key, List* list) {
    int start  = 0;
    int end = list->num -1;
    int mid;
    //左右闭区间的写法
    while(start <= end) {
        mid = (start + end)/2;
        if (list->data[mid] < key) {
            start = mid+1;
        }
        else if(list->data[mid]>key) {
            end = mid -1;
        }
        else return mid;
        
    }
    return -1;
}
//递归的写法
int binarySearchRecursion(int key, List* list, int start, int end) {
    //遍历到最后一个了
    if(start == end) {
        if(list->data[start] == key) {
            return start;
        }
        else return -1; //不一定是哦，记得讨论
    }
    
    //分类
    int mid = (start + end)/2;
    if (list -> data[mid] < key) {
        return binarySearchRecursion(key, list, mid + 1, end);
    }
    else if (list -> data[mid] > key) {
        return binarySearchRecursion(key, list, start, mid - 1);
    }
    else 
        return mid;
}

int main() {
    List* list = initList(9);
    listAdd(1, list);
    listAdd(2, list);
    listAdd(3, list);
    listAdd(4, list);
    listAdd(5, list);
    listAdd(6, list);
    listAdd(7, list);
    listAdd(8, list);
    listAdd(9, list);
    printList(list);
    printf("data %d in %d\n", 7, binarySearch(7, list));//%d 不一定得要变量，这样搞给他也行的
    printf("data %d in %d\n", 10, binarySearch(10, list));
    printf("data %d in %d\n", 1, binarySearch(1, list));
    printf("data %d in %d\n", 3, binarySearch(3, list));
    printf("data %d in %d\n", 7, binarySearchRecursion(7, list, 0, list -> num - 1));
    printf("data %d in %d\n", 10, binarySearchRecursion(10, list, 0, list -> num - 1));
    printf("data %d in %d\n", 1, binarySearchRecursion(1, list, 0, list -> num - 1));
    printf("data %d in %d\n", 3, binarySearchRecursion(3, list, 0, list -> num - 1));
    return 0;
}