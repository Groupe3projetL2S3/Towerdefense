jeu: jeu.c map.c mob.c liste.c tower.c tir.c collision.c jeu.h
	gcc -o jeu  jeu.c map.c mob.c liste.c tower.c tir.c collision.c -Wall -g `sdl-config --cflags --libs ` -lm 
clean:
	rm jeu

