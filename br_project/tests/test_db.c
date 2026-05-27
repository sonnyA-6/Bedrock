#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "db.h"

void test_db_init() {
    Database db;
    int result = db_init(&db);

    assert(result == 0);
    printf("test_db_init passed\n");
}

void test_db_create_table() {
    Database db;
    db_init(&db);

    char *table_name = "table_a";
    Column table_a_columns;
    table_a_columns.is_column_nullable= true;
    table_a_columns.type_of_column = COLUMN_TYPE_STRING;
    strncpy(table_a_columns.column_name, "col_a", MAX_NAME_LENGTH);
    uint32_t num_of_cols_for_table_a = 1;

    int result = db_create_table(&db, table_name, &table_a_columns, num_of_cols_for_table_a);

    assert(result == 0);
    printf("test_db_create_table passed\n");
}

//Found bug in char to index function | Cannot handle spaces or capitalization
//Bug will be fixed in a later revision.
void test_db_drop_table() {
    Database db;
    db_init(&db);

    char *table_name = "table_a";
    Column table_a_column;
    table_a_column.is_column_nullable = false;
    table_a_column.type_of_column = COLUMN_TYPE_STRING;
    strncpy(table_a_column.column_name, "A", MAX_NAME_LENGTH);
    uint32_t num_of_cols_for_table_a = 1;

    db_create_table(&db, table_name, &table_a_column, num_of_cols_for_table_a);
    Table  *sanity_check = db_find_table(&db, table_name);
    assert(sanity_check != NULL);

    int result = db_drop_table(&db, table_name);

    assert(result == 0);
    assert(db.database_table[0].table_name[0] == '\0');
    assert(db.database_table[0].column_count == 0);
    assert(db.table_count == 0);
    assert(trie_search(&db.table_index,"table_a") == false);

    printf("test_db_drop_table passed\n");
}

void test_db_find_table() {
    Database db;
    db_init(&db);

    char *table_name = "find_this_table";
    char *not_found = "table_never_created";
    Column table_a_column;
    table_a_column.is_column_nullable = false;
    table_a_column.type_of_column = COLUMN_TYPE_STRING;
    strncpy(table_a_column.column_name, "A", MAX_NAME_LENGTH);
    uint32_t num_of_cols_for_table_a = 1;

    db_create_table(&db, table_name, &table_a_column, num_of_cols_for_table_a);
    Table  *table_found = db_find_table(&db, table_name);
    assert(table_found != NULL);
    assert(strcmp(table_found->table_name, table_name) == 0);

    Table *no_created_table = db_find_table(&db, not_found);
    assert(no_created_table == NULL);

    printf("test_db_find_table passed\n");
}

void test_db_add_column() {
    Database db;
    db_init(&db);

    char *table_name = "add_column";
    Column table_a_column;
    table_a_column.is_column_nullable = true;
    table_a_column.type_of_column = COLUMN_TYPE_INT;
    strncpy(table_a_column.column_name, "add_this_column", MAX_NAME_LENGTH);
    uint32_t num_of_cols_for_table_a = 1;

    db_create_table(&db, table_name, &table_a_column, num_of_cols_for_table_a);
    Table *check_table_col = db_find_table(&db, table_name);

    Column table_a_second_column;
    table_a_second_column.is_column_nullable = false;
    table_a_second_column.type_of_column = COLUMN_TYPE_INT;
    strncpy(table_a_second_column.column_name, "this_is_a_second_column", MAX_NAME_LENGTH);
    db_add_column(check_table_col, &table_a_second_column);

    assert(strcmp(check_table_col->table_column[1].column_name, "this_is_a_second_column") == 0);
    assert(check_table_col->table_column[1].type_of_column != COLUMN_TYPE_STRING);
    assert(check_table_col->table_column[1].is_column_nullable == false);
    assert(check_table_col->column_count == 2);

    printf("test_db_add_column passed\n");
}

void test_db_insert_row() {
    Database db;
    db_init(&db);

    char *table_name = "insert_a_row";
    Column testing_for_row;
    testing_for_row.is_column_nullable = false;
    testing_for_row.type_of_column = COLUMN_TYPE_INT;
    strncpy(testing_for_row.column_name, "column_1", MAX_NAME_LENGTH);
    uint32_t num_of_cols = 1;

    db_create_table(&db, table_name, &testing_for_row, num_of_cols);
    Table *row_insertion = db_find_table(&db, table_name);

    int clean_insert = db_insert_row(row_insertion, 5, "test");
    BSTNode *found_row = db_search_row(row_insertion, 5);
    assert(clean_insert == 0);
    assert(found_row != NULL);
    assert(found_row->data == 5);
    assert(strcmp(found_row->payload, "test") == 0);

    printf("test_db_insert_row passed\n");
}

void test_db_search_row() {
    Database db;
    db_init(&db);

    char *table_name = "insert_a_row";
    Column testing_for_row;
    testing_for_row.is_column_nullable = false;
    testing_for_row.type_of_column = COLUMN_TYPE_INT;
    strncpy(testing_for_row.column_name, "column_1", MAX_NAME_LENGTH);
    uint32_t num_of_cols = 1;

    db_create_table(&db, table_name, &testing_for_row, num_of_cols);
    Table *row_insertion = db_find_table(&db, table_name);

    int clean_insert = db_insert_row(row_insertion, 5, "test");
    BSTNode *found_row = db_search_row(row_insertion, 5);
    assert(clean_insert == 0);
    assert(found_row != NULL);
    assert(found_row->data == 5);
    assert(strcmp(found_row->payload, "test") == 0);

    int clean_delete = db_delete_row(row_insertion, 5);
    BSTNode *unable_to_find_row = db_search_row(row_insertion, 5);
    assert(clean_delete == 0);
    assert(unable_to_find_row == NULL);

    printf("test_db_search_row passed\n");
}

void test_db_delete_row() {
    Database db;
    db_init(&db);

    char *table_name = "insert_a_row";
    Column testing_for_row;
    testing_for_row.is_column_nullable = false;
    testing_for_row.type_of_column = COLUMN_TYPE_INT;
    strncpy(testing_for_row.column_name, "column_1", MAX_NAME_LENGTH);
    uint32_t num_of_cols = 1;

    db_create_table(&db, table_name, &testing_for_row, num_of_cols);
    Table *row_insertion = db_find_table(&db, table_name);

    db_insert_row(row_insertion, 15, "test");
    BSTNode *found_row = db_search_row(row_insertion, 15);
    assert(found_row != NULL);

    int clean_delete = db_delete_row(row_insertion, 15);
    BSTNode *unable_to_find_row = db_search_row(row_insertion, 15);
    assert(clean_delete == 0);
    assert(unable_to_find_row == NULL);

    printf("test_db_delete_row passed\n");
}

int main (void) {
    test_db_init();
    test_db_create_table();
    test_db_drop_table();
    test_db_find_table();
    test_db_add_column();
    test_db_insert_row();
    test_db_search_row();
    test_db_delete_row();

    printf("Tests have passed");
}
