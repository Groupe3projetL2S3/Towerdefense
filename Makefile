jeu: jeu.c jeu.h
	gcc -o jeu  jeu.c -g `sdl-config --cflags --libs ` -lm 
clean:
	rm jeu

