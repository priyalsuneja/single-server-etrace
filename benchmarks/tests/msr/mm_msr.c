 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/mm_msr
 */

#include "msr.h"

void matrix_multiply(int one[MM_SIZE][MM_SIZE], int two[MM_SIZE][MM_SIZE], int result[MM_SIZE][MM_SIZE]) {
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

int measure_msr(int cpu_model, int cpu_info[3], double energy_units[2], 
            double *r1, double *r2) {
    int dram_avail = 2;
	int fd;
	long long result;
	double package_before,package_after;
	double dram_before,dram_after;
    int one[MM_SIZE][MM_SIZE], two[MM_SIZE][MM_SIZE], res[MM_SIZE][MM_SIZE];

    for(int i = 0; i < MM_SIZE; i++) {
        for(int j = 0; j < MM_SIZE; j++) {
            one[i][j] = i*j;
            two[i][j] = i+j;
        }
    }


    fd=open_msr(0); // todo: add package detection + map and stuff

    /* Package Energy */
    result=read_msr(fd,MSR_PKG_ENERGY_STATUS);
    package_before=(double)result*energy_units[0];


    /* Updated documentation (but not the Vol3B) says Haswell and	*/
    /* Broadwell have DRAM support too				*/
    if (cpu_info[dram_avail]) {
        result=read_msr(fd,MSR_DRAM_ENERGY_STATUS);
        dram_before=(double)result*energy_units[1];
    }

    close(fd);

    for(int i = 0; i < ITERATIONS_PER_RUN; i++) {
        matrix_multiply(one, two, res);
    }

    fd = open_msr(0);

    result=read_msr(fd,MSR_PKG_ENERGY_STATUS);
    package_after=(double)result*energy_units[0];
    *r1 = package_after - package_before;


    if (cpu_info[dram_avail]) {
        result=read_msr(fd,MSR_DRAM_ENERGY_STATUS);
        dram_after=(double)result*energy_units[1];
        *r2 = dram_after - dram_before;
    }

    close(fd);
// 	return retval;
    return 1;

}

int main (int argc, char* argv[]) {
    double package_measure[RUNS];
    double dram_measure[RUNS];
    int cpu_info[3]; // 0 -> pp0, 1-> pp1, 2-> dram
    double energy_units[2]; // 0 -> cpu, 1 -> dram

    get_cpu_info(CPU_HASWELL_EP, cpu_info, energy_units);
    
    printf("---------------------------------------\n");
        measure_msr(CPU_HASWELL_EP, cpu_info, energy_units, 
                                    (package_measure + 0), (dram_measure + 0));

    print_avg(package_measure, RUNS);
//     print_avg(dram_measure);

    return 0;

}
