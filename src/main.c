#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include <scip/scip_solve.h>
#include <scip/scip_sol.h>
#include <scip/pricestore.h>
#include <scip/sepastore.h>
#include <scip/cutpool.h>
#include <scip/reopt.h>
#include <scip/cons_linear.h>
#include <scip/struct_cons.h>
#include <scip/struct_lp.h>
#include <scip/struct_scip.h>
#include <scip/struct_set.h>
#include <scip/sepa.h>
#include <scip/struct_sol.h>
#include <scip/struct_mem.h>
#include <scip/struct_prob.h>
#include <scip/struct_stat.h>
#include <scip/struct_var.h>
#include <scip/struct_misc.h>
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

//#include <_funcs.c>
/** constraint data for linear constraints */

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
    SCIP_Bool cutoff;
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

    //SCIP_CALL( SCIPpresolve(scip) );

    //lp.c: 115
    SCIP_CALL( SCIPconstructLP( scip, &cutoff ));

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
    
    // SCIP_CALL( //
    // SCIPlpSolveAndEval(
    //     scip->lp, 
    //     scip->set, 
    //     scip->messagehdlr,  
    //     scip->mem->probmem, 
    //     scip->stat, 
    //     scip->eventqueue, 
    //     scip->eventfilter, 
    //     scip->origprob, 
    //     -1LL, 
    //     FALSE, 
    //     FALSE, 
    //     FALSE, 
    //     &lperror)
    // );

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