#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "aes.h"
#include "commands.h"


int readFile (char *fileName, unsigned char **out) {
  	FILE *f = fopen(fileName, "rb");
	int i = 0;
	while (!feof(f)) {
		*out = realloc(*out, ++i * sizeof(unsigned char));
		fread(*out + (i - 1), 1, 1, f);
	}
  	return i - 1;
	fclose(f);
}

Bool isTheFirstTime(char *fileName) {
	unsigned char *buffer = NULL;
	readFile(fileName, &buffer);
	if (!buffer) return True;
	return False;
}

// char* readFileEncrypt (char *fileName, unsigned char **out, unsigned char *key) {
// 	unsigned char *buffer = NULL;

// 	FILE *f = fopen(fileName, "rb");
// 	int i = 0;
// 	while (!feof(f)) {
// 		*out = realloc(*out, ++i * sizeof(unsigned char));
// 		fread(*out + (i - 1), 1, 1, f);
// 	}
// 	fclose(f);


// 	aes_decrypt (*out, i - 1, key, &buffer);

// 	return buffer;
// }

void read1Line(char *fileName, char *msg) 
{

	FILE *f = fopen(fileName, "r");
	// mean of fscanf is read all character except '\n' and end when touching '\n'.
	fscanf(f, "%200[^\n]\n", msg);
	fclose(f);
}

void writeFile(char *fileName, const char *msg, int len) 
{
	FILE *f = fopen(fileName, "wb");
	for (int i = 0; i < len; i++) {
		fwrite(&msg[i], 1, 1, f);
	}
	fclose(f);
}

void getTime(long int *n) 
{
	FILE *f = fopen("time.log", "r");
	fscanf(f, "%ld", n);
	fclose(f);
}

void saveTime(long int *n)
{
	FILE *f = fopen("time.log", "w");
	fprintf(f, "%ld", *n);
	fclose(f);
}

void writeTextEncrypt(char *fileName, char *text, char *key, int len) {
	unsigned char *cipher = NULL;
	int cipherLen = aes_encrypt(text, len, key, &cipher);
	writeFile(fileName, cipher, cipherLen);
}

void writeCipherDecrypt(char *fileName, char *cipher, char *key, int len) {
	unsigned char *text = NULL;
	aes_decrypt(cipher, len, key, &text);
	int textLen = strlen(text);
	writeFile(fileName, text, textLen);
}