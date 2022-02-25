#include <scip/scip.h>
#include <scip/type_lp.h>
#include <cvector.h>

typedef struct subRootNode SUBROOTNODE;
struct subRootNode{
    Node* parent;
    SCIP_ROW** newRows;
};

typedef struct SUBROOTNOTE subRootNode{
    SCIP_LPSOLSTAT* lpSolstat;
    SCIP_Real lowerbound;
    int arraypos;
}

struct Node{
    SCIP_Longint number;
    int depth;
    union{
        SUBROOTNODE*    subRootNode;
    } data;
    bool isRoot;
};

struct tree{
    cvector_vector_type(Node*) nodes;
    Node** leafnodes;
};