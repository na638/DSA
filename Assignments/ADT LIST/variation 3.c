#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elem;
    int count;
    int max;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);

int main() {
    List L;
    L = initialize(L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 30, 2);
    display(L);

    L = deletePos(L, 1);
    display(L);

    printf("Locate 30: %d\n", locate(L, 30));

    L = insertSorted(L, 40);
    L = insertSorted(L, 50);

    display(L);

    free(L.elem);
    return 0;
}

List initialize(List L) {
    L.elem = (int*)malloc(LENGTH * sizeof(int));
    L.count = 0;
    L.max = LENGTH;
    return L;
}

List insertPos(List L, int data, int position) {
    if (position <= L.count && position >= 0) {
        if (L.count == L.max) {
            L = resize(L);
        }
        for (int i = L.count; i > position; i--) {
            L.elem[i] = L.elem[i - 1];
        }
        L.elem[position] = data;
        L.count++;
    }
    return L;
}

List deletePos(List L, int position) {
    if (position < L.count && position >= 0) {
        for (int i = position; i < L.count - 1; i++) {
            L.elem[i] = L.elem[i + 1];
        }
        L.count--;
    }
    return L;
}

int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elem[i] == data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    if (L.count == L.max) {
        L = resize(L);
    }
    int i = L.count - 1;
    while (i >= 0 && L.elem[i] > data) {
        L.elem[i + 1] = L.elem[i];
        i--;
    }
    L.elem[i + 1] = data;
    L.count++;
    return L;
}

void display(List L) {
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

List resize(List L) {
    int newMax = L.max * 2;
    int *newElem = (int*)malloc(newMax * sizeof(int));
    for (int i = 0; i < L.count; i++) {
        newElem[i] = L.elem[i];
    }
    free(L.elem);
    L.elem = newElem;
    L.max = newMax;
    return L;
}

