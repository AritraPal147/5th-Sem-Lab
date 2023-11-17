// For file input, check lab 3 question 2

#include <stdio.h>

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) 
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {1, 9, 5, 2, 10};
    int size = sizeof(arr) / 4;
    insertionSort(arr, size);
    displayArray(arr, size);
    return 0;
}
