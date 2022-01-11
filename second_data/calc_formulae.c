#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double l1_icache0 = 9.064e-6;
//     double cycles0 = -8.627e-10;
    double cycles0 = 0;
    double l20 = 2.467e-7;
    double tlb0 = 5.216e-8;
    double l1_dcache0 = 1.131e-7;
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

        double l2 = atof(input);

        fgets(input, 20, stdin);

        double tlb = atof(input);

        fgets(input, 20, stdin);

        double l1_dcache = atof(input);

        fgets(input, 20, stdin);

        double ans = atof(input);

        double output = 0;

        output += l1_icache0*l1_icache;
        output += cycles0*cycles;
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
