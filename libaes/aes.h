#ifndef AES_H
#define BLOCK_LEN 16
#define BLOCK_SIDE 4

void addRoundKey(unsigned char state[BLOCK_SIDE][BLOCK_SIDE],
                 unsigned char word[BLOCK_SIDE][BLOCK_SIDE]);
void subBytes(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);
void shiftRows(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);
void mixColumns(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);

void rv_subBytes(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);
void rv_shiftRows(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);
void rv_mixColumns(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]);

int aes_encrypt(unsigned char *text, int textLen,
                unsigned char *key,
                unsigned char **out);

void aes_encrypt_block(unsigned char *text, int textLen,
                       unsigned char word[][BLOCK_SIDE][BLOCK_SIDE],
                       unsigned char out[BLOCK_LEN]);

int aes_decrypt(unsigned char *cipher, int cipherLen,
                unsigned char *key,
                unsigned char **out);

void aes_decrypt_block(unsigned char *cipher, int cipherLen,
                       unsigned char word[][BLOCK_SIDE][BLOCK_SIDE],
                       unsigned char out[BLOCK_LEN]);
#endif
