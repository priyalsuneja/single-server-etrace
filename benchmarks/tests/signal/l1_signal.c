 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/l1_msr
 */

#include "signal.h"

void l1_measure() {
    int retval;
    int arr[L1_LL_SIZE];
    
    for(int i = 0; i < L1_LL_SIZE; i++) {
        arr[i] = L1_LL_SIZE - i;
    }

    for(int i = 0; i < 1000; i++) {
        int index = 0; 

        while(index < L1_SIZE) {
            int j = index;
            while(j < L1_LL_SIZE) {
                retval += arr[j];
                j += L1_SIZE;
            }
            index++;
        }
    }

	return ;

}

int main (int argc, char* argv[]) {

    measure_msr("l1_signal_out", &l1_measure);

    return 0;

}
