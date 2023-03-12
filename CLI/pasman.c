#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include "./includes/pasman.h"
#include "./includes/aes.h"
#include "./includes/commands.h"
#include "./includes/file.h"

#define DATABASE "./data/database.json"
#define KEY_LOG "./data/key.log"

char key[80];
unsigned char *cipher = NULL;

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		puts("-h to get help");
		return 0;
	}

	if (isFirstTime())
	{
		setMasterKey();
		return 0;
	}

	if (!isAuthorize() && useAuthenticate())
	{
		decryptDatabase();
	}

	Command cmd = determineCommand(argc, argv);
	executeCommand(cmd, argv);
	return 0;
}

Command determineCommand(int argc, char *argv[])
{
	char ch;
	while ((ch = getopt(argc, argv, ":f:hn:rl")) != -1)
		switch (ch)
		{
		case 'f':
			return Find;
		case 'n':
			if (argc < 4)
			{
				error(argv[1]);
				return Error;
			}
			return New;
		case 'r':
			return Delete;
		case 'l':
			return List;
		case ':':
			error(argv[1]);
			return Error;
		case '?':
			error(argv[1]);
			return Error;
		case 'h':
			return Help;
		}
}

void executeCommand(Command cmd, char *argv[])
{
	switch (cmd)
	{
	case Find:;
		char *username = argv[2];
		find(username);
		break;
	case Help:
		help();
		break;
	case Delete:
		delete ();
		break;
	case New:;
		Account newAccount = {argv[2], argv[3]};
		new (newAccount);
		break;
	case List:
		list();
		break;
	}
}

Bool isFirstTime()
{
	readFile(KEY_LOG, &cipher);
	if (strlen(cipher) == 0)
		return True;
	return False;
}

Bool isAuthorize()
{
	time_t lastTime, current;

	time(&current);
	lastTimeAuthorize(&lastTime);

	if (difftime(current, lastTime) > 59 || difftime(current, lastTime) < 0)
		return False;
	return True;
}

void setMasterKey()
{
	printf("Set your key: ");
	scanf("%79s", key);
	int cipherLen = aes_encrypt(key, strlen(key), key, &cipher);
	writeFile(KEY_LOG, cipher, cipherLen);
	writeTextEncrypt(DATABASE, "[]", key, 2);
	exit(0);
}

Bool useAuthenticate()
{
	unsigned char *keyCheck = NULL;

	printf("Key: ");
	scanf("%79s", key);
	aes_decrypt(cipher, strlen(cipher), key, &keyCheck);

	if (strcmp(key, keyCheck))
	{
		printf("Wrong password!\n");
		exit(0);
	}

	time_t current;
	time(&current);
	saveTime(&current);
	return True;
}

Bool decryptDatabase()
{
	pid_t pid = fork();
	if (!pid)
	{
		if (execl("./encrypt/encrypt", "./encrypt/encrypt", key, NULL) == -1)
		{
			fprintf(stderr, "Can't run encrypt function: %s\n", strerror(errno));
			return False;
		}
	}
	if (isDecrypted())
		return True;
}

Bool isDecrypted()
{
	unsigned char *check;
	do
	{
		sleep(0.5);
		check = NULL;
		readFile(DATABASE, &check);
	} while (check[strlen(check) - 1] != ']');
	return True;
}