#include "data_structures.h"
#include "analytics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node* nodesCombined(Node* head, Node* new_node) {
   new_node->next = head;
   return new_node;
}



//this function will take all the vars and allocate space for it then be passed to create the node
//the constant char allows you pass a string literal safely to the function
Node* createStruct(Node* head, const char* date, double price, double open, double high, double low, double volume, double change){
   Data* d = malloc(sizeof(Data));  // Allocate memory for Data
    if (!d) return head;  // Return head if memory allocation fails

    // Safely copy the date string to avoid overflow
    strncpy(d->date, date, sizeof(d->date) - 1);
    d->date[sizeof(d->date) - 1] = '\0';  // Ensure null termination
    d->price = price;
    d->open = open;
    d->high = high;
    d->low = low;
    d->volume = volume;
    d->change = change;

    Node* new_node = malloc(sizeof(Node));  // Allocate memory for the new Node
    if (!new_node) {
        free(d);  // Free d if memory allocation for new_node fails
        return head;
    }

    new_node->d = *d;  // Copy the data into the node
    new_node->next = NULL;  // Initialize the next pointer to NULL

    free(d);  // Free d since its data is now in the new_node

    return nodesCombined(head, new_node);
}


void clearingMemory(Node *head) {
    Node *temp;
    while (head != NULL) {
       temp = head;
       head = head->next;
       free(temp);
   }
}