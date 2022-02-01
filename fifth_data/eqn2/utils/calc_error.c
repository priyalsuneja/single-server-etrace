// currently only supports graphing relative error, have to add support for
// other stuff
#include "calc_error.h"

int print_graphing_info(char* graph_fname, char name[20], double
                                         inputs[INPUT_SIZE], double rel_error) {

    FILE* fptr = fopen(graph_fname, "a+");
    if(!fptr) {
        return -1;
    }

    fprintf(fptr,"%s,%.0f,%.0f,%.2f,%.0f,%.0f,%.0f,%.0f,%.3f\n",name, inputs[L1_ICACHE],
        inputs[CYCLES], inputs[IPC], inputs[L2], inputs[TLB_DATA],
        inputs[L1_DCACHE], inputs[TLB_INS], rel_error);

    return 0;

}

double calc_error (double weights[INPUT_SIZE], double inputs[INPUT_SIZE]) {


    double output = 0;

    output += weights[L1_ICACHE]*inputs[L1_ICACHE];
    output += weights[CYCLES]*inputs[CYCLES];
    output += weights[IPC]*inputs[IPC];
    output += weights[L2]*inputs[L2];
    output += weights[TLB_DATA]*inputs[TLB_DATA];
    output += weights[L1_DCACHE]*inputs[L1_DCACHE];
    output += weights[TLB_INS]*inputs[TLB_INS];

    return output - inputs[ANS];
}

void print_stats(double inputs[INPUT_SIZE]) {

    double total_inputs = 0;
    for(int i = 0; i < INPUT_SIZE - 1; i++) {
        total_inputs += inputs[i];
    }
    printf("\t%% L1_ICACHE: %.4f\n", inputs[L1_ICACHE]/total_inputs);
    printf("\t%% CYCLES: %.4f\n", inputs[CYCLES]/total_inputs);
    printf("\t%% IPC: %.4f\n", inputs[IPC]/total_inputs);
    printf("\t%% L2: %.4f\n", inputs[L2]/total_inputs);
    printf("\t%% TLB_DATA: %.4f\n", inputs[TLB_DATA]/total_inputs);
    printf("\t%% L1_DCACHE: %.4f\n", inputs[L1_DCACHE]/total_inputs);
    printf("\t%% TLB_INS: %.4f\n", inputs[TLB_INS]/total_inputs);

    printf("\n");

}

int get_input(char name[20], double inputs[INPUT_SIZE]) {
    char input[20];
    fgets(input, 20, stdin);
    
    if(input[0] == ';') {
        return 0;
    }

    strncpy(name, input, 20);

    name[strlen(input)-1]='\0';

    fgets(input, 20, stdin);

    inputs[L1_ICACHE] = atof(input);

    fgets(input, 20, stdin);

    inputs[CYCLES] = atof(input);

    fgets(input, 20, stdin);

    inputs[IPC] = atof(input);

    fgets(input, 20, stdin);

    inputs[L2] = atof(input);
    
    fgets(input, 20, stdin);


    inputs[TLB_DATA] = atof(input);

    fgets(input, 20, stdin);

    inputs[L1_DCACHE] = atof(input);

    fgets(input, 20, stdin);

    inputs[TLB_INS] = atof(input);

    fgets(input, 20, stdin);

    inputs[ANS] = atof(input);

    return 1;

}

int calc_error_main (double weights[INPUT_SIZE], char* flags, char* graph_fname) {

    double inputs[INPUT_SIZE];

    char name[20];
    double error_sum = 0;
    int num_data  = 0;

    while(1) {

        if(!get_input(name, inputs)) {
            break;
        }

        double error = calc_error(weights, inputs);

        error_sum += abs(error);
        num_data++;

        printf("******* File: %s *********\n \tAnswer: %.3f, Output: %.3f\n",
        name, inputs[ANS], inputs[ANS]+error);
        printf("\tError: %.3f, error %% : %.3f%%\n\n", error, (abs(error)/inputs[ANS])*100);

        if(strstr(flags, "s")) {
            print_stats(inputs);
        }
        if(strstr(flags, "g")) {
            print_graphing_info(graph_fname, name, inputs, abs(error)/inputs[ANS]);
        }
    }

    if(strstr(flags, "m")) {
        printf("Mean error: %f", error_sum/num_data);
    }

    return 0;

}

