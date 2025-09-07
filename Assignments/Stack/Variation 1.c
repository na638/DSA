#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack* initialize();
void push(Stack *NewStack, int value);
int pop(Stack *NewStack);
int peek(Stack *NewStack);
void display(Stack *NewStack);

int main() {
    Stack *NewStack = initialize();

    push(NewStack, 10);
    push(NewStack, 20);
    push(NewStack, 30);
    push(NewStack, 40);
    display(NewStack);

    printf("\nPeek: %d\n", peek(NewStack));

    int value = pop(NewStack);
    printf("Popped: %d\n", value);
    display(NewStack);

    push(NewStack, 50);
    printf("\nAfter pushing 40:\n");
    display(NewStack);

    free(NewStack);
    return 0;
}

Stack* initialize() {
    
    Stack *NewStack = (Stack*)malloc(sizeof(Stack));
    
    if(NewStack == NULL){
        exit(1);
    }
    
    
    NewStack->top = -1;
    return NewStack;
}

void push(Stack *NewStack, int value) {
    if(NewStack->top == MAX - 1){
        return;
    }
    
    NewStack->top++;
    NewStack->items[NewStack->top] = value;
    
}

int pop(Stack* NewStack) {
    if(NewStack->top == -1){
        return -1;
    }
    
    int value = NewStack->items[NewStack->top];
    NewStack->top--;
    
    return value;
 
}

int peek(Stack* NewStack) {
    if(NewStack->top == -1){
        return -1;
    }
    
    return NewStack->items[NewStack->top];
}

void display(Stack* NewStack) {
    
    int i;
    if (NewStack->top == 1){
        return;
    }
    
    printf("Stack elements:\n");
    
    for(i = NewStack->top; i >= 0; i--){
        printf("%d ", NewStack->items[i]);
    }
    printf("\n");
}
