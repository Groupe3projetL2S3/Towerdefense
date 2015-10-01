#include "jeu.h"

s_Tower tower_init(s_Tower t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;

  t.temps = 0;
  return t;
}


void tower_affichage(liste_tower L, SDL_Surface *screen) {

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


void tower_tir (liste_tower *L, liste_mob M, liste_tir *T, s_Tir tir, SDL_Surface *screen, int temps_jeu){
  

  liste_tower it = *L;

  liste_mob mit = M;

  liste_tir tmp = *T;


  if(liste_is_empty_mob(M)==0){

    while (it != NULL) {
      s_Tower tow = it->t;
      
	
      if(temps_jeu - tow.temps > 1500 ){

	while(mit != NULL){
	
	  s_Mob m = mit->m;
	  
	  if( abs((tow.coords.x + tow.rcSprite.w) - (m.coords.x + m.rcSprite.w)) < DISTANCE_MAGIC_TOWER && abs((tow.coords.y+tow.rcSprite.h)-(m.coords.y+m.rcSprite.h)) < DISTANCE_MAGIC_TOWER){

	    tir = tir_spawn(tir, tow);
	    printf("%d \n",m.numero);
	    tir = direction_tir(tir, m);
	    tir.cible = m;
	    tmp = liste_cons_tir(tir,tmp);
	    *T = tmp;

	    }

	  mit->m = m;
	  mit = mit->next;
	  tow.temps = temps_jeu;

	  }

	
      }

      it->t = tow;
      it = it->next;
      
    }
  }
}
