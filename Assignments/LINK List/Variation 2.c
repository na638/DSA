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

List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deleteLast(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);

List* initialize() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL){
      return NULL;  
    }
    
    list->head = NULL;
    list->count = 0;
    return list;
    
}

void empty(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    newNode->data = data;
    newNode->next = list->head;
    
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    }
    
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    list->count++;
}

void insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count){
        return;
    }

    if (index == 0) {
        insertFirst(list, data);
    } 
    if (index == list->count) {
        insertLast(list, data);
    }
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node *current = list->head;
    int i = 0;
    while (current != NULL && i < index - 1) {
        current = current->next;
            i++;
    }

    newNode->next = current->next;
    current->next = newNode;
    list->count++;
    
}

void deleteStart(List *list) {
    if (list->head == NULL){
        return;
    }

    Node *temp = list->head;
    list->head = list->head->next;
    
    free(temp);
    list->count--;
}

void deleteLast(List *list) {
    if (list->head == NULL){
        return;
    } 

    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
    } 
    
    Node *current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
        
    }
    
    free(current->next);
    current->next = NULL;
    
    list->count--;
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count){
        return;
    }

    if (index == 0) {
        deleteStart(list);
    }
    Node *current = list->head;
    int i = 0;
    while (i < index - 1) {
        current = current->next;
        i++;
    }
    
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
}

int retrieve(List *list, int index) {
    if (index < 0 || index >= list->count){
        return -1;
    }

    Node *current = list->head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    return current->data;
}

int locate(List *list, int data) {
    Node *current = list->head;
    int index = 0;

    while (current != NULL) {
        if (current->data == data){
            return index;
        }
        
        current = current->next;
        index++;
    }
    return -1;
}

void display(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
    printf("\n");
}


int main() {
    List *list = initialize();

    insertFirst(list, 10);
    insertLast(list, 20);
    insertFirst(list, 30);
    insertPos(list, 40, 2);

    display(list);
    
    printf("Retrieve index 1: %d\n", retrieve(list, 1));
    printf("Locate data 20: %d\n", locate(list, 20));

    printf("\nAfter deleteing:\n");
    deleteStart(list);
    deleteLast(list);
    deletePos(list, 1);

    display(list);

   
    empty(list);
    free(list);

    return 0;
}
