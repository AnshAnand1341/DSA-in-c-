#include <stdio.h>
#include <stdlib.h>

// Define structure for node
struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, value;
    
    scanf("%d", &n);
    
    if (n <= 0) {
        return 0;
    }
    
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        
        // Allocate memory for new node
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
            temp = head;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    
    // Make it circular
    temp->next = head;
    
    // Traverse and print circular linked list
    struct Node* current = head;
    
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    
    return 0;
}