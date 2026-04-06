#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
bool visited[MAX];
int n; // number of vertices

// DFS function to detect cycle
bool dfs(int node, int parent) {
    visited[node] = true;

    for (int i = 0; i < n; i++) {
        if (graph[node][i]) { // if edge exists
            if (!visited[i]) {
                if (dfs(i, node))
                    return true;
            }
            else if (i != parent) {
                // visited and not parent => cycle found
                return true;
            }
        }
    }
    return false;
}

// Function to check cycle in graph
bool hasCycle() {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1))
                return true;
        }
    }
    return false;
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // initialize graph and visited
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected graph
    }

    if (hasCycle())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}