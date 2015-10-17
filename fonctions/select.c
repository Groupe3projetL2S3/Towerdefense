#include "../jeu.h"

s_Range Range_init(s_Range r, int taillew, int tailleh) {
 
  r.rcSrc.x = 0;
  r.rcSrc.y = 0;
  r.rcSrc.w = taillew;
  r.rcSrc.h = tailleh;

  return r;
}

s_Upgrade upgrade_init(s_Upgrade up, int taillew, int tailleh) {

  up.rcSrc.x = 0;
  up.rcSrc.y = 0;
  up.rcSrc.w = taillew;
  up.rcSrc.h = tailleh;

  return up;
}
  
s_Sell sell_init(s_Sell s, int taillew, int tailleh) {

  s.rcSrc.x = 0;
  s.rcSrc.y = 0;
  s.rcSrc.w = taillew;
  s.rcSrc.h = tailleh;

  return s;
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

void upgrade_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.up.rcSprite.x = (int) SCREEN_WIDTH - UP_WIDTH;
      t.up.rcSprite.y = 0;

      SDL_BlitSurface(t.up.up, &t.up.rcSrc, screen, &t.up.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}

void sell_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.sell.rcSprite.x = (int) SCREEN_WIDTH - SELL_WIDTH;
      t.sell.rcSprite.y = UP_HEIGHT;

      SDL_BlitSurface(t.sell.sell, &t.sell.rcSrc, screen, &t.sell.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}
