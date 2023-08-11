/*
    Given an array arr[] of size N, find the prefix sum of the array. 
    A prefix sum array is another array prefixSum[] of the same size, such 
    that the value of prefixSum[i] is arr[0] + arr[1] + arr[2] . . . arr[i] 
    and print all elements whose values are greater than the sum of elements 
    appear before them.
    
    Input Array: 	3 	4 	5 	1	 2
    Output Array: 	3 	7 	12 	13 	15
*/

#include <stdio.h>
int main()
{
    int n, i;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Input Array: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    int prefixSum[n];
    prefixSum[0] = arr[0];
    for (i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    
    printf("Output Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", prefixSum[i]);
    printf("\n");

    return 0;
}
