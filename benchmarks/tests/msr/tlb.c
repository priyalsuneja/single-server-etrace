 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/tlb
 */
#include "msr.h"

int main() {

    struct page_size_ll *head = malloc(sizeof(struct page_size_ll));
    struct page_size_ll *curr = head; 

    int retval = populate_ps_list(head, TLB_LL_SIZE);

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

//     free_list(head);
    return retval;
}
