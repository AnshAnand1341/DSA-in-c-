#include <stdio.h>
#include <string.h>

#define EMPTY -1

int hash(int key, int size) {
    return key % size;
}

// Insert using quadratic probing
void insert(int table[], int size, int key) {
    int index = hash(key, size);

    if (table[index] == EMPTY) {
        table[index] = key;
        return;
    }

    // Collision handling using quadratic probing
    for (int i = 1; i < size; i++) {
        int newIndex = (index + i * i) % size;

        if (table[newIndex] == EMPTY) {
            table[newIndex] = key;
            return;
        }
    }

    printf("Hash table is full\n");
}

// Search using quadratic probing
int search(int table[], int size, int key) {
    int index = hash(key, size);

    for (int i = 0; i < size; i++) {
        int newIndex = (index + i * i) % size;

        if (table[newIndex] == key)
            return 1;

        if (table[newIndex] == EMPTY)
            return 0;
    }

    return 0;
}

int main() {
    int m, n;
    scanf("%d", &m);   // size of hash table
    scanf("%d", &n);   // number of operations

    int table[m];

    // Initialize table
    for (int i = 0; i < m; i++)
        table[i] = EMPTY;

    char op[10];
    int key;

    for (int i = 0; i < n; i++) {
        scanf("%s %d", op, &key);

        if (strcmp(op, "INSERT") == 0) {
            insert(table, m, key);
        } else if (strcmp(op, "SEARCH") == 0) {
            if (search(table, m, key))
                printf("FOUND\n");
            else
                printf("NOT FOUND\n");
        }
    }

    return 0;
}