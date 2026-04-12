#include <stdio.h>
#include <string.h>

#define MAX 15

typedef char string[16];

typedef struct{
    string acctname;
    string id;
}User;    

typedef struct{
    string charName;
    float weight;
}Character;

typedef struct{
    int speed, acceleration, weight, handling, traction;
}Stats;

typedef struct{
    string componentName;
    Stats car, wheels, glider, total;
}Car;

typedef struct{
    string itemName;
    string desc;
}Inventory;

typedef struct{
    User IGN;
    Character selected;
    Car chosen;
    Inventory items[2];
    int coins;
}Player;

typedef struct{
    Player details;
    int next;
}cell, HeapSpace[MAX];

typedef struct{
    HeapSpace H;
    int avail;
}VHeap;

typedef struct{
    int L;
    int count;
}RaceList;

void initVHeap(VHeap *VH) {
    for (int i = 0; i < MAX - 1; i++) {
        VH->H[i].next = i + 1;
    }
    VH->H[MAX - 1].next = -1;
    VH->avail = 0;
}

int allocSpace(VHeap *VH) {
    int temp = VH->avail;
    if (temp != -1) {
        VH->avail = VH->H[temp].next;
    }
    return temp;
}

void deallocSpace(VHeap *VH, int index) {
    VH->H[index].next = VH->avail;
    VH->avail = index;
}

void insertFirst(RaceList *RL, VHeap *VH, Player p) {
    int newNode = allocSpace(VH);
    if (newNode != -1) {
        VH->H[newNode].details = p;
        VH->H[newNode].next = RL->L;
        RL->L = newNode;
        RL->count++;
    }
}

void insertLast(RaceList *RL, VHeap *VH, Player p) {
    int newNode = allocSpace(VH);
    if (newNode != -1) {
        VH->H[newNode].details = p;
        VH->H[newNode].next = -1;

        int *curr = &RL->L;
        while (*curr != -1) {
            curr = &VH->H[*curr].next;
        }

        *curr = newNode;
        RL->count++;
    }
}

void insertAtPos(RaceList *RL, VHeap *VH, Player p, int pos) {
    if (pos < 0 || pos > RL->count) {
        printf("Invalid position.\n");
    } else {
        int newNode = allocSpace(VH);
        if (newNode == -1){
            printf("No Space.\n");
        } else {
            int *curr = &RL->L;
            for (int i = 0; i < pos; i++) {
                curr = &VH->H[*curr].next;
            }

            VH->H[newNode].details = p;
            VH->H[newNode].next = *curr;
            *curr = newNode;

            RL->count++;
        }
    }    
}

void insertbyKey(RaceList *RL, VHeap *VH, Player p) {
    int newNode = allocSpace(VH);
    if (newNode == -1){
        printf("No Space.\n");
    } else {
        int *curr = &RL->L;
        while (*curr != -1 && VH->H[*curr].details.coins < p.coins) {
            curr = &VH->H[*curr].next;
        }

        VH->H[newNode].details = p;
        VH->H[newNode].next = *curr;
        *curr = newNode;

        RL->count++;
    }
}

void deleteFirst(RaceList *RL, VHeap *VH) {
    if (RL->L != -1) {
        int temp = RL->L;
        RL->L = VH->H[temp].next;
        deallocSpace(VH, temp);
        RL->count--;
    }
}

void deleteLast(RaceList *RL, VHeap *VH) {
    if (RL->L == -1) return;

    int *curr = &RL->L;
    while (VH->H[*curr].next != -1) {
        curr = &VH->H[*curr].next;
    }

    int temp = *curr;
    *curr = -1;

    deallocSpace(VH, temp);
    RL->count--;
}

void deleteAtPos(RaceList *RL, VHeap *VH, int pos) {
    if (pos < 0 || pos >= RL->count){
        printf("Invalid position.\n");
    } else{
        int *curr = &RL->L;
        for (int i = 0; i < pos; i++) {
            curr = &VH->H[*curr].next;
        }

        int temp = *curr;
        *curr = VH->H[temp].next;

        deallocSpace(VH, temp);
        RL->count--;
    }
}

void deleteBykey(RaceList *RL, VHeap *VH, char *id) {
    int *curr = &RL->L;

    while (*curr != -1 && strcmp(VH->H[*curr].details.IGN.id, id) != 0) {
        curr = &VH->H[*curr].next;
    }

    if (*curr != -1) {
        int temp = *curr;
        *curr = VH->H[temp].next;

        deallocSpace(VH, temp);
        RL->count--;
    }
}

void enqueueItem(Player *p, Inventory item) {
    p->items[1] = p->items[0];
    p->items[0] = item;
}

void dequeueItem(Player *p) {
    p->items[0] = p->items[1];
    strcpy(p->items[1].itemName, "");
    strcpy(p->items[1].desc, "");
}

void display(RaceList RL, VHeap VH) {
    int trav = RL.L;
    printf("\nPlayers:\n");

    while (trav != -1) {
        printf("ID: %s | Coins: %d\n",
               VH.H[trav].details.IGN.id,
               VH.H[trav].details.coins);
        trav = VH.H[trav].next;
    }
}

int main() {
    VHeap VH;
    RaceList RL = {-1, 0};

    initVHeap(&VH);

    Player p1 = {.IGN = {"Mario", "ID1"}, .coins = 50};
    Player p2 = {.IGN = {"Luigi", "ID2"}, .coins = 30};
    Player p3 = {.IGN = {"Peach", "ID3"}, .coins = 70};
    Player p4 = {.IGN = {"Yoshi", "ID4"}, .coins = 40};

    insertFirst(&RL, &VH, p1);
    insertLast(&RL, &VH, p2);
    insertAtPos(&RL, &VH, p3, 1);
    insertbyKey(&RL, &VH, p4);

    display(RL, VH);

    deleteFirst(&RL, &VH);
    deleteLast(&RL, &VH);
    deleteAtPos(&RL, &VH, 0);
    deleteBykey(&RL, &VH, "ID4");

    display(RL, VH);

    Inventory i1 = {"Shell", "Attack"};
    Inventory i2 = {"Banana", "Trap"};
    Inventory i3 = {"Mushroom", "Boost"};

    enqueueItem(&p1, i1);
    enqueueItem(&p1, i2);
    enqueueItem(&p1, i3);

    printf("\nInventory:\n");
    for (int i = 0; i < 2; i++) {
        printf("%s\n", p1.items[i].itemName);
    }

    dequeueItem(&p1);

    printf("\nAfter Dequeue:\n");
    for (int i = 0; i < 2; i++) {
        printf("%s\n", p1.items[i].itemName);
    }

    return 0;
}