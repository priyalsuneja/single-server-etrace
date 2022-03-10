 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 */
#include "msr.h"

 extern int errno;

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

    fd=open_msr(0); // todo: add package detection + map and stuff

    /* Calculate the units used */
    result=read_msr(fd,MSR_RAPL_POWER_UNIT);

    cpu_energy_units=pow(0.5,(double)((result>>8)&0x1f));

    /* On Haswell EP and Knights Landing */
    /* The DRAM units differ from the CPU ones */
        dram_energy_units=pow(0.5,(double)16);   // we know we're on haswell
                                                    // so this is ok
    energy_units[0] = cpu_energy_units;
    energy_units[1] = dram_energy_units;

    return 0;
}

void sig_handler(int signum) {
    int fd = open_msr(0);

    long long result = read_msr(fd, MSR_PKG_ENERGY_STATUS);

    close(fd);

    reading = (double)result*energy_units[0];
    fprintf(fptr, "%f\n", reading);

    sig_triggered = 1;
}

void measure_msr(char* filename, void (*func_ptr)()) {

    fptr = fopen(filename, "w+");

    if(!fptr) {
        printf("errno: %d, err_string: %s\n", errno, strerror(errno));
        return;
    }

    signal(SIGALRM, sig_handler);

    ualarm(500*1000, 500*1000); // 1000 us = 1ms,; 0.5s = 500 ms
//     sig_handler(SIGALRM);
//     sig_triggered = 0;

    get_cpu_info(CPU_HASWELL_EP, cpu_info, energy_units);

    func_ptr();

    if(sig_triggered == 0) {
        sig_handler(SIGALRM);
    }
}
