 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/mm_msr
 */

#include "signal.h"

void matrix_multiply(int **one, int **two, int **result) {
    int rows1 = MM_SIZE;
    int cols2 = MM_SIZE;
    int common = MM_SIZE; //cols of 1 and rows of 2

    for(int rr = 0; rr < rows1; rr++) {
        for(int rc = 0; rc < cols2; rc++) {
            result[rr][rc] = 0;
        }
    }
    for(int i = 0; i < rows1; i++) {
        for(int j=0; j < cols2; j++) {
            for(int k = 0; k < common; k++) {
                result[i][j] += one[i][k]*two[k][j];
            }
        }
    }
}

void matrix_multiply_measure() {
    int **one = malloc(MM_SIZE*sizeof(int*));
    int **two = malloc(MM_SIZE*sizeof(int*));
    int **res = malloc(MM_SIZE*sizeof(int*));
    for(int i = 0; i < MM_SIZE; i++) {
        one[i] = malloc(MM_SIZE*sizeof(int));
        two[i] = malloc(MM_SIZE*sizeof(int));
        res[i] = malloc(MM_SIZE*sizeof(int));
    }

    for(int i = 0; i < MM_SIZE; i++) {
        for(int j = 0; j < MM_SIZE; j++) {
            one[i][j] = i*j;
            two[i][j] = i+j;
        }
    }

    for(int i = 0; i < 100; i++) {
        matrix_multiply(one, two, res);
    }

    for(int i = 0; i < MM_SIZE; i++) {
        free(one[i]);
        free(two[i]);
        free(res[i]);
    }

    free(one);
    free(two);
    free(res);

    return;

}

int main (int argc, char* argv[]) {

    measure_msr("mm_signal_out", &matrix_multiply_measure);

    return 0;
}
