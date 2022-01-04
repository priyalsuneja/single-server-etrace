#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    double l10 = 2.096e-7, l20 = 3.556e-7, tlb0 = 7.659e-7, i0 = 2.16e-8;
    char input[20];

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

    output*= 0.1;

    printf("answer: %f\n", output);
    

}
