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


void tower_tir (liste_tower *L, liste_mob *M, liste_tir *T, s_Tir tir, SDL_Surface *screen, int temps_jeu, s_Tower s_tower){
  
  
  liste_tower it = *L;

  liste_tir tmp = *T;


  if(liste_is_empty_mob(*M)==0){
    
    
    
    
    while (it != NULL) {
      s_Tower tow = it->t;
      float tir_priorite = 0;
      liste_mob mit = *M;
 

      if(temps_jeu - tow.temps > 1500 ){
	  
	while(mit != NULL){
	  
	  s_Mob mo = mit->m;
	  

	  
	  
	   if( abs((tow.coords.x + tow.rcSprite.w) - (mo.coords.x + mo.rcSprite.w)) < DISTANCE_MAGIC_TOWER && abs((tow.coords.y+tow.rcSprite.h)-(mo.coords.y+mo.rcSprite.h)) < DISTANCE_MAGIC_TOWER){
	     
	     if(mo.priorite > tir_priorite && mo.coords.x > 10){
	       
	       tir = tir_spawn(tir, tow);
	       tir = direction_tir(tir, mo);
	       tir.cible = mo;
	       
	     }
	     
	     tir_priorite = mo.priorite;
	     
	     if(mit->next == NULL){
	       
	       tmp = liste_cons_tir(tir,tmp);
	       *T = tmp;
	     }
	   }
	   
	   mit->m = mo;
	   mit = mit->next;	      

	}
	
	
	
	tow.temps = temps_jeu;
      }
      
      it->t = tow;
      it = it->next;
      
    }
    
  }
}
