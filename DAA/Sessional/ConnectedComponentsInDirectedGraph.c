#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; ++i)
        graph->adjList[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Utility function to perform DFS
int isReachableDFS(int src, int dest, int visited[], struct Graph* graph) {
    visited[src] = 1;

    if (src == dest)
        return 1; // Nodes are connected

    struct Node* temp = graph->adjList[src];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            if (isReachableDFS(temp->data, dest, visited, graph))
                return 1; // Nodes are connected
        }
        temp = temp->next;
    }

    return 0; // Nodes are not connected
}

// Function to check if nodes are connected using DFS
int areNodesConnectedDFS(struct Graph* graph, int src, int dest) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i)
        visited[i] = 0;

    int result = isReachableDFS(src, dest, visited, graph);

    free(visited);

    return result;
}

int main() {
    struct Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    int src = 0;
    int dest = 4;

    if (areNodesConnectedDFS(graph, src, dest))
        printf("Nodes %d and %d are connected.\n", src, dest);
    else
        printf("Nodes %d and %d are not connected.\n", src, dest);

    return 0;
}
