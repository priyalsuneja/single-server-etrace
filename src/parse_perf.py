import csv
import os
import argparse

# FIRST_LINE = 3
parser = argparse.ArgumentParser()

parser.add_argument('inputfolder', type=str, default="")
parser.add_argument('tempfolder', type=str, default=".sse_temp")
parser.add_argument('data_labels_file', type=str, default=".data_labels")

args = parser.parse_args()

def get_perf_data(path):
    f = open(path)
    lines = f.readlines()

    data_needed = []
    with open(args.data_labels_file, "r") as f_labels:
        for data_line in f_labels:
            data_needed.append(data_line[:-1])

    j = 0
    data = []
    ipc = 0

    for i in range(3, len(lines)):
        if j == len(data_needed):
            break
        if data_needed[j] == 'cycles':
            j+=1
        elif data_needed[j] in lines[i]:
            if data_needed[j] == 'instructions':
                ipc_text = lines[i].split()[3]
                ipc = cast(ipc_text)
            text = lines[i].split()[0]
            if(text == "<not"):
                text = "0"

            data.append(cast(text))
            j += 1
        
    return ipc, data

def cast(input):
    return float(input.replace(',', ''))


all_data = []
files = []
ipc_list = []

for filename in os.scandir(args.inputfolder + "/data"):
    ipc, data = get_perf_data(filename.path)
    files.append(filename.name)

    all_data.append(data)
    ipc_list.append(ipc)

ipc_line = ""
f_ipc = open(args.tempfolder + "/" + "ipc_input", "w")
for i in range(len(ipc_list) -1):
    ipc_line += str(ipc_list[i])
    ipc_line += ","

ipc_line += str(ipc_list[len(ipc_list) -1])

f_ipc.write(ipc_line)
    

# CREATES INPUT FOR MATRIX A
f1 = open(args.tempfolder + "/" + "A_data", "w")
line1 = ""

for i in range(len(all_data) - 1):
    data = all_data[i]
    for j in range(len(data) - 1):
        line1 += str(data[j]) + " "
    line1 += str(data[len(data) - 1]) + "; "
data = all_data[len(all_data) - 1]
for j in range(len(data) - 1):
    line1 += str(data[j]) + " "
line1 += str(data[len(data) - 1])

f1.write(line1)
