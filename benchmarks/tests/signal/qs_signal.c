 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/qs_signal
 */

#include "signal.h"

int cmpfunc (const void * a, const void * b) {

       return ( *(int*)a - *(int*)b );
}

void qs_measure () {
    int qs_arr[L2_SIZE];    // array that fits into L3 cache

    for(int i = 0; i < L2_SIZE;i++) {
        qs_arr[L2_SIZE-i] = i;
    }

    for(int i = 0; i < ITERATIONS_PER_RUN; i++) {
        qsort(qs_arr, L2_SIZE, sizeof(int), cmpfunc);
    }

}

int main (int argc, char* argv[]) {
    
    measure_msr("qs_signal_out", &qs_measure);

    return 0;

}
