#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>

//this function will create the node, hold the data and will be initialized to NULL and then be passed to nodesCombined to be linked together?
void nodesCreate(Data d){
    printf("Hi");
    Node *n = malloc(sizeof(Node));
    n->d = d;
    n->next = NULL;
    printf("Data: %d", d);
    nodesCombined(n);
}

Node* nodesCombined(Node *n){ //the node from nodesCreate will be passed here and connected to each other
    static Node *head = NULL; //it will keep the head across function calls
    Node *temp = n;

    printf("THIS IS IS THE START");
    while(temp != NULL){
        temp->next = head;
        head = temp;
        temp = temp->next;
    }
    printf("Hello");
    return head;
}




//the header file is for declaring functions
//strtok()