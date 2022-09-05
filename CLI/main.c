#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "aes.h"
#include "file.h"
#include <time.h>
#include <errno.h>
#include <stdlib.h>

char *timeLog = "time.log";
char *keyLog = "key.log";
char *dataLog = "database.json";

enum Command determineCommand(int argc, char *argv[]);
void executeCommand(enum Command cmd, char *argv[]) ;


int main(int argc, char *argv[]) {

	if (argc == 1) {
		puts("-h to get help"); 
		return 0;
	}

	char key[80];
	unsigned char *cipher = NULL;
	readFile(keyLog, &cipher);
	if (strlen(cipher) == 0) {
		printf("Set your key: ");
		scanf("%79s", key);
		int cipherLen = aes_encrypt(key, strlen(key), key, &cipher);
		writeFile(keyLog, cipher, cipherLen);
		writeTextEncrypt(dataLog, "[]", key, 2);
		return 0;
	}
	time_t lastTime, thisTime;

	time(&thisTime);
	getTime(&lastTime);
	if (difftime(thisTime, lastTime) > 59 || difftime(thisTime, lastTime) < 0) {
		unsigned char *keyCheck = NULL;

		printf("Key: ");
		scanf("%79s", key);
		aes_decrypt(cipher, strlen(cipher), key, &keyCheck);

		if (strcmp(key, keyCheck))
		{
			printf("Wrong password!\n");
			return 0;
		} 

		time(&thisTime); 
		saveTime(&thisTime);

		pid_t pid = fork();
		if (!pid) {
			if (execl("./encrypt", "./encrypt", key, NULL) == -1) {
				fprintf(stderr, "Can't run encrypt function: %s\n", strerror(errno));
				return 1;
			}
		}
		unsigned char *check;
		do {
			sleep(0.5);
			check = NULL;
			readFile(dataLog, &check);
		} while (check[strlen(check) - 1] != ']');	
	}
	enum Command cmd = determineCommand(argc, argv);
	executeCommand(cmd, argv); 
	return 0;	
}


enum Command determineCommand(int argc, char *argv[]) {
	char ch;
	while ((ch = getopt(argc, argv, ":f:hn:rl"))!= -1)
		switch (ch) {
			case 'f': 
				return Find;
			case 'n':
				if (argc < 4) 
				{
					error(argv[1]);
					return Exit;
				}	 
				return New;
			case 'r':
				return Delete;
			case 'l':
				return List;
			case ':':
				error(argv[1]);
				return Exit;	
			case '?':
				error(argv[1]);
				return Exit;
			case 'h':
				return Help;
		}
}

void executeCommand(enum Command cmd, char *argv[]) {
	switch (cmd) {
		case Find: ;
			char *username = argv[2];
			find(username);
			break;
		case Help:
			help();
			break;
		case Delete:
			delete();
			break;
		case New: ;
			Account newAccount = {argv[2], argv[3]};
			new(newAccount);
			break;
		case List:
			list();
			break;			
	}
}
