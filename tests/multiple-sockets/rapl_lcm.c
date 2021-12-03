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

int main () {

    int *arr = malloc(2*L1_SIZE*sizeof(int));

    int retval;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if(retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "papi didnt init %s\n", PAPI_strerror(retval));
        return 0;
    }
    int eventset = PAPI_NULL;

    retval = PAPI_create_eventset(&eventset);
    if(retval != PAPI_OK) {
        fprintf(stderr, "couldn't create eventset %s\n", PAPI_strerror(retval) );
        return -1;
    }

    retval = PAPI_add_named_event(eventset, "PAPI_L1_DCM");
    if(retval != PAPI_OK) {
        fprintf(stderr, "error adding cache miss count, error %s\n",
        PAPI_strerror(retval));
    }
    long long count;

    PAPI_reset(eventset);
    retval = PAPI_start(eventset);
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
    
    retval=PAPI_stop(eventset, &count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return 0;
        
    }
    else {
//         printf("package energy p0 %lld, package energy p1 %lld cache misses %lld \n", 
//         count[0], count[1], count[NUM_EVENTS]);
        printf("num cache misses: %lld\n", count);
    }
    PAPI_cleanup_eventset(eventset);
    PAPI_destroy_eventset(&eventset);
    free(arr);

    return 0;

}
