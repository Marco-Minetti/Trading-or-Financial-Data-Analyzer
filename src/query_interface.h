#ifndef QUERY_INTERFACE_H
#define QUERY_INTERFACE_H

void query_stock_price(const char *filename, const char *start_date, const char *end_date,
                       const char *change_filter, const char *price_range, 
                       const char *high_range, const char *low_range);

Node* query_live_stock_price(int duration, const char *start_date, const char *end_date, 
                        const char *change_filter, const char *price_range, 
                        const char *high_range, const char *low_range);

#endif