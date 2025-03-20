//creating the nodes 
//linking the nodes

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H


typedef struct { //when defining structs in the header they don't have to be defined again in the c file
char date[20];
float price;
float open;
float high;
float low;
float volume;
float change;
}Data;

typedef struct Node{ //when you open a file you read it all
    Data d;
    struct Node* next;
}Node;

void createStruct(date, price, open, high, low, volume, change);

Node* nodesCombined(Node *n);

void nodesCreate(Data d);

#endif

/*Header File---------------

void printhello(void); 

this is the declaration
allows you to reference the printhello from the main C file
kind of like an abstract method
*/


//C source file-------------------
/*

#include <stdio.h>

void printhello(void){
printf("Say hello");
}



this is where you will add the definition of the method 
the header links into our definition
*/


/* Main file-----------------------

#include "myheader.h" 

int main(){

printHello();
return 0;

}

in the header file you will include any functions that you want to be used throughout the program almost like public
if you just want to almost be private you would just leave it in the c file
*/