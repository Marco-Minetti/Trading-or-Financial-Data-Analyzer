//creating the nodes 
//linking the nodes
#include <stdlib.h>

typedef struct {
float price;
float open;
float high;
float low;
float change;
}Data;

typedef struct Node{
}Node;

void *nodesCreate(Data d);




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