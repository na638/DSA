#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*---------------------------------------------*/
//Queue is a linked list with front and rear. 
//FRONT is a pointer to the first node of the list, 
//REAR is a pointer to the last node of the list.
/*---------------------------------------------*/
typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isEmpty(Queue* q) {
    return (q->front == NULL);
}


bool isFull(Queue* q) {
    return false;
}


void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void enqueueUnique(Queue* q, int value) {
    Node* temp = q->front;

    while (temp != NULL) {
        if (temp->data == value) {
            printf("Value %d already exists. Not inserted.\n", value);
            return;
        }
        temp = temp->next;
    }

    enqueue(q, value);
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    Node* temp = q->front;
    int value = temp->data;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int frontValue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }
    return q->front->data;
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return;
    }

    Node* temp = q->front;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Queue* Q = initialize();

    printf("Enqueue 1, 3, 5:\n");
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    display(Q);

    printf("\nEnqueueUnique 3 (duplicate):\n");
    enqueueUnique(Q, 3);
    display(Q);

    printf("\nEnqueueUnique 4 (new value):\n");
    enqueueUnique(Q, 4);
    display(Q);

    printf("\nDequeue:\n");
    int removed = dequeue(Q);
    printf("Removed: %d\n", removed);
    display(Q);

    printf("\nFront Value: %d\n", frontValue(Q));

    return 0;
}