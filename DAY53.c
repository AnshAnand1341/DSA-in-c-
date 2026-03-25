#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Queue Node (for BFS)
struct QNode {
    struct Node* node;
    int hd;
};

// Create new tree node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Simple queue implementation
struct QNode queue[1000];
int front = 0, rear = 0;

void enqueue(struct Node* node, int hd) {
    queue[rear].node = node;
    queue[rear].hd = hd;
    rear++;
}

struct QNode dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

// Function for Vertical Order Traversal
void verticalOrder(struct Node* root) {
    if (root == NULL) return;

    // To store nodes for each HD
    int minHD = 0, maxHD = 0;

    // Array of lists (simple 2D array)
    int map[200][100];   // map[hd+offset][values]
    int count[200] = {0};

    int offset = 100; // To handle negative HD

    enqueue(root, 0);

    while (!isEmpty()) {
        struct QNode temp = dequeue();
        struct Node* node = temp.node;
        int hd = temp.hd;

        // Store node data
        map[hd + offset][count[hd + offset]++] = node->data;

        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        if (node->left)
            enqueue(node->left, hd - 1);

        if (node->right)
            enqueue(node->right, hd + 1);
    }

    // Print vertical order
    for (int i = minHD; i <= maxHD; i++) {
        for (int j = 0; j < count[i + offset]; j++) {
            printf("%d ", map[i + offset][j]);
        }
        printf("\n");
    }
}

// Build tree from level order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);

    struct Node* q[1000];
    int f = 0, r = 0;
    q[r++] = root;

    int i = 1;

    while (i < n) {
        struct Node* curr = q[f++];

        // Left child
        if (arr[i] != -1) {
            curr->left = newNode(arr[i]);
            q[r++] = curr->left;
        }
        i++;

        // Right child
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            q[r++] = curr->right;
        }
        i++;
    }

    return root;
}

// Driver Code
int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}