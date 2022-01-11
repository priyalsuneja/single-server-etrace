#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double l1_icache0 = 2.445e-10;
    double ipc0 = 5.591e+1;
    double l20 = 1.898e-7;
    double tlb0 = 0;
    double l1_dcache0 = 0;
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

        double tlb = atof(input);

        fgets(input, 20, stdin);

        double l1_dcache = atof(input);

        fgets(input, 20, stdin);

        double ans = atof(input);

        double output = 0;

        output += l1_icache0*l1_icache;
        output += ipc0*ipc;
        output += l20*l2;
        output += tlb0*tlb;
        output += l1_dcache0*l1_dcache;

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
