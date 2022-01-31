# this file is written assuming the input file has order:
# name, l1_icache, cycles, ipc, l2, tlb_data, l1_dcache, tlb_ins, error

import matplotlib

matplotlib.use("Agg") # imp to use over ssh

import matplotlib.pyplot as plt
import numpy as np
import sys

def graph_relative_error(name, errors, field_data):
    plt.xlabel(name)
    plt.ylabel("Relative Error")
    plt.xticks(rotation=90)

#     plt.plot(field_data, errors, linestyle="None")
    plt.scatter(field_data,errors)
    plt.savefig(name + ".png", bbox_inches='tight')


def main():
    names=[]
    l1_icache=[]
    cycles=[]
    ipc=[]
    l2=[]
    tlb_data=[]
    l1_dcache=[]
    tlb_ins=[]
    error=[]

    if(len(sys.argv) == 1):
        sys.exit("No input file mentioned!")

    for i in range(1, len(sys.argv)):
        with open(sys.argv[i]) as f:
            for line in f:
                str_list = line.split(",")

                names.append(str_list[0])
                l1_icache.append(str_list[1])
                cycles.append(str_list[2])
                ipc.append(str_list[3])
                l2.append(str_list[4])
                tlb_data.append(str_list[5])
                l1_dcache.append(str_list[6])
                tlb_ins.append(str_list[7])
                error.append(str_list[8])

    graph_relative_error("l1_icache",error, l1_icache)

main()

    



