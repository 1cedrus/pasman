PROG = main
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` 

${PROG}: ${PROG}.c view.c file.c aes.c
	${CC} ${CFLAGS} -o ${PROG} ${PROG}.c view.c file.c aes.c ${LIBS}	

clean:
	rm ${PROG}