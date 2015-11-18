#include "../jeu.h"

//Charge une image en BMP
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




//Fonction qui gère TOUS les évènement clavier/souris
void update_events(char* keys, liste_mob *L, liste_tower *T, s_Mob mob, s_Mob mob2, s_Mob mob3, s_Mob mob4, s_Tower sniper1, s_Tower sniper2, s_Tower sniper3, s_Tower magic1, s_Tower magic2, s_Tower magic3, s_Tower fire1, s_Tower fire2, s_Tower fire3, s_Tower slow1, s_Tower slow2, s_Tower slow3, Map *map, Map *map_o,int *i, int *case1, int *case2, int *case3, int *case4, int *gameover, int *pause, int *menu, int *fin, int *money, SDL_Surface *screen, int *click, int *speedup)
{ 
  SDL_Event event;
  int mny = *money;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *gameover = 1;
      *pause = 0;
      *menu = 0;
      *fin = 0;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
	
      case SDLK_RETURN:
	*menu = 0;
	break;
      case SDLK_q:
      case SDLK_ESCAPE:
	*gameover = 1;
	*pause = 0;
	*menu = 0;
	*fin = 0;
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
      case SDLK_s:
	mob_add(i, mob4, L);
	break;
      case SDLK_p:
	if (*pause == 0){
	  *pause = 1;
	}
        else{
	  *pause = 0;
	}
	break;
      case SDLK_k:
	if (*speedup == 0){
	  *speedup = 1;
	}
        else{
	  *speedup = 0;
	}
	break;
      case SDLK_t:
        *gameover = 1;
	*pause = 0;
	*menu = 0;
	break;
      case SDLK_m:
	mny = mny + 1000;
      }
      keys[event.key.keysym.sym] = 1;
      break;

    case SDL_MOUSEBUTTONDOWN:    
      switch(event.button.button){
	
      case SDL_BUTTON_LEFT:
	if(!*pause){
	  tower_menu(sniper1, magic1, fire1, slow1, T, event.button.x, event.button.y, map, map_o, case1, case2, case3, case4, &mny);
	  tower_select(*T, event.button.x, event.button.y);
	  tower_gestion(T, sniper2, sniper3, magic2, magic3, fire2, fire3, slow2, slow3, event.button.x, event.button.y, &mny);

	  if(*menu == 1 && 
	     event.button.x >= 208 && event.button.x <= 463 &&
	     event.button.y >= 278 && event.button.y <= 328) {
	    *menu = 0;
	  }
	}
	break;
      case SDL_BUTTON_RIGHT: 

	break;
      }
      keys[event.button.button] = 1;      
      break; 

    case SDL_MOUSEMOTION:
      tower_motion(*T, event.motion.x, event.motion.y);
      up_sell_motion(*T, event.motion.x, event.motion.y, screen);
      if(*menu == 1 && 
	 event.motion.x >= 208 && event.motion.x <= 463 &&
	 event.motion.y >= 278 && event.motion.y <= 328) {
	*click = 1;
      } 
      if(*menu == 1 && ( 
	 event.motion.x <= 208 || event.motion.x >= 463 ||
	 event.motion.y <= 278 || event.motion.y >= 328)) {
	*click = 0;
      }
      break;
    
    }
  }
  *money = mny;
}
