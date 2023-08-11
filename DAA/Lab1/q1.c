/*
    Write a program to find out the second smallest and second largest element stored 
    in an array of n integers and delete them.
    Input: Size of the array is ‘n’ and read ‘n’ number of elements from a disc file.
    Output: Second smallest, Second largest
              Remaining elements of the array after deletion
*/

#include <stdio.h>
#include <stdlib.h>
void findSecondSmallestAndLargest(int arr[], int n, int *second_smallest, int *second_largest)
{
    int smallest = arr[0];
    int largest = arr[0];
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            *second_smallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] < *second_smallest)
            *second_smallest = arr[i];

        if (arr[i] > largest)
        {
            *second_largest = largest;
            largest = arr[i];
        }
        else if (arr[i] > *second_largest)
            *second_largest = arr[i];
    }
}
int main()
{
    int n, i, j;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        fscanf(file, "%d", &arr[i]);
    fclose(file);

    int second_smallest = arr[0], second_largest = arr[0];
    findSecondSmallestAndLargest(arr, n, &second_smallest, &second_largest);

    printf("Second smallest: %d\n", second_smallest);
    printf("Second largest: %d\n", second_largest);
    for (i = 0; i < n; i++)
    {
        if (arr[i] == second_smallest || arr[i] == second_largest)
        {
            for (j = i; j < n - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            n--;
            i--;
        }
    }
    printf("Array after deletion of second smallest and second largest elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
