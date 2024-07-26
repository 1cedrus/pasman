fn main() {
    println!("cargo:rustc-link-lib=dylib=aes");
    println!("cargo:rustc-link-search=native=./libaes");
}

