 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_sleep_msr rapl_sleep_msr.c -lpapi
 * to run: sudo ./rapl_sleep_msr
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include "utils.h"

#define RUNS 1
#define L3_SIZE 5*30720*1024
#define MSR_RAPL_POWER_UNIT	0x606

/*
 * Platform specific RAPL Domains.
 * Note that PP1 RAPL Domain is supported on 062A only
 * And DRAM RAPL Domain is supported on 062D only
 */
/* Package RAPL Domain */
#define MSR_PKG_RAPL_POWER_LIMIT 0x610
#define MSR_PKG_ENERGY_STATUS 0x611
#define MSR_PKG_PERF_STATUS	0x613
#define MSR_PKG_POWER_INFO 0x614

/* PP0 RAPL Domain */
#define MSR_PP0_POWER_LIMIT	0x638
#define MSR_PP0_ENERGY_STATUS 0x639
#define MSR_PP0_POLICY 0x63A
#define MSR_PP0_PERF_STATUS 0x63B

/* PP1 RAPL Domain, may reflect to uncore devices */
#define MSR_PP1_POWER_LIMIT	0x640
#define MSR_PP1_ENERGY_STATUS 0x641
#define MSR_PP1_POLICY 0x642

/* DRAM RAPL Domain */
#define MSR_DRAM_POWER_LIMIT 0x618
#define MSR_DRAM_ENERGY_STATUS 0x619
#define MSR_DRAM_PERF_STATUS 0x61B
#define MSR_DRAM_POWER_INFO 0x61C

/* PSYS RAPL Domain */
#define MSR_PLATFORM_ENERGY_STATUS 0x64d

/* RAPL UNIT BITMASK */
#define POWER_UNIT_OFFSET 0
#define POWER_UNIT_MASK	0x0F

#define ENERGY_UNIT_OFFSET 0x08
#define ENERGY_UNIT_MASK 0x1F00

#define TIME_UNIT_OFFSET 0x10
#define TIME_UNIT_MASK	0xF000

#define CPU_SANDYBRIDGE	42
#define CPU_SANDYBRIDGE_EP 45
#define CPU_IVYBRIDGE 58
#define CPU_IVYBRIDGE_EP 62
#define CPU_HASWELL	60
#define CPU_HASWELL_ULT	69
#define CPU_HASWELL_GT3E 70
#define CPU_HASWELL_EP 63
#define CPU_BROADWELL 61
#define CPU_BROADWELL_GT3E 71
#define CPU_BROADWELL_EP 79
#define CPU_BROADWELL_DE 86
#define CPU_SKYLAKE 78
#define CPU_SKYLAKE_HS 94
#define CPU_SKYLAKE_X 85
#define CPU_KNIGHTS_LANDING	87
#define CPU_KNIGHTS_MILL 133
#define CPU_KABYLAKE_MOBILE	142
#define CPU_KABYLAKE 158
#define CPU_ATOM_SILVERMONT	55
#define CPU_ATOM_AIRMONT 76
#define CPU_ATOM_MERRIFIELD 74
#define CPU_ATOM_MOOREFIELD	90
#define CPU_ATOM_GOLDMONT	92
#define CPU_ATOM_GEMINI_LAKE 122
#define CPU_ATOM_DENVERTON 95

void print_avg(double measurements[]) {

    double sum = 0;      // overflow possibility?
    for(int i = 0; i < RUNS; i++) {
        sum+=measurements[i];
    }

    double avg = sum/RUNS;

    fprintf(stdout, "Average over %d runs: %f\n", RUNS, avg);
    printf("---------------------------------------\n");

}

void print_avg_ll(long long measurements[]) {

    long long sum = 0;      // overflow possibility?
    for(int i = 0; i < RUNS; i++) {
        sum+=measurements[i];
    }

//     double avg = sum/RUNS;

    fprintf(stdout, "sum over %d runs: %lld\n", RUNS, sum);
    printf("---------------------------------------\n");

}

static int open_msr(int core) {

	char msr_filename[BUFSIZ];
	int fd;

	sprintf(msr_filename, "/dev/cpu/%d/msr", core);
	fd = open(msr_filename, O_RDONLY);
	if ( fd < 0 ) {
		if ( errno == ENXIO ) {
			fprintf(stderr, "rdmsr: No CPU %d\n", core);
			exit(2);
		} else if ( errno == EIO ) {
			fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n",
					core);
			exit(3);
		} else {
			perror("rdmsr:open");
			fprintf(stderr,"Trying to open %s\n",msr_filename);
			exit(127);
		}
	}

	return fd;
}

static long long read_msr(int fd, int which) {

	long long data;

	if ( pread(fd, &data, sizeof data, which) != sizeof data ) {
		perror("rdmsr:pread");
		exit(127);
	}

	return (long long)data;
}

int get_cpu_info(int cpu_model, int cpu_info[3], double energy_units[2]) {
    int fd, result;
	double power_units,time_units;
	double cpu_energy_units,dram_energy_units;

    /** indices to cpu_info **/
    int pp0_avail = 0;
    int pp1_avail = 1;
    int dram_avail = 2;

	if (cpu_model<0) {
		printf("\tUnsupported CPU model %d\n",cpu_model);
		return -1;
	}

	switch(cpu_model) {

		case CPU_SANDYBRIDGE_EP:
		case CPU_IVYBRIDGE_EP:
			cpu_info[pp0_avail]=1;
			cpu_info[pp1_avail]=0;
			cpu_info[dram_avail]=1;
			break;

		case CPU_HASWELL_EP:
		case CPU_BROADWELL_EP:
		case CPU_SKYLAKE_X:
			cpu_info[pp0_avail]=1;
			cpu_info[pp1_avail]=0;
			cpu_info[dram_avail]=1;
			break;

		case CPU_KNIGHTS_LANDING:
		case CPU_KNIGHTS_MILL:
			cpu_info[pp0_avail]=0;
			cpu_info[pp1_avail]=0;
			cpu_info[dram_avail]=1;
			break;

		case CPU_SANDYBRIDGE:
		case CPU_IVYBRIDGE:
			cpu_info[pp0_avail]=1;
			cpu_info[pp1_avail]=1;
			cpu_info[dram_avail]=0;
			break;

		case CPU_HASWELL:
		case CPU_HASWELL_ULT:
		case CPU_HASWELL_GT3E:
		case CPU_BROADWELL:
		case CPU_BROADWELL_GT3E:
		case CPU_ATOM_GOLDMONT:
		case CPU_ATOM_GEMINI_LAKE:
		case CPU_ATOM_DENVERTON:
			cpu_info[pp0_avail]=1;
			cpu_info[pp1_avail]=1;
			cpu_info[dram_avail]=1;
			break;

		case CPU_SKYLAKE:
		case CPU_SKYLAKE_HS:
		case CPU_KABYLAKE:
		case CPU_KABYLAKE_MOBILE:
			cpu_info[pp0_avail]=1;
			cpu_info[pp1_avail]=1;
			cpu_info[dram_avail]=1;
			break;

	}

		printf("\tListing paramaters for package #0\n");

    fd=open_msr(0); // todo: add package detection + map and stuff

    /* Calculate the units used */
    result=read_msr(fd,MSR_RAPL_POWER_UNIT);

    power_units=pow(0.5,(double)(result&0xf));
    cpu_energy_units=pow(0.5,(double)((result>>8)&0x1f));
    time_units=pow(0.5,(double)((result>>16)&0xf));

    /* On Haswell EP and Knights Landing */
    /* The DRAM units differ from the CPU ones */
        dram_energy_units=pow(0.5,(double)16);   // we know we're on haswell
                                                    // so this is ok
        printf("DRAM: Using %lf instead of %lf\n",
            dram_energy_units,cpu_energy_units);

    printf("\t\tPower units = %.3fW\n",power_units);
    printf("\t\tCPU Energy units = %.8fJ\n",cpu_energy_units);
    printf("\t\tDRAM Energy units = %.8fJ\n",dram_energy_units);
    printf("\t\tTime units = %.8fs\n",time_units);

    energy_units[0] = cpu_energy_units;
    energy_units[1] = dram_energy_units;
    printf("\n");

    return 0;
}

int measure_msr(int cpu_model, int cpu_info[3], double energy_units[2], 
            double *r1, double *r2) {
    int dram_avail = 2;
	int fd;
	long long result;
	double package_before,package_after;
	double dram_before,dram_after;
    struct ll *head = malloc(sizeof(struct ll));
    struct ll *curr = head; 
    long long ll_size = 1*L3_SIZE;

    int retval = populate_list(head, ll_size);


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

    while(curr != NULL) {
        curr = curr->next; 
    }
    curr = head;

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
    for(int i = 0; i < RUNS; i++) {
        measure_msr(CPU_HASWELL_EP, cpu_info, energy_units, 
                                    (package_measure + i), (dram_measure + i));
    }

    print_avg(package_measure);
//     print_avg(dram_measure);

    return 0;

}
