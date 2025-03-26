#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "analytics.h"
#include "data_structures.h"

// Load stock Node from CSV
int loadStockNode(const char *filename, StockRecord records[], int maxRecords) {
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
/*
void calculateSMA(StockRecord records[], int count, int window) {
    if (count < window) {
        printf("Not enough Node for SMA calculation\n");
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
}*/

void calculateSMA(Node* head, int window) {
    if (!head) {
        printf("No Data available for SMA calculation.\n");
        return;
    }

    Node* current = head;
    int count = 0;
    double sum = 0.0;
    Node* windowStart = head;  // Pointer to start of window

    printf("\nSMA (%d-day):\n", window);

    while (current != NULL) {
        sum += current->d.price;
        count++;

        if (count >= window) {
            printf("%s SMA: %.2f\n", current->d.date, sum / window);
            sum -= windowStart->d.price;  // Remove the oldest value
            windowStart = windowStart->next;  // Move window forward
        }

        current = current->next;
    }
}

// Find Min/Max prices
/*
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
}*/

void calculateMinMax(Node* head) {
    if (!head) {
        printf("No Data available for Min/Max calculation.\n");
        return;
    }

    double minPrice = head->d.price, maxPrice = head->d.price;
    char minDate[20], maxDate[20];
    strcpy(minDate, head->d.date);
    strcpy(maxDate, head->d.date);

    Node* current = head->next;

    while (current != NULL) {
        if (current->d.price < minPrice) {
            minPrice = current->d.price;
            strcpy(minDate, current->d.date);
        }
        if (current->d.price > maxPrice) {
            maxPrice = current->d.price;
            strcpy(maxDate, current->d.date);
        }
        current = current->next;
    }

    printf("\nMax Price: %.2f on %s\n", maxPrice, maxDate);
    printf("Min Price: %.2f on %s\n", minPrice, minDate);
}

// Calculate volatility
/*
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
}*/

void calculateVolatility(Node* head) {
    if (!head) {
        printf("No Data available for volatility calculation.\n");
        return;
    }

    int count = 0;
    double sum = 0.0, mean, variance = 0.0, stddev;
    Node* current = head;

    // Calculate mean
    while (current != NULL) {
        sum += current->d.price;
        count++;
        current = current->next;
    }

    mean = sum / count;
    current = head;

    // Calculate variance
    while (current != NULL) {
        variance += pow(current->d.price - mean, 2);
        current = current->next;
    }

    variance /= count;
    stddev = sqrt(variance);

    printf("\nVolatility (Std Dev of Close Prices): %.2f\n", stddev);
}