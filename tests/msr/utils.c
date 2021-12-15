#include "utils.h"

// assumes that ll is not NULL
int populate_list(struct ll *head, long long size) {
    if(head == NULL) {
        return -1;
    }

    head->size = size;
    struct ll* curr = head;

    for(long long i = 0; i < size; i++) {
        curr->val = -1; 
        curr->next = malloc(sizeof(struct ll));
        curr = curr->next;
    }

    curr->next = NULL;

    return 0;

}

int free_list(struct ll *head) {
    struct ll *curr = head; 

    while(curr != NULL) {
        struct ll *temp = curr; 
        curr = curr->next; 
        free(temp);
    }
    return 0;
}

int populate_ps_list(struct page_size_ll *head, long long size) {
    if(head == NULL) {
        return -1;
    }

    head->size = size;
    struct page_size_ll* curr = head;

    for(long long i = 0; i < size; i++) {
        curr->arr[0] = 0; 
        curr->next = malloc(sizeof(struct page_size_ll));
        curr = curr->next;
    }

    curr->next = NULL;

    return 0;

}

int free_ps_list(struct page_size_ll* head) {
    struct page_size_ll *curr = head; 

    while(curr != NULL) {
        struct page_size_ll *temp = curr; 
        curr = curr->next; 
        free(temp);
    }
    return 0;

}

void print_avg(double measurements[], int runs) {

    double sum = 0;      // overflow possibility?
    for(int i = 0; i < runs; i++) {
        sum+=measurements[i];
    }

    double avg = sum/runs;

    fprintf(stdout, "Average over %d runs: %fJ\n", runs, avg);
    printf("---------------------------------------\n");

}
