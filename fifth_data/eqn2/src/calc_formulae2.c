#include "../utils/calc_error.h"
int main(int argc, char** argv) {
    double weights[INPUT_SIZE];
    weights[L1_ICACHE] = -8.95735226e-09;
    weights[CYCLES]  = -8.02684763e-10;
    weights[IPC] = 1.33355394e-01;
    weights[L2] = 2.99123032e-07;
    weights[TLB_DATA] = -3.86319360e-08;
    weights[L1_DCACHE] = -5.82881663e-09;
    weights[TLB_INS] = 1.52839413e-04;

    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");

}
