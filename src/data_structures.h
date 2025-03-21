//creating the nodes 
//linking the nodes

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H


typedef struct { //when defining structs in the header they don't have to be defined again in the c file
char date[20];
float price, open, high, low, volume, change;
}Data;

typedef struct Node{ 
    Data d;
    struct Node* next;
}Node;

void createStruct(const char *date, float price, float open, float high, float low, float volume, float change);

Node* nodesCombined(Node *n);

void nodesCreate(Data d);

#endif
