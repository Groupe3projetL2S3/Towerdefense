#include "../jeu.h"

s_Tower tower_init(s_Tower t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  t.type = 1; // a définir
  t.actif = 0;

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
  
  while (it != NULL) {
    s_Tower tow = it->t;
    float tir_priorite = 0.0;
    liste_mob mit = *M;
    tir.cible.numero = 0;
 
    if(temps_jeu - tow.temps > 50 && tow.actif){
	  
      while(mit != NULL){
	  
	s_Mob mo = mit->m;
	  
	if( abs((tow.coords.x + tow.rcSprite.w/2) - (mo.coords.x + mo.rcSprite.w/2)) < DISTANCE_MAGIC_TOWER && abs((tow.coords.y+tow.rcSprite.h/2)-(mo.coords.y+mo.rcSprite.h/2)) < DISTANCE_MAGIC_TOWER){
	     
	  if(mo.priorite > tir_priorite && mo.coords.x > 10){
	    tir = tir_spawn(tir, tow);
	    tir = direction_tir(tir, mo);
	    tir.cible = mo;
	  }
	  tir_priorite = mo.priorite;	     
	}
	mit->m = mo;
	mit = mit->next;	      
      }
      if(tir.cible.numero > 0 )
	tmp = liste_cons_tir(tir,tmp);

      tow.temps = temps_jeu;
    }
    *T = tmp;

    it->t = tow;
    it = it->next;
  }  
}


void tower_menu(s_Tower tower, liste_tower *T,  int event_button_x, int event_button_y, Map *map, Map *map_o) {

  int case1 = 0;
  liste_tower tmp2 = NULL;

  /* pour ajouter les 3 autres tours, il suffira de faire un switch avec un "case:" pour chaque bouton, puis mettre le contenu du "else" dans le cas général du switch. Puis je ferai une fonction "tower_add" pour racourcir le code (voir mob_add dans update_event) */

  if (event_button_x >= 9 && event_button_x <= 63
      && event_button_y >= 439 && event_button_y <= 493 && !case1 ) {
    case1 = 1;
    tmp2 = NULL;
    tmp2 = *T;
    tmp2 = liste_cons_tower(tower,tmp2);
    tmp2->t.coords.x = event_button_x - MAGIC_WIDTH / 2;
    tmp2->t.coords.y = event_button_y - MAGIC_HEIGHT /2 - 16;
    *T = tmp2;
  } else {

    if(*T == NULL)
      return;

    int x = (int) event_button_x/TILE_SIZE;
    int y = (int) event_button_y/TILE_SIZE;

    if (y < map->nbtiles_hauteur_monde && x < map->nbtiles_largeur_monde){
      if (map->tab_props[map->monde[x][y]].type == 1 && map_o->tab_props[map_o->monde[x][y]].type == 1 ){
	tmp2 = NULL;
	tmp2 = *T;
	if (!tmp2->t.actif){
	  tmp2->t.coords.x = (event_button_x / TILE_SIZE) * TILE_SIZE;
	  tmp2->t.coords.y = (event_button_y / TILE_SIZE) * TILE_SIZE -20; //on récup' les coords exactes ou afficher la tour
	  tmp2->t.actif = 1;
	  case1 = 0;
	}
	*T = tmp2;
      }
    }
  }
}

void tower_motion(liste_tower *T, int event_motion_x, int event_motion_y) {

  liste_tower tmp2 = NULL;

  if (*T != NULL) {
    tmp2 = *T;
    if (!tmp2->t.actif){
      tmp2->t.coords.x = event_motion_x - MAGIC_WIDTH / 2;
      tmp2->t.coords.y = event_motion_y - MAGIC_HEIGHT / 2 - 16; //pour centrer sur la souris
    }
    *T = tmp2;
  }  
}
