 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4*1024

struct ll {
    long long size;
    int val; 
    struct ll* next; 
};

int populate_list(struct ll *head, long long size);
int free_list(struct ll* head);

struct page_size_ll {
    long long size;
    int arr[PAGE_SIZE]; 
    struct page_size_ll* next; 
};

int populate_ps_list(struct page_size_ll *head, long long size);
int free_ps_list(struct page_size_ll* head);
void print_avg(double measurements[], int runs);
