 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/mm_msr
 */

#include "msr.h"

// int cpu_info[3]; // 0 -> pp0, 1-> pp1, 2-> dram
// double energy_units[2]; // 0 -> cpu, 1 -> dram

// extern int errno;

// double readings[1000000];
// double reading;
// FILE *fptr;
// unsigned int count = 0;

// void sig_handler(int signum) {
//     int fd=open_msr(0); // todo: add package detection + map and stuff
// 
//     /* Package Energy */
//     long long result = read_msr(fd,MSR_PKG_ENERGY_STATUS);
// 
//     close(fd);
// 
//     reading = (double)result*energy_units[0];
//     fprintf(fptr, "%f\n", reading);
//     
// }

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

void matrix_multiply_2() {
    int **one = malloc(MM_SIZE*sizeof(int*));
    int **two = malloc(MM_SIZE*sizeof(int*));
    int **res = malloc(MM_SIZE*sizeof(int*));
    for (int i = 0; i < MM_SIZE; i++) {
	one[i] = malloc(MM_SIZE*sizeof(int));
	two[i] = malloc(MM_SIZE*sizeof(int));
	res[i] = malloc(MM_SIZE*sizeof(int));
    }

    for (int i = 0; i < MM_SIZE; i++) {
	for(int j = 0; j < MM_SIZE; j++) {
	    one[i][j] = i*j;
	    two[i][j] = i+j;
	}
    }

    for (int i = 0; i < 100; i++) {
	matrix_multiply(one, two, res);
    }

    for (int i = 0; i < MM_SIZE; i++) {
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

//     fptr = fopen("mm_signal_out", "w+");
// 
//     if(!fptr) {
//         printf("errno: %d ", errno);
//         printf("err string: %s\n", strerror(errno));
//         return 0;
//     }
// 
//     signal(SIGALRM, sig_handler);
// 
//     ualarm(500*1000,500*1000);  // 1000 us = 1 ms; 0.5s = 500 ms
// //     ualarm(500,500);
// 
//     get_cpu_info(CPU_HASWELL_EP, cpu_info, energy_units);
//     
//     measure_msr();
// 
// //     fclose(fptr);

    printf("%s\n", strcat(argv[0], "_out"));
    
    printf("main: %p\n", &main);

    measure_msr("mm_signal_out", &matrix_multiply_measure);

    printf("next one!\n");
    measure_msr("mm_signal_out_2", &matrix_multiply_2);
    return 0;
}
