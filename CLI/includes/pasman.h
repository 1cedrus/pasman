#ifndef PASMAN

typedef enum Bool
{
  True = 1,
  False = 0
} Bool;

Bool isFirstTime();
Bool isAuthorize();
Bool useAuthenticate();
Bool decryptDatabase();
void setMasterKey();
Bool isDecrypted();

#endif