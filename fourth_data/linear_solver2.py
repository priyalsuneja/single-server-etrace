import cvxpy as cp
import numpy as np 
import csv

A_data = open('fourth_data/A_input')
A_input = A_data.read()

B_data = open('fourth_data/data.csv')
B_reader = csv.reader(B_data)
x = cp.Variable(6)
'''
A = np.matrix('1106532 0.63 241883851 112964265 302996969 156787; \
1120819 0.65 173700287 82785104 227693531 262389; \
1042915 0.65 178048842 82601371 225725815 264178; \
1050443 0.64 259685744 118837781 337752947 203052; \
128905 0.50 412073934 114105 410950816 15366; \
270376 0.46 705997739 211140 657901285 23049; \
1231344 0.59 485970913 204637555 619468512 224684; \
1184361 0.60 401461195 170084950 512314105 225532; \
2967299 0.63 241156551 95894554 304069459 503069; \
3559496 0.82 731930858 117084328 649577427 525536; \
57525 0.10 32353896 20539920 32436945 110915')

b= [75.286255, 70.716797, 67.974243, 71.803833, 140.682190, 249.596802, 84.429199, 80.265686, 84.155579, 184.976379, 28.126038]
'''
A = np.matrix(A_input)
b = []
for row in B_reader:
    b.append(row[0])
print(b)
# '''
obj = cp.Minimize(cp.sum(cp.abs(A@ x - b)))
# con = [x>=0]
con = [0<=x]

prob = cp.Problem(obj,con)

# prob.solve(verbose=True)
prob.solve()

print(x.value)

# p = cp.sum(cp.abs(A @ x.value - b))

# print (A@x.value -b)
