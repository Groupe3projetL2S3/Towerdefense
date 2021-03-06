#include "../jeu.h"

//initialisation de la structure des tours
s_Tower tower_init(s_Tower t, int taillew, int tailleh, int type, int distance, int cadence, int prix) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  t.type = type;
  t.actif = 0;
  t.select = 0;
  t.niveau = 1;
  t.price = prix;
  t.print_sell = 0;
  t.print_up = 0;
  t.range.range_max = distance;
  t.cadence = cadence;
  t.temps = 0;
  return t;
}

//affichage des tours
void tower_affichage(liste_tower L, SDL_Surface *screen) {
  liste_tower it = liste_tri_tower(L);

  while (it != NULL) {
    s_Tower t = it->t;
    t.rcSprite.x = (int) t.coords.x;
    t.rcSprite.y = (int) t.coords.y;
    SDL_BlitSurface(t.tower, &t.rcSrc, screen, &t.rcSprite);

    it->t = t;
    it = it->next;
  }
}

//gestion des spawns des tirs des tours
void tower_tir (liste_tower *L, liste_mob *M, liste_tir *T, s_Tir tir_magic, s_Tir tir_sniper, s_Tir tir_fire, SDL_Surface *screen, int temps_jeu, s_Tower s_tower){
    
  liste_tower it = *L;
  liste_tir tmp = *T;
  s_Tir tir;

  
  while (it != NULL) {
    s_Tower tow = it->t;
    float tir_priorite = 0.0;
    liste_mob mit = *M;
    int range;

    if(tow.type == TYPE_SNIPER){
      tir = tir_sniper;
      tir.type = TYPE_SNIPER;
      }
    if(tow.type == TYPE_MAGIC){
      tir = tir_magic;
      tir.type = TYPE_MAGIC;
      }
    if(tow.type == TYPE_FIRE){
      tir = tir_fire;
      tir.type = TYPE_FIRE;
      }
    if(tow.type == TYPE_SLOW){
      tir.type = TYPE_SLOW;
      }

    tir.cible.numero = 0;
 
    if(temps_jeu - tow.temps > tow.cadence && tow.actif){ // definir la cadence par tower
	  
      while(mit != NULL){
	s_Mob mo = mit->m;
	range = in_range(tow, mo);

	if(range){
	     
	  if (tow.type == TYPE_MAGIC || tow.type == TYPE_SNIPER) {
	    if(mo.priorite > tir_priorite && mo.coords.x > 10){
	      tir = tir_spawn(tir, tow);
	      tir = direction_tir(tir, mo);
	      tir.cible = mo;
	    }
	    tir_priorite = mo.priorite;
	    }
	  if (tow.type == TYPE_FIRE) {
	    tir = tir_spawn(tir, tow);
	    tir = direction_tir(tir, mo);
	    tir.cible = mo;
	    tmp = liste_cons_tir(tir, tmp);
	    }
	}

	mit->m = mo;
	mit = mit->next;	      
      }
      if(tir.cible.numero > 0 && tir.type != TYPE_SLOW){
	tmp = liste_cons_tir(tir,tmp);
      }
      tow.temps = temps_jeu;
    }
    *T = tmp;

    it->t = tow;
    it = it->next;
  }  
}

//gestion du menu d'achat (en bas de l'écran)
void tower_menu(s_Tower sniper, s_Tower magic, s_Tower fire, s_Tower slow, liste_tower *T,  int event_button_x, int event_button_y, Map *map, Map *map_o, int *case1, int *case2, int *case3, int *case4, int *money) {

  liste_tower tmp2 = NULL;
  int posay;
  int mny = *money;

  if (event_button_x >= 9 && event_button_x <= 63
      && event_button_y >= 439 && event_button_y <= 493 && *case1
      && mny >= sniper.price){
    tower_add(T, sniper, case1, case2, case3, case4, event_button_x, event_button_y);
    mny = mny - sniper.price;
  }
  else if (event_button_x >= 177 && event_button_x <= 231 
	   && event_button_y >= 439 && event_button_y <= 493 && *case2
	   && mny >= magic.price){
    tower_add(T, magic, case1, case2, case3, case4, event_button_x, event_button_y);
    mny = mny - magic.price;
  } 
  else if (event_button_x >= 345 && event_button_x <= 399 
	   && event_button_y >= 439 && event_button_y <= 493 && *case3
	   && mny >= fire.price){
    tower_add(T, fire, case1, case2, case3, case4, event_button_x, event_button_y);
    mny = mny - fire.price;
  } 
  else if (event_button_x >= 513&& event_button_x <= 567
	   && event_button_y >= 439 && event_button_y <= 493 && *case4
	   && mny >= slow.price){
    tower_add(T, slow, case1, case2, case3, case4, event_button_x, event_button_y);
    mny = mny - slow.price;
  } 

else {
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
	  *case3 = 1;
	  *case4 = 1;
	  tmp2 = liste_tri_tower(tmp2);
	}
	*T = tmp2;
      }
    }
  }
  *money = mny;
}

//fonction qui permet à la tour de suivre la souris apres achat
void tower_motion(liste_tower T, int event_motion_x, int event_motion_y) {

  liste_tower it = T;

  while (it != NULL) {
    s_Tower t = it->t;

    if (!t.actif){
      t.coords.x = event_motion_x - MAGIC_WIDTH / 2;
      t.coords.y = event_motion_y - MAGIC_HEIGHT / 2 - TILE_SIZE/2; //pour centrer sur la souris
    }

    it->t = t;
    it = it->next;
  }

}

//gestion de la selection des tours
void tower_select(liste_tower T, int event_button_x, int event_button_y) {

  liste_tower it = T;

  while (it != NULL) {
    s_Tower t = it->t;

    if (event_button_x >= t.coords.x
	&& event_button_x <= t.coords.x + t.rcSrc.w
	&& event_button_y >= t.coords.y + t.rcSrc.h-TILE_SIZE
	&& event_button_y <= t.coords.y + t.rcSrc.h)
      t.select = 1;
    
    else if (event_button_x >= (t.up.rcSprite.x) 
	     && event_button_x <= (t.up.rcSprite.x + t.up.rcSrc.w) 
	     && event_button_y >= (t.up.rcSprite.y)
	     && event_button_y <= (t.up.rcSprite.y + t.up.rcSrc.h) 
	     && t.select == 1)
      t.select = 1;
    else if (event_button_x >= (t.sell.rcSprite.x)
	     && event_button_x <= (t.sell.rcSprite.x + t.sell.rcSrc.w)
	     && event_button_y >= (t.sell.rcSprite.y)
	     && event_button_y <= (t.sell.rcSprite.y + t.sell.rcSrc.h)
	     && t.select == 1)
      t.select = 1;
    else
      t.select = 0;

    it->t = t;
    it = it->next;
  }
}

//fonction qui retourne si la tour est posée ou non
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

//ajoute une tour a la liste
void tower_add(liste_tower *T, s_Tower tower, int *case1, int *case2, int *case3, int *case4, int event_button_x, int event_button_y) {
 
  liste_tower tmp2;
  tmp2 = NULL;
  tmp2 = *T;
  tower.coords.x = event_button_x - SNIPER_WIDTH / 2;
  tower.coords.y = event_button_y - SNIPER_HEIGHT /2 - TILE_SIZE/2;
  tmp2 =liste_cons_tower(tower,tmp2);

  *T = tmp2;
  *case1 = 0;
  *case2 = 0;
  *case3 = 0;
  *case4 = 0;
  
}

//initalisation des tours pour l'upgrade
s_Tower towerup_init(s_Tower t, s_Tower t_up, int distance) {
  
  t_up.rcSrc = t.rcSrc;
  t_up.range.rcSrc = t.range.rcSrc;
  t_up.range.rcSrc.w = distance;
  t_up.range.rcSrc.h = distance;
  t_up.coords = t.coords;
  t_up.niveau = t.niveau + 1;
  t_up.type = t.type;
  t_up.actif = t.actif;
  t_up.select = t.select;
  t_up.temps = t.temps;
  t_up.print_sell = t.print_sell;
  t_up.print_up = t.print_up;
  if(t.type == TYPE_SNIPER)
    t_up.range.range_max = t.range.range_max +20;
  if(t.type == TYPE_MAGIC)
    t_up.range.range_max = t.range.range_max +10;
  if(t.type == TYPE_FIRE){
    if(t.niveau == 1)
      t_up.range.range_max = t.range.range_max +5;
    else
      t_up.range.range_max = t.range.range_max +10;
  }
  if(t.type == TYPE_SLOW)
    t_up.range.range_max = t.range.range_max;
  if(t.type == TYPE_FIRE)
    t_up.cadence = t.cadence;
  else
    t_up.cadence = t.cadence/1.5;
  t_up.price = t.price*2;

  return t_up;
}

//gestion des actions sur les tours (upgrade, sell)
void tower_gestion(liste_tower *T, s_Tower sniper2, s_Tower sniper3, s_Tower magic2, s_Tower magic3, s_Tower fire2, s_Tower fire3, s_Tower slow2, s_Tower slow3, int event_button_x, int event_button_y, int *money) {

  liste_tower new_liste_tower = NULL;
  liste_tower poubelle_tower = NULL;
  int mny = *money;

  liste_tower tit = *T;

      while(tit != NULL) {
	
	s_Tower t = tit->t;
	if (t.select == 1 && t.actif == 1 && mny >= t.price*2
	    && event_button_x >= (t.up.rcSprite.x) 
	    && event_button_x <= (t.up.rcSprite.x + t.up.rcSrc.w) 
	    && event_button_y >= (t.up.rcSprite.y)
	    && event_button_y <= (t.up.rcSprite.y + t.up.rcSrc.h) 
	    && t.niveau < 3 ) {
	  poubelle_tower = liste_cons_tower(t, poubelle_tower);
	  if (t.type == TYPE_SNIPER) {
	    if (t.niveau == 2) {
	      sniper3 = towerup_init(t, sniper3, DISTANCE_SNIPER_TOWER3*2);
	      new_liste_tower = liste_cons_tower(sniper3, new_liste_tower);
	      mny = mny - sniper3.price;
	    }
	    if (t.niveau == 1) {
	      sniper2 = towerup_init(t, sniper2, DISTANCE_SNIPER_TOWER2*2);
	      new_liste_tower = liste_cons_tower(sniper2, new_liste_tower);
	      mny = mny - sniper2.price;
	    }
	  }
	  if (t.type == TYPE_MAGIC) {
	    if (t.niveau == 2) {
	      magic3 = towerup_init(t, magic3, DISTANCE_MAGIC_TOWER3*2); 
	      new_liste_tower = liste_cons_tower(magic3, new_liste_tower);
	      mny = mny - magic3.price;
	    }
	    if (t.niveau == 1) {
	      magic2 = towerup_init(t, magic2, DISTANCE_MAGIC_TOWER2*2);
	      new_liste_tower = liste_cons_tower(magic2, new_liste_tower);
	      mny = mny - magic2.price;
	    }
	  }
	  if (t.type == TYPE_FIRE) {
	    if (t.niveau == 2) {
	      fire3 = towerup_init(t, fire3, DISTANCE_FIRE_TOWER3*2);
	      new_liste_tower = liste_cons_tower(fire3, new_liste_tower);
	      mny = mny - fire3.price;
	    }
	    if (t.niveau == 1) {
	      fire2 = towerup_init(t, fire2, DISTANCE_FIRE_TOWER2*2);
	      new_liste_tower = liste_cons_tower(fire2, new_liste_tower);
	      mny = mny - fire2.price;
	    }
	  }
	  if (t.type == TYPE_SLOW) {
	    if (t.niveau == 2) {
	      slow3 = towerup_init(t, slow3, DISTANCE_SLOW_TOWER*2);
	      new_liste_tower = liste_cons_tower(slow3, new_liste_tower);
	      mny = mny - slow3.price;
	    }
	    if (t.niveau == 1) {
	      slow2 = towerup_init(t, slow2, DISTANCE_SLOW_TOWER*2);
	      new_liste_tower = liste_cons_tower(slow2, new_liste_tower);
	      mny = mny - slow2.price;
	    }
	  }
	  //mny = mny - t.price;
	}	    
	else if (t.select == 1 && t.actif == 1 
		 && event_button_x >= (t.sell.rcSprite.x)
		 && event_button_x <= (t.sell.rcSprite.x + t.sell.rcSrc.w)
		 && event_button_y >= (t.sell.rcSprite.y)
		 && event_button_y <= (t.sell.rcSprite.y + t.sell.rcSrc.h)) {
	  poubelle_tower = liste_cons_tower(t, poubelle_tower);
	  mny = mny + (t.price/2);
	}
	else {
	  new_liste_tower = liste_cons_tower(t, new_liste_tower);
	}
	tit->t = t;
	tit = tit->next;
      }
      liste_free_tower(&poubelle_tower);
      liste_inverser_tower(&new_liste_tower);
      *T = new_liste_tower;
      new_liste_tower = NULL;
      liste_free_tower(&new_liste_tower);
      *money = mny;
}
    
//Test si un mob est dans la range d'une tour
int in_range(s_Tower t, s_Mob m){

  float distance;
  distance = sqrt(pow(t.range.coords.x - (m.coords.x + m.rcSrc.w/2), 2) + pow(t.range.coords.y - (m.coords.y + m.rcSrc.h/2), 2));

  if (distance < t.range.range_max){
    return 1;
  }
  return 0;
}

