#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define RUNS 1
#define ITERATIONS_PER_RUN 1000
#define PAGE_SIZE 4*1024    // 4kB * 8 just to see
#define TLB_ENTRIES 64
#define TLB_ASSOC 4


int main() {

    struct page_size_ll *head = malloc(sizeof(struct page_size_ll));
    struct page_size_ll *curr = head; 
    long long ll_size = TLB_ASSOC*TLB_ENTRIES*8;

    int retval = populate_ps_list(head, ll_size);

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

//     free_ps_list(head);
}
