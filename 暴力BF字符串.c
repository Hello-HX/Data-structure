#include<stdio.h>
#include<stdlib.h>

//什么高大上的东西，就是一个个暴力匹配的无脑算法

typedef struct String
{
    char* data;
    int len;
}String;


String* initString() {
    String* s = (String*)malloc(sizeof(String));
    s->data = NULL;
    s->len = 0;
    return s;
}

//字符串初始化
void stringAssign(String* s,char* data)
{
    //如果原来字符串中有字符，直接清掉
    if (s->data) {
        free(s->data);
    }
    int len = 0;
    char* temp = data;
    //统计长度，巧用指针
    while(*temp) {
        len++;
        temp++;
    }
    if (len == 0) {
        s->data = NULL;
        s->len = 0;
    }
    else {
        temp = data;
        s->len = len;
        //要多一个位置用来截止'\0'
        s->data = (char*)malloc(sizeof(char)*(len+1));
        for (int i = 0; i < len; i++,temp++) {
            s->data[i] = *temp; //指针妙啊
        }
    }
}

void printString(String* s) {
    for (int i = 0; i < s->len; i++) {
        printf(i == 0 ? "%c" : "->%c",s->data[i]);//还可以这么搞！！！
    }
    printf("\n");
}


void forceMatch(String* master, String* sub) {
    int i = 0;
    int j = 0;
    while(i < master -> len && j <sub->len) {
        if(master -> data[i] == sub -> data[j]) {
            i++; j++;
        }
        else {
            //回退且进一
            i = i -j+1;
            j = 0;
        }
    }
    if (j == sub -> len) {
        printf("force match success.\n");
    }
    else printf("force match fail.\n");
}



int main() {
    String* s = initString();
    String* s1 = initString();
    stringAssign(s,"abcdef");
    stringAssign(s1,"cde");
    printString(s);
    printString(s1);
    forceMatch(s,s1);
    return 0;
}