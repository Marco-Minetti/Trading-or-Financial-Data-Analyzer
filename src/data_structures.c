#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


void nodesCombined(Node *n){ //
    Node *head = NULL;

    while(head != NULL){
        n->next = head;
        head = n;
    }
}

//this function will create the node, hold the data and will be initialized to NULL and then be passed to nodesCombined to be linked together?
void nodesCreate(Data d){
    Node *n = malloc(sizeof(Node));
    n->d = d;
    n->next = NULL;
    nodesCombined(n);
}


//the header file is for declaring functions
//strtok()