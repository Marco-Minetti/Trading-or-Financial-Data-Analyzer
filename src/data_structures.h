//creating the nodes 
//linking the nodes

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

extern int numberOfNodes; //global variable used to keep track of nodes possibly

typedef struct {
    char date[20];
    float price, open, high, low, volume, change;
    }Data;

typedef struct Node{ 
    Data d;
    struct Node* next;
}Node;

void nodesCreate(Data *d);

Node* nodesCombined(Node *n);

void createStruct(const char* date, float price, float open, float high, float low, float volume, float change);

void clearingMemory(Node *head);

#endif
