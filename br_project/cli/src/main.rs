mod repl;
mod commands;
pub mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}
use crate::bindings::*;
use crate::repl::run_repl;

fn main() {
    //Initialize a Database
    let mut rust_database: Database = unsafe { std::mem::zeroed() };
    unsafe { db_init(&mut rust_database) };
    run_repl(&mut rust_database);
}
