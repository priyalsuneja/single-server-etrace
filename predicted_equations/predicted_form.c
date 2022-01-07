/**
 * weights when we use sssp, pr, tc, cc
 * double l10 = 6.229e-7, l20 = -5.37349e-7, tlb0 = -5.78604e-7, i0 = 2.7320e-9;
 * 
 * weights when we use ssp, pr, tc, pr_spmv
 * double l10 = 4.77114e-9, l20 = -1.23844e-7, tlb0 = 3.20677e-7, i0 = 2.64018e-9;
 *
 * weights with l1_msr, l2_msr, ins_msr, tlb_msr
 * double l10 = -6.2314e-7, l20 = 5.46754e-7, tlb0 = 1.13077e-6, i0 = 4.00627e-8;
 *
 * weights with bfs, l2_msr, tlb_msr, tc
 * double l10 = -6.3738e-8, l20 = 4.34886e-7, tlb0 = 7.68219e-7, i0 = -2.03196e-9;
 *
 * from python:
 * double l10 = 3.425e-8, l20 = 3.310e-7, tlb0 = 4.205e-8, i0 = -9.058e-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[20];
    double l10 = 3.425e-8, l20 = 3.310e-7, tlb0 = 4.205e-8, i0 = -9.058e-10;

    while(1) {
        printf("Enter num of l1 cache misses: ");
        fgets(input, 20, stdin);

        double l1 = atof(input);

    //     printf("String value: %s, double value: %f\n", input, l1);
        printf("Enter num of l2 cache misses: ");
        fgets(input, 20, stdin);

        double l2 = atof(input);

    //     printf("String value: %s, double value: %f\n", input, l2);
        printf("Enter num of tlb misses: ");
        fgets(input, 20, stdin);

        double tlb = atof(input);

        printf("Enter num of instructions: ");
        fgets(input, 20, stdin);

        double ins = atof(input);

        double output = 0;

        output += l10*l1;
        output += l20*l2;
        output += tlb0*tlb;
        output += i0*ins;

        printf("answer: %f\n", output);

    }

    

}
