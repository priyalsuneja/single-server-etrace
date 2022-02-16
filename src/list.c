#include "list.h"

int init_list(ch_al* list) {
    list->array = malloc(10*sizeof(char*));
    list->len = 10;
    list->size = 0;

    return 0;
}

int append(ch_al* list, char* elem, ssize_t size_of_elem) {
    if(list->len == list->size) {
        list->array = realloc(list->array, 2*list->len);
        list->len = 2*list->len;
    }

    list->array[list->size] = malloc(size_of_elem);
//     printf("%x, %x\n", list->array[list->size], elem);
    strncpy(list->array[list->size], elem, size_of_elem);
    list->size++;

    return 0;
}

int free_list(ch_al* list) {
    for(int i = 0; i < list->size; i++) {
        free(list->array[i]);
    }

    free(list->array);

    return 0;
}

void print_list(const ch_al *const list) {

    printf("Printing list start ---------- \n");
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", list->array[i]);
    }
    printf("Printing list end ---------- \n");

}
