CC = gcc
CFLAGS = -Wall -pedantic -g

testfile:testfile.o mafile.o fonctions_en_plus.o
	$(CC) -o testfile fonctions_en_plus.o testfile.o mafile.o $(CFLAGS)

testfile.o:testfile.c mafile.h
	$(CC) -c testfile.c $(CFLAGS)

mafile.o:mafile.c mafile.h
	$(CC) -c mafile.c $(CFLAGS)

fonctions_en_plus.o:fonctions_en_plus.c mafile.h
	$(CC) -c fonctions_en_plus.c $(CFLAGS)

clean:
	rm -rf *.o
