// currently only supports graphing relative error, have to add support for
// other stuff
#include "utils.h"

int print_graphing_info(char* graph_fname, char name[20], double* inputs, double rel_error,
                                         double output) {

    FILE* fptr = fopen(graph_fname, "a+");
    if(!fptr) {
        return -1;
    }

    // TODO: turn this into a loop

    fprintf(fptr,"%s,%.0f,%.0f,%.2f,%.0f,%.0f,%.0f,%.0f,%.0f,%.3f,%.3f,%.3f\n",name, inputs[L1_ICACHE],
        inputs[CYCLES], inputs[IPC], inputs[L2], inputs[TLB_DATA],
        inputs[L1_DCACHE], inputs[TLB_INS], inputs[L3], rel_error, inputs[ANS], output);

    fclose(fptr);

    return 0;

}

double calc_error (char name[20], double* weights, double* inputs, char* print, 
                                                        FILE *fptr, int input_size ) {


    double output = 0;
    double ind_out[input_size];
    int i; 

     for(i = 0; i <input_size-1; i++) {
         ind_out[i] = weights[i]*inputs[i];
     }

    for(i = 0; i < input_size; i++) {
        output+= ind_out[i];
    }

    double error = output - inputs[input_size-1];
    
    if(print) {             // TODO: fix this 
        fprintf(fptr, "%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t",name,inputs[input_size-1], output, error, (fabs(error)*100/inputs[input_size-1]));
        for(i = 0; i < input_size; i++) {
            fprintf(fptr,"%.2f\t",ind_out[i]*100/output);

        }
        fprintf(fptr, "\n");
    }
//     printf("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
//     name,  inputs[ANS], output, error, (fabs(error) * 100/inputs[ANS]),
//     l1i, cycles, ipc, l2, tlbd, l1d, tlbi);

    return error;
}

void print_stats(double* inputs) {

//     double total_inputs = 0;
//     for(int i = 0; i < INPUT_SIZE - 1; i++) {
//         total_inputs += inputs[i];
//     }

    printf("\t Normalized by instructions: \n");

    printf("\t%%L1_icache: %.4f\n", inputs[L1_ICACHE]*100/inputs[INS]);
    printf("\t%% L2: %.4f\n", inputs[L2]*100/inputs[INS]);
    printf("\t%% TLB_data: %.4f\n", inputs[TLB_DATA]*100/inputs[INS]);
    printf("\t%% L1_dcache: %.4f\n", inputs[L1_DCACHE]*100/inputs[INS]);
    printf("\t%% TLB_ins: %.4f\n", inputs[TLB_INS]*100/inputs[INS]);
    printf("\t%% L3: %.4f\n", inputs[L3]*100/inputs[INS]);

    printf("\n");

}

int get_input(char name[20], double* inputs, int input_size) {   

    char input[20];    

    fgets(input, 20, stdin);
    
    if(input[0] == ';') {
        return 0;
    }

    strncpy(name, input, 20);

    name[strlen(input)-1]='\0';

    for( int i = 0; i < input_size; i++) {
        fgets(input, 20, stdin);
        inputs[i] = atof(input);
    }
//     fgets(input, 20, stdin);
// 
//     inputs[L1_CACHE] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[CYCLES] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[IPC] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[L2] = atof(input);
//     
//     fgets(input, 20, stdin);
// 
//     inputs[TLB_DATA] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[L1_DCACHE] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[TLB_INS] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[L3] = atof(input);
// 
//     fgets(input, 20, stdin);
// 
//     inputs[ANS] = atof(input);

    return 1;
}

int calc_error_main (double* weights, char* flags, char* graph_fname, 
                                                        int input_size) {

    double inputs[input_size];

    double total_inputs = 0;
    char name[20];
    double error_sum = 0;
    int num_data  = 0;

    FILE* fptr = fopen(TABLE_OUT_FILE, "w+");

    if(strstr(flags, "t")) {
        fprintf(fptr,
          "----------------------------------------------------------------------------------------\n"
          );
        fprintf(fptr, 
          "File\t\tAnswer\tOutput\tError\tError%%\tL1_I%%\tStalls%%\tIns%%\tL2%%\tTLB_D%%\tL1_D%%\tTLB_I%%i\tL3%%\n"
          );
          fprintf(fptr, 
          "----------------------------------------------------------------------------------------\n"
          );
    }
    while(1) {

        total_inputs = 0;

        if(!get_input(name, inputs, input_size)) {
            break;
        }

        double error = calc_error(name, weights, inputs, strstr(flags, "t"),
        fptr, input_size);

        error_sum += (fabs(error)*100/inputs[ANS]) ;
        num_data++;

        for(int i = 0; i < input_size - 1; i++) {
            total_inputs += inputs[i];
        }
        total_inputs -= inputs[CYCLES];

        printf("******* File: %s *********\n \tAnswer: %.3f, Output: %.3f\n",
        name, inputs[ANS], inputs[ANS]+error);
        printf("\tError: %.3f, error %% : %.3f%%\n\n", error, ((fabs(error) *
        100)/inputs[ANS]));

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
        if(strstr(flags, "t")) {
            fprintf(fptr, "Mean error: %.3f\n", error_sum/num_data);
        }
    }


    fclose(fptr);

    return 0;

}

