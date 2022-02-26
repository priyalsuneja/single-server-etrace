#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define L1_ICACHE 0
#define CYCLES 1
#define IPC 2
#define INS 2
#define L2 3
#define TLB_DATA 4
#define L1_DCACHE 5
#define TLB_INS 6
#define L3 7
#define ANS 8

#define TABLE_OUT_FILE "output_table"


int calc_error_main(double* weights, char* flags, char* graph_fname, int input_size);

double calc_error(char name[20], double* weights, 
                    double* inputs, char* print, FILE* fptr, int input_size);

int get_input(char name[20], double* input, int input_size);

void print_stats(double* inputs);

int print_graphing_info(char* graph_fname, char name[20], 
                                    double* inputs, double rel_error, double output);
