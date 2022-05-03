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

    count = 0
    ax.scatter(new_x, new_y, color="none", edgecolor="red")
    for i, j in zip(new_x, new_y): 
        if count % 2 == 0:
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        else:
            ax.annotate(names[count], (i,j), ha="left", fontsize=10)
        count+=1
    plt.xticks(rotation=90)
    plt.savefig("ansvoutputs.png", bbox_inches='tight')
    

def graph_relative_error(name, errors, field_data, names):
    fig, ax = plt.subplots(nrows=1, ncols=1)
    ax.set_xlabel(name)
    ax.set_ylabel("Relative Error")

    lists = list(zip(field_data,errors,names))
    lists.sort()
    new_x, new_y, new_names = list(zip(*lists))

    count = 0
    ax.scatter(new_x, new_y, color="none", edgecolor="red")
    for i, j in zip(new_x, new_y): 
        if count % 2 == 0:
            ax.annotate(new_names[count], (i,j), ha="left", fontsize=10)
        else:
            ax.annotate(new_names[count], (i,j), ha="left", fontsize=10)
        count+=1
    plt.xticks(rotation=90)
    plt.savefig(name + ".png", bbox_inches='tight')

def main():
    names=[]
    l1_icache=[]
    cycles=[]
    ins=[]
    l2=[]
    tlb_data=[]
    l1_dcache=[]
    tlb_ins=[]
    error=[]
    ans=[]
    outputs=[]
    ipc=[]
    l3=[]

    if(len(sys.argv) < 3):
        sys.exit("Input files not mentioned!")

    for i in range(1, len(sys.argv) - 1):
        with open(sys.argv[i]) as f:
            for line in f:
                str_list = line.split(",")
                str_list[11] = str_list[11][:-1]

                names.append(str_list[0])
                l1_icache.append(int(str_list[1]))
                cycles.append(int(str_list[2]))
                ins.append(float(str_list[3]))
                l2.append(int(str_list[4]))
                tlb_data.append(float(str_list[5]))
                l1_dcache.append(int(str_list[6]))
                tlb_ins.append(int(str_list[7]))
                l3.append(int(str_list[8]))
                error.append(float(str_list[9]))
                ans.append(float(str_list[10]))
                outputs.append(float(str_list[11]))

    with open(sys.argv[len(sys.argv) - 1]) as f:
        for line in f:
            str_list = line.split(",")
            for i in range(0,len(str_list)):
                ipc.append(float(str_list[i]))
            

    fig, ax = plt.subplots(nrows=2, ncols=4)
    graph_relative_error("l1_icache",error, l1_icache,names)
    graph_relative_error("cycles",error, cycles,names)
    graph_relative_error("ins",error, ins,names)
    graph_relative_error("l2",error, l2,names )
    graph_relative_error("tlb_data",error, tlb_data,names)
    graph_relative_error("l1_dcache",error, l1_dcache,names)
    graph_relative_error("tlb_ins",error, tlb_ins,names)
    graph_relative_error("l3",error, l3,names)

    graph_relative_error("ipc",error, ipc,names)

#     for i in range(0, len(error)):
#         print("error: " + str(error[i]) + "ipc: " + str(ipc[i]))

#     graph_ans_output(names, ans, outputs)

main()

    



