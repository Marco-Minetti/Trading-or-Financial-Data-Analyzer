
#define _POSIX_C_SOURCE 200112L  // Enable POSIX functions like popen, pclose

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "data_structures.h"
#include "query_interface.h"


#define MAX_LINE 1024

int is_date_in_range(const char *date, const char *start_date, const char *end_date) {
    if (start_date && strcmp(date, start_date) < 0) return 0;
    if (end_date && strcmp(date, end_date) > 0) return 0;
    return 1;
}

int is_within_range(double value, const char *range) {
    if (!range) return 1;  // No filter applied

    double min, max;
    if (sscanf(range, "%lf:%lf", &min, &max) != 2) {
        printf("Error: Invalid range format. Use min:max\n");
        return 0;
    }
    return (value >= min && value <= max);
}

int is_change_matching(const char *change, const char *filter) {
    if (!filter) return 1;  // No filter applied
    double change_value = atof(change);
    return (*filter == '+' && change_value > 0) || (*filter == '-' && change_value < 0);
}

Node* query_stock_price(const char *filename, const char *start_date, const char *end_date, 
                       const char *change_filter, const char *price_range, 
                       const char *high_range, const char *low_range) {
    char fileposition[256];
    snprintf(fileposition, sizeof(fileposition), "./data/%s", filename);
    FILE *file = fopen(fileposition, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", fileposition);
        exit(1);
    }

    char line[MAX_LINE];
    int found = 0;
    Node *head = NULL;

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char date[20], price[20], open[20], high[20], low[20], volume[20], change[20]; //[Feature] Arrays

        // Parse CSV line
        sscanf(line, "\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\"",
            date, price, open, high, low, volume, change);  

        double price_value = atof(price);
        double high_value = atof(high);
        double low_value = atof(low);

        char *percent_sign = strchr(change, '%'); //[Feature] String
        if (percent_sign) *percent_sign = '\0';  // Remove '%'
        //double change_value = atof(change) / 100.0;

        // Check filters
        if (!is_date_in_range(date, start_date, end_date)) continue;
        if (!is_change_matching(change, change_filter)) continue;
        if (!is_within_range(price_value, price_range)) continue;
        if (!is_within_range(high_value, high_range)) continue;
        if (!is_within_range(low_value, low_range)) continue;

        // Print matching row
        printf("Date: %s | Price: %s | Open: %s | High: %s | Low: %s | Volume: %s | Change: %s\n",
               date, price, open, high, low, volume, change); //we can take it off when we want
        head = createStruct(head, date, atof(price), atof(open), atof(high), atof(low), atof(volume), atof(change));
        found = 1;
    }

    if (!found) {
        printf("No results found for the given query.\n");
    }

    fclose(file);
    return head;
}


//export FINNHUB_API_KEY=cvrd211r01qp88cpllbgcvrd211r01qp88cpllc0
Node* query_live_stock_price(int duration, const char *start_date, const char *end_date, 
        const char *change_filter, const char *price_range, const char *high_range,
            const char *low_range, const char *symbol) {

    Node* head = NULL;
    int found = 0;
    const char* api_token = getenv("FINNHUB_API_KEY"); //[Feature] Enviromental variable
    if (!api_token) {
        fprintf(stderr, "FINNHUB_API_KEY not set.\n");
        return NULL;
    }

    char command[512];
    snprintf(command, sizeof(command),
        "curl -s --max-time 30 \"https://finnhub.io/api/v1/quote?symbol=%s&token=%s\"", symbol, api_token);

    for (int i = 0; i < duration; i++) {
        FILE* fp = popen(command, "r");
        if (!fp) {
            fprintf(stderr, "Failed to run curl.\n");
            continue;
        }

        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), fp)) {
            float current_price, change, percent_change, high_price, low_price, open_price, previous_close_price;
            long timestamp;
            if (sscanf(buffer, "{\"c\":%f,\"d\":%f,\"dp\":%f,\"h\":%f,\"l\":%f,\"o\":%f,\"pc\":%f,\"t\":%ld}",
           &current_price, &change, &percent_change, &high_price, &low_price, &open_price, &previous_close_price, &timestamp) == 8) {


                time_t rawtime = (time_t)timestamp;
                struct tm* timeinfo = localtime(&rawtime);
                char date[20];
                strftime(date, sizeof(date), "%Y-%m-%d", timeinfo);

                float change_percent = ((current_price - previous_close_price) / previous_close_price) * 100.0f;
                char change_str[32];
                snprintf(change_str, sizeof(change_str), "%.2f", change_percent);

                if (!is_date_in_range(date, start_date, end_date)) continue;
                if (!is_change_matching(change_str, change_filter)) continue;
                if (!is_within_range(current_price, price_range)) continue;
                if (!is_within_range(high_price, high_range)) continue;
                if (!is_within_range(low_price, low_range)) continue;

                /*if (head) {
                    if (strcmp(date, head->d.date) == 0 && 
                        fabs(current_price - head->d.price) < 0.001 &&
                        fabs(open_price - head->d.open) < 0.001 &&
                        fabs(high_price - head->d.high) < 0.001 &&
                        fabs(low_price - head->d.low) < 0.001 &&
                        fabs(change_percent - head->d.change) < 0.001) {
                        printf("The market is closed.\n");
                        exit(0);}
                }*/

                printf("Date: %s | Price: %.2f | Open: %.2f | High: %.2f | Low: %.2f | Change: %.2f%%\n",
                       date, current_price, open_price, high_price, low_price, change_percent);

                head = createStruct(head, date, current_price, open_price, high_price, low_price, 0, change_percent);
                found = 1;
            } else {
                if(current_price == 0) {
                    fprintf(stderr, "The symbol doesn't exist\n");
                    exit(1);}
                else
                    fprintf(stderr, "Bad response: %s\n", buffer);
            }
        }

        pclose(fp);
        sleep(1);
    }

    if (!found) {
        printf("No results found for the given query.\n");
    }

    return head;
}
