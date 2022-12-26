#include <stdio.h>
#include "aes.h"
#include "file.h"
#include <string.h>
#include <time.h>
#include <unistd.h>


int main(int argc, unsigned char *argv[])
{    

    char *dataLog = "database.json";
    unsigned char *text = NULL;
    unsigned char *cipher = NULL;
    unsigned char *key = argv[1];

    int cipherLen = readFile(dataLog, &cipher);
    writeCipherDecrypt(dataLog, cipher, key, cipherLen);

    sleep(60);

    int textLen = readFile(dataLog, &text);
    writeTextEncrypt(dataLog, text, key, textLen);
    return 0;
}
