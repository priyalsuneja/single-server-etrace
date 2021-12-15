#include "msr.h"

int main() {

    struct page_size_ll *head = malloc(sizeof(struct page_size_ll));

    int retval = populate_ps_list(head, TLB_LL_SIZE);

    return retval;
}
