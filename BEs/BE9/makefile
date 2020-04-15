CC = gcc
CFLAGS = -Wall -pedantic

testfile:testfile.o mafile.o
	$(CC) -o testfile testfile.o mafile.o $(CFLAGS)

testfile.o:testfile.c mafile.h
	$(CC) -c testfile.c $(CFLAGS)

mafile.o:mafile.c mafile.h
	$(CC) -c mafile.c $(CFLAGS)

clean:rm - rf *.o
