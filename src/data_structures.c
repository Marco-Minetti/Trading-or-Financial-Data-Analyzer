#include <stdio.h>
#include <stdlib.h>

typedef struct {
float price;
float open;
float high;
float low;
float change;
}Data;


typedef struct Node{ //when you open a file you read it all
    Data d;
    struct Node* next;
}Node;


void *nodesCombined(Node *n){ //
    Node *head = NULL;

    while(head != NULL){
        n->next = head;
        head = n;
    }
}

//this function will create the node, hold the data and will be initialized to NULL and then be passed to nodesCombined to be linked together?
void *nodesCreate(Data d){
    Node *n = malloc(sizeof(Node));
    n->d = d;
    n->next = NULL;
    nodesCombined(*n);
}


//the header file is for declaring functions
//strtok()