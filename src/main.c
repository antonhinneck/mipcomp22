#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include <scip/scip_solve.h>
#include <scip/scip_sol.h>
#include <scip/scip_lp.h>
#include <scip/pricestore.h>
#include <scip/sepastore.h>
#include <scip/cutpool.h>
#include <scip/reopt.h>
#include <scip/cons_linear.h>
#include <scip/struct_cons.h>
#include <scip/struct_lp.h>
#include <scip/struct_scip.h>
#include <scip/type_scip.h>
#include <scip/struct_set.h>
#include <scip/sepa.h>
#include <scip/struct_sol.h>
#include <scip/struct_mem.h>
#include <scip/struct_prob.h>
#include <scip/struct_stat.h>
#include <scip/struct_var.h>
#include <scip/struct_misc.h>
#include <scip/struct_tree.h>
#include <scip/cons_cumulative.h>
#include <scip/scip.h>
#include <scip/prob.h>
#include <scip/type_cons.h>
#include <scip/type_lp.h>
#include <scip/type_set.h>
#include <scip/lp.h>
#include <scip/struct_set.h>
#include <scip/scipdefplugins.h>
#include <scip/misc.h>
#include <scip/pub_misc_linear.h>
#include <scip/set.h>
#include <scip/solve.h>
#include <scip/var.h>
#include <scip/tree.h>
#include <scip/cons.h>
#include <scip/event.h>
#include <scip/branch.h>
#include <scip/implics.h>
#include <scip/primal.h>
#include <scip/conflict.h>
#include <scip/relax.h>
#include <scip/stat.h>
#include <scip/nlp.h>
#include <scip/visual.h>
#include <scip/dcmp.h>
#include <scip/conflictstore.h>
#include <scip/type_message.h>

#include <_structs.c>
/** constraint data for linear constraints */

void checkIfNullAndInit(SCIP* scip, SCIP_Bool init){

    printf("\nChecking allocation: \n\n");

    if(scip->mem->probmem == NULL){
        printf("->mem->probmem: NULL\n");
    } else {
        printf("->mem->probmem: NOT NULL\n");
    } 

    if(scip->set == NULL){
        printf("->set: NULL\n");
    } else {
        printf("->set: NOT NULL\n");
    }

    if(scip->stat == NULL){
        printf("->stat: NULL\n");
    } else {
        printf("->stat: NOT NULL\n");
    } 

    if(scip->transprob == NULL){
        printf("->transprob: NULL\n");
    } else {
        printf("->transprob: NOT NULL\n");
    } 

    if(scip->origprob == NULL){
        printf("->origprob: NULL\n");
    } else {
        printf("->origprob: NOT NULL\n");
    } 

    if(scip->tree == NULL){
        printf("->tree: NULL\n");
    } else {
        printf("->tree: NOT NULL\n");
    }  

    if(scip->reopt == NULL){
        printf("->reopt: NULL\n");
        if(init){
            if (SCIPreoptCreate(&scip->reopt,scip->set,scip->mem->probmem) == SCIP_OKAY){
                printf("->reopt: initialized\n");
            }
        }
    } else {
        printf("->reopt: NOT NULL\n");
    }  

    if(scip->lp == NULL){
        printf("->lp: NULL\n");
    } else {
        printf("->lp: NOT NULL\n");
    }

    if(scip->pricestore == NULL){
        printf("->pricestore: NULL\n");
        if(init){
            if (SCIPpricestoreCreate(&scip->pricestore) == SCIP_OKAY){
                printf("->pricestore: initialized\n");
            }
        }
    } else {
        printf("->pricestore: NOT NULL\n");
    }  

    if(scip->sepastore == NULL){
        printf("->sepastore: NULL\n");
        if(init){
            if (SCIPsepastoreCreate(&scip->sepastore,scip->mem->probmem,scip->set) == SCIP_OKAY){
                printf("->sepastore: initialized\n");
            }
        }
    } else {
        printf("->sepastore: NOT NULL\n");
    }  

    //ToDo: equal signature for ...create functions
    if(scip->cutpool == NULL){
        printf("->cutpool: NULL\n");
        if(init){
            if (SCIPcutpoolCreate(&scip->cutpool,scip->mem->probmem,scip->set,1,1) == SCIP_OKAY){
                printf("->cutpool: initialized\n");
            }
        }
    } else {
        printf("->cutpool: NOT NULL\n");
    }

    if(scip->delayedcutpool == NULL){
        printf("->delayedcutpool: NULL\n");
        if(init){
            if (SCIPcutpoolCreate(&scip->delayedcutpool,scip->mem->probmem,scip->set,1,1) == SCIP_OKAY){
                printf("->delayedcutpool: initialized\n");
            }
        }
    } else {
        printf("->delayedcutpool: NOT NULL\n");
    } 

    if(scip->branchcand == NULL){
        printf("->branchcand: NULL\n");
    } else {
        printf("->branchcand: NOT NULL\n");
    }  

    if(scip->eventqueue == NULL){
        printf("->eventqueue: NULL\n");
    } else {
        printf("->eventqueue: NOT NULL\n");
    }  

    if(scip->eventfilter == NULL){
        printf("->eventfilter: NULL\n");
    } else {
        printf("->eventfilter: NOT NULL\n");
    }  

    if(scip->cliquetable == NULL){
        printf("->cliquetable: NULL\n");
    } else {
        printf("->cliquetable: NOT NULL\n");
    } 

    printf(" \n");
}

// scip->mem->probmem, scip->set, scip->stat, scip->transprob, scip->origprob,
//           scip->tree, scip->reopt, scip->lp, scip->pricestore, scip->sepastore, scip->cutpool, scip->branchcand,
//           scip->eventqueue, scip->eventfilter, scip->cliquetable,
// void printArray(SCIP_Real * array, int len){
//     for(int i = 0; i < len; i ++){
//         printf("%f  ", array[i]);
//     }
//     printf("\n---------------------\n");
// }

// void printVarArray(SCIP_VAR ** array, int len){
//     for(int i = 0; i < len; i ++){
//         printf(" %f   ", array[i]->obj);
//     }
//     printf("\n---------------------\n");
// }
 

int main(int argc, char *argv[]){
    
    assert(argc == 2 && "ERROR: A single MPS file is expected as a command line argument.\n");
    if( !(access(argv[1], F_OK) == 0) ){
        printf("ERROR: MPS file specified (%s) does not exist.\n", argv[1]);
        return 0;
    }
    
    printf("Mps file: %s found ... \n", argv[1]);

    SCIP* scip;
    SCIP_CALL( SCIPcreate(& scip) );
    SCIP_CALL( SCIPincludeDefaultPlugins(scip) );
    SCIP_RESULT* result = malloc( 3 * sizeof(SCIP_RESULT) );
    SCIP_READER* reader = malloc( 1 * sizeof(int) );

    int *varnamessize = malloc(sizeof(int));
    int *consnamessize = malloc(sizeof(int)); 
    int *nvarnames = malloc(sizeof(int)); 
    int *nconsnames = malloc(sizeof(int));
    SCIP_Bool error, lperror, solved;
    int i;
    SCIP_CONSDATA* consdata;
    SCIP_CONS* cons_trans;
    //SCIP_Bool cutoff;
    //SCIP_NODE* node;
    // SCIP_Bool initroot = 1;
    // SCIP_CONS* cons;
    // SCIP_COL* col;
    // SCIP_CONSDATA* consdata;
    // char* cname = malloc(128 * sizeof(char));
    // int clen = 0;

    // SCIP_Bool lperror;
    // SCIP_Bool infeasible;

    SCIP_CALL( SCIPreadMps(scip,
        reader,
        argv[1],
        result,
        NULL, NULL,
        // varnames, consnames,
        varnamessize, consnamessize, nvarnames, nconsnames
    ));

    printf("Mps file: %s parsed ... \n", argv[1]);
    error = 1;
    assert(error);
    scip->set->stage = SCIP_STAGE_PROBLEM;
    // checkIfNullAndInit(scip, 0);
    // SCIPeventfilterCreate(&scip->eventfilter, scip->mem->probmem);
    // SCIPeventqueueCreate(&scip->eventqueue);
    // SCIP_CALL( SCIPbranchcandCreate(&scip->branchcand) );
    // SCIP_CALL( SCIPlpCreate(&scip->lp, scip->set, scip->messagehdlr, scip->stat, SCIPprobGetName(scip->origprob)) );
    // SCIP_CALL( SCIPprimalCreate(&scip->primal) );
    // SCIP_CALL( SCIPtreeCreate(&scip->tree, scip->mem->probmem, scip->set, SCIPsetGetNodesel(scip->set, scip->stat)) );
    // SCIP_CALL( SCIPrelaxationCreate(&scip->relaxation, scip->mem->probmem, scip->set, scip->stat, scip->primal, scip->tree) );
    // SCIP_CALL( SCIPconflictCreate(&scip->conflict, scip->mem->probmem, scip->set) );
    // SCIP_CALL( SCIPcliquetableCreate(&scip->cliquetable, scip->set, scip->mem->probmem) );
    // SCIP_CALL( SCIPtransformProb(scip) );
    scip->set->disp_verblevel = SCIP_VERBLEVEL_FULL;
    SCIP_CALL( SCIPpresolve(scip) );

    solved = 0;
    printf("%d", solved);
    //SCIP_CALL( initSolve(scip, solved) );


    // scip->set->stage = SCIP_STAGE_TRANSFORMING;
    //SCIP_CALL( SCIPtransformProb(scip) );

    
    scip->set->stage = SCIP_STAGE_SOLVING;
    printf("%d\n", scip->transprob->nconss);
    assert(scip->tree != NULL);

    for(i = 0; i <= scip->transprob->nconss; i++){
        cons_trans = scip->transprob->conss[i];
        //SCIP_CALL( SCIPconsInitlp(scip->transprob->conss[i],scip->set,&error));
        //SCIP_CALL(SCIPtransformCons(scip, cons_orig, &scip->origprob->conss[i]));
        //assert(SCIPconsIsInitial(cons_trans);
        consdata = SCIPconsGetData(cons_trans);
        printf("%s ", cons_trans->name);
        printf("%f ", consdata->lhs );
        printf("%d ", consdata->nvars );
        printf("%f \n", consdata->rhs );
        // SCIP_CALL( SCIPcreateEmptyRowCons(scip, &consdata->row, cons_trans, SCIPconsGetName(cons_trans), consdata->lhs, consdata->rhs,
        // SCIPconsIsLocal(cons_trans), SCIPconsIsModifiable(cons_trans), SCIPconsIsRemovable(cons_trans)) );
        //SCIP_CALL( SCIPaddVarsToRow(scip, consdata->row, consdata->nvars, consdata->vars, consdata->vals) );
    }

    //for(i = 0; i <= scp->set->nc)
    //SCIPtreeCreate(&scip->tree, scip->mem->probmem, scip->set, SCIPsetGetNodesel(scip->set, scip->stat));
    //node = SCIPtreeGetCurrentNode(scip->tree);
    //printf("%d", node->depth)
    //./bin/mipcomp MIP\ 2022\ Open\ Instances/eil33-2.mps
    //./mipcomp.sh MIP\ 2022\ Open\ Instances/eil33-2.mps
    //scip_lp.c: 115
    //SCIP_CALL( SCIPconstructLP( scip, &cutoff ));
    

    // SCIP_Real obj = SCIPgetLPObjval(scip);
    // printf("Objective %f\n", obj);

    // for(int i = 0; i < scip->origprob->nvars; i++){
    //     SCIP_CALL( SCIPvarColumn(
    //         scip->origprob->vars[i],    /**< problem variable */
    //         scip->mem->probmem,         /**< block memory */
    //         scip->set,                  /**< global SCIP settings */
    //         scip->stat,                 /**< problem statistics */
    //         scip->transprob,             /**< problem data */
    //         scip->lp                    /**< current LP data */
    //     ));
    //     col = SCIPvarGetCol(scip->origprob->vars[i]);
    //     SCIP_CALL( SCIPlpAddCol(scip->lp, scip->set, col, 0) );
    // }
    //scip->origprob->nconss
    // for(int i = 0; i < 1; i++){
    //     cons = scip->origprob->conss[i];
    //     addRelaxation(scip, cons, &cutoff);
    //     //consdata = SCIPconsGetData(scip->origprob->conss[i]);
    //     // printVarArray(consdata->vars, consdata->nvars);
    //     // SCIP_CALL( SCIPcreateRowCons(
    //     //     scip, 
    //     //     &(consdata->row), 
    //     //     scip->origprob->conss[i], 
    //     //     SCIPconsGetName(scip->origprob->conss[i]), 
    //     //     consdata->nvars, 
    //     //     scip->lp->cols,
    //     //     consdata->vals,
    //     //     consdata->lhs, 
    //     //     consdata->rhs, 
    //     //     FALSE, 
    //     //     FALSE, 
    //     //     TRUE)
    //     // );

    //     // assert(consdata->row != NULL);
    //     // SCIP_CALL(SCIPlpAddRow(
    //     //     scip->lp, 
    //     //     scip->mem->probmem, 
    //     //     scip->set, 
    //     //     scip->eventqueue, 
    //     //     scip->eventfilter, 
    //     //     consdata->row, 
    //     //     0)
    //     // );
    // }

    // infeasible = 0;
    // printf("%d\n", infeasible);
    // printf("SCIP infinity: %f\n", SCIPinfinity(scip));

    // row = SCIPconsGetRow(scip, scip->origprob->conss[0]);
    // assert(scip->origprob->conss[0]->consdata->row != NULL);
    // printf("row rhs: %f\n", scip->origprob->conss[0]->consdata->row->lhs);

    // for(int i = 0; i <= scip->origprob->nconss; i++){

    // }

    // printf("Number of columns: %d\n", scip->lp->ncols);
    // printf("Number of rows: %d\n", scip->lp->nrows);
    
    SCIP_CALL( //
    SCIPlpSolveAndEval(
        scip->lp, 
        scip->set, 
        scip->messagehdlr,  
        scip->mem->probmem, 
        scip->stat, 
        scip->eventqueue, 
        scip->eventfilter, 
        scip->transprob, 
        -1LL, 
        FALSE, 
        FALSE, 
        FALSE, 
        &lperror)
    );

    printf("\n%d\n", scip->lp->solved);
    printf("\n%f\n", scip->lp->lpobjval);
    printf("\n%d\n", scip->lp->nrows);
    printf("\n%d\n", scip->lp->ncols);

    // SCIPcreateLPSol(scip, &newsol, NULL);
    // for(int i = 0; i < scip->lp->nlpicols; i++){
    //     printf("%f  ", scip->lp->lpicols[i]->primsol);
    // }
    // printf("Number of lpi columns: %f\n", scip->origprob->vars[1]->relaxsol);
    // printf("Objective value of LP relaxation: %f\n", scip->lp->lpobjval);
    // printf("Solution status of LP relaxation: %d\n", scip->lp->lpsolstat);
    // printf("Number of solved LPs: %lld\n", scip->stat->lpcount);
    
    // printf("LP solved: %d\n", scip->lp->solved);
        // SCIP_LPSOLSTAT_NOTSOLVED    = 0,     /**< LP was not solved, no solution exists */
        // SCIP_LPSOLSTAT_OPTIMAL      = 1,     /**< LP was solved to optimality */
        // SCIP_LPSOLSTAT_INFEASIBLE   = 2,     /**< LP is primal infeasible */
        // SCIP_LPSOLSTAT_UNBOUNDEDRAY = 3,     /**< LP has a primal unbounded ray */
        // SCIP_LPSOLSTAT_OBJLIMIT     = 4,     /**< objective limit was reached during optimization */
        // SCIP_LPSOLSTAT_ITERLIMIT    = 5,     /**< iteration limit was reached during optimization */
        // SCIP_LPSOLSTAT_TIMELIMIT    = 6,     /**< time limit was reached during optimization */
        // SCIP_LPSOLSTAT_ERROR        = 7      /**< an error occured during optimization */
    
    

    // printf("LP objective value: %f\n", scip->lp->lpobjval);
    // SCIP_CALL(SCIPsolve(scip));

    // Free allocated memory
    //----------------------
    // free(result);
    // free(reader);
    free(varnamessize);
    free(consnamessize);
    free(nvarnames);
    free(nconsnames);

    return 0;
}