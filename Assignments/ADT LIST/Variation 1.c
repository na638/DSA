#include <stdio.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize (List L);
List insertPos (List L, int pos, int data);
List deletePos(List L, int pos);
int locate (List L, int data);
List insertSorted (List L, int data);
void display(List L);

int main(){
    List L;
    L = initialize (L);

    L = insertPos(L, 0, 10);
    L = insertPos(L, 1, 20);
    L = insertPos(L, 2, 30);

    display(L);

    L = deletePos(L, 2);

    display(L);
    printf("\nLocation: %d\n\n", locate(L, 20));
    
    L = insertSorted(L, 40);
    display(L);
    
    return 0;
}

List initialize (List L){
   L.count = 0;
   int i;
   
   for(i = 0; i < MAX; i++){
       L.elem[i] = -1;
   }
   
   return L;
}

List insertPos (List L, int pos, int data){
    int i;
    
    for(i = L.count; i > pos; i--){
        L.elem[i] = L.elem[i - 1];
    }
    
    L.elem[i] = data;
    L.count++;
    return L;
}

List deletePos(List L, int pos){
  int i;
  
  for(i = pos; i < L.count; i++){
      L.elem[i] = -1;
  }
  
  return L;
}

int locate (List L, int data){
    int i;
    while(i < MAX){
        if(L.elem[i] != data){
            i++;
        }
    }
    
    return i;
}

List insertSorted (List L, int data){
    if(L.count >= MAX){
        return L;
    }
    
    int pos = 0;
    while(pos < L.count && L.elem[pos] < data){
        pos++;
    }
    return insertPos(L, pos, data);
}

void display(List L){
    int i;
    for(i = 0; i < MAX; i++){
        printf("%d ", L.elem[i]);
    }
    
    printf("\n");
}