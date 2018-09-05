#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int*, int);
void print_array(int*, int);

int main(){
    int arr[10] = {4, 6, 21, 44, 12, 1, 6, 8, 31, 10};

    printf("Array before sort:\n");
    print_array(arr, 10);

    bubble_sort(arr, 10);

    printf("Array after sort:\n");
    print_array(arr, 10);

    return 0;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *array, int n){
    bool flag = true;

    while (flag){
        flag = false;

        for(int i = 0, j = n - 1; i < j; i++){
            if(array[i] > array[i+1]){
                swap(&array[i], &array[i+1]);
                flag = true;
            }
        }
    }
}

void print_array(int *array, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}