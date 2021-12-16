 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/l2
 */
#include "msr.h"

int main() {

    struct ll *head = malloc(sizeof(struct ll));
    struct ll *curr = head; 

    int retval = populate_list(head, L2_LL_SIZE);

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

//     free_list(head);
    return retval;
}
