 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_ins rapl_ins.c -lpapi
 * to run: sudo ./rapl_ins
 * measures energy use based on number of instructions completed
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <papi.h>

#define NUM_EVENTS 3
#define RUNS 10
#define ITERATIONS_PER_RUN 10000000
#define L1_SIZE 128*1024

char rapl_events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE0",
};

char perf_event[BUFSIZ]="PAPI_TOT_INS";

void print_avg(float measurements[]) {

    float sum = 0;      // overflow possibility?
    int tot = 0;
    for(int i = 0; i < RUNS; i++) {
        sum+=measurements[i];
        if(measurements[i] != 0) {
            tot++;
        }
    }

    float avg = sum/tot;

    fprintf(stdout, "Average over %d runs: %f\n", tot, avg);
    printf("---------------------------------------\n");

}
int add_events(int eventset, int eventset2, int rapl_cid) {
    int eventcode = PAPI_NATIVE_MASK; 
    int retval;

    int r = PAPI_enum_cmp_event(&eventcode, PAPI_ENUM_FIRST, rapl_cid);
    int i = 0;

    while(r == PAPI_OK) {
        if( i >= NUM_EVENTS) {
            break;
        }
        retval = PAPI_add_named_event(eventset, rapl_events[i]);
        if(retval != PAPI_OK) {
            fprintf(stderr, "error adding event %s, error %s\n", rapl_events[i],
            PAPI_strerror(retval));
            return -1;
        }
        i++;
        r = PAPI_enum_cmp_event(&eventcode, PAPI_ENUM_FIRST, rapl_cid);
    }
    retval = PAPI_add_named_event(eventset2, perf_event);
    if(retval != PAPI_OK) {
        fprintf(stderr, "error adding instructions issued event, error %s\n",
        PAPI_strerror(retval));
        return -1;
    }
    return 0;
}
int create_eventsets(int *eventset, int *eventset2) {
    int retval = PAPI_create_eventset(eventset);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }
    retval = PAPI_create_eventset(eventset2);
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

int do_measure(int eventset, int eventset2, float* r1) {
    int retval;
    long long count[NUM_EVENTS]; 
    long long count2; 

    PAPI_reset(eventset);
    PAPI_reset(eventset2);
    retval = PAPI_start(eventset);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
        return -1;
    } 
    int n;
    retval = PAPI_start(eventset2);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
        return -1;
    } 

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {
        n+=i;      // all this should do is issue instructions
    }
    
    retval=PAPI_stop(eventset, count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return -1;
    }
    retval=PAPI_stop(eventset2, &count2);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return -1;
    }
    else {

        for(int j = 0; j < NUM_EVENTS; j++) {
            printf("%s: %lld\n", rapl_events[j], count[j]);
        }

        printf("Num instructions completed: %lld\n", count2);

    }

    float avg_energy = ((float) count[0]/count2);

    printf("Avg energy consumed per instruction completed: %f\n", avg_energy);
    printf("---------------------------------------\n");
    *r1 = avg_energy;
    return n;   // returning n so it doesn't optimize it away

}

int main (int argc, char* argv[]) {
    
    int debug = 0;
    int retval;
    int eventset = PAPI_NULL;
    int eventset2 = PAPI_NULL;
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

    retval = create_eventsets(&eventset, &eventset2);
    if(retval != 0) {
        fprintf(stderr, "eventset didn't init\n");
        return -1;
    }

    int rapl_cid = find_rapl(debug);

    retval = add_events(eventset, eventset2, rapl_cid);
    if(retval != 0) {
        fprintf(stderr, "events weren't added\n");
        return -1;
    }

    printf("---------------------------------------\n");
    for(int i = 0; i < RUNS; i++) {
        do_measure(eventset, eventset2, (measurements + i));
    }

    print_avg(measurements);


    do_cleanup(&eventset);
    do_cleanup(&eventset2);

    return 0;

}
