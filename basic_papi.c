#include <stdio.h>
#include <papi.h>
int main (int main, char **argv) {

    int retval; 
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if(retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "papi didnt init %s\n", PAPI_strerror(retval));
        return 0;
    }

    int eventset=PAPI_NULL;

    retval = PAPI_create_eventset(&eventset);

    if(retval != PAPI_OK) {
        fprintf(stderr, "papi create eventset %s\n", PAPI_strerror(retval));
        return 0;
    }

    retval = PAPI_add_event(eventset, PAPI_TOT_INS);
    if(retval != PAPI_OK) {
        fprintf(stderr, "papi add eventset %s\n", PAPI_strerror(retval));
        return 0;
    }
    retval = PAPI_add_event(eventset, PAPI_TOT_CYC);
    if(retval != PAPI_OK) {
        fprintf(stderr, "papi add eventset cyc %s\n", PAPI_strerror(retval));
        return 0;
    }
    
    long long count[2]; 

    PAPI_reset(eventset);
    retval = PAPI_start(eventset);
//     if(retval != PAPI_OK) { 
//         fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
//     } 
    printf("hello world\n");
//     int x = 55;
    printf("bye bye\n");
    
    retval=PAPI_stop(eventset, count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return 0;
        
    }
    else {
        printf("Measured %lld ins, %lld cycles\n", count[0], count[1]);
    }

    PAPI_cleanup_eventset(eventset);
    PAPI_destroy_eventset(&eventset);


    return 0;

}
