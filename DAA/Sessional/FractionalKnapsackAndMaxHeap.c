/*
1) Write a C program to find the maximum profit nearest to but not exceeding 
   the given knapsack capacity using the Fractional Knapsack algorithm.
   Notes# Declare a structure ITEM having data members item_id, item_profit, 
   item_weight and profit_weight_ratio. Apply heap sort technique to sort the items 
   in non-increasing order, according to their profit /weight.

   Input:
   Enter the number of items: 3
   Enter the profit and weight of item no 1: 27  16
   Enter the profit and weight of item no 2: 14  12
   Enter the profit and weight of item no 3: 26  13
   Enter the capacity of knapsack:18

   Output:
   Item No	Profit		Weight		Amount to be taken
   3		26.000000	13.000000	    1.000000
   1    	27.000000   16.000000   	0.312500
   2        4.000000   	12.000000     	0.000000
   Maximum profit: 34.437500
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
    float amt_taken;
};

void swap(struct ITEM *a, struct ITEM *b) {
	struct ITEM temp = *a;
	*a = *b;
    *b = temp;
}

// Function to perform heapify operation in the max heap
void minHeapify(struct ITEM arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio < arr[smallest].profit_weight_ratio)
        smallest = left;

    if (right < n && arr[right].profit_weight_ratio < arr[smallest].profit_weight_ratio)
        smallest = right;

    if (smallest != i) {
        // Swap arr[i] and arr[smallest]
        swap(&arr[i], &arr[smallest]);

        // Recursively heapify the affected sub-tree
        minHeapify(arr, n, smallest);
    }
}

// Function to perform heap sort on items based on profit/weight ratio
void heapSort(struct ITEM arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // call min heapify on the reduced heap
        minHeapify(arr, i, 0);
    }
}

// Function to perform Fractional Knapsack and print the result
void fractionalKnapsack(struct ITEM items[], int n, float capacity) {
    // Sort items based on profit/weight ratio using heap sort
    heapSort(items, n);
    // printf("\nItem No\tProfit\t\tWeight\t\tProfit/Weight Ratio\n");
	// for (int i=0; i<n; i++)
	// 	printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, items[i].profit_weight_ratio);
	// printf("\n\n");

    printf("\nItem No\tProfit\t\tWeight\t\tAmount to be taken\n");

    float totalProfit = 0;
    int i;
    for (i = 0; i < n && capacity > 0; i++) {
        float taken = (capacity < items[i].item_weight) ? capacity : items[i].item_weight;
        float fraction = 1;
        if (items[i].item_weight > capacity)
        	fraction = (capacity / items[i].item_weight);
        float profit = taken * items[i].profit_weight_ratio;
		
		items[i].amt_taken = fraction;
        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);

        totalProfit += profit;
        capacity -= taken;
    }
    
    while (i < n) {
    	float z = 0;
    	printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, z);
    	i++;
    }

    printf("\nMaximum profit: %.6f\n", totalProfit);
}

int main() {
    int n;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    fractionalKnapsack(items, n, capacity);

    return 0;
}