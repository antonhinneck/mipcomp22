 
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

typedef struct SCIP_ConsData CONSDATA;