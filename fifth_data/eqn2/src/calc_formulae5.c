#include "../utils/calc_error.h"
#include "errno.h"
int main(int argc, char** argv) {


    double weights[INPUT_SIZE];
//     weights[L1_ICACHE] = 2.40490160e-07;
//     weights[CYCLES]  = -5.51959774e-10;
//     weights[IPC] = 1.27338249e-01;
//     weights[L2] = 2.62021396e-07;
//     weights[TLB_DATA] = -1.90155521e-08;
//     weights[L1_DCACHE] = -5.98634829e-09;
//     weights[TLB_INS] = 1.54041924e-04;

    errno = 0;

    FILE* fp = fopen("/homes/sys/suneja/treehouse/single-server-etrace/coefficients.csv", "r");
    if(fp == NULL) {
        printf("file not opened, errno: %d!\n", errno);
        return -1;
    }
    
    char* line = NULL;

    size_t len = 0;
    ssize_t amt_read = 0;

    amt_read = getline(&line, &len, fp);

    if( amt_read == -1 ) {
        printf("read nothing from file :(\n");
        return -1;
    }

    printf("%s\n", line);

    char* token = strtok(line, ",");
    int i = 0;

    while(token != NULL) {
        weights[i] = atof(token);
        printf("%e\n", weights[i]);
        token = strtok(NULL, ",");
        i++;
    }


    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");
}
