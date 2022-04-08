## Import
#########
import os, sys
import numpy as np
import torch
import numpy as np
from torch import concat, nn
from torch.utils.data import DataLoader
from pyscipopt import Model, Sepa
import pyscipopt
from _utils import *

## Check if mps file passed
###########################
n = len(sys.argv)
assert n == 2, "Error: A MPS file must be passed."
mps_file = sys.argv[1]
        
## Read models:
## The main model is for reference, while 
## only the lp model is manipulated / updated / reloaded.
#########################################################
print("Creating original problem:")
m = Model("main_model")
m.readProblem(mps_file)
print()
# orig.setParam("limits/nodes", 1)

cutstore = cutstore()
lazy_cuts = Sepa()
lp, lpvars, lpnvars = lp_init(mps_file)
lp.includeSepa(lazy_cuts, "lazy_cuts", "Origin of cutting planes for branching.", freq = 0)
for i in range(0, cutstore.getNCuts()):
    _var, _coef, _rhs = cutstore.getCut(i)
    _row = lp.createEmptyRowSepa(lazy_cuts, name = "bc%d"%(-1), lhs = None, rhs = _rhs)
    lp.addVarToRow(_row, _var, _coef)
lp.optimize()

vars = m.getVars()
nvars = m.getNVars()

sol_lb = heur_triv_lb(m, vars, nvars)
sol_ub = heur_triv_ub(m, vars, nvars)

res = m.trySol(sol_lb, free=0, printreason=False)
print(res)
res = m.trySol(sol_ub, free=0, printreason=False)
print(res)

## Start Random Dive
####################

branchcands = []
itr_max = 1

get_branchcands(lp, branchcands)
lpsol = lp.getBestSol()
node = sel_bc_rand(branchcands)
direction = sel_rand_direction()

if direction == 0:
    cutstore.addCut(node, 1.0, np.floor(lpsol[node]))
if direction == 1:
    cutstore.addCut(node, -1.0, np.ceil(lpsol[node]))

for i in range(0, itr_max):

    lp, lpvars, lpnvars = lp_init(mps_file)
    lazy_cuts = Sepa()
    lp.includeSepa(lazy_cuts, "lazy_cuts", "Origin of cutting planes for diving.", freq = 0)
    # for i in range(0, cutstore.getNCuts()):
    #     _var, _coef, _rhs = cutstore.getCut(i, verbose = True)
    #     _row = lp.createEmptyRowSepa(lazy_cuts, name = "bc%d_%d"%(itr, i), lhs = None, rhs = _rhs)
    #     lp.addVarToRow(_row, _var, _coef)

    lp.optimize()

    i += 1


