 
 /** constraint data for linear constraints */
 struct SCIP_ConsData
 {
    SCIP_Real             lhs;                /**< left hand side of row (for ranged rows) */
    SCIP_Real             rhs;                /**< right hand side of row */
    SCIP_Real             maxabsval;          /**< maximum absolute value of all coefficients */
    SCIP_Real             minabsval;          /**< minimal absolute value of all coefficients */
    SCIP_Real             minactivity;        /**< minimal value w.r.t. the variable's local bounds for the constraint's
                                               *   activity, ignoring the coefficients contributing with infinite value */
    SCIP_Real             maxactivity;        /**< maximal value w.r.t. the variable's local bounds for the constraint's
                                               *   activity, ignoring the coefficients contributing with infinite value */
    SCIP_Real             lastminactivity;    /**< last minimal activity which was computed by complete summation
                                               *   over all contributing values */
    SCIP_Real             lastmaxactivity;    /**< last maximal activity which was computed by complete summation
                                               *   over all contributing values */
    SCIP_Real             glbminactivity;     /**< minimal value w.r.t. the variable's global bounds for the constraint's
                                               *   activity, ignoring the coefficients contributing with infinite value */
    SCIP_Real             glbmaxactivity;     /**< maximal value w.r.t. the variable's global bounds for the constraint's
                                               *   activity, ignoring the coefficients contributing with infinite value */
    SCIP_Real             lastglbminactivity; /**< last global minimal activity which was computed by complete summation
                                               *   over all contributing values */
    SCIP_Real             lastglbmaxactivity; /**< last global maximal activity which was computed by complete summation
                                               *   over all contributing values */
    SCIP_Real             maxactdelta;        /**< maximal activity contribution of a single variable, or SCIP_INVALID if invalid */
    SCIP_VAR*             maxactdeltavar;     /**< variable with maximal activity contribution, or NULL if invalid */
    uint64_t              possignature;       /**< bit signature of coefficients that may take a positive value */
    uint64_t              negsignature;       /**< bit signature of coefficients that may take a negative value */
    SCIP_ROW*             row;                /**< LP row, if constraint is already stored in LP row format */
    SCIP_NLROW*           nlrow;              /**< NLP row, if constraint has been added to NLP relaxation */
    SCIP_VAR**            vars;               /**< variables of constraint entries */
    SCIP_Real*            vals;               /**< coefficients of constraint entries */
    SCIP_EVENTDATA**      eventdata;          /**< event data for bound change events of the variables */
    int                   minactivityneginf;  /**< number of coefficients contributing with neg. infinite value to minactivity */
    int                   minactivityposinf;  /**< number of coefficients contributing with pos. infinite value to minactivity */
    int                   maxactivityneginf;  /**< number of coefficients contributing with neg. infinite value to maxactivity */
    int                   maxactivityposinf;  /**< number of coefficients contributing with pos. infinite value to maxactivity */
    int                   minactivityneghuge; /**< number of coefficients contributing with huge neg. value to minactivity */
    int                   minactivityposhuge; /**< number of coefficients contributing with huge pos. value to minactivity */
    int                   maxactivityneghuge; /**< number of coefficients contributing with huge neg. value to maxactivity */
    int                   maxactivityposhuge; /**< number of coefficients contributing with huge pos. value to maxactivity */
    int                   glbminactivityneginf;/**< number of coefficients contrib. with neg. infinite value to glbminactivity */
    int                   glbminactivityposinf;/**< number of coefficients contrib. with pos. infinite value to glbminactivity */
    int                   glbmaxactivityneginf;/**< number of coefficients contrib. with neg. infinite value to glbmaxactivity */
    int                   glbmaxactivityposinf;/**< number of coefficients contrib. with pos. infinite value to glbmaxactivity */
    int                   glbminactivityneghuge;/**< number of coefficients contrib. with huge neg. value to glbminactivity */
    int                   glbminactivityposhuge;/**< number of coefficients contrib. with huge pos. value to glbminactivity */
    int                   glbmaxactivityneghuge;/**< number of coefficients contrib. with huge neg. value to glbmaxactivity */
    int                   glbmaxactivityposhuge;/**< number of coefficients contrib. with huge pos. value to glbmaxactivity */
    int                   varssize;           /**< size of the vars- and vals-arrays */
    int                   nvars;              /**< number of nonzeros in constraint */
    int                   nbinvars;           /**< the number of binary variables in the constraint, only valid after
                                               *   sorting in stage >= SCIP_STAGE_INITSOLVE
                                               */
    unsigned int          boundstightened:2;  /**< is constraint already propagated with bound tightening? */
    unsigned int          rangedrowpropagated:2; /**< did we perform ranged row propagation on this constraint?
                                                  *   (0: no, 1: yes, 2: with potentially adding artificial constraint */
    unsigned int          validmaxabsval:1;   /**< is the maximum absolute value valid? */
    unsigned int          validminabsval:1;   /**< is the minimum absolute value valid? */
    unsigned int          validactivities:1;  /**< are the activity bounds (local and global) valid? */
    unsigned int          validminact:1;      /**< is the local minactivity valid? */
    unsigned int          validmaxact:1;      /**< is the local maxactivity valid? */
    unsigned int          validglbminact:1;   /**< is the global minactivity valid? */
    unsigned int          validglbmaxact:1;   /**< is the global maxactivity valid? */
    unsigned int          presolved:1;        /**< is constraint already presolved? */
    unsigned int          removedfixings:1;   /**< are all fixed variables removed from the constraint? */
    unsigned int          validsignature:1;   /**< is the bit signature valid? */
    unsigned int          changed:1;          /**< was constraint changed since last aggregation round in preprocessing? */
    unsigned int          normalized:1;       /**< is the constraint in normalized form? */
    unsigned int          upgradetried:1;     /**< was the constraint already tried to be upgraded? */
    unsigned int          upgraded:1;         /**< is the constraint upgraded and will it be removed after preprocessing? */
    unsigned int          indexsorted:1;      /**< are the constraint's variables sorted by type and index? */
    unsigned int          merged:1;           /**< are the constraint's equal variables already merged? */
    unsigned int          cliquesadded:1;     /**< were the cliques of the constraint already extracted? */
    unsigned int          implsadded:1;       /**< were the implications of the constraint already extracted? */
    unsigned int          coefsorted:1;       /**< are variables sorted by type and their absolute activity delta? */
    unsigned int          varsdeleted:1;      /**< were variables deleted after last cleanup? */
    unsigned int          hascontvar:1;       /**< does the constraint contain at least one continuous variable? */
    unsigned int          hasnonbinvar:1;     /**< does the constraint contain at least one non-binary variable? */
    unsigned int          hasnonbinvalid:1;   /**< is the information stored in hasnonbinvar and hascontvar valid? */
    unsigned int          checkabsolute:1;    /**< should the constraint be checked w.r.t. an absolute feasibilty tolerance? */
 };

  SCIP_RETCODE transformSols(
    SCIP*                 scip                /**< SCIP data structure */
    )
 {
    SCIP_SOL** sols;
    SCIP_SOL** scipsols;
    SCIP_SOL* sol;
    SCIP_Real* solvals;
    SCIP_Bool* solvalset;
    SCIP_Bool added;
    SCIP_Longint oldnsolsfound;
    int nsols;
    int ntransvars;
    int naddedsols;
    int s;
 
    nsols = SCIPgetNSols(scip);
    oldnsolsfound = scip->primal->nsolsfound;
 
    /* no solution to transform */
    if( nsols == 0 )
       return SCIP_OKAY;
 
    SCIPdebugMsg(scip, "try to transfer %d original solutions into the transformed problem space\n", nsols);
 
    ntransvars = scip->transprob->nvars;
    naddedsols = 0;
 
    /* It might happen, that the added transferred solution does not equal the corresponding original one, which might
     * result in the array of solutions being changed.  Thus we temporarily copy the array and traverse it in reverse
     * order to ensure that the regarded solution in the copied array was not already freed when new solutions were added
     * and the worst solutions were freed.
     */
    scipsols = SCIPgetSols(scip);
    SCIP_CALL( SCIPduplicateBufferArray(scip, &sols, scipsols, nsols) );
    SCIP_CALL( SCIPallocBufferArray(scip, &solvals, ntransvars) );
    SCIP_CALL( SCIPallocBufferArray(scip, &solvalset, ntransvars) );
 
    for( s = nsols-1; s >= 0; --s )
    {
       sol = sols[s];
 
       /* it might happen that a transferred original solution has a better objective than its original counterpart
        * (e.g., because multi-aggregated variables get another value, but the solution is still feasible);
        * in this case, it might happen that the solution is not an original one and we just skip this solution
        */
       if( !SCIPsolIsOriginal(sol) )
          continue;
 
       SCIP_CALL( SCIPprimalTransformSol(scip->primal, sol, scip->mem->probmem, scip->set, scip->messagehdlr, scip->stat,
             scip->origprob, scip->transprob, scip->tree, scip->reopt, scip->lp, scip->eventqueue, scip->eventfilter, solvals,
             solvalset, ntransvars, &added) );
 
       if( added )
          ++naddedsols;
    }
 
    if( naddedsols > 0 )
    {
       SCIPverbMessage(scip, SCIP_VERBLEVEL_HIGH, NULL,
          "transformed %d/%d original solutions to the transformed problem space\n",
          naddedsols, nsols);
 
       scip->stat->nexternalsolsfound += scip->primal->nsolsfound - oldnsolsfound;
    }
 
    SCIPfreeBufferArray(scip, &solvalset);
    SCIPfreeBufferArray(scip, &solvals);
    SCIPfreeBufferArray(scip, &sols);
 
    return SCIP_OKAY;
 }

 SCIP_RETCODE initSolve(
    SCIP*                 scip,               /**< SCIP data structure */
    SCIP_Bool             solved              /**< is problem already solved? */
    )
 {
    assert(scip != NULL);
    assert(scip->mem != NULL);
    assert(scip->set != NULL);
    assert(scip->stat != NULL);
    assert(scip->nlp == NULL);
    assert(scip->set->stage == SCIP_STAGE_PRESOLVED);
 
    /**@todo check whether other methodscan be skipped if problem has been solved */
    /* if problem has been solved, several time consuming tasks must not be performed */
    if( !solved )
    {
       /* reset statistics for current branch and bound run */
       SCIPstatResetCurrentRun(scip->stat, scip->set, scip->transprob, scip->origprob, solved);
       SCIPstatEnforceLPUpdates(scip->stat);
 
       /* LP is empty anyway; mark empty LP to be solved and update validsollp counter */
       SCIP_CALL( SCIPlpReset(scip->lp, scip->mem->probmem, scip->set, scip->stat, scip->eventqueue, scip->eventfilter) );
 
       /* update upper bound and cutoff bound due to objective limit in primal data */
       SCIP_CALL( SCIPprimalUpdateObjlimit(scip->primal, scip->mem->probmem, scip->set, scip->stat, scip->eventfilter,
        scip->eventqueue, scip->transprob, scip->origprob, scip->tree, scip->reopt, scip->lp) );
    }
 
    /* switch stage to INITSOLVE */
    scip->set->stage = SCIP_STAGE_INITSOLVE;
 
    /* initialize NLP if there are nonlinearities */
    if( scip->transprob->nlpenabled && !scip->set->nlp_disable )
    {
       SCIPdebugMsg(scip, "constructing empty NLP\n");
 
       SCIP_CALL( SCIPnlpCreate(&scip->nlp, scip->mem->probmem, scip->set, scip->stat, SCIPprobGetName(scip->transprob), scip->transprob->nvars) );
       assert(scip->nlp != NULL);
 
       SCIP_CALL( SCIPnlpAddVars(scip->nlp, scip->mem->probmem, scip->set, scip->transprob->nvars, scip->transprob->vars) );
 
       /* Adjust estimation of external memory: SCIPtransformProb() estimated the memory used for the LP-solver. As a
        * very crude approximation just double this number. Only do this once in the first run. */
       if( scip->set->misc_estimexternmem && scip->stat->nruns <= 1 )
       {
          scip->stat->externmemestim *= 2;
          SCIPdebugMsg(scip, "external memory usage estimated to %" SCIP_LONGINT_FORMAT " byte\n", scip->stat->externmemestim);
       }
    }
 
    /* possibly create visualization output file */
    SCIP_CALL( SCIPvisualInit(scip->stat->visual, scip->mem->probmem, scip->set, scip->messagehdlr) );
 
    /* initialize solution process data structures */
    SCIP_CALL( SCIPpricestoreCreate(&scip->pricestore) );
    SCIP_CALL( SCIPsepastoreCreate(&scip->sepastore, scip->mem->probmem, scip->set) );
    SCIP_CALL( SCIPsepastoreCreate(&scip->sepastoreprobing, scip->mem->probmem, scip->set) );
    SCIP_CALL( SCIPcutpoolCreate(&scip->cutpool, scip->mem->probmem, scip->set, scip->set->sepa_cutagelimit, TRUE) );
    SCIP_CALL( SCIPcutpoolCreate(&scip->delayedcutpool, scip->mem->probmem, scip->set, scip->set->sepa_cutagelimit, FALSE) );
    SCIP_CALL( SCIPtreeCreateRoot(scip->tree, scip->reopt, scip->mem->probmem, scip->set, scip->stat, scip->eventfilter, scip->eventqueue,
          scip->lp) );
 
    /* update dual bound of the root node if a valid dual bound is at hand */
    if( scip->transprob->dualbound < SCIP_INVALID )
    {
       SCIP_Real internobjval = SCIPprobInternObjval(scip->transprob, scip->origprob, scip->set, scip->transprob->dualbound);
 
       scip->stat->lastlowerbound = internobjval;
 
       SCIPnodeUpdateLowerbound(SCIPtreeGetRootNode(scip->tree), scip->stat, scip->set, scip->tree, scip->transprob,
          scip->origprob, internobjval);
    }
 
    /* try to transform original solutions to the transformed problem space */
    if( scip->set->misc_transorigsols )
    {
       SCIP_CALL( transformSols(scip) );
    }
 
    /* inform the transformed problem that the branch and bound process starts now */
    SCIP_CALL( SCIPprobInitSolve(scip->transprob, scip->set) );
 
    /* transform the decomposition storage */
    SCIP_CALL( SCIPtransformDecompstore(scip) );
 
    /* inform plugins that the branch and bound process starts now */
    SCIP_CALL( SCIPsetInitsolPlugins(scip->set, scip->mem->probmem, scip->stat) );
 
    /* remember number of constraints */
    SCIPprobMarkNConss(scip->transprob);
 
    /* if all variables are known, calculate a trivial primal bound by setting all variables to their worst bound */
    if( scip->set->nactivepricers == 0 )
    {
       SCIP_VAR* var;
       SCIP_Real obj;
       SCIP_Real objbound;
       SCIP_Real bd;
       int v;
 
       objbound = 0.0;
       for( v = 0; v < scip->transprob->nvars && !SCIPsetIsInfinity(scip->set, objbound); ++v )
       {
          var = scip->transprob->vars[v];
          obj = SCIPvarGetObj(var);
          if( !SCIPsetIsZero(scip->set, obj) )
          {
             bd = SCIPvarGetWorstBoundGlobal(var);
             if( SCIPsetIsInfinity(scip->set, REALABS(bd)) )
                objbound = SCIPsetInfinity(scip->set);
             else
                objbound += obj * bd;
          }
       }
 
       /* adjust primal bound, such that solution with worst bound may be found */
       if( objbound + SCIPsetCutoffbounddelta(scip->set) != objbound ) /*lint !e777*/
          objbound += SCIPsetCutoffbounddelta(scip->set);
       /* if objbound is very large, adding the cutoffbounddelta may not change the number; in this case, we are using
        * SCIPnextafter to ensure that the cutoffbound is really larger than the best possible solution value
        */
       else
          objbound = SCIPnextafter(objbound, SCIP_REAL_MAX);
 
       /* update cutoff bound */
       if( !SCIPsetIsInfinity(scip->set, objbound) && SCIPsetIsLT(scip->set, objbound, scip->primal->cutoffbound) )
       {
          /* adjust cutoff bound */
          SCIP_CALL( SCIPprimalSetCutoffbound(scip->primal, scip->mem->probmem, scip->set, scip->stat, scip->eventfilter,
                scip->eventqueue, scip->transprob, scip->origprob, scip->tree, scip->reopt, scip->lp, objbound, FALSE) );
       }
    }
 
    /* switch stage to SOLVING */
    scip->set->stage = SCIP_STAGE_SOLVING;
 
    return SCIP_OKAY;
 }
 
//  /** frees solution process data structures */
//  static
//  SCIP_RETCODE freeSolve(
//     SCIP*                 scip,               /**< SCIP data structure */
//     SCIP_Bool             restart             /**< was this free solve call triggered by a restart? */
//     )
//  {
//     assert(scip != NULL);
//     assert(scip->mem != NULL);
//     assert(scip->set != NULL);
//     assert(scip->stat != NULL);
//     assert(scip->set->stage == SCIP_STAGE_SOLVING || scip->set->stage == SCIP_STAGE_SOLVED);
 
//     /* mark that we are currently restarting */
//     if( restart )
//     {
//        scip->stat->inrestart = TRUE;
 
//        /* copy the current dual bound into the problem data structure such that it can be used initialize the new search
//         * tree
//         */
//        SCIPprobUpdateDualbound(scip->transprob, SCIPgetDualbound(scip));
//     }
 
//     /* remove focus from the current focus node */
//     if( SCIPtreeGetFocusNode(scip->tree) != NULL )
//     {
//        SCIP_NODE* node = NULL;
//        SCIP_Bool cutoff;
 
//        SCIP_CALL( SCIPnodeFocus(&node, scip->mem->probmem, scip->set, scip->messagehdlr, scip->stat, scip->transprob,
//              scip->origprob, scip->primal, scip->tree, scip->reopt, scip->lp, scip->branchcand, scip->conflict,
//              scip->conflictstore, scip->eventfilter, scip->eventqueue, scip->cliquetable, &cutoff, FALSE, TRUE) );
//        assert(!cutoff);
//     }
 
//     /* switch stage to EXITSOLVE */
//     scip->set->stage = SCIP_STAGE_EXITSOLVE;
 
//     /* cleanup the conflict storage */
//     SCIP_CALL( SCIPconflictstoreClean(scip->conflictstore, scip->mem->probmem, scip->set, scip->stat, scip->transprob, scip->reopt) );
 
//     /* inform plugins that the branch and bound process is finished */
//     SCIP_CALL( SCIPsetExitsolPlugins(scip->set, scip->mem->probmem, scip->stat, restart) );
 
//     /* free the NLP, if there is one, and reset the flags indicating nonlinearity */
//     if( scip->nlp != NULL )
//     {
//        SCIP_CALL( SCIPnlpFree(&scip->nlp, scip->mem->probmem, scip->set, scip->stat, scip->eventqueue, scip->lp) );
//     }
//     scip->transprob->nlpenabled = FALSE;
 
//     /* clear the LP, and flush the changes to clear the LP of the solver */
//     SCIP_CALL( SCIPlpReset(scip->lp, scip->mem->probmem, scip->set, scip->stat, scip->eventqueue, scip->eventfilter) );
//     SCIPlpInvalidateRootObjval(scip->lp);
 
//     /* resets the debug environment */
//     SCIP_CALL( SCIPdebugReset(scip->set) ); /*lint !e506 !e774*/
 
//     /* clear all row references in internal data structures */
//     SCIP_CALL( SCIPcutpoolClear(scip->cutpool, scip->mem->probmem, scip->set, scip->lp) );
//     SCIP_CALL( SCIPcutpoolClear(scip->delayedcutpool, scip->mem->probmem, scip->set, scip->lp) );
 
//     /* we have to clear the tree prior to the problem deinitialization, because the rows stored in the forks and
//      * subroots have to be released
//      */
//     SCIP_CALL( SCIPtreeClear(scip->tree, scip->mem->probmem, scip->set, scip->stat, scip->eventfilter, scip->eventqueue, scip->lp) );
 
//     SCIPexitSolveDecompstore(scip);
 
//     /* deinitialize transformed problem */
//     SCIP_CALL( SCIPprobExitSolve(scip->transprob, scip->mem->probmem, scip->set, scip->eventqueue, scip->lp, restart) );
 
//     /* free solution process data structures */
//     SCIP_CALL( SCIPcutpoolFree(&scip->cutpool, scip->mem->probmem, scip->set, scip->lp) );
//     SCIP_CALL( SCIPcutpoolFree(&scip->delayedcutpool, scip->mem->probmem, scip->set, scip->lp) );
//     SCIP_CALL( SCIPsepastoreFree(&scip->sepastoreprobing, scip->mem->probmem) );
//     SCIP_CALL( SCIPsepastoreFree(&scip->sepastore, scip->mem->probmem) );
//     SCIP_CALL( SCIPpricestoreFree(&scip->pricestore) );
 
//     /* possibly close visualization output file */
//     SCIPvisualExit(scip->stat->visual, scip->set, scip->messagehdlr);
 
//     /* reset statistics for current branch and bound run */
//     if( scip->stat->status == SCIP_STATUS_INFEASIBLE || scip->stat->status == SCIP_STATUS_OPTIMAL || scip->stat->status == SCIP_STATUS_UNBOUNDED || scip->stat->status == SCIP_STATUS_INFORUNBD )
//        SCIPstatResetCurrentRun(scip->stat, scip->set, scip->transprob, scip->origprob, TRUE);
//     else
//        SCIPstatResetCurrentRun(scip->stat, scip->set, scip->transprob, scip->origprob, FALSE);
 
//     /* switch stage to TRANSFORMED */
//     scip->set->stage = SCIP_STAGE_TRANSFORMED;
 
//     /* restart finished */
//     assert( ! restart || scip->stat->inrestart );
//     scip->stat->inrestart = FALSE;
 
//     return SCIP_OKAY;
//  }