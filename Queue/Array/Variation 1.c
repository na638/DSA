#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*---------------------------------------------*/
 // Queue is a static array with count, front, and rear.
/*---------------------------------------------*/
#define MAX 10

typedef struct {
    int items[MAX];
    int count;
    int front;
    int rear;
} Queue;

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->count = 0;
    q->front = 0;
    q->rear = -1;
    return q;
}

bool isFull(Queue* q) {
    return (q->count == MAX);
}

bool isEmpty(Queue* q) {
    return (q->count == 0);
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is Full\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    q->count++;
}

void enqueueUnique(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is Full\n");
        return;
    }

    if (!isEmpty(q)) {
        int i;
        int index = q->front;

        for (i = 0; i < q->count; i++) {
            if (q->items[index] == value) {
                printf("Value already exists. Not inserted.\n");
                return;
            }
            index = (index + 1) % MAX;
        }
    }

    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    q->count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    int value = q->items[q->front];

    if (q->count == 1) {
        q->front = 0;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }

    q->count--;
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

    int i;
    int index = q->front;

    for (i = 0; i < q->count; i++) {
        printf("%d ", q->items[index]);
        index = (index + 1) % MAX;
    }
    printf("\n");
}



int main() {
    Queue* Q = initialize();

    printf("Enqueue 1, 3, 5\n");
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    display(Q);

    printf("\nEnqueueUnique 3 (duplicate)\n");
    enqueueUnique(Q, 3);
    display(Q);

    printf("\nEnqueueUnique 4 (new value)\n");
    enqueueUnique(Q, 4);
    display(Q);

    printf("\nDequeue:\n");
    int removed = dequeue(Q);
    printf("Removed: %d\n", removed);
    display(Q);

    printf("\nFront Value: %d\n", frontValue(Q));

    return 0;
}