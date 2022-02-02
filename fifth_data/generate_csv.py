import csv
import argparse
parser = argparse.ArgumentParser()

parser.add_argument('datafolder', type=str, default="")
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

files = ['bc', 'bfs', 'cc', 'cc_sv', 'l1_msr', 'l2_msr', 'pr', 'pr_spmv',
'sssp', 'tc', 'tlb_msr'] ##TODO: automate to looping through all files in folder
all_data = []

# CREATES CSV FILE OF ENERGIES
with open('b_data.csv', 'w') as f:
    writer = csv.writer(f)
    
    for path in files:
        energy, data = get_data(args.datafolder + '/' + path)
        all_data.append(data)

        writer.writerow([energy])

# CREATES INPUT FOR MATRIX A
f1 = open("A_data", "w")
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
