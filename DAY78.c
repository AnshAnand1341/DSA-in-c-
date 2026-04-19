#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1005

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* adj[MAX];
int visited[MAX];

// Min heap structure
typedef struct {
    int node, weight;
} HeapNode;

HeapNode heap[MAX * MAX];
int heapSize = 0;

// Swap heap nodes
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push into min heap
void push(int node, int weight) {
    heap[++heapSize].node = node;
    heap[heapSize].weight = weight;

    int i = heapSize;
    while (i > 1 && heap[i].weight < heap[i / 2].weight) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

// Pop from min heap
HeapNode pop() {
    HeapNode top = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;
    while (1) {
        int left = 2 * i, right = 2 * i + 1, smallest = i;

        if (left <= heapSize && heap[left].weight < heap[smallest].weight)
            smallest = left;
        if (right <= heapSize && heap[right].weight < heap[smallest].weight)
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else break;
    }
    return top;
}

// Add edge to adjacency list
void addEdge(int u, int v, int w) {
    Edge* e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = v;
    e1->weight = w;
    e1->next = adj[u];
    adj[u] = e1;

    Edge* e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = u;
    e2->weight = w;
    e2->next = adj[v];
    adj[v] = e2;
}

int prim(int n) {
    int totalWeight = 0;

    push(1, 0); // start from node 1

    while (heapSize > 0) {
        HeapNode current = pop();
        int u = current.node;
        int w = current.weight;

        if (visited[u]) continue;

        visited[u] = 1;
        totalWeight += w;

        Edge* temp = adj[u];
        while (temp) {
            if (!visited[temp->to]) {
                push(temp->to, temp->weight);
            }
            temp = temp->next;
        }
    }

    return totalWeight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
        visited[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    int result = prim(n);
    printf("%d\n", result);

    return 0;
}