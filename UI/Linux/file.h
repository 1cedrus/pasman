

int readFile(char *fileName, unsigned char **out);
void writeFile(char *fileName, const char *msg, int len);
void read1Line(char *fileName, char *msg);


void writeCipherDecrypt(char *fileName, char *cipher, char *key, int len);
void writeTextEncrypt(char *fileName, char *text, char *key, int len);

void saveTime(long int *n);
void getTime(long int *n);