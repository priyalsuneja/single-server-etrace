/* TODO
 * look at rapl_basic and see how they normalize to W and J of energy 
 * also add actual tests instead of just function call!
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <papi.h>
// #include "papi_test.h"

#define NUM_EVENTS 6
#define L1_SIZE 1280*1024

char events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "PACKAGE_ENERGY:PACKAGE1",
    "DRAM_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE1",
    "PP0_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE1"
};

int main () {

    int *arr = malloc(2*L1_SIZE*sizeof(int));

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
            fprintf(stdout, "found rapl at %d\n", rapl_cid);
            break;
        }
    }

    if(cid == numcmp) {
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

//     printf("hello world\n");
//     printf("bye bye\n");
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    arr[0] = 1;
    arr[L1_SIZE] = 2; 
    
    retval=PAPI_stop(eventset, count);
    retval=PAPI_stop(eventset2, &count2);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return 0;
        
    }
    else {
        printf("package energy p0 %lld, package energy p1 %lld cache misses %lld \n", 
        count[0], count[1], count2);
//         printf("package energy p0 %lld, package energy p1 %lld\n", 
//         count[0], count[1]);
    }
    PAPI_cleanup_eventset(eventset);
    PAPI_destroy_eventset(&eventset);
    PAPI_cleanup_eventset(eventset2);
    PAPI_destroy_eventset(&eventset2);
    free(arr);

    return 0;

}
