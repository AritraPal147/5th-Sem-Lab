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

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void DFSUtil(int vertex, struct Graph* graph, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        if (!visited[temp->data])
            DFSUtil(temp->data, graph, visited);
        temp = temp->next;
    }
}

void connectedComponents(struct Graph* graph) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i)
        visited[i] = 0;

    for (int i = 0; i < graph->vertices; ++i) {
        if (!visited[i]) {
            printf("Connected Component: ");
            DFSUtil(i, graph, visited);
            printf("\n");
        }
    }

    free(visited);
}

int main() {
    int edgesCount;
    printf("Enter number of edges: ");
    scanf("%d", &edgesCount);

    struct Graph* graph = createGraph(edgesCount + 1);
    printf("Enter edges:\n");
    for (int i = 0; i < edgesCount; i++ ) {
        int e1, e2;
        scanf("%d %d", &e1, &e2);
        addEdge(graph, e1, e2);
    }

    printf("Nodes of Connected Components:\n");
    connectedComponents(graph);

    return 0;
}
