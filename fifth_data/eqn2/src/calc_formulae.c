#include "../utils/calc_error.h"
int main(int argc, char** argv) {
    double weights[INPUT_SIZE];
    weights[L1_ICACHE] = -1.95201937e-08;
    weights[CYCLES]  = -1.10324767e-09;
    weights[IPC] = 1.34071534e-01;
    weights[L2] = 3.04372269e-07;
    weights[TLB_DATA] = 8.10513107e-08;
    weights[L1_DCACHE] = 1.19991876e-08;
    weights[TLB_INS] = 1.62549907e-04;

    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");

    
}
