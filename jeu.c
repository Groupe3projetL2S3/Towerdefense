#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

SDL_Surface* Load_image(const char* image) {
  SDL_Surface* res;
  SDL_Surface* temp = SDL_LoadBMP(image);
  res = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return res;
}



/******************************          Programme          *******************************/

/* varaible pour les phases de jeux */

int gameover;


/* SDL Function */
liste_mob update_events(char* keys, liste_mob L, s_Mob m)
{
  SDL_Event event;
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
	L = liste_cons_mob(m,L);
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;
    }
  }
  return L;
}


liste_tower update_events_mouse(char* keys, liste_tower L, s_Tower t, Map *map)
{
  SDL_Event event;
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT){
      t.coords.x = (event.button.x / TILE_SIZE) * TILE_SIZE;
      t.coords.y = (event.button.y / TILE_SIZE) * TILE_SIZE -20; //on récup' les coords exactes ou afficher la tour
      printf("%d %d \n", event.button.x, event.button.y);
      printf("%f %f \n", t.coords.x, t.coords.y);
      L = liste_cons_tower(t, L);
    }
    break;
  }
  return L;
}


/* ******************************************   MAIN   ********************************************** */




int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp;

  SDL_Event event;

  int colorkey;
  s_Mob creep;
  s_Tower magic;
  liste_mob liste_creep;
  liste_tower liste_magic;
  Map* map, *map_objet;




  /* set the title bar */
  SDL_WM_SetCaption("Tower Defense", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);
  
 
  /* **********************   LOAD IMAGE ******************* */
  map = LoadMap("monde.txt");
  map_objet = LoadMap("objet.txt");
  
  creep.mob = Load_image("sprite_creeper.bmp");
  magic.tower = Load_image("tower_magic1.bmp");

  /* ********************   colorkey ******************* */



  /* Pour le ROSE */
  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(map_objet->tileset, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(creep.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

  char key[SDLK_LAST] = {0};
  gameover = 0;
  
  liste_creep = liste_new_empty_mob();
  liste_magic = liste_new_empty_tower();
  /* ******************** boucle principale ******************* */
  
  
  creep = mob_spawn(creep, CREEP_WIDTH, CREEP_HEIGHT);
  magic = tower_init(magic, MAGIC_WIDTH, MAGIC_HEIGHT);

  /* message pump */
  while (!gameover)
    {
      
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);
      
      
      /* look for an event */
      liste_creep = update_events(key,liste_creep,creep);
      
      liste_magic = update_events_mouse(key, liste_magic, magic, map);

  
      PrintMap(map,screen);
      PrintMap(map_objet,screen);

      /* draw the creeper */
      mob_affichage(liste_creep, creep, map, screen);
      
      /* draw the tower */
      tower_affichage(liste_magic, magic, screen);

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

  liste_free_mob(&liste_creep);
  liste_free_tower(&liste_magic);
  SDL_FreeSurface(magic.tower);
  SDL_FreeSurface(creep.mob);

  SDL_Quit();
  
  return 0;

}
