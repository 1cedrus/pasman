typedef struct {
    const char *username;
    const char *password;
} Account;

void find(char *username_need_to_find);
void help();
void delete();
void new(Account newAccount);
void list();
void error(char *ch);

enum Command {
	Find,
	Help,
	New,
	Delete,
	List,
	Exit,
	Error,
};

typedef enum Bool {
	True = 1,
	False = 0
} Bool;



