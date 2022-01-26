#include "calc_error.h"
int main() {
    double l1_icache0 = -1.07426387e-07;
    double cycles0  = -1.19791805e-09;
    double ipc0 = 1.36041724e-01;
    double l20 = 3.42851678e-07;
    double data_tlb0 = -4.64261793e-08;
    double l1_dcache0 = -4.97131448e-09;
    double ins_tlb0 = 1.80499648e-04;

    return calc_error(l1_icache0, cycles0, ipc0, l20, data_tlb0, l1_dcache0, ins_tlb0);
}
