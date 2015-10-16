#include "../jeu.h"

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




/* SDL Function */
void update_events(char* keys, liste_mob *L, liste_tower *T, s_Mob mob, s_Mob mob2, s_Mob mob3,s_Tower sniper, s_Tower magic, Map *map, Map *map_o,int *i, int *case1, int *case2, int *case3, int *case4, int *gameover)
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *gameover = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
	
      case SDLK_q:
      case SDLK_ESCAPE:
	*gameover = 1;
	break;

      case SDLK_d:
	mob_add(i, mob, L);
	break;

      case SDLK_f:
	mob_add(i, mob2, L);

	break;
      case SDLK_g:
	mob_add(i, mob3, L);
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;

    case SDL_MOUSEBUTTONDOWN:    
      switch(event.button.button){
	
      case SDL_BUTTON_LEFT: 
	tower_menu(sniper, magic, T, event.button.x, event.button.y, map, map_o, case1, case2, case3, case4);     
	tower_select( T, event.button.x, event.button.y);
	break;
      }
      keys[event.button.button] = 1;      
      break; 

    case SDL_MOUSEMOTION:
      tower_motion(T, event.motion.x, event.motion.y);
      break;

    }
  }
}