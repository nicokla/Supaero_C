CC = gcc
CFLAGS = -Wall -pedantic

prog:arbreBin.o prog.o
	$(CC) -o prog prog.o arbreBin.o $(CFLAGS)

arbreBin.o:arbreBin.c arbreBin.h
	$(CC) -c arbreBin.c  $(CFLAGS)

prog.o:prog.c arbreBin.h
	$(CC) -c prog.c $(CFLAGS)

clean:
	rm -rf *.o
