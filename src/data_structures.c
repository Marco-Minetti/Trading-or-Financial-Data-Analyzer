#include "data_structures.h"
#include "analytics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int numberOfNodes = 0;

//this function will take all the vars and allocate space for it then be passed to create the node
//the constant char allows you pass a string literal safely to the function
Node* createStruct(Node* head, const char* date, double price, double open, double high, double low, double volume, double change){
   /*Data* d = malloc(sizeof(Data));
   if (!d) return head;

   strncpy(d->date, date, sizeof(d->date) - 1);
   d->date[sizeof(d->date) - 1] = '\0';
   d->price = price;
   d->open = open;
   d->high = high;
   d->low = low;
   d->volume = volume; //if there is a volume is in the head put the if statement here and if there isn't put 0
   d->change = change;

   Node* new_node = malloc(sizeof(Node));
   if (!new_node) {
      free(d);
      return head;
   }
   new_node->d = *d;
   new_node->next = NULL;
*/

Node* new_node = malloc(sizeof(Node));
if (!new_node) return head;

strncpy(new_node->d.date, date, sizeof(new_node->d.date) - 1);
new_node->d.date[sizeof(new_node->d.date) - 1] = '\0';
new_node->d.price = price;
new_node->d.open = open;
new_node->d.high = high;
new_node->d.low = low;
new_node->d.volume = volume;
new_node->d.change = change;
new_node->next = NULL;
return nodesCombined(head, new_node);
}


Node* nodesCombined(Node* head, Node* new_node) {
   new_node->next = head;
   return new_node;
}


void clearingMemory(Node *head) {
    Node *temp;
    while (head != NULL) {
       temp = head;
       head = head->next;
       free(temp);
   }
}