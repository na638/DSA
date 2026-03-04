#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

/*---------------------------------------------*/
 // Stack is a static array.
 // TOP starts from the LAST position and moves to the beginning.
 // It is initialized to MAX indicating empty.
/*---------------------------------------------*/

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack* initialize() {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->top = MAX;
    return s;
}

bool isFull(Stack *s) {
    return s->top == 0;
}

bool isEmpty(Stack *s) {
    return s->top == MAX;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
    } else {
        --s->top;
        s->items[s->top] = value;
    }
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int value = s->items[s->top];
    ++s->top;
    return value;
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

int top(Stack *s) {
    return s->top;
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
    } else {
        for (int i = s->top; i < MAX; i++) {
            printf("%d ", s->items[i]);
        }
        printf("\n");
    }
}

void pushUnique(Stack *s, int value) {
    Stack *temp = initialize();
    bool found = false;

    while (!isEmpty(s)) {
        int elem = pop(s);
        if (elem == value) {
            found = true;
        }
        push(temp, elem);
    }

    while (!isEmpty(temp)) {
        push(s, pop(temp));
    }

    if (!found) {
        push(s, value);
    }

    free(temp);
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