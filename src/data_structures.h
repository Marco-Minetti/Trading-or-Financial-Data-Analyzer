
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct {
   char date[20];
   double price, open, high, low, volume, change;
}Data;

typedef struct Node{
   Data d;
   struct Node* next;
}Node;

struct bitfield{
   unsigned int number: 1;
};

Node* nodesCombined(Node* head, Node* new_node);

Node* createStruct(Node* head, char const *date, double price, double open, double high, double low, double volume, double change);

void clearingMemory(Node *head);

#endif
