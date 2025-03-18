#include <stdio.h>

typedef struct Data{
    FILE *dataIn = fopen("NIVIDIA Stock Price History.csv", "r");
    struct Data *next;
}Data;


int main(){

Data *d = malloc(sizeof(Data));

Data *head;
Data *temp;






}