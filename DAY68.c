#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack
int stack[MAX], top = -1;

// Graph (Adjacency List)
int adj[MAX][MAX];
int visited[MAX];
int V;

// Push to stack
void push(int node) {
    stack[++top] = node;
}

// DFS function
void dfs(int node) {
    visited[node] = 1;

    for (int i = 0; i < V; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }

    push(node); // push after visiting neighbors
}

// Topological Sort
void topoSort() {
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Print stack (reverse order)
    printf("Topological Order: ");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
}

// Main function
int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        for (int j = 0; j < V; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    topoSort();

    return 0;
}