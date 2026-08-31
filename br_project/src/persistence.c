#include "persistence.h"
#include <stddef.h>
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

static int calculate_row_payload_size(const Column *col, uint32_t column_count, uint32_t  *total_row_payload){
    //Null guard
    if (col == NULL || total_row_payload == NULL){
        return -1;
    }

    uint32_t row_accumulation = 0;
    for (uint32_t i = 0; i < column_count; i++){
        switch (col[i].type_of_column) {
            case COLUMN_TYPE_INT:
                row_accumulation += sizeof(int32_t);
                break;
            case COLUMN_TYPE_STRING:
                row_accumulation += col[i].column_max_bytes;
                break;
            default:
                return -1;
        }
    }
    *total_row_payload = row_accumulation;
    return 0;
}

int db_save(Database *db, const char *filepath) {

    //Declaring File 
    FILE *writeFile = fopen(filepath, "wb");
    if (writeFile == NULL) {
        return -1; // write has failed | no go to as fclose(NULL) is undefined
    }

    int status = 0;

    size_t tableWrite = fwrite(&db->table_count, sizeof(uint32_t), 1, writeFile);
    if (tableWrite != 1){
        status = -1;
        goto cleanup;
    }

    //Iterate through the table count and write information into file  | go to cleanup if we need to exit early
    for (uint32_t i = 0; i < db->table_count; i++){
        size_t tableNameWrite = fwrite(db->database_table[i].table_name, sizeof(db->database_table[i].table_name), 1, writeFile);
        if (tableNameWrite != 1){
            status = -1;
            goto cleanup;
        }

        size_t tableColumnWrite = fwrite(db->database_table[i].table_column, sizeof(db->database_table[i].table_column[0]), db->database_table[i].column_count, writeFile);
        if (tableColumnWrite != db->database_table[i].column_count){
            status = -1;
            goto cleanup;
        }
        
        size_t tableColCountWrite = fwrite(&db->database_table[i].column_count, sizeof(uint32_t), 1, writeFile);
        if (tableColCountWrite != 1){
            status = -1;
            goto cleanup;
        }

        uint32_t computed_payload;
        int payload_success = calculate_row_payload_size(db->database_table[i].table_column, db->database_table[i].column_count, &computed_payload);
        if (payload_success != 0){
            status = -1;
            goto cleanup;
        }

        int bst_helper_success = bst_write_helper(db->database_table[i].table_rows.root, writeFile, computed_payload);
        if (bst_helper_success != 0){
            status = -1;
            goto cleanup;
        }
    }

    //Handle early exit or success
    cleanup:
        fclose(writeFile);
        return status;
}

