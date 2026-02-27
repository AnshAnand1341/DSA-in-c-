#include <stdio.h>
#include <stdlib.h>

// Structure for linked list node
struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at end
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL)
        return newNode;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Delete first occurrence of key
struct Node* deleteFirstOccurrence(struct Node* head, int key) {
    if (head == NULL)
        return head;

    struct Node *temp = head, *prev = NULL;

    // If head node contains key
    if (temp->data == key) {
        head = temp->next;
        free(temp);
        return head;
    }

    // Search for key
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key not found
    if (temp == NULL)
        return head;

    // Unlink node
    prev->next = temp->next;
    free(temp);

    return head;
}

// Print list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    int n, value, key;
    struct Node* head = NULL;

    // Input number of nodes
    scanf("%d", &n);

    // Input list elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        head = insertEnd(head, value);
    }

    // Input key to delete
    scanf("%d", &key);

    // Delete first occurrence
    head = deleteFirstOccurrence(head, key);

    // Print updated list
    printList(head);

    return 0;
}