## Import
#########
import os, sys
import numpy as np
from pyscipopt import Model
from pyscipopt import Sepa
import pyscipopt

## CLASSES
##########

class cutstore:

    def __init__(self):
        self.added_cut_var = []
        self.added_cut_coef = []
        self.added_cut_rhs = []
        self.ncuts = 0
    
    def addCut(self, var, coef, rhs):
        self.added_cut_var.append(var)
        self.added_cut_coef.append(coef)
        self.added_cut_rhs.append(rhs)
        self.ncuts += 1

    def getNCuts(self):
        return self.ncuts

    def printCut(self, idx):
        print(str(self.added_cut_coef[idx]) + " * " + str(self.added_cut_var[idx]) + " <= " + str(self.added_cut_rhs[idx]))

    def getCut(self, idx, verbose = False):
        if verbose:
            self.printCut(idx)
        return self.added_cut_var[idx], self.added_cut_coef[idx], self.added_cut_rhs[idx]


## FUNCTIONS
############

def lp_init(mps_file):
    print()
    print("Creating LP instance:")
    _lp = Model("lp_model")
    _lp.readProblem(mps_file)
    print()
    _lpvars = _lp.getVars()
    _lpnvars = _lp.getNVars()
    for i in range(0, _lpnvars):
        if _lpvars[i].vtype() == "BINARY" or _lpvars[i].vtype() == "INTEGER":
            _lp.chgVarType(_lpvars[i], "CONTINUOUS")
    return _lp, _lpvars, _lpnvars

# Heuristics
############

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

def heur_simple_round(_prob, _lpsol, _lpvars, _vars, _nvars):
    _sol = _prob.createSol()
    for i in range(0,_nvars):
        _sol[_vars[i]] = np.round(_lpsol[_lpvars[i]])
    return _sol

# BRANCHING
###########
        
def get_branchcands(_lp, _branchcand):
    assert _lp.getStage() == 10, "Error: Model needs to be solved."
    _lpsol = _lp.getBestSol()
    _vars = _lp.getVars()
    for i in range(0, _lp.getNVars()):
        if not np.isclose(_lpsol[_vars[i]], np.round(_lpsol[_vars[i]]), 0.0001):
            #print(_lpsol[_vars[i]])
            _branchcand.append(_vars[i])

def sel_bc_rand(_branchcand):
    _n = len(_branchcand)
    return _branchcand[np.random.randint(_n)]

def sel_rand_direction():
    # 0 = floor, 1 = ceil
    return np.random.randint(2)