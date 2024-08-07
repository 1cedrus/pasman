use std::{fs::{self }, io:: Error};

mod account;
mod style;
mod aes;
use clap::{ Parser, Subcommand };

type Result<T> = std::result::Result<T, Error>;


/// A fictional versioning CLI
#[derive(Debug, Parser)] // requires `derive` feature
#[command(name = "pasman")]
#[command(about = "A simple password manager", long_about = None)]
struct Cli {
    #[command(subcommand)]
    command: Commands,
}

#[derive(Debug, Subcommand)]
enum Commands {
    /// Clones repos
    #[command(arg_required_else_help = true)]
    Encrypt {
        /// The remote to clone
        file_path: String,
    },
    /// Compare two commits
    #[command(arg_required_else_help = true)]
    Decrypt {
        file_path: String,
    },
}

fn main() -> Result<()> {
    let args = Cli::parse();

    match args.command {
        Commands::Encrypt { file_path } => { 
            let plain_text = fs::read_to_string(&file_path).expect("File is not existed");
            let key = rpassword::prompt_password("Password: ").unwrap();
            let confirmation = rpassword::prompt_password("Retype password: ").unwrap();

            if key != confirmation {
                println!("Password does not match");
                return Ok(());
            }

            let cipher_text = aes::encrypt(&plain_text, &key);

            fs::write(&file_path, cipher_text).expect("Unable to write file");
        }
        Commands::Decrypt {file_path} => { 
            let cipher_text = fs::read_to_string(&file_path).expect("File is not existed");
            let key = rpassword::prompt_password("Password: ").unwrap();
            
            let plain_text = aes::decrypt(&cipher_text.trim(), &key);

            fs::write(&file_path, plain_text).expect("Unable to write file");
        }
    }

    Ok(())
}
