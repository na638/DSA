#include <stdio.h>
#include <string.h>
#define MAX 10

typedef struct {
    char name[50];
    char gender;
    int age;
    int next;
} Node;

typedef struct {
    Node nodes[MAX];
    int head;
    int avail;
} CursorList;

void initialize(CursorList *L);
int allocNode(CursorList *L);
void freeNode(CursorList *L, int index);
void insertFirst(CursorList *L, char name[], int age, char gender);
void printList(CursorList L);

void initialize(CursorList *L) {
    int i;
    for (i = 0; i < MAX - 1; i++) {
        L->nodes[i].next = i + 1;
    }
    L->nodes[MAX - 1].next = -1;
    L->avail = 0;
    L->head = -1;
}

int allocNode(CursorList *L) {
    if (L->avail == -1) return -1;
    int index = L->avail;
    L->avail = L->nodes[index].next;
    return index;
}

void freeNode(CursorList *L, int index) {
    L->nodes[index].next = L->avail;
    L->avail = index;
}

void insertFirst(CursorList *L, char name[], int age, char gender) {
    int index = allocNode(L);
    if (index != -1) {
        strcpy(L->nodes[index].name, name);
        L->nodes[index].age = age;
        L->nodes[index].gender = gender;
        L->nodes[index].next = L->head;
        L->head = index;
    }
}

void printList(CursorList L) {
    if (L.head == -1) {
        printf("-1\n");
        return;
    }
    int curr = L
