#ifndef COMMANDS_H

typedef enum
{
	Find = 0,
	Help,
	Delete,
	New,
	List,
	Error
} Command;

typedef struct
{
	const char *username;
	const char *password;
} Account;

void find(char *username_need_to_find);
void help();
void delete();
void new(Account newAccount);
void list();
void error(char *ch);
Command determineCommand(int argc, char *argv[]);
void executeCommand(Command cmd, char *argv[]);

#endif