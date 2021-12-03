 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_sleep rapl_sleep.c -lpapi
 * to run: sudo ./rapl_sleep
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <papi.h>
#include <sys/syscall.h>

#define NUM_EVENTS 3
#define RUNS 1
#define ITERATIONS_PER_RUN 1

char events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE0",
};

void print_avg(float measurements[]) {

    float sum = 0;      // overflow possibility?
    for(int i = 0; i < RUNS; i++) {
        sum+=measurements[i];
    }

    float avg = sum/RUNS;

    fprintf(stdout, "Average over %d runs: %f\n", RUNS, avg);
    printf("---------------------------------------\n");

}
int add_events(int eventset, int rapl_cid) {
    int eventcode = PAPI_NATIVE_MASK; 
    int retval;

    int r = PAPI_enum_cmp_event(&eventcode, PAPI_ENUM_FIRST, rapl_cid);
    int i = 0;

    while(r == PAPI_OK) {
        if( i >= NUM_EVENTS) {
            break;
        }
        retval = PAPI_add_named_event(eventset, events[i]);
        if(retval != PAPI_OK) {
            fprintf(stderr, "error adding event %s, error %s\n", events[i],
            PAPI_strerror(retval));
            return -1;
        }
        i++;
        r = PAPI_enum_cmp_event(&eventcode, PAPI_ENUM_FIRST, rapl_cid);
    }
    return 0;
}
int create_eventsets(int *eventset) {
    int retval = PAPI_create_eventset(eventset);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }

    return 0;
}

void do_cleanup(int *eset_ptr) {
    PAPI_cleanup_eventset(*eset_ptr);
    PAPI_destroy_eventset(eset_ptr);
}

int find_rapl(int debug) {
    const PAPI_component_info_t *cmpinfo = NULL;
    int numcmp = PAPI_num_components();
    if(debug) {
        printf("num components: %d\n", numcmp);
    }
    int rapl_cid, cid;
    rapl_cid = -1;
    for(cid = 0; cid < numcmp; cid++) {
        if((cmpinfo = PAPI_get_component_info(cid)) == NULL) {
            fprintf(stderr, "error getting componenet info\n");
        }

        if(strstr(cmpinfo->name, "rapl")) {
            rapl_cid = cid;
            if(cmpinfo->disabled) {
                fprintf(stderr, "rapl disabled\n");
                return -1;
            }
            if(debug) {
                fprintf(stderr, "found rapl at %d\n", rapl_cid);
            }
        } else {
            if(debug) {
                fprintf(stderr, "did not find rapl at %d, found %s\n", cid,
                cmpinfo->name);
            }

        }
    }

    if(rapl_cid ==-1) {
        fprintf(stderr, "did not find rapl" );
        return -1;
    }

    return rapl_cid;
}

int do_measure(int eventset, float* r1) {
    int retval;
    long long count[NUM_EVENTS]; 

    PAPI_reset(eventset);
    retval = PAPI_start(eventset);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
        return -1;
    } 

    sleep(1);
    
    retval=PAPI_stop(eventset, count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return -1;
    }
    else {

        for(int j = 0; j < NUM_EVENTS; j++) {
            printf("%s: %lld\n", events[j], count[j]);
        }


    }

    printf("---------------------------------------\n");
    *r1 = count[0];
    return 0;

}

int main (int argc, char* argv[]) {
    
    int debug = 0;
    int retval;
    int eventset = PAPI_NULL;
    float measurements[RUNS];

    if(argc > 1) {
        if(strcmp(argv[1],"-d") == 0) {
            debug = 1;
        }
    }

    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if(retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "papi didnt init %s\n", PAPI_strerror(retval));
        return -1;
    }

    retval = PAPI_create_eventset(&eventset);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }

    int rapl_cid = find_rapl(debug);

    retval = add_events(eventset, rapl_cid);
    if(retval != 0) {
        fprintf(stderr, "events weren't added\n");
        return -1;
    }

    printf("---------------------------------------\n");
    for(int i = 0; i < RUNS; i++) {
        do_measure(eventset, (measurements + i));
    }

    print_avg(measurements);


    do_cleanup(&eventset);

    return 0;

}
