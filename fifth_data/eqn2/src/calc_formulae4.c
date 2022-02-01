#include "../utils/calc_error.h"
int main(int argc, char** argv) {
    double weights[INPUT_SIZE];
    weights[L1_ICACHE] = 2.40490160e-07;
    weights[CYCLES]  = -5.51959774e-10;
    weights[IPC] = 1.27338249e-01;
    weights[L2] = 2.62021396e-07;
    weights[TLB_DATA] = -1.90155521e-08;
    weights[L1_DCACHE] = -5.98634829e-09;
    weights[TLB_INS] = 1.54041924e-04;

    if(argc == 2) {
        if(argv[1][0] == '-') {
            return calc_error_main(weights, argv[1], "graph_out_one");
        }
    }

    return calc_error_main(weights, "", "graph_out_one");
}
