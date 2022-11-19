#include <stdio.h>

void printArray(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
//思想：选一个点，一刀切开放两边，继续切，树形结构
//进行交换

//寻找下标
int partiton(int array[], int i, int j) {
    int x = array[i];//把第一个元素提取出来，防止覆盖掉
    while(i < j) {
        //j的拿出来，填上去前面的
        while(i < j &&array[j] >=x ) j--;
        if(i < j) array[i] = array[j];
        //i拿出来，填上去后面的
        while(i < j && array[i] < x) i++;
        if(i < j) array[j] = array[i]; 
    }
    //这里返回i和j都无所谓，最终一定是相等的，切所指空的，放个x在中间
    array[i] = x;
    return i;
}


void quickSort(int array[],int l,int r)
{
    //不能让他一直递归下去，最后那一刻必定i == j，所以我就限制i < j 才能进入
	if(l < r) {
        int index = partiton(array, l,r);
        quickSort(array,l,index-1);
        quickSort(array,index+1,r);
    }
}

int main()
{
    int array[8] = {27, 38, 13, 49, 76, 97, 65, 49};
    quickSort(array, 0, 7);
    printArray(array,8);
    return 0;
}