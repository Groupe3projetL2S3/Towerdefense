#include "jeu.h"

s_Tower tower_init(s_Tower t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  return t;
}


void tower_affichage(liste_tower L, s_Tower t, SDL_Surface *screen) {

      liste_tower it = L;
      
      while (it != NULL) {
	s_Tower t = it->t;
	
	t.rcSprite.x = (int) t.coords.x;
	t.rcSprite.y = (int) t.coords.y;
	SDL_BlitSurface(t.tower, &t.rcSrc, screen, &t.rcSprite);

	it->t = t;
	it = it->next;
      }
}
