#include "../utils/calc_error.h"
int main(int argc, char** argv) {
    double weights[INPUT_SIZE];
    weights[L1_ICACHE] = -1.07426387e-07;
    weights[CYCLES]  = -1.19791805e-09;
    weights[IPC] = 1.36041724e-01;
    weights[L2] = 3.42851678e-07;
    weights[TLB_DATA] = -4.64261793e-08;
    weights[L1_DCACHE] = -4.97131448e-09;
    weights[TLB_INS] = 1.80499648e-04;

    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");
}
