#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*---------------------------------------------*/
 //Queue is a static array with count, front, and rear.
/*---------------------------------------------*/

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack* initialize() {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isFull(Stack *s) {
    return false;
}

bool isEmpty(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
    } else {
        Node *temp = s->top;
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void pushUnique(Stack *s, int value) {
    Stack *tempStack = initialize();
    bool found = false;

    while (!isEmpty(s)) {
        int elem = pop(s);
        if (elem == value) {
            found = true;
        }
        push(tempStack, elem);
    }

    while (!isEmpty(tempStack)) {
        push(s, pop(tempStack));
    }

    if (!found) {
        push(s, value);
    } else {
        printf("Value %d already exists. Not pushed.\n", value);
    }

    free(tempStack);
}

int main() {
    Stack *S = initialize();

    push(S, 10);
    push(S, 20);
    push(S, 30);

    display(S);

    pushUnique(S, 20);
    pushUnique(S, 40);

    display(S);

    return 0;
}