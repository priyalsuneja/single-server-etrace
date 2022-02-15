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
#define INPUT_SIZE 9

#define TABLE_OUT_FILE "output_table"


int calc_error_main(double weights[INPUT_SIZE], char* flags, char* graph_fname);

double calc_error(char name[20], double weights[INPUT_SIZE], 
                    double inputs[INPUT_SIZE], char* print, FILE* fptr);

int get_input(char name[20], double inputs[INPUT_SIZE]);

void print_stats(double inputs[INPUT_SIZE]);

int print_graphing_info(char* graph_fname, char name[20], double
                                         inputs[INPUT_SIZE], double rel_error,
                                         double output);
