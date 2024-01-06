use ncurses::*;
use std::cmp::*;
use std::{
    fs::*,
    io::{BufRead, BufReader, Error},
};

const REGULAR_PAIR: i16 = 0;
const HIGHLIGHT_PAIR: i16 = 1;
const HIDDEN_PAIR: i16 = 2;

type Result<T> = std::result::Result<T, Error>;

struct Credential {
    username: String,
    password: String,
}

fn main() -> Result<()> {
    // Initial CLI screen
    initscr();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
    start_color();
    init_pair(REGULAR_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(HIGHLIGHT_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(HIDDEN_PAIR, COLOR_WHITE, COLOR_WHITE);

    let mut quit = false;
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
            'q' => quit = true,
            'j' => cursor = min(cursor + 1, credentials.len() - 1),
            'k' => {
                if cursor > 0 {
                    cursor = cursor - 1
                }
            }
            'c' => show = if show.eq(&cursor) { usize::MAX } else { cursor },
            _ => {}
        };
    }

    endwin();
    Ok(())
}
