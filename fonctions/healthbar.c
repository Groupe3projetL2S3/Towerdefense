#include "../jeu.h"

s_Healthbar healthbar_init(s_Healthbar h, int taillew, int tailleh) {
 
  h.rcSrc.x = 0;
  h.rcSrc.y = 0;
  h.rcSrc.w = taillew;
  h.rcSrc.h = tailleh;

  return h;
}


void healthbar_affichage(liste_mob L, SDL_Surface *screen) {

  liste_mob it = L;
  float marge = 3.0;
  while (it != NULL) {
    s_Mob m = it->m;
	

    m.healthbar.rcSprite.x = (int) m.coords.x - marge;
    m.healthbar.rcSprite.y = (int) m.coords.y - marge;
    SDL_BlitSurface(m.healthbar.vie, &m.healthbar.rcSrc, screen, &m.healthbar.rcSprite);

    it->m = m;
    it = it->next;
  }
}
