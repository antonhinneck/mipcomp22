#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <scip/scip.h>

int main(int argc, char *argv[]){
    
    assert(argc == 2 && "ERROR: A single MPS file is expected as a command line argument.\n");
    if( !(access(argv[1], F_OK) == 0) ){
        printf("ERROR: MPS file specified (%s) does not exist.\n", argv[1]);
        return 0;
    }
    
    printf("Mps file: %s found!\n", argv[1]);
    return 0;
}