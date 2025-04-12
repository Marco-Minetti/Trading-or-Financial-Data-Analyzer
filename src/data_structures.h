#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

extern int numberOfNodes; //global variable used to keep track of nodes possibly

typedef struct {
   char date[20];
   double price, open, high, low, volume, change;
}Data;

typedef struct Node{
   Data d;
   struct Node* next;
}Node;

void nodesCreate(Data *d);

Node* nodesCombined(Node *n);

void createStruct(char const *date, double price, double open, double high, double low, double volume, double change);

void clearingMemory(Node *head);

#endif
