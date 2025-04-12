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
    //start of the openMP section IDK if this is correct or not but this is what i cooked up
    Node *head1 = head;
    Node *head2 = NULL;
    Node *tempHead1 = head;

    //push just for linuxz

    for(int i = 0; i < numberOfNodes/2; i++){
        ///head = start of the firs tlinked list
        //head2 = start of the second linked list
        if(i >= numberOfNodes / 2){
           head2 = tempHead1->next;
           tempHead1->next = NULL;
        } else {
            tempHead1 = tempHead1->next;
        }
    }
    double sum1 = 0.0, sum2 = 0.0;
    int count1 = 0, count2 = 0;

    Node *temp1 = head
    Node *temp2 = head2;

    printf("\nSMA (%d-day):\n", window);

    #pragma omp parallel sections{
        #pragma omp section {

            while(temp1 != NULL){
                sum1 += head1->d.price;
                count1++

                if(count1 >= window){
                    #pragma omp critical {
                    printf("%s SMA: %.2f\n", head1->d.date, sum1 / window);
                    }
                    sum1 -= temp1->d.price;
                    temp1 = head1->next;
                    head1 = temp1;
                }
                head1 = head1->next;
            }
        }

        #pragma omp section{
            #pragma omp section {

                while(temp2 != NULL){
                    sum2 += head2->d.price;
                    count2++;

                if(count2 >= window) {
                    printf("%s SMA: %.2f\n", head1->d.date, sum2 / window);
                    sum2 -= temp2->d.price;
                    temp2 = head2->next;
                    head2 = temp2;
                }
                head2 = head2->next;
                }
            }
        }
    }
}