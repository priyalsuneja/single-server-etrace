 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 */
#include "msr.h"

int main() {

    struct ll *head = malloc(sizeof(struct ll));
    struct ll *curr = head; 
    int retval;
    retval = populate_list(head, L1_LL_SIZE);


    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

    return retval;
}
