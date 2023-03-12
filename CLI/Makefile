all: pasman encrypt

pasman: pasman.o file.o commands.o aes.o
	gcc $^ -o $@ -ljson-c


encrypt: encrypt.o file.o aes.o
	cd ./encrypt; gcc ./encrypt.o ../file.o ../aes.o -o encrypt

encrypt.o: 
	cd ./encrypt; gcc encrypt.c -c encrypt.o
	
pasman.o: pasman.c	
file.o: file.c
commands.o: commands.c
aes.o: aes.c

clean: 
	rm -f *.o; cd encrypt; rm -f *.o
	rm pasman
	cd ./encrypt; rm -f encrypt