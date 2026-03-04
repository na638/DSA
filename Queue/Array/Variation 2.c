#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*---------------------------------------------*/
//Queue is a static array with front, rear, and a sacrificial space.
//Sacrificial space will always be the space before front.
// [ (front - 1 + MAX) % MAX ]
/*---------------------------------------------*/
#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 1;
    q->rear = 0;
    return q;
}

bool isEmpty(Queue* q) {
    return (q->front == (q->rear + 1) % MAX);
}

bool isFull(Queue* q) {
    return (q->front == (q->rear + 2) % MAX);
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is Full\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}


void enqueueUnique(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is Full\n");
        return;
    }

    if (!isEmpty(q)) {
        int i = q->front;

        while (i != (q->rear + 1) % MAX) {
            if (q->items[i] == value) {
                printf("Value already exists. Not inserted.\n");
                return;
            }
            i = (i + 1) % MAX;
        }
    }


    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}


int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return value;
}

int frontValue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    return q->items[q->front];
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return;
    }

    int i = q->front;

    while (i != (q->rear + 1) % MAX) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Queue* Q = initialize();

    printf("Enqueue 10, 20, 30\n");
    enqueue(Q, 10);
    enqueue(Q, 20);
    enqueue(Q, 30);
    display(Q);

    printf("\nEnqueueUnique 20 (duplicate)\n");
    enqueueUnique(Q, 20);
    display(Q);

    printf("\nEnqueueUnique 40 (new value)\n");
    enqueueUnique(Q, 40);
    display(Q);

    printf("\nDequeue:\n");
    int removed = dequeue(Q);
    printf("Removed: %d\n", removed);
    display(Q);

    printf("\nFront Value: %d\n", frontValue(Q));

    return 0;
}