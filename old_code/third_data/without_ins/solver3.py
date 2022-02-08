#without tlb and l1 dcache
import cvxpy as cp
import numpy as np 

x = cp.Variable(3)
A = np.matrix('799880 0.63 244755694 ; \
725530 0.65 176533690 ; \
647162 0.65 176983498 ; \
683244 0.65 259874874 ; \
88114 0.49 412012388 ; \
276557 0.46 698682776 ; \
891182 0.60 483714237 ; \
819116 0.60 400633603 ; \
2649810 0.64 244835471 ; \
2781145 0.82 730560735 ; \
50400 0.10 32350051 ')

b= [75.263794, 70.703674, 69.942810, 74.367065, 142.235718, 240.032043, 84.461609, 81.222534, 84.954407, 184.529419, 27.319214]
obj = cp.Minimize(cp.sum(cp.abs(A@ x - b)))
# con = [x>=0]
con = [0<=x]

prob = cp.Problem(obj,con)

# prob.solve(verbose=True)
prob.solve()

print(x.value)

# p = cp.sum(cp.abs(A @ x.value - b))

# print (A@x.value -b)
