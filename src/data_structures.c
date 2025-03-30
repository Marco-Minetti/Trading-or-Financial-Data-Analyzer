#include "data_structures.h"
#include "analytics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[20];
    float price, open, high, low, volume, change;
    }Data;

//this function will take all the vars and allocate space for it then be passed to create the node
//the constant char allows you pass a string literal safely to the function
void createStruct(const char *date, float price, float open, float high, float low, float volume, float change){
    Data *d = malloc(sizeof(Data));
    strncpy(d->date, date, sizeof(d->date) - 1);
    d->date[sizeof(d->date) - 1] = '\0';
    d->price = price;
    d->open = open;
    d->high = high;
    d->low = low;
    d->volume = volume;
    d->change = change;
    nodesCreate(d);
}

//this function will create the node, hold the data and will be initialized to NULL and then be passed to nodesCombined to be linked together
void nodesCreate(Data *d){
    Node *n = malloc(sizeof(Node));
    n->d = *d;
    n->next = NULL;
    nodesCombined(n);
}

Node* nodesCombined(Node *n){ //the node from nodesCreate will be passed here and connected to each other
    static Node *head = NULL; //will retain its state when the function is done, and it wont be reinitialized on each call
    Node *temp = n;
    
    while(temp != NULL){
        Node *ref = temp->next; //will always be set to null due to temp->next being always being NULL
        temp->next = head;
        head = temp;
        temp = ref; //will refer to ref and temp will be set to NULL
    }
    return head;
}


//the header file is for declaring functions