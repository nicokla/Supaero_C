CC=gcc
CFLAGS=-Wall -pedantic

comparer:comparer.o personne.o date.o
	$(CC) -o comparer comparer.o personne.o date.o $(CFLAGS)

comparer.o:comparer.c
	$(CC) -c comparer.c $(CFLAGS)

personne.o:personne.c personne.h date.c date.h
	$(CC) -c personne.c $(CFLAGS)

date.o:date.c date.h
	$(CC) -c date.c $(CFLAGS)

clean:
	rm -rf *.o
