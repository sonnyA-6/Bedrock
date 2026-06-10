#include "persistence.h"
#include <stdio.h>

typedef struct row_recon{
    int32_t key;
    void *payload;
}row_recon;

static int bst_write_helper(BSTNode *node, FILE *file);
static int bst_reconstruction_helper(BST *tree, const row_recon *array, int32_t low_bound, int32_t high_bound);
