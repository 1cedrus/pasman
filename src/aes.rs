use libc;
use std::{num::ParseIntError, ptr};
use std::fmt::*;
use std::result::Result;

extern "C" {
    fn aes_encrypt(text: *const u8, textLen: libc::c_int, key: *const u8, out: *mut *mut u8) -> libc::c_int;
    fn aes_decrypt(cipher: *const u8, cipherLen: libc::c_int, key: *const u8, out: *mut *mut u8) -> libc::c_int;
}

pub fn encrypt(plain_text: &str, key: &str) -> String {
    let len = plain_text.len() as libc::c_int;
    let mut encrypted: *mut u8 = ptr::null_mut();
    
    let cipher_len = unsafe {
        aes_encrypt(plain_text.as_ptr(), len, key.as_ptr(), &mut encrypted)
    };

    let encrypted_slice = unsafe {
        std::slice::from_raw_parts(encrypted, cipher_len as usize)
    };

    encode_hex(encrypted_slice)
}

pub fn decrypt(cipher_text: &str, key: &str) -> String {
    let cipher_text = decode_hex(cipher_text).unwrap();

    let len = cipher_text.len() as libc::c_int;
    let mut decrypted: *mut u8 = ptr::null_mut();
    
    let cipher_len = unsafe {
        aes_decrypt(cipher_text.as_ptr(), len, key.as_ptr(), &mut decrypted)
    };

    let decrypted_str = unsafe {
        let decrypted_slice = std::slice::from_raw_parts(decrypted, cipher_len as usize);
        std::str::from_utf8(decrypted_slice).unwrap()
    };

    decrypted_str.trim_matches(char::from(0)).to_string()
}


// Ref: https://stackoverflow.com/questions/52987181/how-can-i-convert-a-hex-string-to-a-u8-slice
pub fn decode_hex(s: &str) -> Result<Vec<u8>, ParseIntError> {
    (0..s.len())
        .step_by(2)
        .map(|i| u8::from_str_radix(&s[i..i + 2], 16))
        .collect()
}

pub fn encode_hex(bytes: &[u8]) -> String {
    let mut s = String::with_capacity(bytes.len() * 2);
    for &b in bytes {
        write!(&mut s, "{:02x}", b).unwrap();
    }

    s
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn should_correctly_encrypt_infomation() {
        let plain_text = "Hello, World!";
        let key = "secretkey";
        let cipher_text = encrypt(plain_text, key);
        let decrypt_text = decrypt(&cipher_text, key);

        assert_eq!(plain_text, decrypt_text);
    }
}

