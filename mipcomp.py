import os, sys
import torch
import numpy as np
from torch import nn
from torch.utils.data import DataLoader
from pyscipopt import Model
import pyscipopt

## Check if mps file passed
n = len(sys.argv)
assert n == 2, "Error: A MPS file must be passed."
mps_file = sys.argv[1]

def lp_init():
    _lp=Model("lp_model")
    _lp.readProblem(mps_file)
    _lpvars = _lp.getVars()
    _lpnvars = _lp.getNVars()
    for i in range(0, _lpnvars):
        if _lpvars[i].vtype() == "BINARY" or _lpvars[i].vtype() == "INTEGER":
            _lp.chgVarType(_lpvars[i], "CONTINUOUS")
    return _lp, _lpvars, _lpnvars

def heur_triv_lb(_prob, _vars, _nvars):
    _sol = _prob.createSol()
    for i in range(0,_nvars):
        _sol[_vars[i]] = _vars[i].getLbOriginal()
    return _sol

def heur_triv_ub(_prob, _vars, _nvars):
    _sol = _prob.createSol()
    for i in range(0,_nvars):
        _sol[_vars[i]] = _vars[i].getUbOriginal()
    return _sol

def heur_triv_ceil(_prob, _lpsol, _lpvars, _vars, _nvars):
    _sol = _prob.createSol()
    for i in range(0,_nvars):
        _sol[_vars[i]] = np.ceil(_lpsol[_lpvars[i]])
    return _sol
        
def get_branchcands(_lp, _branchcand):
    assert _lp.getStage() == 10, "Error: Model needs to be solved."
    _lpsol = _lp.getBestSol()
    _vars = _lp.getVars()
    for i in range(0, _lp.getNVars()):
        if not np.isclose(_lpsol[_vars[i]], np.round(_lpsol[_vars[i]]), 0.0001):
            print(_lpsol[_vars[i]])
            _branchcand.append(_vars[i])

def sel_bc_rand(_branchcand):
    _n = len(_branchcand)
    return _branchcand[np.random.randint(_n)]

def sel_rand_direction():
    # 0 = floor, 1 = ceil
    return np.random.randint(2)
        
## Read models:
## The main model is for reference, while 
## only the lp model is manipulated.
m=Model("main_model")
m.readProblem(mps_file)
# orig.setParam("limits/nodes", 1)

lp,lpvars,lpnvars=lp_init()
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

itr = 0
itr_max = 10

for i in range(0,itr_max):
    branchcands = []

    lpsol = lp.getBestSol()
    get_branchcands(lp, branchcands)
    node = sel_bc_rand(branchcands)
    direction = sel_rand_direction()

    # lp,lpvars,lpnvars=lp_init()
    # if direction == 0:
    #     lp.addCons(node <= np.floor(lpsol[node]))
    # else:
    #     lp.addCons(node >= np.ceil(lpsol[node]))

    cut = pyscipopt.Row()
    if direction == 0:
        lp.createEmptyRowSepa(cut, lhs = None, rhs = np.floor(lpsol[node]))
        lp.addVarToRow(cut, node, -1)
    if direction == 1:
        lp.createEmptyRowSepa(cut, lhs = None, rhs = np.ceil(lpsol[node]))
        lp.addVarToRow(cut, node, 1)

    itr += 1


