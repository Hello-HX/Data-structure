#include<stdio.h>

void printArray(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//希尔排序
//每次用步长去分组
//组内插入排序（找位置 挪动， 插入）
//然后每次步长减半，重复，直到为1
void shellSort(int array[], int length, int step) {
    for (int i = 0; i < length; i++) {
        //选择起始点
        for (int j = i + step; j < length; j +=step) { //分组，且是末尾点
            
            for (int k = i; k < j; k+=step) {//i到j，前面的有序数组进行比较
                if (array[j] < array[k]) {
                    int temp = array[j];//交换挪动位置
                    for (int l = j - step; l >= k; l-=step) {
                        array[l + step] = array[l];
                    }
                    array[k] = temp;
                }
            }
        }
    }
}

int main() {
    int array[10] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int steps[3] = {5, 3, 1};
    //不同的步长去交换
    for (int i = 0; i < 3; i++) {
        shellSort(array, 10, steps[i]);
        printArray(array, 10);
    }
    return 0;
}