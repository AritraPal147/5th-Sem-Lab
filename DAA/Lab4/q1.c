/*
    Aim of the program: Write a menu driven program to sort 
    list of array elements using Merge Sort technique and calculate 
    the execution time only to sort the elements.  Count the number of comparisons. 
    Note# 
    • To calculate execution time, assume that single program is under execution in the CPU. 
    • Number of elements in each input file should vary from 300 to 500 entries. 
    • For ascending order: Read data from a file “inAsce.dat” having 
      content 10 20 30 40….., Store the result in “outMergeAsce.dat”.
    • For descending order: Read data from a file “inDesc.dat” having 
      content 90 80 70 60…., Store the result in “outMergeDesc.dat”.
    • For random data: Read data from a file “inRand.dat” having 
      content 55 66 33 11 44 …, Store the result in “outMergeRand.dat”

    Sample Input from file:
    MAIN MENU (MERGE SORT)
    1. Ascending Data
    2. Descending Data
    3. Random Data
    4. ERROR (EXIT)

    Output:
    Enter option: 1
    Before Sorting: Content of the input file
    After Sorting: Content of the output file
    Number of Comparisons: Actual
    Execution Time: lapse time in nanosecond
*/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right, long long int* comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right, long long int *comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid + 1, right, comparisons);

        merge(arr, left, mid, right, comparisons);
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) 
        printf("%d ", arr[i]);
    printf("\n");
}

void processScenario(const char *inputFileName, const char* outputFileName) {
    FILE *inputFile, *outputFile;
    int option, numElements;
    struct timespec start_time, end_time;

    inputFile = fopen(inputFileName, "r");
        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            exit(1);
        }

        int size;
        printf("Enter number of elements to be read from file: ");
        scanf("%d", &size);

        int arr[size];
        for (int i = 0; i < size; i++) 
            fscanf(inputFile, "%d", &arr[i]);
        fclose(inputFile);

        printf("Before Sorting: ");
        displayArray(arr, size);

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        long long int comparisons = 0;
        mergeSort(arr, 0, size - 1, &comparisons);
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double execution_time = (end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec);

        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            exit(1);
        }

        for (int i = 0; i < size; i++) 
            fprintf(outputFile, "%d ", arr[i]);
        fclose(outputFile);

        printf("After Sorting: ");
        displayArray(arr, size);

        printf("Number of Comparisons: %lld\n", comparisons);
        printf("Execution Time: %.2lf nanoseconds\n\n", execution_time);
}

int main() {
    FILE *inputFile, *outputFile;
    int option, numElements;
    
    struct timespec start_time, end_time;

    do {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                processScenario("inAsce.dat", "outMergeAsce.dat");
                break;
            case 2:
                processScenario("inDesc.dat", "outMergeDesc.dat");
                break;
            case 3:
                processScenario("inRand.dat", "outMergeRand.dat");
                break;
            case 4:
                printf("Exiting program.\n\n");
                break;
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while(option != 4);

    return 0;
}
