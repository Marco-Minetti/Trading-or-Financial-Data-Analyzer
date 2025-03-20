#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this function will take all the vars and allocate space for it then be passed to create the node
void createStruct(char[] date, price, open, high, low, volume, change){
    Data *d = malloc(sizeof(Data));
    strcpy(d->date, *date); 
    d->price = price;
    d->open = open;
    d->high = high;
    d->low = low;
    d->volume = volume;
    d->change = change;
    nodesCreate(*d);
}

//this function will create the node, hold the data and will be initialized to NULL and then be passed to nodesCombined to be linked together?
void nodesCreate(Data d){
    Node *n = malloc(sizeof(Node));
    n->d = d;
    n->next = NULL;
    nodesCombined(n);
}

Node* nodesCombined(Node *n){ //the node from nodesCreate will be passed here and connected to each other
    static Node *head = NULL; //it will keep the head across function calls
    Node *temp = n;

    while(temp != NULL){
        temp->next = head;
        head = temp;
        temp = temp->next;
    }
    return head;
}


//the header file is for declaring functions