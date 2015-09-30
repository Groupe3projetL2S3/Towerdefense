jeu: jeu.c map.c mob.c liste.c tower.c tir.c jeu.h
	gcc -o jeu  jeu.c map.c mob.c liste.c tower.c tir.c -g `sdl-config --cflags --libs ` -lm 
clean:
	rm jeu

