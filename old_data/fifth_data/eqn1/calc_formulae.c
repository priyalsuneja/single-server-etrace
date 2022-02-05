#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double l1_icache0 = 4.81060400e-08;
    double cycles0  = -8.17063773e-10;
    double ipc0 = 1.13736536e+02;
    double l20 = 2.74446865e-07;
    double data_tlb0 = -2.31093052e-07;
    double l1_dcache0 = -5.66985353e-08;
    double ins_tlb0 = 4.96718823e-05;

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

        printf("Answer: %f, Output: %f\n", ans, output);
        printf("\tError: %f, error %% : %f%%\n", error, (error/ans)*100);

    }
    

}
