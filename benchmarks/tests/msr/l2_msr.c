 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/l2_msr
 */
#include "msr.h"

int measure_msr(int cpu_model, int cpu_info[3], double energy_units[2], double *r1, double *r2) {
    int dram_avail = 2;
	int fd;
	long long result;
	double package_before,package_after;
	double dram_before,dram_after;
    int retval = 0;

    int *arr = malloc(L2_LL_SIZE*sizeof(int));

    for(int i = 0; i < L2_LL_SIZE; i++) {
        arr[i] = L2_LL_SIZE - i;
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
        int index = 0;

        while(index < L2_SIZE) {
            int j = index;
            for (j; j < L2_LL_SIZE;) {
                retval += arr[j];
                j += L2_SIZE;
            }
            index++;
        }
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
	return retval;

}

int main (int argc, char* argv[]) {
    double package_measure[RUNS];
    double dram_measure[RUNS];
    int cpu_info[3]; // 0 -> pp0, 1-> pp1, 2-> dram
    double energy_units[2]; // 0 -> cpu, 1 -> dram

    get_cpu_info(CPU_HASWELL_EP, cpu_info, energy_units);
    
    printf("---------------------------------------\n");
//     for(int i = 0; i < RUNS; i++) {
        measure_msr(CPU_HASWELL_EP, cpu_info, energy_units, 
                                    (package_measure + 0), (dram_measure + 0));
//     }

    print_avg(package_measure, RUNS);
//     print_avg(dram_measure);

    return 0;

}
