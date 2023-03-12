#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../includes/aes.h"
#include "../includes/file.h"
#include "../includes/pasman.h"
#define DATABASE "./data/database.json"

int main(int argc, unsigned char *argv[])
{
    unsigned char *text = NULL;
    unsigned char *cipher = NULL;
    unsigned char *key = argv[1];

    int cipherLen = readFile(DATABASE, &cipher);
    writeCipherDecrypt(DATABASE, cipher, key, cipherLen);

    sleep(60);

    int textLen = readFile(DATABASE, &text);
    writeTextEncrypt(DATABASE, text, key, textLen);
    return 0;
}
