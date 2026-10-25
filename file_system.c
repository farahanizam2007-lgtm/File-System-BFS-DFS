#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
char names[MAX][50];
int n;

void BFS(int start, char target[]) {
    int queue[MAX];
    int front = 0, rear = 0, found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];

        printf("%s ", names[current]);

        if (strcmp(names[current], target) == 0)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    if (found)
        printf("\nFile '%s' found using BFS.\n", target);
    else
        printf("\nFile '%s' not found using BFS.\n", target);
}

void DFSvisit(int current, char target[], int *found) {
    visited[current] = 1;
    printf("%s ", names[current]);

    if (strcmp(names[current], target) == 0)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] == 1 && !visited[i])
            DFSvisit(i, target, found);
    }
}

void DFS(int start, char target[]) {
    int found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS Traversal: ");
    DFSvisit(start, target, &found);

    if (found)
        printf("\nFile '%s' found using DFS.\n", target);
    else
        printf("\nFile '%s' not found using DFS.\n", target);
}

int main(void) {
    int start;
    char target[50];

    printf("FILE SYSTEM USING BFS AND DFS\n");

    printf("Enter number of nodes (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter node names without spaces:\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        if (scanf("%49s", names[i]) != 1)
            return 1;
    }

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                printf("Enter only 0 or 1 in the matrix.\n");
                return 1;
            }
        }
    }

    printf("Enter starting node index (0-%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    printf("Enter file name to search: ");
    if (scanf("%49s", target) != 1)
        return 1;

    BFS(start, target);
    DFS(start, target);

    return 0;
}
