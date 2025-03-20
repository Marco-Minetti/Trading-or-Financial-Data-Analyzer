#ifndef ANALYTICS_H
#define ANALYTICS_H

#define MAX_LINE 1024
#define MAX_RECORDS 10000
#define SMA_WINDOW 5

// Struct for stock data
typedef struct {
    char date[20];
    double open, high, low, close;
    int volume;
} StockRecord;

// Function prototypes
int loadStockData(const char *filename, StockRecord records[], int maxRecords);
void calculateSMA(StockRecord records[], int count, int window);
void calculateMinMax(StockRecord records[], int count);
void calculateVolatility(StockRecord records[], int count);

#endif