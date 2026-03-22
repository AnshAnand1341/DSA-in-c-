#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

// Recursive search
int searchRecursive(struct Node* root, int key) {
    if (root == NULL)
        return 0;

    if (root->data == key)
        return 1;
    else if (key < root->data)
        return searchRecursive(root->left, key);
    else
        return searchRecursive(root->right, key);
}

// Iterative search
int searchIterative(struct Node* root, int key) {
    while (root != NULL) {
        if (root->data == key)
            return 1;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}

// Inorder traversal (for checking BST)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, val, key, choice;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Enter value to search: ");
    scanf("%d", &key);

    printf("Choose method:\n1. Recursive\n2. Iterative\n");
    scanf("%d", &choice);

    if (choice == 1) {
        if (searchRecursive(root, key))
            printf("Found\n");
        else
            printf("Not Found\n");
    } else if (choice == 2) {
        if (searchIterative(root, key))
            printf("Found\n");
        else
            printf("Not Found\n");
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}