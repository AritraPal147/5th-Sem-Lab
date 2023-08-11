/*
    Write a program to read ‘n’ integers from a disc file that must contain 
    some duplicate values and store them into an array. Perform the following 
    operations on the array.
    a) Find out the total number of duplicate elements.
    b) Find out the most repeating element in the array.

    Input:
    Enter how many numbers you want to read from file: 15

    Output:
    The content of the array: 10 40 35 47 68 22 40 10 98 10 50 35 68 40 10
    Total number of duplicate values = 4
    The most repeating element in the array = 10
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, i, j;
    printf("Enter how many numbers you want to read from the file: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    FILE *file = fopen("input2.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        fscanf(file, "%d", &arr[i]);
    fclose(file);
    printf("The content of the array: ");

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int total_duplicates = 0;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                total_duplicates++;
                break;
            }
        }
    }
    printf("Total number of duplicate values = %d\n", total_duplicates);
    int max_repeating_element = arr[0];
    int max_frequency = 1;
    for (i = 0; i < n; i++)
    {
        int current_element = arr[i];
        int current_frequency = 1;

        for (j = i + 1; j < n; j++)
            if (arr[j] == current_element)
                current_frequency++;

        if (current_frequency > max_frequency)
        {
            max_frequency = current_frequency;
            max_repeating_element = current_element;
        }
    }
    printf("The most repeating element in the array = %d\n", max_repeating_element);
    free(arr);
    return 0;
}
