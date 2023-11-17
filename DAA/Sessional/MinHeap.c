#include <stdio.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int heapSize = 0;

// Function to get the index of the parent
int parent(int i) {
    return (i - 1) / 2;
}

// Function to get the index of the left child
int leftChild(int i) {
    return 2 * i + 1;
}

// Function to get the index of the right child
int rightChild(int i) {
    return 2 * i + 2;
}

// Function to swap two elements in the heap
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree with the root at index i
void minHeapify(int i) {
    int l = leftChild(i);
    int r = rightChild(i);
    int smallest = i;

    if (l < heapSize && heap[l] < heap[smallest])
        smallest = l;

    if (r < heapSize && heap[r] < heap[smallest])
        smallest = r;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(smallest);
    }
}

// Function to insert a new key in the heap
void insertMinHeap(int key) {
    if (heapSize == MAX_HEAP_SIZE) {
        printf("Overflow: Could not insert key.\n");
        return;
    }

    int i = heapSize++;
    heap[i] = key;

    // Fix the min heap property if it is violated
    while (i != 0 && heap[parent(i)] > heap[i]) {
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
}

// Function to extract the minimum element from the heap
int extractMin() {
    if (heapSize <= 0)
        return -1; // Signify an empty heap

    if (heapSize == 1) {
        heapSize--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[--heapSize];
    minHeapify(0);

    return root;
}

// Function to print the elements of the heap
void printMinHeap() {
    printf("Min Heap: ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main() {
    insertMinHeap(3);
    insertMinHeap(2);
    insertMinHeap(15);
    insertMinHeap(5);
    insertMinHeap(4);
    insertMinHeap(45);

    printMinHeap();

    int minElement = extractMin();
    if (minElement != -1)
        printf("Extracted Min: %d\n", minElement);

    printMinHeap();

    return 0;
}
