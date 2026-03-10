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
    Node *newNode;
    int i;

    if (position < 0 || position > L.count) {
        printf("Invalid Position\n");
        return L;
    } else {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;

        if (position == 0) {
            newNode->next = L.head;
            L.head = newNode;
        } else {
            Node *curr = L.head;
            for (i = 0; i < position - 1; i++) {
            curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        L.count++;
        return L;
    }
}

List deletePos(List L, int position) {
    Node *temp;
    int i;

    if (position < 0 || position >= L.count) {
        printf("Invalid Pos\n");
        return L;
    } else {
        if (position == 0) {
            temp = L.head;
            L.head = temp->next;
            free(temp);
        } else {
            Node *curr = L.head;
            for (i = 0; i < position - 1; i++) {
                curr = curr->next;
            }
            temp = curr->next;
            curr->next = temp->next;
            free(temp);
        }
        L.count--;
        return L;
    }
}

int locate(List L, int data) {
    Node *curr = L.head;
    int pos = 0;

    while (curr != NULL) {
        if (curr->data == data) {
            return pos;
        }
        curr = curr->next;
        pos++;
    }

    return -1;
}

int retrieve(List L, int position) {
    Node *curr = L.head;
    int i;

    if (position < 0 || position >= L.count) {
        return -1;
    }

    for (i = 0; i < position; i++) {
        curr = curr->next;
    }

    return curr->data;
}

List insertSorted(List L, int data) {
    Node *newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if (L.head == NULL || data < L.head->data) {
        newNode->next = L.head;
        L.head = newNode;
    } else {
        Node *curr = L.head;
        while (curr->next != NULL && curr->next->data < data) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    L.count++;
    return L;
}

void display(List L) {
    Node *curr = L.head;

    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
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

int main() {
    List L;

    L = initialize();

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 30, 2);
    display(L);

    L = insertSorted(L, 25);
    display(L);

    L = deletePos(L, 2);
    display(L);

    printf("Locate 20: %d\n", locate(L, 20));
    printf("Retrieve pos 1: %d\n", retrieve(L, 1));

    L = makeNULL(L);

    return 0;
}
