#include <stdio.h>
#include <stdlib.h>
#define LENGTH 5  

typedef struct {
    int *elem;   
    int count; 
    int max;   
} List;

List initialize(List L){
    L.elem = (int*) malloc(sizeof(int) * LENGTH);
    L.max = LENGTH;
    L.count = 0;
    return L;
}

List resize(List L){
    L.max *= 2;
    L.elem = (int*) realloc(L.elem, sizeof(int) * L.max);
    return L;
}

List insertPos(List L, int data, int position){

    if(position < 0 || position > L.count){
        printf("Invalid Position\n");
        return L;
    }

    if(L.count == L.max){
        L = resize(L);
    }

    for(int i = L.count; i > position; i--){
        L.elem[i] = L.elem[i - 1];
    }

    L.elem[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position){

    if(position < 0 || position >= L.count){
        printf("Invalid Position\n");
        return L;
    }

    for(int i = position; i < L.count - 1; i++){
        L.elem[i] = L.elem[i + 1];
    }

    L.count--;
    return L;
}

int locate(List L, int data){
    for(int i = 0; i < L.count; i++){
        if(L.elem[i] == data){
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data){

    if(L.count == L.max){
        L = resize(L);
    }

    int i;
    for(i = L.count - 1; i >= 0 && L.elem[i] > data; i--){
        L.elem[i + 1] = L.elem[i];
    }

    L.elem[i + 1] = data;
    L.count++;
    return L;
}

void display(List L){
    for(int i = 0; i < L.count; i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}


int main(){
    List L;
    L = initialize(L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 30, 1);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 40, 3);
    L = insertPos(L, 50, 4);
    L = insertPos(L, 60, 5);   

    display(L);

    L = deletePos(L, 2);
    display(L);

    printf("Position of 40: %d\n", locate(L, 40));

    L = insertSorted(L, 25);
    display(L);

    free(L.elem);
    return 0;
}
