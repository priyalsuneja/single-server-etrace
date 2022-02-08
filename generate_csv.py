import csv
import os
import argparse
parser = argparse.ArgumentParser()

parser.add_argument('inputfolder', type=str, default="")
parser.add_argument('outputfolder', type=str, default="")
parser.add_argument('tempfolder', type=str, default=".sse_temp")
args = parser.parse_args()
def get_data(path):
    f = open(path)
    text = f.readlines()

    offset = 0
    
    if text[1].startswith('energy'):
        offset = 1
        energy = text[1].split()
        energy = float(energy[2][0:-1])
    else:
        energy = text[0].split()
        energy = float(energy[4])

    data = []
    key_lines = [4, 5, 6, 7, 8, 9, 10]
    for i in key_lines:
        if i == 6:
            data.append(cast(text[i + offset].split(), 3))
        else:
            data.append(cast(text[i + offset].split(), 0))

    return energy, data 

def cast(input, index):
    return float(input[index].replace(',', ''))

all_data = []
energy_list = []
files = []

# CREATES CSV FILE OF ENERGIES
with open(args.outputfolder + "/" + args.tempfolder + "/" + 'b_data.csv', 'w') as f:
    writer = csv.writer(f)
    
    for filename in os.scandir(args.inputfolder):
        energy, data = get_data(filename.path)
        files.append(filename.name)

        all_data.append(data)
        energy_list.append(energy)

        writer.writerow([energy])

b_line = ""
f = open(args.outputfolder + "/" + args.tempfolder + "/" + "bm_input", "w")
for i in range(len(energy_list) -1):
    b_line += str(energy_list[i])
    b_line += "; "

b_line += str(energy_list[len(energy_list) -1])

f.write(b_line)
    

# CREATES INPUT FOR MATRIX A

f1 = open(args.outputfolder + "/" + args.tempfolder + "/" + "A_data", "w")
line1 = ""

f2 = open(args.outputfolder + "/" + args.tempfolder + "/" + "temp", "w")

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
