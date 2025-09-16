#include <stdio.h>
#include <stdlib.h>

#define LENGTH 5

typedef struct {
    int *data;
    int count;
    int max;
} List;

void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int locate(List *L, int data);
int retrieve(List *L, int position);
void insertSorted(List *L, int data);
void display(List *L);
void resize(List *L);
void makeNULL(List *L);

int main() {
    List L;
    initialize(&L);

    insertPos(&L, 10, 0);
    insertPos(&L, 20, 1);
    insertPos(&L, 30, 2);
    insertPos(&L, 40, 3);
    insertPos(&L, 50, 4);

    display(&L);

    deletePos(&L, 2);
    display(&L);

    printf("Locate 40: %d\n", locate(&L, 40));
    printf("Retrieve at pos 1: %d\n", retrieve(&L, 1));

    insertSorted(&L, 25);
    display(&L);

    makeNULL(&L);
    return 0;
}

void initialize(List *L) {
    L->data = (int*)malloc(sizeof(int) * LENGTH);
    L->count = 0;
    L->max = LENGTH;
    for (int i = 0; i < L->max; i++) {
        L->data[i] = -1;
    }
}

void insertPos(List *L, int data, int position) {
    if (position < 0 || position > L->count) return;
    if (L->count == L->max) resize(L);
    for (int i = L->count; i > position; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[position] = data;
    L->count++;
}

void deletePos(List *L, int position) {
    if (position < 0 || position >= L->count) return;
    for (int i = position; i < L->count - 1; i++) {
        L->data[i] = L->data[i + 1];
    }
    L->data[L->count - 1] = -1;
    L->count--;
}

int locate(List *L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->data[i] == data) return i;
    }
    return -1;
}

int retrieve(List *L, int position) {
    if (position < 0 || position >= L->count) return -1;
    return L->data[position];
}

void insertSorted(List *L, int data) {
    if (L->count == L->max) resize(L);
    int i = L->count - 1;
    while (i >= 0 && L->data[i] > data) {
        L->data[i + 1] = L->data[i];
        i--;
    }
    L->data[i + 1] = data;
    L->count++;
}

void display(List *L) {
    for (int i = 0; i < L->max; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

void resize(List *L) {
    int newMax = L->max * 2;
    int *newData = (int*)malloc(sizeof(int) * newMax);
    for (int i = 0; i < L->count; i++) {
        newData[i] = L->data[i];
    }
    for (int i = L->count; i < newMax; i++) {
        newData[i] = -1;
    }
    free(L->data);
    L->data = newData;
    L->max = newMax;
}

void makeNULL(List *L) {
    free(L->data);
    L->data = NULL;
    L->count = 0;
    L->max = 0;
}
