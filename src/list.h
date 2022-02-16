#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct char_array_list {
    char** array;
    ssize_t len; // capacity of array
    ssize_t size;   // number of elements in array
} ch_al;


int init_list(ch_al* list);

int append(ch_al* list, char* elem, ssize_t size_of_elem);

int free_list(ch_al* list);

void print_list(const ch_al* const list);

