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
// - init a table
// - destroy a table
// - create table
// - drop a table
// - search for a table by name


//Table Functions
// - add a column
// - insert a row
// - search for a row
// - delete a row
#endif //BEDROCK_DB_H
