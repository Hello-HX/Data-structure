#include<stdio.h>
#include<stdlib.h>

#define NUM 5

//哈希表结构
typedef struct HashList {
    int num;//当前数量
    char* data;//数据域
}HashList;

//初始化哈希表
HashList* initList() {
    HashList* list = (HashList*)malloc(sizeof(HashList));
    list->num = 0;
    list ->data = (char*)malloc(sizeof(char)*NUM);
    for (int i = 0; i<NUM; i++) {
        list->data[i] = 0;
    }
    return list;
}

//哈希函数，线性法
int hash(int data) {
    return data % NUM;
}

//哈希填入
void put(HashList* list,char data) {
    int index = hash(data);
    if(list->data[index] != 0) {
        int count = 1;
        //处理冲突
        while(list -> data[index] != 0) {
            //线性处理哈希冲突，(hash-data + count 再次哈希)
            index = hash(hash(data)+count);
            count++;
        }
    }
    list->data[index] = data;
    list->num++;
}

int main() {
    //建一个哈希表并初始化，指向结构体的指针
    HashList* list = initList();
    put(list, 'A');
    put(list, 'F');
    printf("%c\n",list -> data[0]);
    printf("%c\n",list -> data[1]);
    return 0;

}