#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------*/
//List is a Linked List and accessed by value.
/*---------------------------------------------*/
typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;


List initialize() {
    List L;
    L.head = NULL;
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position) {
    Node *newNode, *trav;
    int i;

    if (position < 0 || position > L.count) {
        printf("Invalid Position\n");
        return L;
    } 

    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if (position == 0) {
        newNode->next = L.head;
        L.head = newNode;
    } else {
        trav = L.head;
        for (i = 0; i < position - 1; i++) {
            trav = trav->next;
        }
        newNode->next = trav->next;
        trav->next = newNode;
    }

    L.count++;
    return L;
}

List deletePos(List L, int position) {
    Node *temp, *trav;
    int i;

    if (position < 0 || position >= L.count) {
        return L;
    }

    if (position == 0) {
        temp = L.head;
        L.head = temp->next;
        free(temp);
    } else {
        trav = L.head;
        for (i = 0; i < position - 1; i++) {
            trav = trav->next;
        }
        temp = trav->next;
        trav->next = temp->next;
        free(temp);
    }

    L.count--;
    return L;
}

int locate(List L, int data) {
    Node *trav = L.head;
    int pos = 0;

    while (trav != NULL) {
        if (trav->data == data) {
            return pos;
        }
        trav = trav->next;
        pos++;
    }

    return -1;
}

int retrieve(List L, int position) {
    Node *trav = L.head;
    int i;

    if (position < 0 || position >= L.count) {
        return -1;
    }

    for (i = 0; i < position; i++) {
        trav = trav->next;
    }

    return trav->data;
}

List insertSorted(List L, int data) {
    Node *newNode, *trav;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    if (L.head == NULL || data < L.head->data) {
        newNode->next = L.head;
        L.head = newNode;
    } else {
        trav = L.head;
        while (trav->next != NULL && trav->next->data < data) {
            trav = trav->next;
        }
        newNode->next = trav->next;
        trav->next = newNode;
    }

    L.count++;
    return L;
}

void display(List L) {
    Node *trav = L.head;

    while (trav != NULL) {
        printf("%d ", trav->data);
        trav = trav->next;
    }
    printf("\n");
}

List makeNULL(List L) {
    Node *temp;

    while (L.head != NULL) {
        temp = L.head;
        L.head = temp->next;
        free(temp);
    }

    L.count = 0;
    return L;
}

/* MAIN — NOT main(void) */
int main() {
    List L;

    L = initialize();

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 15, 1);
    display(L);

    L = insertSorted(L, 12);
    display(L);

    L = deletePos(L, 2);
    display(L);

    printf("Locate 20: %d\n", locate(L, 20));
    printf("Retrieve pos 1: %d\n", retrieve(L, 1));

    L = makeNULL(L);

    return 0;
}