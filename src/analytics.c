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

    //Count total nodes
    int totalNodes = 0;
    Node *temp = head;
    while(temp){
        totalNodes++;
        temp = temp->next;
    }

    if(totalNodes < window){
        printf("Not enough data to calculate %d-day SMA. Only %d data points available. \n", window, totalNodes);
        return;
    }

    int middleOfLinkedList = totalNodes/2;

    //start of the openMP section
    Node *start1 = NULL;
    Node *start2 = head;

    for(int i = 0; i < middleOfLinkedList; i++){ //this is the loop that determines where the the linked list should be split
        start1 = start2;
        start2 = start2->next; //this will be set to the next node
    }

    
    if(start1 != NULL){ //the node that start1 is currently at will be set to null and start2 will be the next start of the second linked list
        start1->next = NULL;
    }


    double sum1 = 0.0, sum2 = 0.0;
    int count1 = 0, count2 = 0;

    Node *temp1 = head; //the first temp will be assinged to start of the first linked list
    Node *temp2 = start2; //the second temp will be assigned to start of the second linked list
    

    printf("\nSMA (%d-day):\n", window);

    #pragma omp parallel sections //both sections stated below will be done parllel to each other 
    {
        #pragma omp section //this section will be assigned to the 0 thread cpu
        {
            while (temp1 != NULL) {
                sum1 += temp1->d.price;
                count1++;

                Node *traverse1 = temp1; //this node will traverse through the first linked list

                if (count1 >= window) {
                    printf("%s SMA: %.2f\n", temp1->d.date, sum1 / window);
                    sum1 -= traverse1->d.price;
                    traverse1 = traverse1->next;
                }

                temp1 = temp1->next;

                /*if(temp1 == NULL){
                    free(traverse1);
                }*/
            }
        }

        #pragma omp section //this will be assigned to the 1 thread in the cpu
        {
            while (temp2 != NULL) {
                sum2 += temp2->d.price;
                count2++;

                Node *traverse2 = temp2; //this node will traverse through the second linked list

                if (count2 >= window) {
                    printf("%s SMA: %.2f\n", temp2->d.date, sum2 / window);
                    sum2 -= traverse2->d.price;
                    traverse2 = traverse2->next;
                }

                temp2 = temp2->next;

                /*if(temp2 == NULL){
                    free(traverse2);
                }*/
            }
        }
    }
    /*free(start1);
    free(start2);
    free(temp1);
    free(temp2);*/
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