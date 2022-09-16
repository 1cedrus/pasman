#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "file.h"
#include "aes.h"
#include <json-c/json.h>

json_object *database, *username, *password, *account;

void find(char *username_need_to_find) 
{
    size_t numOfAcc;
	Bool existed = False;
	
    database = json_object_from_file("database.json");
    numOfAcc = json_object_array_length(database);

    for (int i = 0; i < numOfAcc; i++) 
    {
        account = json_object_array_get_idx(database, i);
        username = json_object_object_get(account, "username");
        password = json_object_object_get(account, "password");
        if (strstr(json_object_get_string(username), username_need_to_find)) 
		{
            printf("%s|%s\n", json_object_get_string(username), json_object_get_string(password));
			existed = True;
		}
    }
	if (!existed) puts("Username isn't existed");
}

// void find(char *username_need_to_find)
// {
// 	size_t numOfAcc;
// 	Bool existed = False;

// 	unsigned char *buf = NULL;
// 	int n = readFile("database.json", &buf);
// 	database = json_tokener_parse(buf);
// 	numOfAcc = json_object_array_length(database);

// 	for (int i = 0; i < numOfAcc; i++) 
//     {
//         account = json_object_array_get_idx(database, i);
//         username = json_object_object_get(account, "username");
//         password = json_object_object_get(account, "password");
//         if (strstr(json_object_get_string(username), username_need_to_find)) 
// 		{
//             printf("%s|%s\n", json_object_get_string(username), json_object_get_string(password));
// 			existed = True;
// 		}
//     }
// 	if (!existed) puts("username isn't existed");
	
// }

void help() 
{

	puts("-f <username> / to find password.");
	puts("-n <username> <password> / to add acc and password.");
	puts("-r / to remove acc.");
	puts("-l / to show list acc.");

}	

void new(Account newAccount) 
{
	json_object *newAcc = json_object_new_object();
	json_object *newUsername = json_object_new_string(newAccount.username);
	json_object *newPassword = json_object_new_string(newAccount.password);

	json_object_object_add(newAcc, "username", newUsername);
	json_object_object_add(newAcc, "password", newPassword);


	database = json_object_from_file("database.json");
	json_object_array_add(database, newAcc);

	json_object_to_file("database.json", database);
}

void delete()
{

	int numOfAcc, i;

	database = json_object_from_file("database.json");
	
	numOfAcc = json_object_array_length(database);

	for (i = 0; i < numOfAcc; i++) 
	{
		account = json_object_array_get_idx(database, i);
		username = json_object_object_get(account, "username");
		password = json_object_object_get(account, "password");
		printf("[%d] %s|%s\n", i, json_object_get_string(username), json_object_get_string(password));	
	}
	printf("number: ");
	scanf("%d", &i);

	json_object_array_del_idx(database, i, 1);

	json_object_to_file("database.json", database);
}

void list() 
{
	
	size_t numOfAcc;

	database = json_object_from_file("database.json");
	numOfAcc = json_object_array_length(database);

	for (int i = 0; i < numOfAcc; i++) 
	{
		account = json_object_array_get_idx(database, i);
		username = json_object_object_get(account, "username");
		password = json_object_object_get(account, "password");
		printf("[%i] %s|%s\n", i, json_object_get_string(username), json_object_get_string(password));	
	}
}

void error(char *ch) 
{
	if (!strcmp(ch, "-f")) 
	{
		puts("-f <username>");
		return;
	}
	if (!strcmp(ch, "-n")) {
		puts("-n <username> <password>");
		return;
	}
	printf("option %s is not existed\n-h to get help\n", ch);
}