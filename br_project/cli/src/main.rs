mod repl;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::ffi::{CString};

fn main() {
    //Initialize a Database
    let mut rust_database: Database = unsafe { std::mem::zeroed() };
    let mut table_name= CString::new("rust_table")
        .expect("CString::new failed");
    let mut column: Column = unsafe { std::mem::zeroed() };
    let name = b"rust_column\0";
    unsafe {
        std::ptr::copy_nonoverlapping(
            name.as_ptr(),
            column.column_name.as_mut_ptr() as *mut u8,
            name.len()
        );
    }
    column.is_column_nullable = false;
    column.type_of_column = ColumnType_COLUMN_TYPE_STRING;
    let number_of_cols:u32 = 1;

    unsafe { db_init(&mut rust_database) };
    unsafe { db_create_table(&mut rust_database, table_name.as_ptr(),&column, number_of_cols ); }
}
