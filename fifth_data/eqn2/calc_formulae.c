#include "calc_error.h"
int main() {
    double l1_icache0 = -1.95201937e-08;
    double cycles0  = -1.10324767e-09;
    double ipc0 = 1.34071534e-01;
    double l20 = 3.04372269e-07;
    double data_tlb0 = 8.10513107e-08;
    double l1_dcache0 = 1.19991876e-08;
    double ins_tlb0 = 1.62549907e-04;


    return calc_error(l1_icache0, cycles0, ipc0, l20, data_tlb0, l1_dcache0, ins_tlb0);
}
