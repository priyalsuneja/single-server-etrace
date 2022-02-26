#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double l1_icache0 = -2.40296529e-11;
    double ipc0 = 4.43486640e+01;
    double l20 = 1.87260721e-07;
    double data_tlb0 = 3.71603522e-12;
    double l1_dcache0 = -6.61550837e-12;
    double ins_tlb0 = 2.19821809e-05;

    char input[20];


    while(1) {
        fgets(input, 20, stdin);
        
        if(input[0] == 'a') {
            break;
        }

        double l1_icache = atof(input);

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

        printf("Answer: %f, Output: %f\n", ans, output);
        printf("\tError: %f, error %% : %f%%\n", error, (error/ans)*100);

    }
    

}
