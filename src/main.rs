use ncurses::*;
use std::cmp::*;
use std::io::{Write, BufWriter};
use std::{
    fs::*,
    io::{BufRead, BufReader, Error},
};

const REGULAR_PAIR: i16 = 0;
const HIGHLIGHT_PAIR: i16 = 1;
const HIDDEN_PAIR: i16 = 2;

type Result<T> = std::result::Result<T, Error>;

#[derive(Debug)]
struct Credential {
    username: String,
    password: String,
}

fn main() -> Result<()> {
    let command: Vec<String> = std::env::args().collect(); 
    let mut quit = true;
        
    if command.len() <= 1 {
        quit = false;
    } else {
        let command = &command[1..];
        match command {
           [command, username, password] => {
            if command.eq("add") {
                let mut credentials_file = OpenOptions::new().append(true).open("credentials.sou")?;
                credentials_file.write(format!("{username}:{password}\n").as_bytes())?;

                println!("INFO: New credential added!");
            }
           }
           _ => {}
        }
    }


    // Initial CLI screen
    initscr();
    noecho();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
    start_color();
    init_pair(REGULAR_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(HIGHLIGHT_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(HIDDEN_PAIR, COLOR_WHITE, COLOR_WHITE);

    let credentials_buffer = BufReader::new(File::open("credentials.sou")?);
    let mut credentials: Vec<Credential> = vec![];

    for credential in credentials_buffer.lines() {
        if let [username, password] = credential.unwrap().split(':').collect::<Vec<&str>>()[..2] {
            credentials.push(Credential {
                username: username.to_string(),
                password: password.to_string(),
            })
        }
    }

    let mut cursor: usize = 0;
    let mut show: usize = usize::MAX;
    let mut delete: usize = usize::MAX;

    while !quit {
        clear();

        for (row, credential) in credentials.iter().enumerate() {
            let pair = if row.eq(&cursor) {
                HIGHLIGHT_PAIR
            } else {
                REGULAR_PAIR
            };

            attron(COLOR_PAIR(pair));
            mv(row as i32, 0);
            addstr(credential.username.as_str());
            mv(row as i32, 32);
            addch(':' as u32);
            if !show.eq(&row) {
                attron(COLOR_PAIR(HIDDEN_PAIR));
                addstr(&credential.password.as_str());
                attroff(COLOR_PAIR(HIDDEN_PAIR));
            } else {
                addstr(&credential.password.as_str());
                attroff(COLOR_PAIR(pair));
            }
        }

        refresh();
        let key = getch();
        match key as u8 as char {
            'q' => quit = {
                let mut credentials_file = BufWriter::new(File::create("credentials.sou")?);
                for credential in &credentials {
                    credentials_file.write_all(format!("{}:{}\n", credential.username, credential.password).as_bytes())?;
                }
                true
            },
            'j' => cursor = min(cursor + 1, credentials.len() - 1),
            'k' => {
                if cursor > 0 {
                    cursor = cursor - 1
                }
            }
            'c' => show = if show.eq(&cursor) { usize::MAX } else { cursor },
            'd' => delete = if delete.eq(&cursor) { credentials.remove(delete); usize::MAX } else { cursor },
            _ => {}
        };
    }

    endwin();
    Ok(())
}

