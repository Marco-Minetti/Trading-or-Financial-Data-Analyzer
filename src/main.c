#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include "data_structures.h"
#include "query_interface.h"
#include "analytics.h"
#include "binary_io.h"

void print_usage(const char *program_name) {
    printf("Usage: %s -m <mode> [options]\n", program_name);
    printf("Modes:\n");
    printf("  csv   - Analyze data from a CSV file\n");
    printf("  live  - Fetch and analyze live data from Finnhub\n");
    printf("\nOption for 'csv' mode:\n");
    printf("  -f <csv_file>     CSV file containing stock data\n");
    printf("  -b                Save to binar\n");
    printf("  -r                Read from binary\n");
    printf("\nOption for 'live' mode:\n");
    printf("  -t <duration>     Duration in seconds to fetch live data\n");
    printf("  -y <symbol>   Stock symbol to query (e.g., AAPL, TSLA). Default is AAPL.\n");
    printf("\nOptional options for both mode:\n"); 
    printf("  -s <start_date>   Start date for analysis (optional)\n");
    printf("  -e <end_date>     End date for analysis (optional)\n");
    printf("  -c <+|->          Change filter: '+' for positive, '-' for negative (optional)\n");
    printf("  -p <min:max>      Price range filter (optional)\n");
    printf("  -h <min:max>      High price range filter (optional)\n");
    printf("  -l <min:max>      Low price range filter (optional)\n");
}

int main(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;
    int opt;
    int duration = 5;
    char *mode = NULL;
    char *filename = NULL;
    char *start_date = NULL;
    char *end_date = NULL;
    char *change_filter = NULL;
    char *price_range = NULL;
    char *high_range = NULL;
    char *low_range = NULL;
    char *symbol = "AAPL";
    int save_binary = 0;
    int load_binary = 0;

    while ((opt = getopt(argc, argv, "m:f:s:e:c:p:h:l:t:y:br")) != -1) {
        switch (opt) {
            case 'm': mode = optarg; break;
            case 'f': filename = optarg; break;
            case 's': start_date = optarg; break;
            case 'e': end_date = optarg; break;
            case 'c': change_filter = optarg; break; // '+' or '-'
            case 'p': price_range = optarg; break;  // "min:max"
            case 'h': high_range = optarg; break;   // "min:max"
            case 'l': low_range = optarg; break;    // "min:max"
            case 't': duration = atoi(optarg); break;
            case 'y': 
            for (int i = 0; optarg[i] != '\0'; i++) {
                optarg[i] = toupper((unsigned char)optarg[i]);  // Convert to uppercase
            }
            symbol = optarg; 
            break;      
            case 'b': save_binary = 1; break;         // save to binary
            case 'r': load_binary = 1; break;         // read from binary
            default:
                print_usage(argv[0]);
                //printf("Usage: %s -f <csv_file> [-s start_date] [-e end_date] [-c +|-] [-p min:max] [-h min:max] [-l min:max]\n", argv[0]);
                return 1;
        }
    }

    if (mode == NULL) {
        fprintf(stderr, "Error: Mode must be specified using -m option.\n");
        print_usage(argv[0]);
        return 1;
    }

    Node* head = NULL;

    if (strcmp(mode, "csv") == 0) {
        if (load_binary) {
            // Load previously saved binary file
            head = load_from_binary("stock_data.bin");
            if (!head) {
                fprintf(stderr, "Failed to load data from binary file.\n");
                return 1;
            }
            printf("Data loaded from binary file.\n");
        } else {
            if (filename == NULL) {
                fprintf(stderr, "Error: CSV file must be specified using -f option in 'csv' mode.\n");
                print_usage(argv[0]);
                return 1;
            }
            head = query_stock_price(filename, start_date, end_date, change_filter, price_range, high_range, low_range);
            if (save_binary) {
                save_to_binary(head, "stock_data.bin");
                printf("Data saved to binary file.\n");
            }
        }
    } else if (strcmp(mode, "live") == 0) {
        if (duration <= 0) {
            fprintf(stderr, "Error: Duration must be specified using -t option in 'live' mode.\n");
            print_usage(argv[0]);
            return 1;
        }
        head = query_live_stock_price(duration, start_date, end_date, change_filter, price_range, high_range, low_range, symbol);
    } else {
        fprintf(stderr, "Error: Invalid mode specified.\n");
        print_usage(argv[0]);
        return 1;
    }

    if (head != NULL) {
        calculateSMA(head, 5);      // Compute 5-day SMA
        calculateMinMax(head);      // Find min/max price
        if(strcmp(mode, "csv") == 0)
            calculateVolatility(head);  // Compute volatility
        clearingMemory(head);
    } else {
        fprintf(stderr, "Error: No data available for analysis.\n");
    }

    return 0;
}