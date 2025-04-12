#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "analytics.h"
#include "data_structures.h"
#include <omp.h>


// Calculate SMA
void calculateSMA(Node* head, int window) {
    if (!head) {
        printf("No Data available for SMA calculation.\n");
        return;
    }
    Node* copy = copyLinkedList(head);
    Node* current = head;
    int count = 0;
    double sum = 0.0;
    Node* windowStart = head;  // Pointer to start of window


    //start of the openMP section IDK if this is correct or not but this is what i cooked up
    Node *head1 = NULL;
    Node *head2 = NULL;
    Node static *start1 = head;


    for(int i = 0; i < numberOfNodes/2; i++){
        if(i >= numberOfNodes / 2){
            head1 = head;
            head2 = head1;
            head2 = head->next;
            head->next = NULL;
            head = NULL;
        } else {
            head = head->next;
        }
    }
    double sum1 = 0.0;
    double sum2 = 0.0;

    int count1 = 0;
    int count2 = 0;
    head1 = start1;
    Node *temp1 = head
    Node *temp2 = head2;

    #pragma omp parallel sections{
        #pragma omp section {
        for(int i = 0; i < numberOfNodes && head1->next != NULL; i++){
                sum1 += head1->d.price;
                count1++

                if(count1 >= window){
                    printf("%s SMA: %.2f\n", head1->d.date, sum1 / window);
                    temp1 = head1->next;
                    head1 = temp1;
                }
                head1 = head1->next;
            }

        }

        #pragma omp section{
            for(int j = 0; i < numberOfNodes * 2 && head2->next != NULL; i++){
                sum2 += head2->d.price;
                count2++;

                if(count2 >= window) {
                    printf("%s SMA: %.2f\n", head1->d.date, sum2 / window);
                    temp2 = head2->next;
                    head2 = temp2;
                }
                head2 = head2->next;
            }
        }
    }

    printf("\nSMA (%d-day):\n", window);
    while(current != NULL){
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
        //#pragma omp atomic could be added
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