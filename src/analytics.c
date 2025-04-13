#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "analytics.h"
#include "data_structures.h"

// Calculate SMA
void calculateSMA(Node* head, int window) {
    if (!head) {
        printf("No Data available for SMA calculation.\n");
        return;
    }

    // Count total nodes
    int totalNodes = 0;
    Node* temp = head;
    while (temp) {
        totalNodes++;
        temp = temp->next;
    }

    if (totalNodes < window) {
        printf("Not enough data to calculate %d-day SMA. Only %d data points available.\n", window, totalNodes);
        return;
    }

    Node* current = head;
    int count = 0;
    double sum = 0.0;
    Node* windowStart = head;

    printf("\nSMA (%d-day):\n", window);

    while (current != NULL) {
        sum += current->d.price;
        count++;

        if (count >= window) {
            printf("%s SMA: %.2f\n", current->d.date, sum / window);
            sum -= windowStart->d.price;
            windowStart = windowStart->next;
        }

        current = current->next;
    }
}

// Find Min/Max prices
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