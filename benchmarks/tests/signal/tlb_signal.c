 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/tlb_signal
 */

#include "signal.h"

void tlb_measure() {
    struct page_size_ll *head = malloc(sizeof(struct page_size_ll));
    struct page_size_ll *curr = head; 

    populate_ps_list(head, TLB_LL_SIZE);

    for(int i = 0; i < ITERATIONS_PER_RUN; i++) {
        while(curr != NULL) {
            curr = curr->next; 
        }
        curr = head;
    }

//     int retval;
// 
//     int *arr = malloc(TLB_LL_SIZE*sizeof(int)*PAGE_SIZE);
// 
//     for(int i = 0; i < ITERATIONS_PER_RUN; i++) {
//         int index = 0; 
// 
//         while(index < PAGE_SIZE) {
//             int j = index;
//             while(j < TLB_LL_SIZE) {
//                 retval += arr[j];
//                 j += PAGE_SIZE;
//             }
//             index++;
//         }
//     }

	return;

}

int main (int argc, char* argv[]) {

    measure_msr("tlb_signal_out", &tlb_measure);

    return 0;

}
