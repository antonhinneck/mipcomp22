#ifndef _main
#define _main

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "scip/struct_sol.h"

#include "scip/struct_lp.h"
#include "scip/def.h"
#include "scip/type_lp.h"
#include "scip/type_var.h"
#include "scip/type_event.h"

#include "lpi/type_lpi.h"
#include <scip/lp.h>

#include "scip/scip_reader.h"

#include "scip/prob.h"

#include "scip/struct_var.h"

#include "scip/type_cons.h"
#include "scip/struct_cons.h"
#include "scip/cons_linear.h"

#include "scip/scip.h"
#include "scip/struct_scip.h"
#include "scip/set.h"
#include "scip/scipdefplugins.h"

#include "_structs.c"

#endif

struct CmCSR(){
    int *cval, *cind, *cbeg;
}

int countNnz(SCIP_PROB *prob){
    int nnzs, i;
    SCIP_CONSDATA *consdata;

    //ncons = prob->nconss;
    nnzs = 0;
    for(i = 0; i < prob -> nconss; i ++){
        consdata = prob->conss[i]->consdata;
        nnzs += consdata->nvars;
        //printf("%d\n", consdata->nvars);
    }

    return nnzs;
}

void getCm( SCIP_PROB *prob, int *cval, int *cind, int *cbeg){
    SCIP_CONSDATA *consdata;
    int i, j, ctr;

    ctr = 0;
    for (i = 0; i < prob -> nconss; i++){
        cbeg[i] = ctr;
        consdata = prob->conss[i]->consdata;
        for (j = 0; j < consdata -> nvars; j ++){
            cind[ctr] = consdata -> vars[j] -> probindex; 
            cval[ctr] = consdata -> vals[j];
            ctr += 1;
        }
    }
}

int main(int argc, char *argv[]){
    
    // Search MPS file
    assert(argc == 2 && "ERROR: A single MPS file is expected as a command line argument.\n");
    if( !(access(argv[1], F_OK) == 0) ){
        printf("ERROR: MPS file specified (%s) does not exist.\n", argv[1]);
        return 0;
    }
    
    printf("Mps file: %s found ... \n", argv[1]);

    // Create SCIP
    SCIP* scip;
    SCIP_CALL( SCIPcreate(& scip) );
    SCIP_CALL( SCIPincludeDefaultPlugins(scip) );
    SCIP_RESULT* result = malloc( 3 * sizeof(SCIP_RESULT) );
    SCIP_READER* reader = malloc( 1 * sizeof(int) );

    int *varnamessize = malloc(sizeof(int));
    int *consnamessize = malloc(sizeof(int)); 
    int *nvarnames = malloc(sizeof(int)); 
    int *nconsnames = malloc(sizeof(int));
    int cval_size;
    int *cval, *cind, *cbeg;

    //Read MPS
    SCIP_CALL( SCIPreadMps(scip,
        reader,
        argv[1],
        result,
        NULL, NULL,
        // varnames, consnames,
        varnamessize, consnamessize, nvarnames, nconsnames
    ));

    printf("Mps file: %s parsed ... \n", argv[1]);
    
    scip->set->disp_verblevel = SCIP_VERBLEVEL_FULL;
    SCIP_CALL( SCIPpresolve(scip) );

    // Checks
    // printf("\n%d\n", scip->lp->solved);
    // printf("%d\n", scip->origprob->conss[0]->initial);
    // printf("%d\n", scip->transprob->conss[0]->consdata->nvars);
    //printf("%d\n", countNnz(scip->origprob));

    cval_size = countNnz(scip->origprob);

    // TODO: Replace MALLOC with block memory call
    cval = malloc( sizeof(int) * cval_size );
    cind = malloc( sizeof(int) * cval_size );
    cbeg = malloc( sizeof(int) * scip -> origprob -> nconss);

    getCm(scip -> origprob, cval, cind, cbeg);

    free(cval);
    free(cind);
    free(cbeg);

    //countNnz(scip->origprob);

    free(varnamessize);
    free(consnamessize);
    free(nvarnames);
    free(nconsnames);

    return 0;
}