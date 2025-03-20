#include <stdio.h>
#include "analytics.h"

int main() {
    StockRecord records[MAX_RECORDS];
    int count = loadStockData("NVIDIA_STOCK_PRICE_HISTORY.csv", records, MAX_RECORDS);
    
    if (count == 0) {
        printf("No data loaded.\n");
        return 1;
    }

    printf("\nCalculating metrics...\n");
    calculateSMA(records, count, SMA_WINDOW);
    calculateMinMax(records, count);
    calculateVolatility(records, count);

    return 0;
}