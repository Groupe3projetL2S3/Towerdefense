# definition des fichiers
FONCTIONS = jeu.c fonctions/map.c fonctions/mob.c fonctions/liste.c fonctions/tower.c fonctions/tir.c fonctions/collision.c fonctions/healthbar.c fonctions/select.c fonctions/autres.c fonctions/texte.c

CC = gcc


jeu: $(FONCTIONS) jeu.h
	$(CC) -o jeu  $(FONCTIONS) -g `sdl-config --cflags --libs ` -lm -lSDL_ttf	 
clean:
	rm jeu

#-Wall -Wno-switch
