use std::io::{self, Write};
use crate::commands::parse_command;
use crate::bindings::*;

pub fn run_repl(db: &mut Database) {
    println!("REPL initializing!");

    //if database creation is succuss launch the database
    //State that the repl is intialized
    println!("Welcome to REPL -- Database CLI");
    println!("Enter -- help for a list of commands\n\
              Enter -- exit to close out the program\n");

    loop {
        //Print prompt
        print!("bedrock> "); //use print! to keep cursor on same line
        io::stdout().flush().unwrap();
        let mut db_string_buf = String::new();
        io::stdin()
            .read_line(&mut db_string_buf)
            .expect("Failed to read line");
        let trimmed_db_string = db_string_buf.trim();
        match parse_command(trimmed_db_string, db) {
            Ok(k) => {
                if k == "exit" {
                    break;
                }
                println!("{}", k);
            },
            Err(e) => println!("{}", e)
        }
    }
}