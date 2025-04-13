#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "data_structures.h"
#include "query_interface.h"
#include "analytics.h"
#include "binary_io.h"

int main(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;
    int opt;
    char *filename = NULL;
    char *start_date = NULL;
    char *end_date = NULL;
    char *change_filter = NULL;
    char *price_range = NULL;
    char *high_range = NULL;
    char *low_range = NULL;
    int save_binary = 0;
    int load_binary = 0;

    while ((opt = getopt(argc, argv, "f:s:e:c:p:h:l:br")) != -1) {
        switch (opt) {
            case 'f': filename = optarg; break;
            case 's': start_date = optarg; break;
            case 'e': end_date = optarg; break;
            case 'c': change_filter = optarg; break;  // '+' or '-'
            case 'p': price_range = optarg; break;    // "min:max"
            case 'h': high_range = optarg; break;     // "min:max"
            case 'l': low_range = optarg; break;      // "min:max"
            case 'b': save_binary = 1; break;         // save to binary
            case 'r': load_binary = 1; break;         // read from binary
            default:
                printf("Usage: %s -f <csv_file> [-s start_date] [-e end_date] [-c +|-] [-p min:max] [-h min:max] [-l min:max] [-b] [-r]\n", argv[0]);
                return 1;
        }
    }

    Node* head = NULL;
    
    if (load_binary) {
        // Load previously saved binary file
        head = load_from_binary("stock_data.bin");
        if (!head) {
            fprintf(stderr, "Failed to load data from binary file.\n");
            return 1;
        }
        printf("Data loaded from binary file.\n");
    } else {
        if (!filename) {
            printf("Error: CSV file must be specified using -f option.\n");
            return 1;
        }
        // Load and filter CSV data
        query_stock_price(filename, start_date, end_date, change_filter, price_range, high_range, low_range);
        head = nodesCombined(NULL);
        if (!head) {
            fprintf(stderr, "No valid data found.\n");
            return 1;
        }
        if (save_binary) {
            save_to_binary(head, "stock_data.bin");
            printf("Data saved to binary file.\n");
        }
    }

    // Perform calculations
    calculateSMA(head, 5);  // Compute 5-day SMA
    calculateMinMax(head);  // Find min/max price
    calculateVolatility(head);  // Compute volatility
    clearingMemory(head);

    return 0;
}
