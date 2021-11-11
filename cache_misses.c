#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <papi.h>

#define NUM_EVENTS 6

char events[NUM_EVENTS][BUFSIZ]={
    "PACKAGE_ENERGY:PACKAGE0",
    "PACKAGE_ENERGY:PACKAGE1",
    "DRAM_ENERGY:PACKAGE0",
    "DRAM_ENERGY:PACKAGE1",
    "PP0_ENERGY:PACKAGE0",
    "PP0_ENERGY:PACKAGE1"
};

int main (int main, char **argv) {

    const PAPI_component_info_t *cmpinfo = NULL;
    int retval, eventcode = 0;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if(retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "papi didnt init %s\n", PAPI_strerror(retval));
        return 0;
    }

//     for(int i=0; i < NUM_EVENTS; i++) {
//         retval = PAPI_event_name_to_code(events[i],&eventcode);
//         if(retval != PAPI_OK) {
//             fprintf(stderr, "error adding event %s, error %s\n", events[i],
//             PAPI_strerror(retval));
//         } else {
//             printf("eventcode for %d is %d\n", i, eventcode);
//         }
//     }


    //TODO: add code to check if rapl even supported, rn we know vicuna has it

    int numcmp = PAPI_num_components();
    int rapl_cid, cid;
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
    

    // setting events to measure
/*    int eventset=PAPI_NULL;

    retval = PAPI_create_eventset(&eventset);

    if(retval != PAPI_OK) {
        fprintf(stderr, "papi create eventset %s\n", PAPI_strerror(retval));
        return 0;
    }

    for(int i=0; i < NUM_EVENTS; i++) {
        retval = PAPI_add_named_event(eventset, events[i]);
        if(retval != PAPI_OK) {
            fprintf(stderr, "error adding event %s, error %s\n", events[i],
            PAPI_strerror(retval));
        }
    }
    
    long long count[NUM_EVENTS]; 

    PAPI_reset(eventset);
    retval = PAPI_start(eventset);
    if(retval != PAPI_OK) { 
        fprintf(stderr, "error starting CUDA: %s\n", PAPI_strerror(retval));
    } 

    printf("hello world\n");
    printf("bye bye\n");
    
    retval=PAPI_stop(eventset, count);
    if(retval!=PAPI_OK) {
        fprintf(stderr, "papi error stopping %s\n", PAPI_strerror(retval));
        return 0;
        
    }
    else {
//         printf("Measured %lld ins, %lld cycles\n", count[0], count[1]);
        printf("package energy p0 %lld, package energy p1 %lld\n", count[0],
        count[1]);
    }

    PAPI_cleanup_eventset(eventset);
    PAPI_destroy_eventset(&eventset);*/


    return 0;

}
