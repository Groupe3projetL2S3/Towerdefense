#include "../jeu.h"

s_Healthbar healthbar_init(s_Healthbar h, int taillew, int tailleh) {
 
  h.rcSrc.x = 0;
  h.rcSrc.y = 0;
  h.rcSrc.w = taillew;
  h.rcSrc.h = tailleh;

   return h;
}

s_Healthbar healthbar_deplacement(s_Healthbar h, s_Mob m) {
 
  h.coords.x = m.coords.x - 10;
  h.coords.y = m.coords.y;

  return h;
}

void healthbar_affichage(liste_healthbar L, SDL_Surface *screen) {

  liste_healthbar it = L;
      
      while (it != NULL) {
	s_Healthbar h = it->h;
	

	h.rcSprite.x = (int) h.coords.x;
	h.rcSprite.y = (int) h.coords.y;
	SDL_BlitSurface(h.vie, &h.rcSrc, screen, &h.rcSprite);

	it->h = h;
	it = it->next;
      }
}
