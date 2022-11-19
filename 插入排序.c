#include<stdio.h>

void printArray(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


//打扑克牌一样
//选位置，挪位置，插入，前面保持有序
void insertSort(int array[], int length) {
    for (int i = 1; i < length; i++) {   
        for (int j = 0; j < i; j++) {
            if(array[i] < array[j]) {
                int temp = array[i];
                //数好次数，或者直接从角标选取取理解，i-1到j
                for (int k = i-1; k>=j; k--) {
                    array[k+1] = array[k];
                }
                array[j] = temp;
            }
        }
        printArray(array, length);
    }
}


int main()
{
    int array[6] = {4,3,5,1,9,6};
    printArray(array, 6);
    insertSort(array, 6);
    return 0;
}