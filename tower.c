#include "jeu.h"

s_Tower tower_init(s_Tower t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;

  t.temps = 0;
  return t;
}


void tower_affichage(liste_tower L, liste_mob M, liste_tir *T, s_Tir tir, SDL_Surface *screen, int temp_jeu) {

      liste_tower it = L;
      liste_tir tmp = *T;

      s_Mob mob;
      
      while (it != NULL) {
	s_Tower t = it->t;
	
	if(liste_is_empty_mob(M)==0){

	  mob = liste_head_mob(M);

	  if(temp_jeu - t.temps > 300 && abs(t.coords.x-mob.coords.x) < 500 && abs(t.coords.y-mob.coords.y) < 500 ){
	    
	    tir = tir_spawn(tir, t);
	    tir = direction_tir(tir,M);
	    tmp = liste_cons_tir(tir,tmp);
	    *T = tmp;
	    t.temps = temp_jeu;
	  }
	}
	t.rcSprite.x = (int) t.coords.x;
	t.rcSprite.y = (int) t.coords.y;
	SDL_BlitSurface(t.tower, &t.rcSrc, screen, &t.rcSprite);

	it->t = t;
	it = it->next;
      }
}
