#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

void initialize(List *L);
void insertPos(List *L, int data, int pos);
void deletePos(List *L, int pos);
int locate(List *L, int data);
int retrieve(List *L, int pos);
void insertSorted(List *L, int data);
void display(List *L);
void makeNULL(List *L);

int main() {
    List L;
    initialize(&L);

    insertPos(&L, 10, 0);
    insertPos(&L, 20, 1);
    insertPos(&L, 30, 2);
    display(&L);

    deletePos(&L, 1);
    display(&L);

    printf("Locate 30: %d\n", locate(&L, 30));
    printf("Retrieve pos 3: %d\n", retrieve(&L, 3));

    insertSorted(&L, 40);
    display(&L);

    return 0;
}

void initialize(List *L) {
    int i;
    L->count = 0;
    for (i = 0; i < MAX; i++) {
        L->elem[i] = -1;
    }
}

void insertPos(List *L, int data, int pos) {
    int i;
    if (pos < 0 || pos > L->count || L->count == MAX) {
        return;
    }

    for (i = L->count; i > pos; i--) {
        L->elem[i] = L->elem[i - 1];
    }

    L->elem[pos] = data;
    L->count++;
}

void deletePos(List *L, int pos) {
    int i;
    
    if (pos < 0 || pos >= L->count) {
        return;
    }

    for (i = pos; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }

    L->elem[L->count - 1] = -1;
    L->count--;
}

int locate(List *L, int data) {
    int i;
    
    for (i = 0; i < L->count; i++) {
        if (L->elem[i] == data) {
            return i;
        }
    }
    return -1;
}

int retrieve(List *L, int pos) {
    if (pos < 0 || pos >= L->count) {
        return -1;
    }
    return L->elem[pos];
}

void insertSorted(List *L, int data) {
    if (L->count == MAX) return;

    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) {
        pos++;
    }
    insertPos(L, data, pos);
}

void display(List *L) {
    for (int i = 0; i < MAX; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

void makeNULL(List *L) {
    L->count = 0;
    for (int i = 0; i < MAX; i++) {
        L->elem[i] = -1;
    }
}
