import csv

def get_data(path):
    f = open(path)
    text = f.readlines()

    data_needed = ['L1-icache-load-misses', 'instructions', 'l2_rqsts.miss', 'dTLB-load-misses', 'L1-dcache-load-misses', 'iTLB-load-misses']
    
    if text[1].startswith('energy'):
        offset = 1
        energy = text[1].split()
        energy = float(energy[2][0:-1])
    else:
        energy = text[0].split()
        energy = float(energy[4])
        print(energy)

    j = 0
    data = []
    for i in range(4, len(text)):
        if data_needed[j] in text[i]:
            if text[i] == 'instructions':
                data.append(cast(text[i].split(), 3))
            data.append(cast(text[i].split(), 0))
            j += 1

    if (len(data) != len(data_needed) + 1):
        print("something went wrong")

    return energy, data 

def cast(input, index):
    return float(input[index].replace(',', ''))

files = ['bc', 'bfs', 'cc', 'cc_sv', 'l1_msr', 'l2_msr', 'pr', 'pr_spmv', 'sssp', 'tc', 'tlb_msr']
all_data = []

# CREATES CSV FILE OF ENERGIES
with open('b_data.csv', 'w') as f:
    writer = csv.writer(f)
    
    for path in files:
        energy, data = get_data(path)
        all_data.append(data)

        # writer.writerow(data)
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
