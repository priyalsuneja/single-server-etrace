#include "msr.h"

int main() {

    struct ll *head = malloc(sizeof(struct ll));

    int retval = populate_list(head, L2_LL_SIZE);

    return retval;
}
