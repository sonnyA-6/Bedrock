#include "persistence.h"
#include <stdint.h>
#include <stdio.h>

typedef struct row_recon{
    int32_t key;
    void *payload;
}row_recon;

static int bst_write_helper(BSTNode *node, FILE *file, uint32_t payload_size){
    // Null guard | Nothing to write
    if (node == NULL){
        return 0;
    }
    int recurseLt = bst_write_helper(node->left, file, payload_size);
    if (recurseLt != 0){
        return recurseLt; // Bail immediately
    }

    // Complete the write(s): key, payload, and payload byte | Bail if the size is different
    size_t keyWrite = fwrite(&node->data, sizeof(int32_t), 1, file);
    if (keyWrite != 1){
        return -1;
    }

    size_t payloadWrite = fwrite(&payload_size, sizeof(uint32_t), 1, file);
    if (payloadWrite != 1){
        return -1;
    }
    
    size_t payloadByteWrite = fwrite(node->payload, payload_size, 1, file); 
    if (payloadByteWrite != 1){
        return -1;
    }

    int recurseRt = bst_write_helper(node->right, file, payload_size);
    if (recurseRt != 0){
        return recurseRt; // Bail immediately
    }

    //Write was a success
    return 0;

}

static int bst_reconstruction_helper(BST *tree, const row_recon *array, int32_t low_bound, int32_t high_bound);
