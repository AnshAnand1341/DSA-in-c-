#include <stdio.h>

#define MAX 100

int adj[MAX][MAX];   // adjacency matrix (simpler input handling)
int visited[MAX];
int n;

// DFS function
void dfs(int node) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < n; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int s;

    // number of vertices
    scanf("%d", &n);

    // adjacency matrix input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    // starting vertex
    scanf("%d", &s);

    // initialize visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // call DFS
    dfs(s);

    return 0;
}