#ifndef BINARY_IO_H
#define BINARY_IO_H


void save_to_binary(Node* head, const char* filename);
Node* load_from_binary(const char* filename);

#endif