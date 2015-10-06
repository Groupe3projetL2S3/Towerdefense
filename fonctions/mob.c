#include "../jeu.h"


s_Mob mob_spawn(s_Mob s_mob, Map *map, int taillew, int tailleh, float vit) { //gère l'apparition du mob
  /* set mob speed */
  s_mob.vit.x = vit;
  s_mob.vit.y = 0.0;

  /* set sprite position */
  s_mob.coords.x = -30;
  s_mob.coords.y = SeekSpawn(map);
  printf("%f \n", s_mob.coords.y);
  
  /* set sprite animation frame */
  s_mob.rcSrc.x = 0;
  s_mob.rcSrc.y = 0;
  s_mob.rcSrc.w = taillew;
  s_mob.rcSrc.h = tailleh;

  s_mob.animation = 0;
  s_mob.priorite = 0.0;
  
  return s_mob;
}
s_Mob mob_deplacement(s_Mob s_mob) { 

  s_mob.coords.x = s_mob.coords.x + s_mob.vit.x;
  s_mob.coords.y = s_mob.coords.y + s_mob.vit.y;

  s_mob.priorite += fabs(s_mob.vit.x) + fabs(s_mob.vit.y);


  s_mob.box.x = s_mob.coords.x;
  s_mob.box.y = s_mob.coords.y;
  s_mob.box.w = s_mob.coords.x + s_mob.rcSrc.w;
  s_mob.box.h = s_mob.coords.y + s_mob.rcSrc.h;
  
  return s_mob;
}

s_Mob mob_parcours(s_Mob s_mob, Map *map){
  
  int x, y, marge, haut, bas, gauche, droite;
  float vit = fabs(s_mob.vit.x + s_mob.vit.y);
 
  x = (int) (s_mob.coords.x + CREEP_WIDTH/2 ) / TILE_SIZE;
  y = (int) (s_mob.coords.y +  CREEP_HEIGHT/2) / TILE_SIZE;
  marge = 8;
  
  if (s_mob.coords.x > TILE_SIZE && s_mob.coords.x < SCREEN_WIDTH - TILE_SIZE*1.5 ){
    haut = map->monde[x][y-1];
    gauche = map->monde[x-1][y];
    bas = map->monde[x][y+1];
    droite = map->monde[x+1][y];

    
    if (map->tab_props[droite].type == TERRAIN && map->tab_props[haut].type == TERRAIN && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = vit;
    }
    if (map->tab_props[droite].type == TERRAIN && map->tab_props[bas].type == TERRAIN && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -vit;
    }



    if (map->tab_props[bas].type == TERRAIN && map->tab_props[droite].type == TERRAIN && s_mob.vit.y > 0 && s_mob.coords.y >= y*TILE_SIZE -marge){
      s_mob.vit.x = -vit;
      s_mob.vit.y = 0;
    }
    if (map->tab_props[bas].type == TERRAIN && map->tab_props[gauche].type == TERRAIN && s_mob.vit.y > 0 && s_mob.coords.y >= y*TILE_SIZE -marge){
      s_mob.vit.x = vit;
      s_mob.vit.y = 0;
    }



    if (map->tab_props[haut].type == TERRAIN && map->tab_props[droite].type == TERRAIN && s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge){
      s_mob.vit.x = -vit;
      s_mob.vit.y = 0;      
    }
    if (map->tab_props[haut].type == TERRAIN && map->tab_props[gauche].type == TERRAIN &&  s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge){
      s_mob.vit.x = vit;
      s_mob.vit.y = 0;
    }



    if (map->tab_props[gauche].type == TERRAIN && map->tab_props[haut].type == TERRAIN && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = vit;
    }
    if (map->tab_props[gauche].type == TERRAIN && map->tab_props[bas].type == TERRAIN && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -vit;
    }
  }
  return s_mob;
}

s_Mob mob_animation(s_Mob s_mob) {

  if (s_mob.vit.x > 0) {
    s_mob.animation += 1;
    if (s_mob.animation >= 45) 
      s_mob.animation = 0;    
    s_mob.rcSrc.x = (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  if (s_mob.vit.x < 0) {
    s_mob.animation += 1;
    if (s_mob.animation >= 45) 
      s_mob.animation = 0;    
    s_mob.rcSrc.x = (3*s_mob.rcSrc.w) + (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  
  if (s_mob.vit.y > 0) {
    s_mob.animation += 1;
    if (s_mob.animation >= 30) 
      s_mob.animation = 0;    
    s_mob.rcSrc.x = (6*s_mob.rcSrc.w) + (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  if (s_mob.vit.y < 0) {
    s_mob.animation += 1;
    if (s_mob.animation >= 30) 
      s_mob.animation = 0;    
    s_mob.rcSrc.x = (8*s_mob.rcSrc.w) + (s_mob.animation/15)* s_mob.rcSrc.w;
  }
  


  return s_mob;
}


void mob_affichage(liste_mob L, Map *map, SDL_Surface *screen) {

      liste_mob it = L;
      
      while (it != NULL) {
	s_Mob m = it->m;
	m = mob_deplacement(m);
	m = mob_animation(m);

	//printf("%f %f %f %f \n", m.box.x,m.box.y,m.box.w,m.box.h);
	

	m.rcSprite.x = (int) m.coords.x;
	m.rcSprite.y = (int) m.coords.y;
	SDL_BlitSurface(m.mob, &m.rcSrc, screen, &m.rcSprite);
	
	m = mob_parcours(m,map);
	it->m = m;
	it = it->next;
      }
}
