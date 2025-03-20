#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    Data d1;
    d1.price = 12.5;
    d1.open = 15.4;
    d1.high = 45.5;
    d1.low = 42.3;
    d1.high = 45.4;
    d1.change = 78.4;

    nodesCreate(d1);

    Data d2;
    d2.price = 18.5;
    d2.open = 45.2;
    d2.high = 12.6;
    d2.low = 3.4;
    d2.high = 5.4;
    d2.change = 78.4;

    //nodesCreate(d2);

    Data d3;
    d3.price = 12.3;
    d3.open = 12.3;
    d3.high = 47.4;
    d3.low = 14.3;
    d3.high = 75.4;
    d3.change = 47.4;

    //nodesCreate(d3);




return 0;

}