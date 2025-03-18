typedef struct {
float price;
float open;
float high;
float low;
float high;
float change;
}Data;


typedef struct Node{ //when you open a file you read it all
    Data d;
    struct Node *next;
}Node;


void *nodesCombined(Node n){ //
    Node *n = malloc(sizeof(Node));

    while()

}