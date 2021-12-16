 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 */
#include "msr.h"

int main() {

    struct ll *head = malloc(sizeof(struct ll));
    int retval;
    retval = populate_list(head, L1_LL_SIZE);


    return retval;
}
