
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct { //[Feature] Struct
   char date[20];
   double price, open, high, low, change;
   unsigned int volume:3; //[Feature] Bitfield
}Data;

typedef struct Node{ //[Feature] Linked List
   Data d;
   struct Node* next;
}Node;

void counter(Node* head);

Node* nodesCombined(Node* head, Node* new_node);

Node* createStruct(Node* head, char const *date, double price, double open, double high, double low, double volume, double change);

void clearingMemory(Node *head);

#endif
