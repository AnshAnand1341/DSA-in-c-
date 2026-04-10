#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // Number of vertices

// Structure for adjacency list node
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure for graph
struct Graph {
    struct Node* adj[V];
};

// Min Heap Node
struct MinHeapNode {
    int vertex;
    int dist;
};

// Min Heap
struct MinHeap {
    int size;
    struct MinHeapNode* heap[V];
};

// Create new adjacency node
struct Node* newNode(int v, int w) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = v;
    node->weight = w;
    node->next = NULL;
    return node;
}

// Create graph
struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int u, int v, int w) {
    struct Node* node = newNode(v, w);
    node->next = graph->adj[u];
    graph->adj[u] = node;
}

// Swap heap nodes
void swap(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void heapify(struct MinHeap* heap, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && heap->heap[left]->dist < heap->heap[smallest]->dist)
        smallest = left;

    if (right < heap->size && heap->heap[right]->dist < heap->heap[smallest]->dist)
        smallest = right;

    if (smallest != i) {
        swap(&heap->heap[i], &heap->heap[smallest]);
        heapify(heap, smallest);
    }
}

// Extract min
struct MinHeapNode* extractMin(struct MinHeap* heap) {
    if (heap->size == 0) return NULL;

    struct MinHeapNode* root = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

// Decrease key
void decreaseKey(struct MinHeap* heap, int v, int dist) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->heap[i]->vertex == v) {
            heap->heap[i]->dist = dist;
            while (i && heap->heap[i]->dist < heap->heap[(i-1)/2]->dist) {
                swap(&heap->heap[i], &heap->heap[(i-1)/2]);
                i = (i-1)/2;
            }
            break;
        }
    }
}

// Check if empty
int isEmpty(struct MinHeap* heap) {
    return heap->size == 0;
}

// Dijkstra Algorithm
void dijkstra(struct Graph* graph, int src) {
    int dist[V];

    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    heap->size = V;

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        heap->heap[i] = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
        heap->heap[i]->vertex = i;
        heap->heap[i]->dist = dist[i];
    }

    dist[src] = 0;
    heap->heap[src]->dist = 0;

    while (!isEmpty(heap)) {
        struct MinHeapNode* minNode = extractMin(heap);
        int u = minNode->vertex;

        struct Node* temp = graph->adj[u];
        while (temp) {
            int v = temp->vertex;

            if (dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                decreaseKey(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print result
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Driver code
int main() {
    struct Graph* graph = createGraph();

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 0, 7);
    addEdge(graph, 4, 1, 3);
    addEdge(graph, 4, 2, 9);
    addEdge(graph, 4, 3, 2);

    dijkstra(graph, 0);

    return 0;
}