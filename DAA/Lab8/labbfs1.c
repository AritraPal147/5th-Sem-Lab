/*
input:
5 4
1 2
1 4
4 5
2 5
1
Output:
BFS Traversal: 1 2 3 4 5 
Shortest Distances from Node 1:
Node 2: 2
Node 3: -1
Node 4: 2
Node 5: 4

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
struct Edge {
    int to;
    struct Edge* next;
};

// Structure to represent a node in the graph
struct Node {
    struct Edge* edges;
};

// Function to add an edge to the graph
void addEdge(struct Node* nodes, int u, int v) {
    struct Edge* edge = (struct Edge*)malloc(sizeof(struct Edge));
    edge->to = v;
    edge->next = nodes[u].edges;
    nodes[u].edges = edge;

    // Since the graph is undirected, add the reverse edge
    edge = (struct Edge*)malloc(sizeof(struct Edge));
    edge->to = u;
    edge->next = nodes[v].edges;
    nodes[v].edges = edge;
}

// Function to perform Breadth-First Search (BFS)
int* breadthFirstSearch(struct Node* nodes, int n, int start) {
    int* distances = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        distances[i] = -1;  // Initialize distances to -1 (unreachable)
        visited[i] = false;
    }

    distances[start] = 0;  // Distance to the start node is 0
    visited[start] = true;

    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        struct Edge* edge = nodes[current].edges;
        while (edge) {
            int neighbor = edge->to;
            if (!visited[neighbor]) {
                distances[neighbor] = distances[current] + 2;  // Edge weights 2 units
                visited[neighbor] = true;
                queue[rear++] = neighbor;
            }
            edge = edge->next;
        }
    }

    free(queue);
    free(visited);
    return distances;
}

int main() {
    int n, m;  // Number of nodes and edges
    scanf("%d %d", &n, &m);

    struct Node* nodes = (struct Node*)malloc(n * sizeof(struct Node));

    // Initialize nodes
    for (int i = 0; i < n; i++) {
        nodes[i].edges = NULL;
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(nodes, u - 1, v - 1);  // Adjust for 0-based indexing
    }

    int start;
    scanf("%d", &start);
    start--;  // Adjust for 0-based indexing

    int* distances = breadthFirstSearch(nodes, n, start);

    // Display BFS traversal
    printf("BFS Traversal: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i + 1);  // Adjust for 1-based indexing
    }
    printf("\n");

    // Display shortest distances
    printf("Shortest Distances from Node %d:\n", start + 1);  // Adjust for 1-based indexing
    for (int i = 0; i < n; i++) {
        if (i == start) {
            continue;  // Skip the starting node
        }
        printf("Node %d: %d\n", i + 1, distances[i]);  // Adjust for 1-based indexing
    }

    free(nodes);
    free(distances);
    return 0;
}
