/*
2) Huffman coding assigns variable length codewords to 
   fixed length input characters based on their frequencies 
   or probabilities of occurrence. Given a set of characters 
   along with their frequency of occurrences, write a c program
   to construct a Huffman tree.

   Note# 
    • Declare a structure SYMBOL having members alphabet and 
      frequency. Create a Min-Priority Queue, keyed on frequency 
      attributes. 
    • Create an array of structures where size=number of alphabets.

   Input:      
   Enter the number of distinct alphabets: 6
   Enter the alphabets:     	a      	b      	c      	d      	e      	f
   Enter its frequencies:   	45    	13    	12    	16    	9      	5

   Output:
   In-order traversal of the tree (Huffman): a  c  b  f  e  d
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a symbol
struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left, *right;
};

// Structure to represent a Min-Priority Queue
struct MinPriorityQueue {
    int size;
    struct SYMBOL **array;
};

// Function to create a new symbol
struct SYMBOL* newSymbol(char alphabet, int frequency) {
    struct SYMBOL* symbol = (struct SYMBOL*)malloc(sizeof(struct SYMBOL));
    symbol->alphabet = alphabet;
    symbol->frequency = frequency;
    symbol->left = symbol->right = NULL;
    return symbol;
}

// Function to create a new Min-Priority Queue
struct MinPriorityQueue* createMinPriorityQueue(int capacity) {
    struct MinPriorityQueue* minQueue = (struct MinPriorityQueue*)malloc(sizeof(struct MinPriorityQueue));
    minQueue->size = 0;
    minQueue->array = (struct SYMBOL**)malloc(capacity * sizeof(struct SYMBOL*));
    return minQueue;
}

// Function to swap two symbols
void swapSymbols(struct SYMBOL** a, struct SYMBOL** b) {
    struct SYMBOL* t = *a;
    *a = *b;
    *b = t;
}

// Heapify function for Min-Priority Queue
void minHeapify(struct MinPriorityQueue* minQueue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minQueue->size && minQueue->array[left]->frequency < minQueue->array[smallest]->frequency)
        smallest = left;

    if (right < minQueue->size && minQueue->array[right]->frequency < minQueue->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapSymbols(&minQueue->array[idx], &minQueue->array[smallest]);
        minHeapify(minQueue, smallest);
    }
}

// Function to build Min-Priority Queue
void buildMinPriorityQueue(struct MinPriorityQueue* minQueue) {
    int n = minQueue->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(minQueue, i);
}

// Function to insert a new symbol into Min-Priority Queue
void insertSymbol(struct MinPriorityQueue* minQueue, struct SYMBOL* symbol) {
    minQueue->size++;
    int i = minQueue->size - 1;
    while (i > 0 && symbol->frequency < minQueue->array[(i - 1) / 2]->frequency) {
        minQueue->array[i] = minQueue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minQueue->array[i] = symbol;
}

// Function to extract the minimum from Min-Priority Queue
struct SYMBOL* extractMin(struct MinPriorityQueue* minQueue) {
    struct SYMBOL* minSymbol = minQueue->array[0];
    minQueue->array[0] = minQueue->array[minQueue->size - 1];
    minQueue->size--;
    minHeapify(minQueue, 0);
    return minSymbol;
}

// Function to build Huffman tree
struct SYMBOL* buildHuffmanTree(char alphabets[], int frequencies[], int n) {
    struct SYMBOL *left, *right, *top;

    // Create a Min-Priority Queue and insert all symbols
    struct MinPriorityQueue* minQueue = createMinPriorityQueue(n);
    for (int i = 0; i < n; ++i)
        insertSymbol(minQueue, newSymbol(alphabets[i], frequencies[i]));

    // Build the Huffman tree
    while (minQueue->size > 1) {
        left = extractMin(minQueue);
        right = extractMin(minQueue);

        // Create a new internal node with frequency equal to the sum of the two nodes
        top = newSymbol('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // Insert the new node into the Min-Priority Queue
        insertSymbol(minQueue, top);
    }

    // The remaining node is the root of the Huffman tree
    return extractMin(minQueue);
}

// Function to perform in-order traversal of the Huffman tree
void inOrderTraversal(struct SYMBOL* root) {
    if (root) {
        inOrderTraversal(root->left);
        if (root -> alphabet != '$')
            printf("%c ", root->alphabet);
        inOrderTraversal(root->right);
    }
}

int main() {
    int n;

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int frequencies[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; ++i)
        scanf(" %c", &alphabets[i]);

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; ++i)
        scanf("%d", &frequencies[i]);

    // Build Huffman Tree
    struct SYMBOL* root = buildHuffmanTree(alphabets, frequencies, n);

    printf("\nIn-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");
    return 0;
}
