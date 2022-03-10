 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/l2_signal
 */
#include "signal.h"

void l2_measure() {
    int retval;

    int *arr = malloc(L2_LL_SIZE*sizeof(int));

    for(int i = 0; i < L2_LL_SIZE; i++) {
        arr[i] = L2_LL_SIZE - i;
    }

    for(int i = 0; i < ITERATIONS_PER_RUN; i++) {
        int index = 0;

        while(index < L2_SIZE) {
            int j = index;
            while (j < L2_LL_SIZE) {
                retval += arr[j];
                j += L2_SIZE;
            }
            index++;
        }
    }

	return;

}

int main (int argc, char* argv[]) {

    measure_msr("l2_signal_out", &l2_measure);

    return 0;

}
