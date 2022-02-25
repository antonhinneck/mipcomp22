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

//   static
//  SCIP_RETCODE createRow(
//    SCIP*                 scip,               /**< SCIP data structure */
//    SCIP_CONS*            cons                /**< linear constraint */
//    )
//    {
//    SCIP_CONSDATA* consdata;

//    assert(scip != NULL);
//    assert(cons != NULL);

//    consdata = SCIPconsGetData(cons);
//    assert(consdata != NULL);
//    assert(consdata->row == NULL);

//    SCIP_CALL( SCIPcreateEmptyRowCons(scip, &consdata->row, cons, SCIPconsGetName(cons), consdata->lhs, consdata->rhs,
//          SCIPconsIsLocal(cons), SCIPconsIsModifiable(cons), SCIPconsIsRemovable(cons)) );

//    SCIP_CALL( SCIPaddVarsToRow(scip, consdata->row, consdata->nvars, consdata->vars, consdata->vals) );
//    return SCIP_OKAY;
//    }


// /** adds linear constraint as cut to the LP */
//  static
//  SCIP_RETCODE addRelaxation(
//    SCIP*                 scip,               /**< SCIP data structure */
//    SCIP_CONS*            cons,               /**< linear constraint */
//    SCIP_Bool*            cutoff              /**< pointer to store whether a cutoff was found */
//    )
//    {
//    SCIP_CONSDATA* consdata;

//    assert(scip != NULL);
//    assert(cons != NULL);

//    consdata = SCIPconsGetData(cons);
//    assert(consdata != NULL);

//    if( consdata->row == NULL )
//    {
//       if( !SCIPconsIsModifiable(cons) )
//       {
//          /* replace all fixed variables by active counterparts, as we have no chance to do this anymore after the row has been added to the LP
//          * removing this here will make test cons/linear/fixedvar.c fail (as of 2018-12-03)
//          */
//       //  SCIP_CALL( applyFixings(scip, cons, cutoff) );
//       //  if( *cutoff )
//       //     return SCIP_OKAY;
//       }

//       /* convert consdata object into LP row */
//       SCIP_CALL( createRow(scip, cons) );
//    }
//    assert(consdata->row != NULL);

//    // if( consdata->nvars == 0 )
//    // {
//    // SCIPdebugMsg(scip, "Empty linear constraint enters LP: <%s>\n", SCIPconsGetName(cons));
//    // }
//    /* insert LP row as cut */
//    if( !SCIProwIsInLP(consdata->row) )
//    {
//    //    SCIPdebugMsg(scip, "adding relaxation of linear constraint <%s>: ", SCIPconsGetName(cons));
//    //    SCIPdebug( SCIP_CALL( SCIPprintRow(scip, consdata->row, NULL)) );
//       /* if presolving is turned off, the row might be trivial */
//       if ( ! SCIPisInfinity(scip, -consdata->lhs) || ! SCIPisInfinity(scip, consdata->rhs) )
//       {
//          printf("Consdata nvars = 1. \n");
//          SCIP_CALL( SCIPaddRow(scip, consdata->row, FALSE, cutoff) );
//          printf("Consdata nvars = 2. \n");
//       }
// #ifndef NDEBUG
//       else
//       {
//          int pr;
//          int cr;
//          SCIP_CALL( SCIPgetIntParam(scip, "presolving/maxrounds", &pr) );
//          SCIP_CALL( SCIPgetIntParam(scip, "constraints/linear/maxprerounds", &cr) );
//          assert( pr == 0 || cr == 0 );
//       }
// #endif
//    }

//    return SCIP_OKAY;
// }


static
SCIP_RETCODE initLP(
   BMS_BLKMEM*           blkmem,             /**< block memory buffers */
   SCIP_SET*             set,                /**< global SCIP settings */
   SCIP_STAT*            stat,               /**< dynamic problem statistics */
   SCIP_PROB*            transprob,          /**< transformed problem */
   SCIP_PROB*            origprob,           /**< original problem */
   SCIP_TREE*            tree,               /**< branch and bound tree */
   SCIP_REOPT*           reopt,              /**< reoptimization data structure */
   SCIP_LP*              lp,                 /**< LP data */
   //SCIP_PRICESTORE*      pricestore,         /**< pricing storage */
   SCIP_SEPASTORE*       sepastore,          /**< separation storage */
   SCIP_CUTPOOL*         cutpool,            /**< global cut pool */
   SCIP_BRANCHCAND*      branchcand,         /**< branching candidate storage */
   SCIP_EVENTQUEUE*      eventqueue,         /**< event queue */
   SCIP_EVENTFILTER*     eventfilter,        /**< global event filter */
   SCIP_CLIQUETABLE*     cliquetable,        /**< clique table data structure */
   SCIP_Bool             root,               /**< is this the initial root LP? */
   SCIP_Bool*            cutoff              /**< pointer to store whether the node can be cut off */
   )
{
   SCIP_VAR* var;
   int oldnvars = 0;
   int v;

   assert(set != NULL);
   assert(transprob != NULL);
   assert(lp != NULL);
   assert(cutoff != NULL);

   *cutoff = FALSE;

   /* at the root node, we have to add the initial variables as columns */
   if( root )
   {
      assert(SCIPlpGetNCols(lp) == 0);
      assert(SCIPlpGetNRows(lp) == 0);
      assert(lp->nremovablecols == 0);
      assert(lp->nremovablerows == 0);

      /* store number of variables for later */
      oldnvars = transprob->nvars;
      
      /* inform pricing storage, that LP is now filled with initial data */
      //SCIPpricestoreStartInitialLP(pricestore);
      
      /* add all initial variables to LP */
      //SCIPsetDebugMsg(set, "init LP: initial columns\n");
      for( v = 0; v < transprob->nvars && !(*cutoff); ++v )
      {
         
         var = transprob->vars[v];
         assert(SCIPvarGetProbindex(var) >= 0);
         printf("Val %d\n", transprob->vars[2]->varstatus);
         // if( SCIPvarIsInitial(var) )
         // {
         //    SCIP_CALL( SCIPpricestoreAddVar(pricestore, blkmem, set, eventqueue, lp, var, 0.0, TRUE) );
         // }

         /* check for empty domains (necessary if no presolving was performed) */
         // if( SCIPsetIsGT(set, SCIPvarGetLbLocal(var), SCIPvarGetUbLocal(var)) )
         //    *cutoff = TRUE;
      }
      assert(lp->nremovablecols == 0);
      //SCIP_CALL( SCIPpricestoreApplyVars(pricestore, blkmem, set, stat, eventqueue, transprob, tree, lp) );

      /* inform pricing storage, that initial LP setup is now finished */
      //SCIPpricestoreEndInitialLP(pricestore);
   }

   if( *cutoff )
      return SCIP_OKAY;

   /* put all initial constraints into the LP */
   /* @todo check whether we jumped through the tree */
   
   SCIP_CALL(SCIPsepastoreCreate(&sepastore, blkmem, set));
   SCIP_CALL(SCIPcutpoolCreate(&cutpool, blkmem, set, 1,  1));
   SCIP_CALL(SCIPreoptCreate(&reopt, set, blkmem));
   assert(sepastore != NULL);
   assert(cutpool != NULL);
   assert(cliquetable != NULL);
   assert(reopt != NULL);
   assert(tree != NULL);
   assert(branchcand != NULL);
   assert(eventqueue != NULL);
   assert(stat != NULL);
   assert(eventfilter != NULL);
   assert(cliquetable != NULL);
   assert(origprob != NULL);
   assert(transprob != NULL);
   SCIP_CALL( SCIPinitConssLP(blkmem, set, sepastore, cutpool, stat, transprob, origprob, tree, reopt, lp, branchcand, eventqueue,
         eventfilter, cliquetable, root, TRUE, cutoff) );
   printf("Val 2%d\n", transprob->vars[2]->varstatus);
   /* putting all initial constraints into the LP might have added new variables */
   if( root && !(*cutoff) && transprob->nvars > oldnvars )
   {
      /* inform pricing storage, that LP is now filled with initial data */
      //SCIPpricestoreStartInitialLP(pricestore);

      /* check all initial variables */
      for( v = 0; v < transprob->nvars && !(*cutoff); ++v )
      {
         var = transprob->vars[v];
         assert(SCIPvarGetProbindex(var) >= 0);

         // if( SCIPvarIsInitial(var) && (SCIPvarGetStatus(var) != SCIP_VARSTATUS_COLUMN || !SCIPcolIsInLP(SCIPvarGetCol(var))) )
         // {
         //    SCIP_CALL( SCIPpricestoreAddVar(pricestore, blkmem, set, eventqueue, lp, var, 0.0, TRUE) );
         // }

         /* check for empty domains (necessary if no presolving was performed) */
         if( SCIPsetIsGT(set, SCIPvarGetLbLocal(var), SCIPvarGetUbLocal(var)) )
            *cutoff = TRUE;
      }
      assert(lp->nremovablecols == 0);
      // SCIP_CALL( SCIPpricestoreApplyVars(pricestore, blkmem, set, stat, eventqueue, transprob, tree, lp) );

      // /* inform pricing storage, that initial LP setup is now finished */
      // SCIPpricestoreEndInitialLP(pricestore);
   }

   return SCIP_OKAY;
}