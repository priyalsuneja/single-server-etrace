import cvxpy as cp
import numpy as np 
import csv
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('datafolder', type=str, default="")
args = parser.parse_args()

filepath = args.datafolder + "/"       # maybe change to an argument 
A_data = open(filepath + 'A_data')
A_input = A_data.read()

bm_data = open(filepath + 'bm_input')
bm_input = bm_data.read()

B_data = open(filepath + 'b_data.csv')
B_reader = csv.reader(B_data)
x = cp.Variable(7)

A = np.matrix(A_input)
b = []
for row in B_reader:
    b.append(row[0])

b_temp = []

for i in range(len(b)):
    b_temp.append(1)


b_m = np.matrix(bm_input)   # TODO: automate this input generation
# obj = cp.Minimize(cp.sum(cp.abs(A@ x - b)))
obj = cp.Minimize(cp.sum(cp.square((A/b_m)@ x - b_temp)))
# con = [x>=0]
con = [0<=x]

prob = cp.Problem(obj,con)

# prob.solve(verbose=True)
prob.solve(solver=cp.SCS)

print(x.value)

with open(filepath + 'coefficients.csv', 'w') as f:
    writer = csv.writer(f)

    writer.writerow(x.value)

# p = cp.sum(cp.abs(A @ x.value - b))

# print (A@x.value -b)
