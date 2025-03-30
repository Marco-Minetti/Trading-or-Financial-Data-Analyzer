#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct Node{ 
    Data d;
    struct Node* next;
}Node;

void createStruct(char* date, float price, float open, float high, float low, float volume, float change);

Node* nodesCombined(Node *n);


#endif
