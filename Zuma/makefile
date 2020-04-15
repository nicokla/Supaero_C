CFLAGS = -Wall -g -lm -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
##########################################################

zuma:zuma.o io_console.o vecteurs.o texte_SDL.o 1-initialisations.o 2-niveauEtParcours.o 3-affichage.o 4-avanceeFile.o 5-tir.o 6-insertion.o 7-explosions.o 9-fin.o 8-high_score.o
	gcc -o zuma zuma.o io_console.o vecteurs.o texte_SDL.o 1-initialisations.o 2-niveauEtParcours.o 3-affichage.o 4-avanceeFile.o 5-tir.o 6-insertion.o 7-explosions.o 9-fin.o 8-high_score.o $(CFLAGS)
		
zuma.o : zuma.c zuma.h
	gcc -c zuma.c $(CFLAGS)

###########################################

texte_SDL.o: texte_SDL.c texte_SDL.h
	gcc -c texte_SDL.c $(CFLAGS)

vecteurs.o: vecteurs.c vecteurs.h
	gcc -c vecteurs.c $(CFLAGS)
	
io_console.o: io_console.c io_console.h
	gcc -c io_console.c $(CFLAGS)

#########################################

1-initialisations.o: 1-initialisations.c zuma.h
	gcc -c 1-initialisations.c $(CFLAGS)

2-niveauEtParcours.o: 2-niveauEtParcours.c zuma.h
	gcc -c 2-niveauEtParcours.c $(CFLAGS)

3-affichage.o: 3-affichage.c zuma.h
	gcc -c 3-affichage.c $(CFLAGS)

4-avanceeFile.o:4-avanceeFile.c zuma.h
	gcc -c 4-avanceeFile.c $(CFLAGS)

5-tir.o: 5-tir.c zuma.h
	gcc -c 5-tir.c $(CFLAGS)
	
6-insertion.o: 6-insertion.c zuma.h
	gcc -c 6-insertion.c $(CFLAGS)
	
7-explosions.o: 7-explosions.c zuma.h
	gcc -c 7-explosions.c $(CFLAGS)
	
8-high_score.o : 8-high_score.c zuma.h
	gcc -c 8-high_score.c $(CFLAGS)
	
9-fin.o: 9-fin.c zuma.h
	gcc -c 9-fin.c $(CFLAGS)

clean:
	rm -rf *.o

