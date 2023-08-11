/*
    Write a C program to implement Binary Search to give the position 
    of leftmost appearance of the element in the array being searched. 
    Display the number of comparisons made while searching. 

    Input:
    Enter size of array: 10
    Enter elements of the array: 2 3 7 7 7 11 12 12 20 50 
    Enter the key to be searched: 7
    
    Output:
    7 found at index position 2 
    Number of comparisons: 3
*/

#include <stdio.h>

int binarySearchLeftmost(int arr[], int size, int key, int *comparisons) {
    int low = 0, high = size - 1;
    int result = -1;  // Initialize result to -1 (not found)

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            result = mid;
            high = mid - 1;  // Move to the left half to find the leftmost occurrence
        } else if (arr[mid] < key) 
            low = mid + 1;
        else 
            high = mid - 1;

        (*comparisons)++;
    }

    return result;
}

int main() {
    int size, key, comparisons = 0;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter elements of the array in sorted order: ");
    for (int i = 0; i < size; ++i) 
        scanf("%d", &arr[i]);

    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    int index = binarySearchLeftmost(arr, size, key, &comparisons);

    if (index != -1) {
        printf("%d found at index position %d\n", key, index);
        printf("Number of comparisons: %d\n", comparisons);
    } else {
        printf("%d not found in the array.\n", key);
    }

    return 0;
}
