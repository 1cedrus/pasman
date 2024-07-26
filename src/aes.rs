use libc;
use std::ptr;

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

    unsafe {
        libc::free(encrypted as *mut libc::c_void);
    }

    format!("{:?}", encrypted_slice)
}

pub fn decrypt(cipher_text: &str, key: &str) -> String {
    let len = cipher_text.len() as libc::c_int;
    let mut decrypted: *mut u8 = ptr::null_mut();
    
    let cipher_len = unsafe {
        aes_encrypt(cipher_text.as_ptr(), len, key.as_ptr(), &mut decrypted)
    };

    let decrypted_str = unsafe {
     let decrypted_slice =    std::slice::from_raw_parts(decrypted, cipher_len as usize);
                std::str::from_utf8(decrypted_slice).unwrap()
    };

    unsafe {
        libc::free(decrypted as *mut libc::c_void);
    }

    decrypted_str.to_string() 
}



