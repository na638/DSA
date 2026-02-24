/*---------------------------------------------*/
//List is a dynamic array and accessed by pointer.
/*---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 4

typedef struct {
    int *elem;
    int count;
    int max;
} List;

void initialize(List *L){
    L->elem = (int*) malloc(sizeof(int) * LENGTH);
    L->max = LENGTH;
    L->count = 0;
}

void resize(List *L){
    L->max *= 2;
    L->elem = (int*) realloc(L->elem, sizeof(int) * L->max);
}

void insertPos(List *L, int data, int position){
    if(position < 0 || position > L->count){
        printf("Invalid Position\n");
        return;
    }
    if(L->count == L->max){
        resize(L);
    }
    for(int i = L->count; i > position; i--){
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[position] = data;
    L->count++;
}

void deletePos(List *L, int position){
    if(position < 0 || position >= L->count){
        printf("Invalid Position\n");
        return;
    }
    for(int i = position; i < L->count - 1; i++){
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
}

int locate(List *L, int data){
    for(int i = 0; i < L->count; i++){
        if(L->elem[i] == data){
            return i;
        }
    }
    return -1;
}

int retrieve(List *L, int position){
    if(position < 0 || position >= L->count){
        return -1;
    }
    return L->elem[position];
}

void insertSorted(List *L, int data){
    if(L->count == L->max){
        resize(L);
    }
    int i;
    for(i = L->count - 1; i >= 0 && L->elem[i] > data; i--){
        L->elem[i + 1] = L->elem[i];
    }
    L->elem[i + 1] = data;
    L->count++;
}

void display(List *L){
    for(int i = 0; i < L->count; i++){
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

void makeNULL(List *L){
    free(L->elem);
    L->elem = NULL;
}

int main(){
    List L;
    initialize(&L);

    insertPos(&L, 1, 0);
    insertPos(&L, 3, 1);
    insertPos(&L, 2, 2);
    insertPos(&L, 5, 3);

    display(&L);

    insertPos(&L, 4, 2);
    display(&L);

    deletePos(&L, 1);
    display(&L);

    printf("Locate 5: %d\n", locate(&L, 5));
    printf("Retrieve index 2: %d\n", retrieve(&L, 2));

    insertSorted(&L, 8);
    display(&L);

    makeNULL(&L);
    return 0;
}
