#include "../utils/calc_error.h"
#include "errno.h"
int main(int argc, char** argv) {


    double weights[INPUT_SIZE];

    errno = 0;

    FILE* fp = 
             fopen("/homes/sys/suneja/treehouse/single-server-etrace/.sse_temp/coefficients.csv",
             "r");    // TODO: make this an argument please!
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


    // argv[1] contains flags
    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");
}
