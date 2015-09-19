#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

/*******************************************************************************************/
/******************************          Programme          *******************************/
/*******************************************************************************************/

/* varaible pour les phases de jeux */

int gameover;


/* SDL Function */
void update_events(char* keys)
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
				gameover = 1;
				break;
      }
      keys[event.key.keysym.sym] = 1;
      break;
    }
  }
}



/* ******************************************   MAIN   ********************************************** */




int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *background;
  int colorkey;

  
  /* set the title bar */
  SDL_WM_SetCaption("Tower Defense", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);
  

  /* **********************   LOAD IMAGE ******************* */


  /* load background */
  temp  = SDL_LoadBMP("background.bmp");
  background = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  



  /* ********************   colorkey ******************* */



  /* Pour le ROSE */
  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);

  char key[SDLK_LAST] = {0};
	gameover = 0;


	/* ******************** boucle principale ******************* */

 
	/* message pump */
	while (!gameover)
	{


	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);


	/* look for an event */
	update_events(key);
	
	
	/* draw the background */
	SDL_BlitSurface(background, NULL, screen, NULL);
	
	
	/* update the screen */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(5);
      
    
  }
  
  
  
  
  
  
  
  /* ****************************************************************************************************************************** */
  /* ***********************************     Clean Up    ************************************************************************** */
  /* ****************************************************************************************************************************** */

 
  SDL_FreeSurface(background);
  SDL_Quit();
  
  return 0;

}
