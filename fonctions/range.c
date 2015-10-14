#include "../jeu.h"

s_Range Range_init(s_Range r, int taillew, int tailleh) {
 
  r.rcSrc.x = 0;
  r.rcSrc.y = 0;
  r.rcSrc.w = taillew;
  r.rcSrc.h = tailleh;

  return r;
}

void Range_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.range.rcSprite.x = (int) t.coords.x - (t.range.rcSrc.w - t.rcSrc.w)/2;
      t.range.rcSprite.y = (int) t.coords.y - (t.range.rcSrc.h - t.rcSrc.h)/2 + t.rcSrc.h/4;


      SDL_SetAlpha(t.range.range, SDL_SRCALPHA, 100);
      SDL_BlitSurface(t.range.range, &t.range.rcSrc, screen, &t.range.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}
