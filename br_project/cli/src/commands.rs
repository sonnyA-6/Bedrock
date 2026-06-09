use std::ffi::CString;
use crate::bindings::*;

pub fn parse_command(input: &str, db: &mut Database) -> Result<String, String>{

    let help_commands = r#"
    Available commands:
    --------------------------
    create table <name>
    create column <table_name> <column_name>
    insert row <table> <key> <value>
    search row <key> <value>
    delete row <key> <value>
    drop table <name>"#;
    //Slice pattern match the commands from the user
    let command_to_parse:Vec<&str> = input.split_whitespace().collect();
    match command_to_parse.as_slice() {
        ["create","table", noun] => {
            let table_name = CString::new(*noun).unwrap();
            let table_name_ptr = table_name.as_ptr();
            let result = unsafe { db_create_table(db as *mut Database, table_name_ptr,
                                                  std::ptr::null(), 0u32) };
            if result == -1 {
                Err("Table creation failed!".to_string())
            }
            else{
                Ok("Table has been created!".to_string())
            }
        }
        ["create","column", noun_table, noun_col] => {
            let find_table = CString::new(*noun_table).unwrap();
            let find_table_ptr = find_table.as_ptr();
            let result = unsafe { db_find_table(db as *mut Database, find_table_ptr) };
            if result.is_null() {
                Err("Table not found! Cannot create column".to_string())
            }
            else{
                let mut col: Column = unsafe {std::mem::zeroed()};
                let column_name = CString::new(*noun_col).unwrap();
                unsafe {
                    std::ptr::copy_nonoverlapping(
                        column_name.as_ptr(),
                        col.column_name.as_mut_ptr(),
                        column_name.as_bytes().len(),
                    );
                }
                col.type_of_column = ColumnType_COLUMN_TYPE_INT;
                col.is_column_nullable = false;
                let add_col_to_table = unsafe { db_add_column(result, &mut col as *mut Column) };
                if add_col_to_table == -1 {
                    Err("Column has not been created!".to_string())
                }
                else{
                    Ok("Column has been added to the table!".to_string())
                }
            }
        }
        ["drop", "table", noun] =>{
            let table_to_drop = CString::new(*noun).unwrap();
            let table_to_drop_ptr = table_to_drop.as_ptr();
            let result = unsafe { db_drop_table(db as *mut Database, table_to_drop_ptr)};
            if result == -1 {
                Err("Table drop failed!".to_string())
            }
            else {
                Ok("Table has been dropped!".to_string())
            }
        }
        ["insert","row", table, key, value] => {
            let find_table = CString::new(*table).unwrap();
            let find_table_ptr = find_table.as_ptr();
            let result = unsafe { db_find_table (db as *mut Database, find_table_ptr) };
            //Table pointer is null
            if result.is_null() {
                Err("Table not found! Cannot insert row.".to_string())
            }
            else {
                let insert_row_key: i32 = match (*key).parse(){
                    Ok(k) => k,
                    Err(_)=> return Err("Invalid key - must be an integer".to_string())
                };
                let insert_row_val = CString::new(*value).unwrap();
                let insert_row_val_ptr = insert_row_val.as_ptr();
                let insertion = unsafe { db_insert_row(result, insert_row_key, insert_row_val_ptr
                as *mut std::os::raw::c_void) };

                if insertion == -1{
                    Err("Row insertion has failed!".to_string())
                }
                else{
                    Ok("Row has been inserted!".to_string())
                }
            }
        }
        ["search", "row", table, key] => {
            let find_table = CString::new(*table).unwrap();
            let find_table_ptr = find_table.as_ptr();
            let result = unsafe { db_find_table(db as *mut Database, find_table_ptr) };
            if result.is_null(){
                Err("Table not found! Cannot search for row.".to_string())
            }
            else{
                let search_key: i32 = match (*key).parse(){
                    Ok(k) => k,
                    Err(_) => return Err("Invalid key - must be an integer".to_string())
                };
                let search = unsafe { db_search_row(result, search_key) };
                if search.is_null(){
                    Err("Row now found! Cannot find row.".to_string())
                }
                else{
                    Ok("Row has been found!".to_string())
                }
            }
        }
        ["delete", "row", table, key] => {
            let find_table = CString::new(*table).unwrap();
            let find_table_ptr = find_table.as_ptr();
            let result = unsafe { db_find_table(db as *mut Database, find_table_ptr) };
            if result.is_null(){
                Err("Table not found! Cannot delete row.".to_string())
            }
            else{
                let delete_row_key: i32 = match (*key).parse(){
                    Ok(k) => k,
                    Err(_) => return Err("Invalid key - must be an integer".to_string())
                };
                let deletion = unsafe { db_delete_row(result, delete_row_key) };
                if deletion == -1{
                    Err("Row deletion has failed".to_string())
                }
                else {
                    Ok("Row has been deleted".to_string())
                }
            }
        }
        ["help", ..]=> {
            Ok(help_commands.to_string())
        }
        ["exit", ..] => {
            Ok("exit".to_string())
        }
        _ => {
            Err("This command is not recognized!".to_string())
        }
    }
}