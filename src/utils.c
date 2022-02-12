// currently only supports graphing relative error, have to add support for
// other stuff
#include "utils.h"

int print_graphing_info(char* graph_fname, char name[20], double
                                         inputs[INPUT_SIZE], double rel_error,
                                         double output) {

    FILE* fptr = fopen(graph_fname, "a+");
    if(!fptr) {
        return -1;
    }

    fprintf(fptr,"%s,%.0f,%.0f,%.2f,%.0f,%.0f,%.0f,%.0f,%.3f,%.3f,%.3f\n",name, inputs[L1_ICACHE],
        inputs[CYCLES], inputs[IPC], inputs[L2], inputs[TLB_DATA],
        inputs[L1_DCACHE], inputs[TLB_INS], rel_error, inputs[ANS], output);

    return 0;

}

double calc_error (char name[20], double weights[INPUT_SIZE], double inputs[INPUT_SIZE]) {


    double output = 0;
    double l1i = 0;
    double cycles = 0;
    double ipc = 0;
    double l2 = 0;
    double tlbd = 0;
    double l1d = 0;
    double tlbi = 0;

    l1i = weights[L1_ICACHE]*inputs[L1_ICACHE];
    cycles = weights[CYCLES]*inputs[CYCLES];
    ipc = weights[IPC]*inputs[IPC];
    l2 = weights[L2]*inputs[L2];
    tlbd = weights[TLB_DATA]*inputs[TLB_DATA];
    l1d = weights[L1_DCACHE]*inputs[L1_DCACHE];
    tlbi = weights[TLB_INS]*inputs[TLB_INS];

    output = l1i + cycles + ipc + l2 + tlbd + l1d + tlbi;

    double error = output - inputs[ANS];

    printf("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
    name,  inputs[ANS], output, error, (fabs(error) * 100/inputs[ANS]),
    l1i*100/output, cycles*100/output, ipc*100/output, l2*100/output,
    tlbd*100/output, l1d*100/output, tlbi*100/output);
//     printf("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
//     name,  inputs[ANS], output, error, (fabs(error) * 100/inputs[ANS]),
//     l1i, cycles, ipc, l2, tlbd, l1d, tlbi);

    return error;
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

    double total_inputs = 0;
    char name[20];
    double error_sum = 0;
    int num_data  = 0;
    
    printf(
      "----------------------------------------------------------------------------------------\n"
      );
    printf(
      "File\t\tAnswer\tOutput\tError\tError%%\tL1_I%%\tCycles%%\tIns%%\tL2%%\tTLB_Data%%\tL1_D%%\tTLB_Ins%%\n"
      );
      printf(
      "----------------------------------------------------------------------------------------\n"
      );
    while(1) {

        total_inputs = 0;

        if(!get_input(name, inputs)) {
            break;
        }

        double error = calc_error(name, weights, inputs);

        error_sum += (fabs(error)*100/inputs[ANS]) ;
        num_data++;

        for(int i = 0; i < INPUT_SIZE - 1; i++) {
            total_inputs += inputs[i];
        }
        total_inputs -= inputs[CYCLES];
//         printf("%f\n",total_inputs);

//         printf("******* File: %s *********\n \tAnswer: %.3f, Output: %.3f\n",
//         name, inputs[ANS], inputs[ANS]+error);
//         printf("\tError: %.3f, error %% : %.3f%%\n\n", error, ((fabs(error) *
//         100)/inputs[ANS]));


        if(strstr(flags, "s")) {
            print_stats(inputs);
        }
        if(strstr(flags, "g")) {
            print_graphing_info(graph_fname, name, inputs, error/inputs[ANS],
            inputs[ANS] + error);
        }
    }

    if(strstr(flags, "m")) {
        printf("Mean error: %.3f\n", error_sum/num_data);
    }

    return 0;

}
