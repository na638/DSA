#include <stdio.h>
#define MAX 100

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize(){
    List L;
    L.count = 0;
    return L;
}

List insertPos(List L, int value, int pos){
    if(L.count >= MAX){
        printf("List Full\n");
        return L;
    }

    if(pos < 1 || pos > L.count + 1){
        printf("Invalid Position\n");
        return L;
    }

    for(int i = L.count; i >= pos; i--){
        L.elem[i] = L.elem[i - 1];
    }

    L.elem[pos - 1] = value;
    L.count++;
    return L;
}

List deletePos(List L, int pos){
    if(pos < 1 || pos > L.count){
        printf("Invalid Position\n");
        return L;
    }

    for(int i = pos - 1; i < L.count - 1; i++){
        L.elem[i] = L.elem[i + 1];
    }

    L.count--;
    return L;
}

List insertSorted(List L, int value){
    int i;

    if(L.count >= MAX){
        printf("List Full\n");
        return L;
    }

    for(i = L.count - 1; i >= 0 && L.elem[i] > value; i--){
        L.elem[i + 1] = L.elem[i];
    }

    L.elem[i + 1] = value;
    L.count++;
    return L;
}

int Locate(List L, int value){
    for(int i = 0; i < L.count; i++){
        if(L.elem[i] == value){
            return i + 1;
        }
    }

    return -1;
}

void display(List L){
    for(int i = 0; i < L.count; i++){
        printf("%d ", L.elem[i]);
    }

    printf("\n");
}


int main() {
    List L;
    L = initialize();

    L.elem[0] = 1;
    L.elem[1] = 3;
    L.elem[2] = 2;
    L.elem[3] = 5;
    L.count = 4;

    L = insertPos(L, 4, 2);
    display(L);  

    L = deletePos(L, 1);
    display(L);   

    L = insertSorted(L, 3);
    display(L);   

    printf("Location of 5: %d\n", Locate(L, 5));
}