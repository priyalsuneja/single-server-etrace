#include "calc_error.h"
int main() {
    double l1_icache0 = -8.95735226e-09;
    double cycles0  = -8.02684763e-10;
    double ipc0 = 1.33355394e-01;
    double l20 = 2.99123032e-07;
    double data_tlb0 = -3.86319360e-08;
    double l1_dcache0 = -5.82881663e-09;
    double ins_tlb0 = 1.52839413e-04;

    return calc_error(l1_icache0, cycles0, ipc0, l20, data_tlb0, l1_dcache0, ins_tlb0);

}
