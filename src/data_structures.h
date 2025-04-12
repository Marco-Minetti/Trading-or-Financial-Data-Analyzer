#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

extern int numberOfNodes; //global variable used to keep track of nodes possibly
extern omp_set_num_threads(2);

typedef struct {
    unsigned char date[20]: 4;
    double price, open, high, low, volume, change;
}Data;

typedef struct Node{
    Data d;
    struct Node* next;
}Node;

void nodesCreate(Data *d);

Node* nodesCombined(Node *n);

void createStruct(char const date, double price, double open, double high, double low, double volume, double change);

Node* copyLinkedList(Node *n);

void clearingMemory(Node *head);

#endif
