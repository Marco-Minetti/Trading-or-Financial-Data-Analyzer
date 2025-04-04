#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "data_structures.h" 
#define MAX_LINE 1024
#define MAX_RECORDS 10000
#define SMA_WINDOW 5

// Struct for stock data
typedef struct {
    char date[20];
    double open, high, low, close;
    int volume;
    float price;
} StockRecord;

// Function prototypes
int loadStockData(const char *filename, StockRecord records[], int maxRecords);
void calculateSMA(Node* head, int window); 
void calculateMinMax(Node* head); 
void calculateVolatility(Node* head);       

#endif