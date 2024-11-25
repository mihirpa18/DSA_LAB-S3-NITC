#include <stdlib.h>
#include <stdio.h>

int minind(int n, int visited[], int dist[]) {
    int min = 1e9;
    int min_index = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void djk(int n, int mat[][n+1], int src) {
    int visited[n+1];
    int dist[n+1];
    
    // Initialize visited and dist arrays
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        dist[i] = 1e9;
    }
    
    dist[src] = 0;
    
    for (int i = 1; i <= n; i++) {
        int min = minind(n, visited, dist);
        if (min == -1) break; // No more reachable nodes
        visited[min] = 1;
        
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && mat[min][j] && (dist[min] + mat[min][j]) < dist[j]) {
                dist[j] = dist[min] + mat[min][j];
            }
        }
    }

    // Print the distance array
    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int tail, wt;
    char c;
    
    // Initialize the matrix
    int matrix[n+1][n+1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = 0;
        }
    }

    // Input for adjacency matrix (connections)
    for (int i = 0; i < n; i++) {
        int head;
        scanf("%d", &head);
        while (1) {
            scanf("%c", &c);
            if (c == '\n') break;
            scanf("%d", &tail);
            matrix[head][tail] = 1;
        }
    }

    // Input for weights
    for (int i = 0; i < n; i++) {
        int head;
        scanf("%d", &head);
        while (1) {
            scanf("%c", &c);
            if (c == '\n') break;
            for (int j = 1; j <= n; j++) {
                if (matrix[head][j] == 1) {
                    scanf("%d", &wt);
                    matrix[head][j] = wt;
                }
            }
        }
    }

    // Print the matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Input source node and run Dijkstra's algorithm
    int s;
    scanf("%d", &s);
    djk(n, matrix, s);

    return 0;
}
