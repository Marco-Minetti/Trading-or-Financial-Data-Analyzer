#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_interface.h"
#include "data_structures.h"

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

void query_stock_price(const char *filename, const char *start_date, const char *end_date, 
                       const char *change_filter, const char *price_range, 
                       const char *high_range, const char *low_range) {
    char fileposition[256];
    snprintf(fileposition, sizeof(fileposition), "./data/%s", filename);
    FILE *file = fopen(fileposition, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", fileposition);
        return;
    }

    char line[MAX_LINE];
    int found = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char date[20], price[20], open[20], high[20], low[20], volume[20], change[20];

        // Parse CSV line
        sscanf(line, "\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\",\"%19[^\"]\"",
            date, price, open, high, low, volume, change);

        double price_value = atof(price);
        double high_value = atof(high);
        double low_value = atof(low);

        char *percent_sign = strchr(change, '%');
        if (percent_sign) *percent_sign = '\0';  // Remove '%'
        double change_value = atof(change) / 100.0;

        // Check filters
        if (!is_date_in_range(date, start_date, end_date)) continue;
        if (!is_change_matching(change, change_filter)) continue;
        if (!is_within_range(price_value, price_range)) continue;
        if (!is_within_range(high_value, high_range)) continue;
        if (!is_within_range(low_value, low_range)) continue;

        // Print matching row
        printf("Date: %s | Price: %s | Open: %s | High: %s | Low: %s | Volume: %s | Change: %s\n",
               date, price, open, high, low, volume, change); //we can take it off when we want
        createStruct(date, atof(price), atof(open), atof(high), atof(low), atof(volume), atof(change));
        found = 1;
    }

    if (!found) {
        printf("No results found for the given query.\n");
    }

    fclose(file);
}