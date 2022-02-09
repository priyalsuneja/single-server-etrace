# this file is written assuming the input file has order:
# name, l1_icache, cycles, ipc, l2, tlb_data, l1_dcache, tlb_ins, error

import matplotlib

matplotlib.use("Agg") # imp to use over ssh

import matplotlib.pyplot as plt
import numpy as np
import sys


def graph_ans_output(names, ans, outputs):
    fig, ax = plt.subplots(nrows=1, ncols=1)
    ax.set_xlabel("Output")
    ax.set_ylabel("Answer")

    lists = list(zip(ans,outputs))
    lists.sort()
    new_x, new_y = list(zip(*lists))

#     print(new_x)
#     print(new_y)
    count = 0
    ax.scatter(new_x, new_y, color="none", edgecolor="red")
    for i, j in zip(new_x, new_y): 
        if count % 2 == 0:
#             ax.annotate("{0:.2f}".format((i/normalize_by)), (i,j), ha="left",
#             fontsize=10)
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        else:
#             ax.annotate("{0:.2f}".format((i/normalize_by)), (i,j), ha="right",
#             fontsize=10)
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        count+=1
#     ax.set_xscale("log")
    plt.xticks(rotation=90)
    plt.savefig("ansvoutputs.png", bbox_inches='tight')
    

# def graph_relative_error(axs, name, errors, field_data, row, col, normalize_by):
def graph_relative_error(name, errors, field_data, row, col, normalize_by, names):
#     ax = axs[row,col]
    fig, ax = plt.subplots(nrows=1, ncols=1)
    ax.set_xlabel(name)
    ax.set_ylabel("Relative Error")

    lists = list(zip(field_data,errors))
    lists.sort()
    new_x, new_y = list(zip(*lists))

#     print(new_x)
#     print(new_y)
    count = 0
    ax.scatter(new_x, new_y, color="none", edgecolor="red")
    for i, j in zip(new_x, new_y): 
        if count % 2 == 0:
#             ax.annotate("{0:.2f}".format((i/normalize_by)), (i,j), ha="left",
#             fontsize=10)
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        else:
#             ax.annotate("{0:.2f}".format((i/normalize_by)), (i,j), ha="right",
#             fontsize=10)
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        count+=1
#     ax.set_xscale("log")
    plt.xticks(rotation=90)
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
    ans=[]
    outputs=[]

    if(len(sys.argv) == 1):
        sys.exit("No input file mentioned!")

    for i in range(1, len(sys.argv)):
        with open(sys.argv[i]) as f:
            for line in f:
                str_list = line.split(",")
                str_list[10] = str_list[10][:-1]

                names.append(str_list[0])
                l1_icache.append(int(str_list[1])* 10000 /float(str_list[2]))
                cycles.append(int(str_list[2]))
                ipc.append(float(str_list[3])* 10000 /float(str_list[2]))
                l2.append(int(str_list[4])* 10000 /float(str_list[2]))
                tlb_data.append(float(str_list[5]) * 10000 /float(str_list[2]))
                l1_dcache.append(int(str_list[6])* 10000 /float(str_list[2]))
                tlb_ins.append(int(str_list[7])* 10000 /float(str_list[2]))
                error.append(float(str_list[8]))
                ans.append(float(str_list[9]))
                outputs.append(float(str_list[10]))

    fig, ax = plt.subplots(nrows=2, ncols=4)
#     fig, ax = plt.subplots(nrows=1, ncols=1)
#     graph_relative_error(ax, "l1_icache",error, l1_icache,0,0,1000)
#     graph_relative_error(ax, "cycles",error, cycles,0,1,10000000)
#     graph_relative_error(ax, "ipc",error, ipc,0,2,1)
#     graph_relative_error(ax, "l2",error, l2,0,3,100000)
#     graph_relative_error(ax, "tlb_data",error, tlb_data,1,0,10000)
#     graph_relative_error(ax, "l1_dcache",error, l1_dcache,1,1,100000)
#     graph_relative_error(ax, "tlb_ins",error, tlb_ins,1,2,100000)
    graph_relative_error("l1_icache",error, l1_icache,0,0,1000, names)
    graph_relative_error("cycles",error, cycles,0,1,10000000, names)
    graph_relative_error("ipc",error, ipc,0,2,1, names)
    graph_relative_error("l2",error, l2,0,3,100000, names )
    graph_relative_error("tlb_data",error, tlb_data,1,0,10000, names)
    graph_relative_error("l1_dcache",error, l1_dcache,1,1,100000, names)
    graph_relative_error("tlb_ins",error, tlb_ins,1,2,100000, names)

    graph_ans_output(names, ans, outputs)

main()

    



