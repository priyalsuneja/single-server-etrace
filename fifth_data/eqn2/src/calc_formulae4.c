#include "../utils/calc_error.h"
int main() {
    double l1_icache0 = 2.40490160e-07;
    double cycles0  = -5.51959774e-10;
    double ipc0 = 1.27338249e-01;
    double l20 = 2.62021396e-07;
    double data_tlb0 = -1.90155521e-08;
    double l1_dcache0 = -5.98634829e-09;
    double ins_tlb0 = 1.54041924e-04;
    return calc_error(l1_icache0, cycles0, ipc0, l20, data_tlb0, l1_dcache0, ins_tlb0);
}
