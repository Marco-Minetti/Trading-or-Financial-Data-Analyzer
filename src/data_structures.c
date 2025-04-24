#include "data_structures.h"
#include "analytics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int numberOfNodes = 0;

//this function will take all the vars and allocate space for it then be passed to create the node
//the constant char allows you pass a string literal safely to the function
Node* createStruct(Node* head, const char* date, double price, double open, double high, double low, double volume, double change){
   Data* d = malloc(sizeof(Data)); //[Feature] Malloc
   if (!d) return head;

   strncpy(d->date, date, sizeof(d->date) - 1);
   d->date[sizeof(d->date) - 1] = '\0';
   d->price = price;
   d->open = open;
   d->high = high;
   d->low = low;
   d->volume = (int) volume; //if there is a volume is in the head put the if statement here and if there isn't put 0
   d->change = change;

   Node* new_node = malloc(sizeof(Node));
   if (!new_node) {
      free(d);
      return head;
   }
   new_node->d = *d;
   new_node->next = NULL;

   free(d);

   return nodesCombined(head, new_node);
}


Node* nodesCombined(Node* head, Node* new_node) {
   new_node->next = head;
   return new_node;
}

void counter(Node* head) {
   int c = 0;
    while (head != NULL) {
       head = head->next;
       c++;
   }
   printf("COUNTER: %d\n", c);
}

void clearingMemory(Node *head) {
    Node *temp;
    int c = 0;
    while (head != NULL) {
       temp = head;
       head = head->next;
       c++;
       free(temp);
      }
}