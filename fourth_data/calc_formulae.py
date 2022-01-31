import csv
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('username', type=str, default="")
parser.add_argument('datafolder', type=str, default="")
args = parser.parse_args()

filepath = '/scratch/' + args.username + '/' + args.datafolder + '/'

coeff_file = open(filepath + 'coefficients.csv')
coeff = csv.reader(coeff_file) #check if this gives array

coeffs = []
for row in coeff:
    coeffs.append(row)

coeffs = coeffs[0]

inputs = []
print("Enter num of l1_icache cache misses: ")
inputs.append(float(input()))

print("Enter num of lpc cache misses: ")
inputs.append(float(input()))

print("Enter num of l2 cache misses: ")
inputs.append(float(input()))

print("Enter num of data_tlb misses: ")
inputs.append(float(input()))

print("Enter num of l1_dcache misses: ")
inputs.append(float(input()))

print("Enter num of ins_tlb0 misses: ")
inputs.append(float(input()))


output = 0.0

for i in range(len(inputs)):
    output += float(coeffs[i]) * inputs[i]

output *= 0.1

print("answer: ", str(output))
