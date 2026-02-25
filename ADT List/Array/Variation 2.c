#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/*---------------------------------------------*/
//List is a static array and accessed by pointer.
/*---------------------------------------------*/
typedef struct {
    int elem[MAX];
    int count;
    int max;
} List;

typedef List* EPtr;

void initialize(EPtr L){
    L->count = 0;
    L->max = MAX;
}

void insertPos(EPtr L, int value, int pos){
    if(L->count >= L->max){
        printf("List Full\n");
    } else if(pos < 0 || pos > L->count){
        printf("Invalid Position\n");
        
    } else{
        for(int i = L->count; i > pos; i--){
            L->elem[i] = L->elem[i - 1];
        }   
        L->elem[pos] = value;
        L->count++;
    }
}

void deletePos(EPtr L, int pos){
    if(pos < 0 || pos >= L->count){
        printf("Invalid Position\n");
    } else {
        for(int i = pos; i < L->count - 1; i++){
            L->elem[i] = L->elem[i + 1];
        }
        L->count--;
    }
}

void insertSorted(EPtr L, int value){
    if(L->count >= L->max){
        printf("List Full\n");
    } else {
        int i;
        for(i = L->count - 1; i >= 0 && L->elem[i] > value; i--){
        L->elem[i + 1] = L->elem[i];
        }

        L->elem[i + 1] = value;
        L->count++;
    }
}

int Locate(EPtr L, int value){
    for(int i = 0; i < L->count; i++){
        if(L->elem[i] == value){
            return i;  
        }
    }
    return -1;
}

void display(EPtr L){
    for(int i = 0; i < L->count; i++){
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

int retrieve(EPtr L, int pos){
    if(pos < 0 || pos >= L->count){
        return -1;
    }
    return L->elem[pos];
}

void makeNULL(EPtr L){
    free(L);
}

int main(){
    EPtr L = (EPtr) malloc(sizeof(List));
    if(L == NULL) return 1;

    initialize(L);

    insertPos(L, 1, 0);
    insertPos(L, 3, 1);
    insertPos(L, 2, 1);
    insertPos(L, 5, 3);

    display(L);  

    deletePos(L, 1);
    display(L);  

    insertSorted(L, 4);
    display(L);  

    printf("Position of 5: %d\n", Locate(L, 5));
    printf("Element at index 2: %d\n", retrieve(L, 2));

    makeNULL(L);
    return 0;
}
