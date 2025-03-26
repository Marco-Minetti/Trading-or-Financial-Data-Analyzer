#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "csv_reader.h"
#include "data_structures.h"
#include "query_interface.h"

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

    while ((opt = getopt(argc, argv, "f:s:e:c:p:h:l:")) != -1) {
        switch (opt) {
            case 'f': filename = optarg; break;
            case 's': start_date = optarg; break;
            case 'e': end_date = optarg; break;
            case 'c': change_filter = optarg; break;  // '+' or '-'
            case 'p': price_range = optarg; break;    // "min:max"
            case 'h': high_range = optarg; break;     // "min:max"
            case 'l': low_range = optarg; break;      // "min:max"
            default:
                printf("Usage: %s -f <csv_file> [-s start_date] [-e end_date] [-c +|-] [-p min:max] [-h min:max] [-l min:max]\n", argv[0]);
                return 1;
        }
    }

    if (!filename) {
        printf("Error: CSV file must be specified using -f option.\n");
        return 1;
    }

    query_stock_price(filename, start_date, end_date, change_filter, price_range, high_range, low_range);
    return 0;
}
