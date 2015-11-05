#include "../jeu.h"

s_Range Range_init(s_Range r, int taillew, int tailleh) {
 
  r.rcSrc.x = 0;
  r.rcSrc.y = 0;
  r.rcSrc.w = taillew;
  r.rcSrc.h = tailleh;

  return r;
}

s_Menu menu_select_init(s_Menu menu, int taillew, int tailleh) {

  menu.rcSrc.x = 0;
  menu.rcSrc.y = 0;
  menu.rcSrc.w = taillew;
  menu.rcSrc.h = tailleh;

  return menu;
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

      t.range.coords.x = t.coords.x + t.rcSrc.w/2;
      t.range.coords.y = t.coords.y + 2*(t.rcSrc.h/3);


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
      t.up.rcSprite.x = MENU_SELECT_WIDTH - UP_WIDTH - 7;
      t.up.rcSprite.y = 8;

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
      t.sell.rcSprite.x = MENU_SELECT_WIDTH - SELL_WIDTH - 7;
      t.sell.rcSprite.y = UP_HEIGHT + 12;

      SDL_BlitSurface(t.sell.sell, &t.sell.rcSrc, screen, &t.sell.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}

void menu_select_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.menu.rcSprite.x = 0;
      t.menu.rcSprite.y = 0;

      SDL_BlitSurface(t.menu.menu, &t.menu.rcSrc, screen, &t.menu.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}
