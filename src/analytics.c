#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "analytics.h"
#include "data_structures.h"
#include <omp.h>


// Calculate SMA
void calculateSMA(Node* head, int window) {
    omp_set_num_threads(2); //this the number of threads we are using

    if (!head) {
        printf("No Data available for SMA calculation.\n");
        return;
    }
    //start of the openMP section
    Node *head1 = head;
    Node *head2 = NULL;
    Node *tempHead1 = head;

    for(int i = 0; i < numberOfNodes/2 - 1; i++){
        ///head = start of the first linked list
        //head2 = start of the second linked list
        if(i >= numberOfNodes / 2 - 1){
           head2 = tempHead1->next;
           tempHead1->next = NULL;
        } else {
            tempHead1 = tempHead1->next;
        }
    }
    double sum1 = 0.0, sum2 = 0.0;
    int count1 = 0, count2 = 0;

    Node *temp1 = head1;
    Node *temp2 = head2;

    printf("\nSMA (%d-day):\n", window);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            while (temp1 != NULL) {
                sum1 += temp1->d.price;
                count1++;

                if (count1 >= window) {
                    #pragma omp critical
                    {
                        printf("%s SMA: %.2f\n", temp1->d.date, sum1 / window);
                    }
                    sum1 -= temp1->d.price;
                    temp1 = head1->next;
                    head1 = temp1;
                }

                temp1 = temp1->next;
            }
        }

        #pragma omp section
        {
            while (temp2 != NULL) {
                sum2 += temp2->d.price;
                count2++;

                if (count2 >= window) {
                    #pragma omp critical
                    {
                        printf("%s SMA: %.2f\n", temp2->d.date, sum2 / window);
                    }
                    sum2 -= temp2->d.price;
                    temp2 = head2->next;
                    head2 = temp2;
                }

                temp2 = temp2->next;
            }
        }
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