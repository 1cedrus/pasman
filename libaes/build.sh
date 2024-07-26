gcc -c -fPIC libaes/aes.c -o libaes/aes.o
gcc -shared -o libaes/libaes.so libaes/aes.o

