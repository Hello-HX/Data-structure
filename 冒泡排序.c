#include<stdio.h>

void printArray(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//把元素不断顶上去，交换交换，像泡泡一样
void bubbleSort(int array[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length-i-1; j++) {
            if(array[j] > array[j + 1]) {
                array[j]^=array[j+1];
                array[j+1]^=array[j];
                array[j]^=array[j+1];
            }
        }
         printArray(array, length);
    }
}

int main() {
    int array[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    bubbleSort(array,8);
    return 0;
}