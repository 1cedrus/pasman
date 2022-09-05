#include <stdio.h>
#include "file.h"

int main(int argc, char const *argv[])
{
    int a = isTheFirstTime("key.log");
    printf("%d", a);
    return 0;
}
