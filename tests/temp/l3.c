#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define RUNS 1
#define ITERATIONS_PER_RUN 1
#define L3_SIZE 30720*1024


int main() {

    struct ll *head = malloc(sizeof(struct ll));
    struct ll *curr = head; 
    long long ll_size = 20*L3_SIZE;

    int retval = populate_list(head, ll_size);

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

//     free_list(head);
    return retval;
}
