 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 */
#include <stdio.h>
#include <signal.h>
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
#include "../includes/utils.h"

#define RUNS 1
// #define ITERATIONS_PER_RUN 1000
#define ITERATIONS_PER_RUN  1000
#define L1_SIZE 32*1024
#define L2_SIZE 256*1024
#define PAGE_SIZE 4*1024
#define TLB_ASSOC 4
#define TLB_ENTRIES 64
#define L1_LL_SIZE 5*5*L1_SIZE
#define L2_LL_SIZE 5*5*L2_SIZE
#define TLB_LL_SIZE TLB_ASSOC*TLB_ENTRIES*8*10
// #define MM_SIZE L1_SIZE/4
#define MM_SIZE 1024

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

int open_msr(int core);
long long read_msr(int fd, int which);
void sig_handler(int signum);
int get_cpu_info(int cpu_model, int cpu_info[3], double energy_units[2]);
void measure_msr(char* filename, void (*funcptr)());

extern int cpu_info[3];
extern double energy_units[2];
extern double reading; 
extern FILE *fptr;
extern int sig_triggered;
extern int gargc;
extern char** gargv;
