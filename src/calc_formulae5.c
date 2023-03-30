/**
 * Arguments are as follows:
 * argv[0] - executable 
 * argv[1] - flags (m -> mean, g-> graph, t-> output table, s-> stats)
 * argv[2] - name of data labels file 
 * argv[3] - name of coeff file
 * argv[4] - name of graphing file 
 */ 

#include "list.h"
#include "utils.h"
#include "errno.h"
int main(int argc, char** argv) {
    
//     char weight_names[INPUT_SIZE][10] = {"l1_icache", "cycles", "ins", "l2", "tlb_data", "l1_dcache",
//     "tlb_ins", "l3"};

    char* graph_file = "graph_out_one";

    if(argc < 4) {
        printf("Usage: ./fifth -[mgts] <path to data labels file> <path to \
        coeffecients file> [<path to graphing output file>]\n");
        exit(-1);
    }

    if(argc == 5) {
        graph_file = argv[4];
    }


    ch_al labels_list;
    init_list(&labels_list);

    FILE* fp = fopen(argv[2], "r");
    if(fp == NULL) {
        printf("couldn't open data labels file, errno: %d\n", errno);
        exit(-1);
    }

    char* line = NULL;

    size_t len = 0;
    ssize_t amt_read = 0; 

    amt_read = getline(&line, &len, fp);

    while(amt_read != -1) {
        line[strcspn(line, "\n")]=0;
//         printf("%ld %s", amt_read, line);
        if(strcmp("cycles", line) == 0) {
            amt_read = getline(&line, &len, fp);
            continue;
        }
        append(&labels_list, line, amt_read);
        amt_read = getline(&line, &len, fp);
    }

    print_list(&labels_list);
    printf("%ld\n", labels_list.size);


    double weights[labels_list.size];

    errno = 0;

    fp =  fopen(argv[3], "r");  
    if(fp == NULL) {
        printf("file not opened, errno: %d!\n", errno);
        return -1;
    }
    
    line = NULL;

    len = 0;
    amt_read = 0;

    amt_read = getline(&line, &len, fp);

    if( amt_read == -1 ) {
        printf("read nothing from file :(\n");
        return -1;
    }

//     printf("%s\n", line);

    char* token = strtok(line, ",");
    int i = 0;

    printf("Weights for each field: \n");
    while(token != NULL) {
        weights[i] = atof(token);
        printf("%s: %e\n", labels_list.array[i], weights[i]);
        token = strtok(NULL, ",");
        i++;
    }
    printf("\n");
    printf("labels_list.size is %ld\n", labels_list.size);
    return calc_error_main(weights, argv[1], graph_file, labels_list.size + 1);
}
