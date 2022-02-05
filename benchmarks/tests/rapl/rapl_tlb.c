 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_l2 rapl_l2.c -lpapi
 * to run: sudo ./rapl_l2
 * TODO: might have to remove energy spent on l1 cache miss
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"


#include <papi.h>
// #include "papi_test.h"

#define NUM_EVENTS 3
#define RUNS 1
#define ITERATIONS_PER_RUN 1000
#define PAGE_SIZE 4*1024    // 4kB
#define TLB_ENTRIES 64
#define TLB_ASSOC 4


char rapl_events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE0",
};
// char perf_event[BUFSIZ]="PAPI_TLB_DM";

void print_avg(float measurements[]) {

    float sum = 0;      // overflow possibility?
    for(int i = 0; i < RUNS; i++) {
        sum+=measurements[i];
    }

    float avg = sum/RUNS;

    fprintf(stdout, "Average over %d runs: %f\n", RUNS, avg);
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
    return 0;
}
int create_eventsets(int *eventset, int *eventset2) {
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

int do_measure(int eventset, int eventset2, float* r1) {
    int retval;
    long long count[NUM_EVENTS]; 

    struct page_size_ll *head = malloc(sizeof(struct page_size_ll));
    struct page_size_ll *curr = head;
    long long ll_size = TLB_ASSOC*TLB_ENTRIES*8;

    retval = populate_ps_list(head, ll_size);

    PAPI_reset(eventset);
    retval = PAPI_start(eventset);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting cuda: %s\n", PAPI_strerror(retval));
        return -1;
    } 

    for( int i = 0; i < ITERATIONS_PER_RUN; i++ ) {

        while(curr != NULL) {
            curr = curr->next;
        }

        curr = head;
    }
    
    retval=PAPI_stop(eventset, count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return -1;
    }
    else {

        for(int j = 0; j < NUM_EVENTS; j++) {
            printf("%s: %lld\n", rapl_events[j], count[j]);
        }


    }

    printf("total energy consumed for tlb misses: %lld\n", count[0]);
    printf("---------------------------------------\n");
    *r1 = count[0];
    free_ps_list(head);
    return 0;
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
//     do_cleanup(&eventset2);

    return 0;

}
