#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip/misc.h>

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

    SCIP_CALL( SCIPreadMps(scip,
        reader,
        argv[1],
        result,
        NULL, NULL,
        // varnames, consnames,
        varnamessize, consnamessize, nvarnames, nconsnames
    ));

    printf("Mps file: %s parsed ... \n", argv[1]);

    SCIP_CALL(SCIPsolve(scip));

    // Free alocated memory
    //---------------------
    free(result);
    free(reader);
    free(varnamessize);
    free(consnamessize);
    free(nvarnames);
    free(nconsnames);

    return 0;
}