 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_sleep_msr rapl_sleep_msr.c -lpapi
 * to run: sudo ./rapl_sleep_msr
 */
#include "msr.h"

 int open_msr(int core) {

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

 long long read_msr(int fd, int which) {

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
