include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
use std::io::{self, Write};

fn run_repl(db: &mut Database) {
    let help_commands = r#"
    Available commands:
    --------------------------
    create table <name>
    create column <name>
    insert row <key> <value>
    search row <key> <value>
    delete row <key> <value>
    drop table <name>"#;
    println!("REPL initializing!");

    //if database creation is succuss launch the database
    //State that the repl is intialized
    println!("Welcome to REPL -- Database CLI");
    println!("Enter -- help for a list of commands\n\
              Enter -- exit to close out the program\n");

    loop{
        //Print prompt
        print!("bedrock> "); //use print! to keep cursor on same line
        io::stdout().flush().unwrap();
        let mut db_string_buf = String::new();
        io::stdin()
            .read_line(&mut db_string_buf)
            .expect("Failed to read line");
        let trimmed_db_string = db_string_buf.trim();
        if trimmed_db_string == "exit" {
            break;
        }
        else if trimmed_db_string == "help" {
            //print commands available to the user
                println!("{}", help_commands);
        }
        else {
            //Command to parse information will go here
        }
    }
}