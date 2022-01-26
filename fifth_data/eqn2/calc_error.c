#include "calc_error.h"
int calc_error(float l1_icache0, float cycles0, float ipc0, float l20, 
                        float data_tlb0, float l1_dcache0, float ins_tlb0) {

    double error_sum = 0;
    int num_data  = 0;

    char input[20];


    while(1) {
        fgets(input, 20, stdin);
        
        if(input[0] == 'a') {
            break;
        }

        double l1_icache = atof(input);

        fgets(input, 20, stdin);

        double cycles = atof(input);

        fgets(input, 20, stdin);

        double ipc = atof(input);

        fgets(input, 20, stdin);

        double l2 = atof(input);

        fgets(input, 20, stdin);

        double data_tlb = atof(input);

        fgets(input, 20, stdin);

        double l1_dcache = atof(input);

        fgets(input, 20, stdin);

        double ins_tlb = atof(input);

        fgets(input, 20, stdin);

        double ans = atof(input);

        double output = 0;

        output += l1_icache0*l1_icache;
        output += cycles0*cycles;
        output += ipc0*ipc;
        output += l20*l2;
        output += data_tlb0*data_tlb;
        output += l1_dcache0*l1_dcache;
        output += ins_tlb0*ins_tlb;

        double error;
        if(output > ans) {
            error = output - ans;
        } else {
            error = ans - output;
        }

        error_sum += error;
        num_data++;

        printf("Answer: %.3f, Output: %.3f\n", ans, output);
        printf("\tError: %.3f, error %% : %.3f%%\n", error, (error/ans)*100);

    }

    printf("Mean error: %.3f \n", (error_sum/num_data));


    return 0;

}
