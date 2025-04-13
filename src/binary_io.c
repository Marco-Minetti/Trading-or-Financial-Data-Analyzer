#include "binary_io.h"
#include <stdio.h>
#include <stdlib.h>

void save_to_binary(Node* head, const char* filename) {
    FILE *fp = fopen(filename, "wb");
    if(!fp) {
        perror("Failed to open binary file for writing");
        return;
    }
    Node* current = head;
    while (current) {
        fwrite(&(current->d), sizeof(Data), 1, fp);
        current = current->next;
    }
    fclose(fp);
    printf("Data saved to binary file: %s\n", filename);
}

Node* load_from_binary(const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Failed to open binary file for reading");
        return NULL;
    }
    Data d;
    while (fread(&d, sizeof(Data), 1, fp) == 1) {
        Data *copy = malloc(sizeof(Data));
        *copy = d;
        nodesCreate(copy);
    }
    fclose(fp);
    printf("Data loaded from binary file: %s\n", filename);
    return nodesCombined(NULL);
}
