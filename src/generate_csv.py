import csv
import os
import argparse

# FIRST_LINE = 3
parser = argparse.ArgumentParser()

parser.add_argument('inputfolder', type=str, default="")
parser.add_argument('tempfolder', type=str, default=".sse_temp")
parser.add_argument('data_labels_file', type=str, default=".data_labels")

args = parser.parse_args()

def get_energy_data(path):
    f = open(path)
    lines = f.readlines()

    energyTotal = 0

    for i in range(1, len(lines)):
        diff = float(lines[i]) - float(lines[i-1])
        if(diff < 0):
            continue
        energyTotal += diff
    return energyTotal

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
        
#     if (len(data) != len(data_needed) + 1):
#         print("something went wrong")
#     return ipc, energy, data 
    return ipc, data

def cast(input):
    return float(input.replace(',', ''))


all_data = []
energy_list = []
files = []
ipc_list = []

# CREATES CSV FILE OF ENERGIES
with open(args.tempfolder + "/" + 'b_data.csv', 'w') as f:
    writer = csv.writer(f)
    
    for filename in os.scandir(args.inputfolder + "/data"):
        ipc, data = get_perf_data(filename.path)
        files.append(filename.name)

        all_data.append(data)
        ipc_list.append(ipc)


        energy = get_energy_data(args.inputfolder + "/rapl/" +
        filename.name[:-3] + "rapl")
#         energy = get_energy_data(args.inputfolder + "/rapl/" +
#         filename.name[:-4])
#         energy = get_energy_data(args.inputfolder + "/rapl/" +
#         filename.name + "_out")
        energy_list.append(energy)
        writer.writerow([energy])


b_line = ""
f = open(args.tempfolder + "/" + "bm_input", "w")
for i in range(len(energy_list) -1):
    b_line += str(energy_list[i])
    b_line += "; "

b_line += str(energy_list[len(energy_list) -1])

f.write(b_line)

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

f2 = open(args.tempfolder + "/" + "temp", "w")

for i in range(len(all_data) - 1):
    f2.write(files[i] + "\n")
    data = all_data[i]
    for j in range(len(data) - 1):
        line1 += str(data[j]) + " "
        line2 = str(data[j]) + "\n"
        f2.write(line2)
    line1 += str(data[len(data) - 1]) + "; "
    line2 = str(data[len(data)-1]) + "\n"
    f2.write(line2)
    line2 = str(energy_list[i]) + "\n"
    f2.write(line2)
data = all_data[len(all_data) - 1]
f2.write(files[len(all_data)-1] + "\n")
for j in range(len(data) - 1):
    line1 += str(data[j]) + " "
    line2 = str(data[j]) + "\n"
    f2.write(line2)
line1 += str(data[len(data) - 1])
line2 = str(data[len(data)-1]) + "\n"
f2.write(line2)
line2 = str(energy_list[len(all_data)-1]) + "\n"
f2.write(line2)
f2.write(';')

f1.write(line1)
