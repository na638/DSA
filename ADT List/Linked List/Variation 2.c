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

List* initialize() {
    List *L = (List*)malloc(sizeof(List));

    if (L == NULL) {
        return NULL;
    }

    L->head = NULL;
    L->count = 0;
    return L;
}

void empty(List *list) {
    Node *temp;

    while (list->head != NULL) {
        temp = list->head;
        list->head = temp->next;
        free(temp);
    }

    list->count = 0;
}

void insertFirst(List *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;

    list->count++;
}

void insertLast(List *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        cur->next = newNode;
    }

    list->count++;
}

void insertPos(List *list, int data, int index) {
    Node *newNode, *current;
    int i;

    if (index < 0 || index > list->count) {
        printf("Invalid Position\n");
    }else if (index == 0) {
        insertFirst(list, data);
    }else if (index == list->count) {
        insertLast(list, data);
    } else {
        newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;

        Node *curr = list->head;
        for (i = 0; i < index - 1; i++) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;

        list->count++;
    }
}


void deleteStart(List *list) {
    Node *curr = list->head;

    if (list->head != NULL) {
        list->head = curr->next;
        free(curr);
        list->count--;
    }
}

/* deleteLast */
void deleteLast(List *list) {
    Node *current;
    int i;

    if (list->head == NULL) {
        return;
    }

    if (list->count == 1) {
        free(list->head);
        list->head = NULL;
        list->count--;
        return;
    }

    current = list->head;
    for (i = 0; i < list->count - 2; i++) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;

    list->count--;
}

void deletePos(List *list, int index) {
    Node *temp;
    int i;

    if (index >= 0 && index < list->count) {
        if (index == 0) {
            deleteStart(list);
        } else {
            Node *curr = list->head;
            for (i = 0; i < index - 1; i++) {
                curr = curr->next;
            }

            temp = curr->next;
            curr->next = temp->next;
            free(temp);

            list->count--;
        }
    }
}

int retrieve(List *list, int index) {
    
    int i;

    if (index < 0 || index >= list->count) {
        return -1;
    }

    Node *cur = list->head;
    for (i = 0; i < index; i++) {
        curr = curr->next;
    }

    return curr->data;
}

int locate(List *list, int data) {
    int index = 0;

    if (list->head == NULL) {
        return -1;
    }

    Node *curr = list->head;
    while (curr != NULL) {
        if (curr->data == data) {
            return index;
        }
        curr = curr->next;
        index++;
    }

    return -1;
}

void display(List *list) {
    Node *currt = list->head;

    while (curr != NULL) {
        printf("%d ", curr->data);
        current = curr->next;
    }
    printf("\n");
}