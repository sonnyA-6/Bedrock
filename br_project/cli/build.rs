use std::env;
use std::path::PathBuf;
use bindgen::Builder;

fn main(){
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=wrapper.h");
    println!("cargo:rerun-if-changed=db.h");
    println!("cargo:rerun-if-changed=bst.h");
    println!("cargo:rerun-if-changed=trie.h");
    println!("cargo:rerun-if-changed=stack.h");
    println!("cargo:rustc-link-search=../cmake-build-debug");
    println!("cargo:rustc-link-lib=static=bedrock");

    //Add bindings
    let bindings = Builder::default()
        .header("../include/wrapper.h")
        .clang_arg("-I../include")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings.write_to_file(out_path.join("bindings.rs")).expect("...");
}