//KMP算法
//减少主串指针的移动，并且快速找到能够前后匹配的状态，从而加快匹配进程
//关键在于构建next数组
//前缀不包含最后一个
//后缀不包含前面一个
//next值等于公共前后缀的值+1
//找公共前后缀的目的在于匹配，前后缀的时候一定是能匹配的，那么这个时候要跳到plength+1
//及最长相等前后缀，也就是公共前后缀，核心关键


//初始化串
//求next数组
//kmp匹配

#include<stdio.h>
#include<stdio.h>

typedef struct String {
    char* data;
    int len;
}String;
//初始化字符串
String* initString() {
    String* s = (String*)malloc(sizeof(String));
    s->data = NULL;
    s->len = 0;
    return s;
}

//字符串赋值
void stringAssign(String* s, char* data) {
    if (s->data) {
        free(s->data);
    }
    int len = 0;
    char* temp = data;
    while(*temp) {
        len++;
        temp++;//这里已经改过temp值，后面得改回来
    }
    if (len == 0) {
        s->data = NULL;
        s->len = 0;
    }
    else {
        temp = data;
        s->data = (char*)malloc(sizeof(char)* (len+1));
        s->len = len;
        for (int i = 0; i < len; i++,temp ++) {
            s->data[i] = *temp;
        }
    }
}
//打印
void printString(String* s) {
    for (int i = 0; i < s->len; i++) {
        printf(i == 0 ?"%c":"->%c", s->data[i]);
    }
    printf("\n");
}

//思路
//匹配与回退
//递推的思路
//我




//获得next数组
int* getNext(String* s) {
    int* next = (int*)malloc(sizeof(int)*(s->len));
    next[0] = 0;//第一个位置必为0
    //我按我的思路写一遍
    int j =0;//初始的起点，注意注意
    //遍历后缀
    for (int i = 1; i < s->len; i++) {
        //不满足就回退，起点在里面 
        while( j >= 1 && s->data[i] != s->data[j]) {
            j = next[j-1]; //访问前面的
        }
        if ( s->data[i] == s->data[j]) j++;
        next[i] = j;//直接就是这个值，因为0开始数的 j-1+1；
    }
    return next;
}

//打印next数组
void printNext(int* next, String* s){
    for (int i = 0; i < s->len; i++) {
        printf("%d", next[i]);
    }
    printf("\n");
}

//返回起始坐标
int kmpMatch(String* master, String * needle,int* next) {
    if (needle -> len == 0) return 0;
    int j = 0;//注意j是模式串的 
    for (int i = 0 ; i < master -> len; i++) {
        //回退
        while(j >= 1 && master->data[i] != needle->data[j]) {
            j = next[j-1];
        }
        if(needle->data[j] == master->data[i]) j++; //可以匹配
        if(j==needle->len) return (i - (needle->len) + 1); //可行解
    } 
    return -1;
}


int main() {
    String* s = initString();
    String* s1 = initString();
    stringAssign(s,"aabaabaafa");
    printString(s);
    stringAssign(s1,"aabaaf");
    printString(s1);
    int* next = getNext(s1);
    printNext(next, s1);
    printf("%d", kmpMatch(s, s1, next));
    return 0;
}