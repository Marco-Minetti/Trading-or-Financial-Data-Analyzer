#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "analytics.h"

// Load stock data from CSV
int loadStockData(const char *filename, StockRecord records[], int maxRecords) {
    printf("Attempting to open file: %s\n", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && count < maxRecords) {
        StockRecord rec;
        double price;
        char volumeStr[20];

        if (sscanf(line, "\"%19[^\"]\",\"%lf\",\"%lf\",\"%lf\",\"%lf\",\"%19[^\"]\"",
                   rec.date, &price, &rec.open, &rec.high, &rec.low, volumeStr) == 6) {
            
            rec.close = price;

            // Convert volume from string to integer
            char unit = volumeStr[strlen(volumeStr) - 1];
            volumeStr[strlen(volumeStr) - 1] = '\0';
            rec.volume = atof(volumeStr) * (unit == 'M' ? 1e6 : (unit == 'B' ? 1e9 : 1));

            records[count++] = rec;
        }
    }

    fclose(file);
    return count;
}

// Calculate SMA
void calculateSMA(StockRecord records[], int count, int window) {
    if (count < window) {
        printf("Not enough data for SMA calculation\n");
        return;
    }

    printf("\nSMA (%d-day):\n", window);
    for (int i = 0; i <= count - window; i++) {
        double sum = 0.0;
        for (int j = 0; j < window; j++) {
            sum += records[i + j].close;
        }
        printf("%s SMA: %.2f\n", records[i + window - 1].date, sum / window);
    }
}

// Find Min/Max prices
void calculateMinMax(StockRecord records[], int count) {
    double minPrice = records[0].close, maxPrice = records[0].close;
    char minDate[20], maxDate[20];
    strcpy(minDate, records[0].date);
    strcpy(maxDate, records[0].date);

    for (int i = 1; i < count; i++) {
        if (records[i].close < minPrice) {
            minPrice = records[i].close;
            strcpy(minDate, records[i].date);
        }
        if (records[i].close > maxPrice) {
            maxPrice = records[i].close;
            strcpy(maxDate, records[i].date);
        }
    }

    printf("\nMax Price: %.2f on %s\n", maxPrice, maxDate);
    printf("Min Price: %.2f on %s\n", minPrice, minDate);
}

// Calculate volatility
void calculateVolatility(StockRecord records[], int count) {
    double sum = 0.0, mean, variance = 0.0, stddev;

    for (int i = 0; i < count; i++) {
        sum += records[i].close;
    }
    mean = sum / count;

    for (int i = 0; i < count; i++) {
        variance += pow(records[i].close - mean, 2);
    }
    variance /= count;
    stddev = sqrt(variance);

    printf("\nVolatility (Std Dev of Close Prices): %.2f\n", stddev);
}