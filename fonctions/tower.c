#include "../jeu.h"

s_Tower tower_init(s_Tower t, int taillew, int tailleh, int type) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  t.type = type;
  t.actif = 0;
  t.select = 0;
  t.niveau = 1;

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


void tower_menu(s_Tower sniper, s_Tower magic, liste_tower *T,  int event_button_x, int event_button_y, Map *map, Map *map_o, int *case1, int *case2, int *case3, int *case4) {

  liste_tower tmp2 = NULL;
  int posay;

  if (event_button_x >= 9 && event_button_x <= 63
      && event_button_y >= 439 && event_button_y <= 493 && *case1){
    tower_add(T, sniper, case1, case2, case3, case4, event_button_x, event_button_y);
  }
  else if (event_button_x >= 177 && event_button_x <= 231 
	   && event_button_y >= 439 && event_button_y <= 493 && *case2){
tower_add(T, magic, case1, case2, case3, case4, event_button_x, event_button_y);

  } else {
    if(*T == NULL)
      return;

    int x = (int) event_button_x/TILE_SIZE;
    int y = (int) event_button_y/TILE_SIZE;
    if (y < map->nbtiles_hauteur_monde && x < map->nbtiles_largeur_monde){
      if (map->tab_props[map->monde[x][y]].type == 1 && map_o->tab_props[map_o->monde[x][y]].type == 1){
	tmp2 = NULL;
	tmp2 = *T;
	posay = tower_posay(T, event_button_x, event_button_y);
	if (!tmp2->t.actif && posay){
	  tmp2->t.coords.x = (event_button_x / TILE_SIZE) * TILE_SIZE;
	  tmp2->t.coords.y = (event_button_y / TILE_SIZE) * TILE_SIZE - TILE_SIZE/2; //on récup' les coords exactes ou afficher la tour
	  tmp2->t.actif = 1;
	  *case1 = 1;
	  *case2 = 1;
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


void tower_select(liste_tower *T, int event_button_x, int event_button_y) {

  liste_tower it = *T;

  while (it != NULL) {
    s_Tower t = it->t;
	
    if (event_button_x >= t.coords.x
	&& event_button_x <= t.coords.x + t.rcSrc.w
	&& event_button_y >= t.coords.y + t.rcSrc.h-TILE_SIZE
	&& event_button_y <= t.coords.y + t.rcSrc.h)
      t.select = 1;
    
    else if (event_button_x >= SCREEN_WIDTH - UP_WIDTH
	     && event_button_y <= UP_HEIGHT + SELL_HEIGHT
	     && t.select == 1)
      t.select = 1;
    
    else
      t.select = 0;

    it->t = t;
    it = it->next;
  }
}


int tower_posay(liste_tower *T, int event_button_x, int event_button_y){
   liste_tower it = *T;
   int posay = 1;
  while (it != NULL) {
    s_Tower t = it->t;
    
    if (event_button_x >= t.coords.x && event_button_x <= t.coords.x + TILE_SIZE
	&& event_button_y >= t.coords.y + (t.rcSrc.h - TILE_SIZE) && event_button_y <= t.coords.y + TILE_SIZE + (t.rcSrc.h - TILE_SIZE) && t.actif) {
      posay = 0;
    }

    it->t = t;
    it = it->next;
  }
  return posay;
}


void tower_add(liste_tower *T, s_Tower tower, int *case1, int *case2, int *case3, int *case4, int event_button_x, int event_button_y) {
 
  liste_tower tmp2;
  tmp2 = NULL;
  tmp2 = *T;
  tmp2 =liste_cons_tower(tower,tmp2);
  tmp2->t.coords.x = event_button_x - SNIPER_WIDTH / 2;
  tmp2->t.coords.y = event_button_y - SNIPER_HEIGHT /2 - 16;
  *T = tmp2;
  *case1 = 0;
  *case2 = 0;
  *case3 = 0;
  *case4 = 0;
  
}

s_Tower towerup_init(s_Tower t, s_Tower t_up) {
  
  t_up.rcSrc = t.rcSrc;
  t_up.coords = t.coords;
  t_up.niveau = t.niveau + 1;
  t_up.type = t.type;


  return t_up;
}


void tower_gestion(liste_tower *T, s_Tower sniper2, s_Tower sniper3, s_Tower magic2, int event_button_x, int event_button_y) {

  liste_tower new_liste_tower = NULL;
  liste_tower poubelle_tower = NULL;


  liste_tower tit = *T;


  if (!liste_is_empty_tower(tit)) {
    
      tit = *T;
      
      while(tit != NULL) {
	
	s_Tower t = tit->t;
	
	
	if (t.select == 1 && event_button_x >= (SCREEN_WIDTH - UP_WIDTH)
	    && event_button_y <= UP_HEIGHT) {
	  poubelle_tower = liste_cons_tower(t, poubelle_tower);
	  if (t.type == SNIPER) {
	    printf("t.niveau avant up : %d \n", t.niveau);
	    if (t.niveau == 2) {
	      sniper3 = towerup_init(t, sniper3);
	      new_liste_tower = liste_cons_tower(sniper3, new_liste_tower);
	    }
	    if (t.niveau == 1) {
	      sniper2 = towerup_init(t, sniper2);
	      new_liste_tower = liste_cons_tower(sniper2, new_liste_tower);
	    }
	  }
	}
	    
	else if (t.select == 1 && event_button_x >= SCREEN_WIDTH - SELL_WIDTH
		 && event_button_y <= SELL_HEIGHT + UP_HEIGHT
		 && event_button_y > UP_HEIGHT) {
	  poubelle_tower = liste_cons_tower(t, poubelle_tower);
	}
	else {
	  new_liste_tower = liste_cons_tower(t, new_liste_tower);
	}
	tit->t = t;
	tit = tit->next;
      }
      liste_free_tower(&poubelle_tower);
      *T = new_liste_tower;
      new_liste_tower = NULL;
      liste_free_tower(&new_liste_tower);

  }
}
      
