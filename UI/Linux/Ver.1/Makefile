
PROG = test2

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` 

${PROG}: ${PROG}.c file.c aes.c commands.c
	${CC} ${CFLAGS} -o ${PROG} ${PROG}.c file.c aes.c commands.c ${LIBS} -ljson-c

clean: 
	rm ${PROG}
