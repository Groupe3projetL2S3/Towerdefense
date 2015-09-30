#include "jeu.h"

s_Tir tir_init(s_Tir t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  return t;
}


void tir_affichage(liste_tir L, s_Tir t, SDL_Surface *screen) {

      liste_tir it = L;
      
      while (it != NULL) {
	s_Tir t = it->t;
	
	t = deplacement_tir(t);
	t.rcSprite.x = (int) t.coords.x;
	t.rcSprite.y = (int) t.coords.y;

	SDL_BlitSurface(t.tir, &t.rcSrc, screen, &t.rcSprite);

	it->t = t;
	it = it->next;
      }
}


s_Tir tir_spawn(s_Tir t, s_Tower to) { 
  t.coords.x = to.coords.x;
  t.coords.y = to.coords.y;

  return t;
}

s_Tir direction_tir(s_Tir t, liste_mob L) { //à faire appel quand il spawn
  float alpha;
  s_Mob m;
  m = liste_head_mob(L);

  float xm = m.coords.x + CREEP_WIDTH/2;
  float ym = m.coords.y + CREEP_HEIGHT/2;
  float xt = t.coords.x + TIR_WIDTH/2;
  float yt = t.coords.y + TIR_HEIGHT/2;

  if (xm >= (xt) && ym <= (yt)){
    alpha = (xm-xt)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acos(alpha);
    t.vit.x=cos(alpha);
    t.vit.y=-sin(alpha);
  }
  if (xm < (xt) && ym <= (yt)){
    alpha = (xt-xm)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acos(alpha);
    t.vit.x=-cos(alpha);
    t.vit.y=-sin(alpha);
  }
  if (xm < (xt) && ym > (yt)){
    alpha = (xt-xm)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acos(alpha);
    t.vit.x=-cos(alpha);
    t.vit.y=sin(alpha);
  }
  if (xm >= (xt) && ym > (yt)){
    alpha = (xm-xt)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acos(alpha);
    t.vit.x=cos(alpha);
    t.vit.y=sin(alpha);
  }

  return t;
}


s_Tir deplacement_tir(s_Tir t) { //à faire appel dans affichage

  t.coords.x += t.vit.x*2;
  t.coords.y += t.vit.y*2;

  return t;
}
