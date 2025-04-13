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

Node* nodesCombined(Node* head, Node* new_node);

Node* createStruct(Node* head, char const *date, double price, double open, double high, double low, double volume, double change);

void clearingMemory(Node *head);

#endif
