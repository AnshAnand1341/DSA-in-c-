#include <stdio.h>
#include <stdlib.h>

/* ── Queue (array-based, circular) ── */
#define MAX 100

typedef struct {
    int data[MAX];
    int front, rear, size;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = q->size = 0; }
int  isQueueEmpty(Queue *q) { return q->size == 0; }
void enqueue(Queue *q, int val) {
    q->data[q->rear] = val;
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}
int dequeue(Queue *q) {
    int val = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

/* ── Stack (array-based) ── */
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int  isStackEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, int val) { s->data[++s->top] = val; }
int  pop(Stack *s)           { return s->data[s->top--]; }

/* ── Reverse queue using stack ── */
void reverseQueue(Queue *q) {
    Stack s;
    initStack(&s);

    /* Step 1: Dequeue all → push to stack */
    while (!isQueueEmpty(q))
        push(&s, dequeue(q));

    /* Step 2: Pop all → enqueue back */
    while (!isStackEmpty(&s))
        enqueue(q, pop(&s));
}

int main() {
    int n;
    scanf("%d", &n);

    Queue q;
    initQueue(&q);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        enqueue(&q, x);
    }

    reverseQueue(&q);

    /* Print output */
    while (!isQueueEmpty(&q)) {
        printf("%d", dequeue(&q));
        if (q.size > 0) printf(" ");
    }
    printf("\n");

    return 0;
}