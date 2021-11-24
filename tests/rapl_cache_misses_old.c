 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to compile: gcc -O0 -Wall -o rapl_cache_misses rapl_cache_misses.c -lpapi
 * to run: sudo ./rapl_cache_misses
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <papi.h>

#define NUM_EVENTS 6
#define RUNS 100000
#define L1_SIZE 128*1024

char events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "PACKAGE_ENERGY:PACKAGE1",
    "DRAM_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE1",
    "PP0_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE1"
};

int main (int argc, char* argv[]) {

    
    int debug = 0;

    if(argc > 1) {
        if(strcmp(argv[1],"-d") == 0) {
            debug = 1;
        }
    }

    int *arr = malloc(10*L1_SIZE*sizeof(int));

    const PAPI_component_info_t *cmpinfo = NULL;
    int retval, eventcode = 0;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if(retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "papi didnt init %s\n", PAPI_strerror(retval));
        return 0;
    }
    int eventset = PAPI_NULL;
    int eventset2 = PAPI_NULL;

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
                fprintf(stdout, "found rapl at %d\n", rapl_cid);
            }
        } else {
            if(debug) {
                fprintf(stdout, "did not find rapl at %d, found %s\n", cid,
                cmpinfo->name);
            }

        }
    }

    if(rapl_cid == -1) {
        fprintf(stderr, "did not find rapl" );
        return -1;
    }

    retval = PAPI_create_eventset(&eventset);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }
    retval = PAPI_create_eventset(&eventset2);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }

    eventcode = PAPI_NATIVE_MASK; 

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
        }
        i++;
        r = PAPI_enum_cmp_event(&eventcode, PAPI_ENUM_FIRST, rapl_cid);
    }
    retval = PAPI_add_named_event(eventset2, "PAPI_L1_DCM");
    if(retval != PAPI_OK) {
        fprintf(stderr, "error adding cache miss count, error %s\n",
        PAPI_strerror(retval));
    }
    long long count[NUM_EVENTS]; 
    long long count2; 

    PAPI_reset(eventset);
    PAPI_reset(eventset2);
    retval = PAPI_start(eventset);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
    } 
    retval = PAPI_start(eventset2);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
    } 

    for( int i = 0; i < RUNS; i++ ) {

        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
        arr[0] = 1;
        arr[L1_SIZE] = 2; 
        arr[9*L1_SIZE] = 4;
        arr[2*L1_SIZE] = 3;
        arr[7*L1_SIZE] = 2; 
        arr[3*L1_SIZE] = 4;
        arr[6*L1_SIZE] = 4;
        arr[4*L1_SIZE] = 2; 
        arr[5*L1_SIZE] = 3;
        arr[8*L1_SIZE] = 3;
    }
    
    retval=PAPI_stop(eventset, count);
    retval=PAPI_stop(eventset2, &count2);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return 0;
        
    }
    else {
        for(int j = 0; j < NUM_EVENTS; j++) {
            printf("%s: %lld\n", events[j], count[j]);
        }

        printf("Num cache misses: %lld\n", count2);

    }
    float avg_energy = ((float) count[0]/count2);
    float avg_energy2 = ((float) count[1]/count2);

    printf("Avg energy consumed per cache miss:\n");
    printf("\tpackage 0: %f\n", avg_energy);
    printf("\tpackage 1: %f\n", avg_energy2);
    PAPI_cleanup_eventset(eventset);
    PAPI_destroy_eventset(&eventset);
    PAPI_cleanup_eventset(eventset2);
    PAPI_destroy_eventset(&eventset2);
    free(arr);

    return 0;

}
