#include <cstddef>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"


//Static helpers


//Main Functions
int db_init(Database *db){
    //Null guard
    if(db == NULL){
        return -1;
    }
    //Set items for the database
    db->table_count = 0;
    trie_init(&db->table_index);
    stack_init(&db->table_operation_history);
    for (int i=0; i<DATABASE_MAX_TABLE_AMT; i++){
        db->database_table[i].column_count = 0;
        memset(db->database_table[i].table_name, 0, MAX_NAME_LENGTH);
        bst_init(&db->database_table[i].table_rows);
    }
    return 0;
}

int db_create_table(Database *db, const char *name, const Column *table_cols, uint32_t col_count){
    //Null guard(s)
    if(db == NULL || name == NULL || table_cols == NULL){
        return -1;
    }
    //Verify name length isn't too long
    if (strlen(name) > MAX_NAME_LENGTH){
        return -1;
    }
    //Iterate through the database to find an empty slot
    for (int i=0; i<DATABASE_MAX_TABLE_AMT; i++){
        //Empty spot found
        if(db->database_table[i].table_name[0] == '\0'){
            //Need to copy the columns into destination
            memcpy(db->database_table[i].table_column,table_cols, sizeof(Column) * col_count);
            //insert name 
            trie_insert(&db->table_index, name);
            strncpy(db->database_table[i].table_name, name, MAX_NAME_LENGTH);
            db->table_count++;
            db->database_table[i].column_count = col_count;
            //Successful creation
            return 0;
        }
    }
    //Table is full
    return -1;
}

int db_drop_table(Database *db, const char *name){
    //Null guards
    if(db == NULL || name == NULL){
        return -1;
    }
    //Call find table function
    Table *table_to_drop = db_find_table(db, name);
    if (table_to_drop == NULL){
        return -1;
    }
    //Perform actions to drop the table
    table_to_drop.table_name[0] = '\0';
    table_to_drop.column_count = 0;
    db->table_count--;
    bst_delete_tree(&table_to_drop->table_rows);
    trie_delete_key(&table_index, name);
    return 0;
}

Table *db_find_table(Database *db, const char *name){
    //Null guards
    if(db == NULL || name == NULL){
        return NULL;
    }
    //Check the trie to see if the name exists
    bool existing_name = trie_search(&db->table_index, name);
    if (existing_name){
        //Iterate through the database table to find the name
        for (int i=0; i<DATABASE_MAX_TABLE_AMT; i++){
            //If the table name is found return it
            if (strcmp(db->database_table[i].table_name, name) == 0){
                return &db->database_table[i];
            }
        }
    }
    //doesn't exist in the trie
    return NULL;
}

