# definition des fichiers
FONCTIONS = jeu.c fonctions/map.c fonctions/mob.c fonctions/liste.c fonctions/tower.c fonctions/tir.c fonctions/collision.c

CC = gcc


jeu: $(FONCTIONS) jeu.h
	$(CC) -o jeu  $(FONCTIONS) -Wall -g `sdl-config --cflags --libs ` -lm 
clean:
	rm jeu

