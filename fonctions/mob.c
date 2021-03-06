#include "../jeu.h"


s_Mob mob_spawn(s_Mob s_mob, Map *map, int taillew, int tailleh, float vit, int max_pv, int type) { //gère l'apparition du mob
  /* set mob speed */
  s_mob.vit.x = vit;
  s_mob.vit.y = 0.0;

  /* set sprite position */
  s_mob.coords.x = -30;
  s_mob.coords.y = SeekSpawn(map);
  
  /* set sprite animation frame */
  s_mob.rcSrc.x = 0;
  s_mob.rcSrc.y = 0;
  s_mob.rcSrc.w = taillew;
  s_mob.rcSrc.h = tailleh;

  /* initialisation des pv*/
  s_mob.pv_max = max_pv;
  s_mob.pv = s_mob.pv_max;

  /* init du type */
  s_mob.type = type;

  s_mob.slow = 0;
  s_mob.lvl_slow = 1;
  s_mob.animation = 0.0;
  s_mob.priorite = 0.0;
  s_mob.temps_deplacement = 0;
  
  return s_mob;
}

//deplacement des mobs + initialisatoin hitbox
s_Mob mob_deplacement(s_Mob s_mob) { 

  s_mob.coords.x = s_mob.coords.x + s_mob.vit.x/s_mob.lvl_slow;
  s_mob.coords.y = s_mob.coords.y + s_mob.vit.y/s_mob.lvl_slow;

  s_mob.priorite += fabs(s_mob.vit.x/s_mob.lvl_slow) + fabs(s_mob.vit.y/s_mob.lvl_slow); 


  s_mob.box.x = s_mob.coords.x + CREEP_WIDTH/2;
  s_mob.box.y = s_mob.coords.y + CREEP_HEIGHT/2;
  s_mob.box.w = s_mob.coords.x + s_mob.rcSrc.w - CREEP_WIDTH/2;
  s_mob.box.h = s_mob.coords.y + s_mob.rcSrc.h - CREEP_HEIGHT/2;
  
  return s_mob;
}

//IA des mobs pour qu'ils restent sur le chemin
s_Mob mob_parcours(s_Mob s_mob, Map *map){ 

  int x, y, marge, haut, bas, gauche, droite;
  float vit = fabs(s_mob.vit.x + s_mob.vit.y);
 
  x = (int) (s_mob.coords.x + s_mob.rcSrc.w/2 ) / TILE_SIZE;
  y = (int) (s_mob.coords.y + s_mob.rcSrc.h/2) / TILE_SIZE;
  marge = 8;
  
  if (s_mob.coords.x > TILE_SIZE && s_mob.coords.x < SCREEN_WIDTH - TILE_SIZE*1.5 ){
    haut = map->monde[x][y-1];
    gauche = map->monde[x-1][y];
    bas = map->monde[x][y+1];
    droite = map->monde[x+1][y];


    if (map->tab_props[droite].type != CHEMIN && map->tab_props[haut].type != CHEMIN && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = vit;
    }
    if (!haut && s_mob.vit.x > 0 && map->tab_props[droite].type != CHEMIN && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = vit;
    }
    if (map->tab_props[droite].type != CHEMIN && map->tab_props[bas].type != CHEMIN && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -vit;
    }



    if (map->tab_props[bas].type != CHEMIN && map->tab_props[droite].type != CHEMIN && s_mob.vit.y > 0 && s_mob.coords.y >= y*TILE_SIZE -marge){
      s_mob.vit.x = -vit;
      s_mob.vit.y = 0;
    }
    if (map->tab_props[bas].type != CHEMIN && map->tab_props[gauche].type != CHEMIN && s_mob.vit.y > 0 && s_mob.coords.y >= y*TILE_SIZE -marge){
      s_mob.vit.x = vit;
      s_mob.vit.y = 0;
    }



    if (map->tab_props[haut].type != CHEMIN && map->tab_props[droite].type != CHEMIN && s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge){
      s_mob.vit.x = -vit;
      s_mob.vit.y = 0;      
    }
    if (map->tab_props[haut].type != CHEMIN && map->tab_props[gauche].type != CHEMIN &&  s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge){
      s_mob.vit.x = vit;
      s_mob.vit.y = 0;
    }
    if (!haut &&  s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge){
      s_mob.vit.x = vit;
      s_mob.vit.y = 0;
    }



    if (map->tab_props[gauche].type != CHEMIN && map->tab_props[haut].type != CHEMIN && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = vit;
    }
    if (map->tab_props[gauche].type != CHEMIN && map->tab_props[bas].type != CHEMIN && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -vit;
    }
  }
  return s_mob;
}

//animation des pas des mobs
s_Mob mob_animation(s_Mob s_mob) {
  
  if (s_mob.vit.x > 0) {
    s_mob.animation += (s_mob.vit.x/s_mob.lvl_slow)*3;
    if (s_mob.animation >= 45) 
      s_mob.animation = 0.0;    
    s_mob.rcSrc.x = (int) (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  if (s_mob.vit.x < 0) {
    s_mob.animation += -(s_mob.vit.x/s_mob.lvl_slow)*3;
    if (s_mob.animation >= 45) 
      s_mob.animation = 0.0;    
    s_mob.rcSrc.x =(3*s_mob.rcSrc.w) +  (int) (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  
  if (s_mob.vit.y > 0) {
    s_mob.animation += (s_mob.vit.y/s_mob.lvl_slow)*3;
    if (s_mob.animation >= 30) 
      s_mob.animation = 0.0;    
    s_mob.rcSrc.x = (6*s_mob.rcSrc.w) + (int) (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  if (s_mob.vit.y < 0) {
    s_mob.animation += -(s_mob.vit.y/s_mob.lvl_slow)*3;
    if (s_mob.animation >= 30) 
      s_mob.animation = 0.0;    
    s_mob.rcSrc.x = (8*s_mob.rcSrc.w) +  (int) (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  return s_mob;
}

//affichage des mobs
void mob_affichage(liste_mob L, Map *map, SDL_Surface *screen, int temps_jeu) {

  liste_mob it = L;
      while (it != NULL) {
	s_Mob m = it->m;
	if(temps_jeu - m.temps_deplacement > 20){
	  m = mob_deplacement(m);
	  m = mob_animation(m);
	  m.temps_deplacement = temps_jeu;
	}



	m.rcSprite.x = (int) m.coords.x;
	m.rcSprite.y = (int) m.coords.y;
	if(!m.slow) {
	  SDL_BlitSurface(m.mob, &m.rcSrc, screen, &m.rcSprite);
	} else {
	  SDL_BlitSurface(m.frozen_mob, &m.rcSrc, screen, &m.rcSprite);
	}
	m = mob_parcours(m,map);
	it->m = m;
	it = it->next;
      }

}

//fonction pour ajouter un mob à la liste de mobs
void mob_add(int *i, s_Mob mob, liste_mob *L) {
  int j = 0;
  liste_mob tmp = NULL;

  j = *i +1;
  mob.numero = j;
  *i = j;
  tmp = *L;
  tmp = liste_cons_mob(mob, tmp);
  *L = tmp;
}

//ralentit les mobs affectés par le slow
void mob_slow(liste_mob *M, liste_tower *T, int colorkey) {
  
  liste_mob mit = *M;
  int range;
  while (mit != NULL) {

    s_Mob mo = mit->m;
    mo.slow = 0;

    liste_tower tit = *T;
      while (tit != NULL) {
	s_Tower tow = tit->t;
	if (tow.type == TYPE_SLOW && tow.actif){
	  range = in_range(tow, mo);
	  if(range){
	    mo.lvl_slow = tow.niveau +1;
	    mo.slow = 1;
	  }
	}
	tit->t = tow;
	tit = tit->next;  
      }

      if(!mo.slow){
	mo.lvl_slow = 1;
      }


      SDL_SetColorKey(mo.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
      mit->m = mo;
      mit = mit->next;
  }
}
