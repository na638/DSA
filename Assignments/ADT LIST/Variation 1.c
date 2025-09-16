nclude <stdio.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize (List L);
List insertPos (List L, int data, int position);
List deletePos(List L, int position);
int locate (List L, int data);
List insertSorted (List L, int data);
void display(List L);

int main(){
    List L;
    L = initialize (L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 30, 2);

    display(L);

    L = deletePos(L, 0);
    
    display(L);
    // display(L);
     printf("\nLocation: %d\n\n", locate(L, 30));
    
    L = insertSorted(L, 40);
    display(L);
    
    return 0;
}

List initialize (List L){
   L.count = 0;
   
    for(int i = 0; i < MAX; i++){
        L.elem[i] = -1;
    }
    
    return L;
}

List insertPos (List L, int data, int position){
    if(position <= L.count && position <= MAX){
        for(int i = L.count; i > position; i--){
            L.elem[i] = L.elem[i - 1];
        }
        
        L.elem[position] = data;
        L.count++;
    }
    
    return L;
}

List deletePos(List L, int position){
    
    if(position < L.count){
        for(int i = position; i < L.count; i++){
            L.elem[i] = L.elem[i + 1];
        }
        
        L.elem[L.count - 1] - 1;
        L.count--;
    }
    
    return L;
}

int locate (List L, int data){
    for(int i = 0; i < L.count; i++){
        if(L.elem[i] == data){
            return i;
        }
    }
    
    return -1;
}

List insertSorted (List L, int data){
    if(L.count < MAX){
        int pos = 0;
        
        while(pos < L.count && L.elem[pos] < data){
            pos++;
        }
        
        return insertPos(L, data, pos);
    }
    
    return L;
}

void display(List L){
    for(int i = 0; i < MAX; i++){
        printf("%d ", L.elem[i]);
    }
    
    printf("\n");
}
