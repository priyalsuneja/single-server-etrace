import cvxpy as cp
import numpy as np 
import csv
import argparse
from cvxpy.settings import CPLEX

parser = argparse.ArgumentParser()
parser.add_argument('tempfolder', type=str, default=".sse_temp")
args = parser.parse_args()

filepath = args.tempfolder + "/"      # maybe change to an argument 
A_data = open(filepath + 'A_data')
# A_data = open(filepath + 'A_data_data')
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


b_m = np.matrix(bm_input)
obj = cp.Minimize(cp.sum(cp.square((A/b_m)@ x - b_temp)))
# con = [x>=0]
# con = [0<=x]
con = []

prob = cp.Problem(obj,con)

# prob.solve(verbose=True)
prob.solve(solver=cp.SCS)
# prob.solve(solver=CPLEX, verbose=True)


# print(x.value)

with open(filepath + 'coefficients.csv', 'w') as f:
    writer = csv.writer(f)

    writer.writerow(x.value)
