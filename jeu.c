#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

SDL_Surface* Load_image(const char* image) {
  SDL_Surface* res;
  SDL_Surface* temp = SDL_LoadBMP(image);
  if (temp == NULL) {
    printf("Load_image error ! \n");
    exit(ERROR);
  }
  res = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return res;
}



/******************************          Programme          *******************************/

/* varaible pour les phases de jeux */

int gameover;


/* SDL Function */
void update_events(char* keys, liste_mob *L, liste_tower *T, s_Mob mob, s_Tower tower,Map *map, Map *map_o,int *i)
{
  SDL_Event event;
  liste_mob tmp;
  liste_tower tmp2;
  int j;
  

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      gameover = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
	
      case SDLK_q:
      case SDLK_ESCAPE:
	gameover = 1;
	break;
      case SDLK_d:
	j = *i +1;
	mob.numero = j;
	*i = j;
	tmp = *L;
	tmp = liste_cons_mob(mob,tmp);
	*L = tmp;
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;

    case SDL_MOUSEBUTTONDOWN:    
      switch(event.button.button){
	
      case SDL_BUTTON_LEFT:   

	if (event.button.button == SDL_BUTTON_LEFT){
	  tower.coords.x = (event.button.x / TILE_SIZE) * TILE_SIZE;
	  tower.coords.y = (event.button.y / TILE_SIZE) * TILE_SIZE -20; //on récup' les coords exactes ou afficher la tour
	  int x = (int) event.button.x/TILE_SIZE;
	  int y = (int) event.button.y/TILE_SIZE;

	  if (map->tab_props[map->monde[x][y]].type == 1 && map_o->tab_props[map_o->monde[x][y]].type == 1 ){
	    tmp2 = *T;
	    tmp2 = liste_cons_tower(tower,tmp2);
	    *T = tmp2;
	  }
	}
	break;
      }
      keys[event.button.button] = 1;
      break; 
    }
  }
}



/* ******************************************   MAIN   ********************************************** */




int main(int argc, char* argv[])
{
  SDL_Surface *screen = NULL;

  int colorkey, colorkeyN;

  s_Mob creep;
  s_Tower magic;
  s_Tir tir_magic;
  S_Healthbar hb;

  liste_mob liste_creep = NULL;
  liste_tower liste_magic = NULL;
  liste_tir liste_tir_magic = NULL;
  liste_healthbar liste_hb = NULL;

  Map* map = NULL;
  Map* map_objet = NULL;

  int temps_jeu = 0;
  int num_mob = 0;

  /* set the title bar */
  SDL_WM_SetCaption("Tower Defense", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);
  
 
  /* **********************   LOAD IMAGE ******************* */
  map = LoadMap("monde.txt");
  map_objet = LoadMap("objet.txt");
  
  creep.mob = Load_image("Images/sprite_creeper.bmp");
  magic.tower = Load_image("Images/tower_magic1.bmp");
  tir_magic.tir = Load_image("Images/tir.bmp");
  hb.vie = Load_image("Images/healthbar.bmp");

  /* ********************   colorkey ******************* */

  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);
  colorkeyN =  SDL_MapRGB(screen->format, 0, 0, 0);

  SDL_SetColorKey(map_objet->tileset, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(creep.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(tir_magic.tir, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkeyN);

  char key[SDLK_LAST] = {0};
  gameover = 0;
  
  /* ******************** boucle principale ******************* */
  
  
  creep = mob_spawn(creep, map, CREEP_WIDTH, CREEP_HEIGHT, CREEP_SPEED);
  magic = tower_init(magic, MAGIC_WIDTH, MAGIC_HEIGHT);
  tir_magic = tir_init(tir_magic, TIR_WIDTH, TIR_HEIGHT);
  hb = healthbar_init(hb, HB_WIDTH, HB_HEIGHT);

  /* message pump */
  while (!gameover)
    {
      
      temps_jeu = SDL_GetTicks();
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);
      
      
      /* look for an event */
      update_events(key,&liste_creep, &liste_magic, creep, magic, map, map_objet, &num_mob);



      /* draw the map */
  
      PrintMap(map,screen);
      PrintMap(map_objet,screen);

      /* draw the creeper */
      mob_affichage(liste_creep, map, screen);
      
      /* draw the tower */
      cible(&liste_tir_magic, liste_creep);
      tower_affichage(liste_magic ,screen);

      /* draw the shoot */

      tir_affichage(liste_tir_magic, tir_magic, screen, liste_creep);
      disparition_tir(&liste_tir_magic, liste_creep);

      /* fonction */

      collision_tir_mob(&liste_tir_magic, &liste_creep);

      tower_tir(&liste_magic, &liste_creep, &liste_tir_magic, tir_magic, screen, temps_jeu, magic);
      
      SDL_Flip(screen);

      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(5);
      
      
    }
  
  FreeMap(map);
  FreeMap(map_objet);
  
  /* ****************************************************************************************************************************** */
  /* ***********************************     Clean Up    ************************************************************************** */
  /* ****************************************************************************************************************************** */

  if (liste_creep != NULL)
    liste_free_mob(&liste_creep);
  if (liste_magic != NULL)
    liste_free_tower(&liste_magic);
  if (liste_tir_magic != NULL)
    liste_free_tir(&liste_tir_magic);

  if (magic.tower != NULL)
    SDL_FreeSurface(magic.tower);
  if (creep.mob != NULL)
    SDL_FreeSurface(creep.mob);
  if (tir_magic.tir != NULL)
    SDL_FreeSurface(tir_magic.tir);

  SDL_Quit();
  
  return 0;

}
