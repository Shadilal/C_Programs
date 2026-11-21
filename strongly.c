#include <stdio.h>
#define MAX 20

int graph[MAX][MAX], transpose[MAX][MAX];
int visited[MAX];
int n;

// First DFS - to fill stack in finishing order
void fillOrder(int v, int stack[], int *top) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            fillOrder(i, stack, top);
        }
    }
    stack[++(*top)] = v;
}

// Second DFS - on transpose graph to print one SCC
void DFS_Transpose(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < n; i++) {
        if (transpose[v][i] == 1 && !visited[i]) {
            DFS_Transpose(i);
        }
    }
}

void findTranspose() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpose[i][j] = graph[j][i];
        }
    }
}

int main() {
    int stack[MAX], top = -1;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Step 1: Fill stack using first DFS
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            fillOrder(i, stack, &top);
        }
    }

    // Step 2: Get transpose graph
    findTranspose();

    // Step 3: DFS on transpose in stack order
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nStrongly Connected Components:\n");
    while (top >= 0) {
        int v = stack[top--];
        if (!visited[v]) {
            DFS_Transpose(v);
            printf("\n");
        }
    }

    return 0;
}
