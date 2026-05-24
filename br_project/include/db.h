#ifndef BEDROCK_DB_H
#define BEDROCK_DB_H
#include <stdint.h>
#include <stdbool.h>
#include "stack.h"
#include "trie.h"
#include "bst.h"
#define DATABASE_MAX_TABLE_AMT 32
#define TABLE_MAX_COLS 8
#define MAX_NAME_LENGTH 32


//Column Type Enum
typedef enum {
    COLUMN_TYPE_INT,
    COLUMN_TYPE_STRING
}ColumnType;

typedef struct Column{
    char column_name [MAX_NAME_LENGTH];
    ColumnType type_of_column;
    bool is_column_nullable;
}Column;

typedef struct Table{
    char table_name [MAX_NAME_LENGTH];
    Column table_column [TABLE_MAX_COLS];
    uint32_t column_count;
    BST table_rows;
}Table;

typedef struct Database{
    Table database_table [DATABASE_MAX_TABLE_AMT];
    uint32_t table_count;
    Trie table_index;
    Stack table_operation_history;
}Database;

//Database Functions
int db_init(Database *db);
int db_create_table(Database *db, char const *name, const Column *table_cols, uint32_t col_count);
int db_drop_table(Database *db, const char *name);
Table *db_find_table(Database *db, const char *name);


//Table Functions
int db_add_column(Table *t, Column *col);
int db_insert_row(Table *t, int32_t key, void* payload);
BSTNode* db_search_row(Table *t, int32_t key);
int db_delete_row(Table *t, int32_t key);
#endif //BEDROCK_DB_H
