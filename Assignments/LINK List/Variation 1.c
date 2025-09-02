#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List initialize();
List empty(List list);
List insertFirst(List list, int data);
List insertLast(List list, int data);
List insertPos(List list, int data, int index);
List deleteStart(List list);
List deleteLast(List list);
List deletePos(List list, int index);
int retrieve(List list, int index);
int locate(List list, int data);
void display(List list);

int main() {
    List myList = initialize();

    myList = insertFirst(myList, 10);
    myList = insertLast(myList, 20);
    myList = insertFirst(myList, 30);
    myList = insertPos(myList, 40, 1);

    display(myList);

    printf("Retrieve index 1: %d\n", retrieve(myList, 1));
    printf("Locate data 20: %d\n", locate(myList, 20));

    printf("\nAfter deleting:\n");
    myList = deleteStart(myList);
    myList = deleteLast(myList);
    myList = deletePos(myList, 0);

    display(myList);

    myList = empty(myList);

    return 0;
}

List initialize() {
    List newList;
    newList.head = NULL;
    newList.count = 0;
    return newList;
}

List insertFirst(List list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list.head;
    list.head = newNode;
    list.count++;
    return list;
}

List insertLast(List list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list.head == NULL) {
        list.head = newNode;
    } else {
        Node *temp = list.head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    list.count++;
    return list;
}

List insertPos(List list, int data, int index) {
    if (index < 0 || index > list.count) {
        return list;
    }

    if (index == 0) {
        return insertFirst(list, data);
    }
    if (index == list.count) {
        return insertLast(list, data);
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node *temp = list.head;
    int i = 0;
    while (i < index - 1) {
        temp = temp->next;
        i++;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    list.count++;
    return list;
}

List deleteStart(List list) {
    if (list.head == NULL) return list;

    Node *temp = list.head;
    list.head = list.head->next;
    free(temp);

    list.count--;
    return list;
}

List deleteLast(List list) {
    if (list.head == NULL) return list;

    if (list.head->next == NULL) {
        free(list.head);
        list.head = NULL;
    } else {
        Node *current = list.head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }

    list.count--;
    return list;
}

List deletePos(List list, int index) {
    if (index < 0 || index >= list.count) return list;

    if (index == 0) {
        return deleteStart(list);
    }

    Node *current = list.head;
    int i = 0;
    while (i < index - 1) {
        current = current->next;
        i++;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);

    list.count--;
    return list;
}

int retrieve(List list, int index) {
    if (index < 0 || index >= list.count) {
        return -1;
    }

    Node *current = list.head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }

    return current->data;
}

int locate(List list, int data) {
    Node *current = list.head;
    int index = 0;

    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void display(List list) {
    Node *current = list.head;

    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

List empty(List list) {
    Node *current = list.head;
    Node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list.head = NULL;
    list.count = 0;
    return list;
}
