/*
    Given an array arr[] of size N having distinct numbers sorted in 
    increasing order and the array has been right rotated (i.e. the element 
    will be cyclically shifted to the starting position of the array) k number 
    of times, the task is to find the value of k.
    
    Input: arr[] = {15, 18, 2, 3, 6, 12}
    Output: 2

    Explanation: Initial array must be {2, 3, 6, 12, 15, 18}. 
    We get the given array after rotating the initial array twice. k.
*/

#include <stdio.h>

int findRotationCount(int arr[], int N) {
    int low = 0, high = N - 1;

    while (low <= high) {
        if (arr[low] <= arr[high])
            return low;

        int mid = (low + high) / 2;
        int next = (mid + 1) % N;
        int prev = (mid + N - 1) % N;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) 
            return mid;
        else if (arr[mid] <= arr[high]) 
            high = mid - 1;
        else if (arr[mid] >= arr[low])
            low = mid + 1;
    }

    return -1; // Not found
}

int main() {
    int N;
    printf("Enter the size of the array: ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < N; ++i) 
        scanf("%d", &arr[i]);

    int rotationCount = findRotationCount(arr, N);

    if (rotationCount != -1) 
        printf("The array has been rotated %d times.\n", rotationCount);
    else 
        printf("The array is not rotated.\n");

    return 0;
}
