#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"



/* ******************************************   MAIN   ********************************************** */


int main(int argc, char* argv[])
{
  SDL_Surface *screen = NULL, *menu_tower = NULL;
  SDL_Rect rcMenu_tower;

  int colorkey, colorkeyN;
  int case1 = 1;
  int case2 = 1;
  int case3 = 1;
  int case4 = 1;
  int gameover;

  s_Mob creep;
  s_Mob zombie;
  s_Mob ender;
  s_Tower sniper;
  s_Tower magic;
  s_Tir tir_magic;

  liste_mob liste_mob = NULL;
  liste_tower liste_tower = NULL;
  liste_tir liste_tir = NULL;

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
  zombie.mob = Load_image("Images/sprite_zombie.bmp");
  ender.mob = Load_image("Images/sprite_enderman.bmp");

  sniper.tower = Load_image("Images/tower_sniper1.bmp");
  magic.tower = Load_image("Images/tower_magic1.bmp");

  tir_magic.tir = Load_image("Images/tir.bmp");
  creep.healthbar.vie = Load_image("Images/Bighealthbar.bmp");
  zombie.healthbar.vie = Load_image("Images/Bighealthbar.bmp");
  ender.healthbar.vie = Load_image("Images/Bighealthbar.bmp");
  menu_tower = Load_image("Images/menu_tower.bmp");
  sniper.range.range = Load_image("Images/range_sniper1.bmp");
  magic.range.range = Load_image("Images/range_sniper1.bmp");

  /* ********************   colorkey ******************* */

  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);
  colorkeyN =  SDL_MapRGB(screen->format, 0, 0, 0);

  SDL_SetColorKey(map_objet->tileset, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(creep.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(zombie.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(ender.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(sniper.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(tir_magic.tir, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkeyN);
  SDL_SetColorKey(sniper.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  char key[SDLK_LAST] = {0};

  
  /* ******************** boucle principale ******************* */
  
  
  creep = mob_spawn(creep, map, CREEP_WIDTH, CREEP_HEIGHT, CREEP_SPEED);
  zombie = mob_spawn(zombie, map, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, ZOMBIE_SPEED);
  ender = mob_spawn(ender, map, ENDER_WIDTH, ENDER_HEIGHT, ENDER_SPEED);

  sniper = tower_init(sniper, SNIPER_WIDTH, SNIPER_HEIGHT, SNIPER);
  magic = tower_init(magic, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC);
  tir_magic = tir_init(tir_magic, TIR_WIDTH, TIR_HEIGHT);

  creep.healthbar = healthbar_init(creep.healthbar, HB_WIDTH, HB_HEIGHT);
  zombie.healthbar = healthbar_init(zombie.healthbar, HB_WIDTH, HB_HEIGHT);
  ender.healthbar = healthbar_init(ender.healthbar, HB_WIDTH, HB_HEIGHT);

  sniper.range = Range_init(sniper.range, RANGE_SNIPER1_SIZE , RANGE_SNIPER1_SIZE );
  magic.range = Range_init(magic.range, RANGE_SNIPER1_SIZE , RANGE_SNIPER1_SIZE );
  /* message pump */
  gameover = 0;
  while (!gameover)
    {
      
      temps_jeu = SDL_GetTicks();
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);
      
      /* look for an event */
      update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, sniper, magic, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover);

      /* draw the map */
      PrintMap(map,screen);
      PrintMap(map_objet,screen);

      rcMenu_tower.x = 0;
      rcMenu_tower.y = 416;
      SDL_BlitSurface(menu_tower, NULL, screen, &rcMenu_tower );
      

      sniper.rcSprite.x = 21;
      sniper.rcSprite.y = 439;
      SDL_BlitSurface(sniper.tower, NULL, screen, &sniper.rcSprite );

      magic.rcSprite.x = 189;
      magic.rcSprite.y = 439;
      SDL_BlitSurface(magic.tower, NULL, screen, &magic.rcSprite );
	

      /* draw mobs */
      mob_affichage(liste_mob, map, screen);

      /* draw range */
      Range_affichage(liste_tower, screen);

      /* draw towers */
      cible(&liste_tir, liste_mob);
      tower_affichage(liste_tower ,screen);

      /* draw shoots */
      tir_affichage(liste_tir, tir_magic, screen, liste_mob);
      disparition_tir(&liste_tir, liste_mob);

      /* draw healthbar */
      healthbar_affichage(liste_mob, screen);


      /* fonction */
      collision_tir_mob(&liste_tir, &liste_mob);
      tower_tir(&liste_tower, &liste_mob, &liste_tir, tir_magic, screen, temps_jeu, sniper);
      
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

  if (liste_mob != NULL)
    liste_free_mob(&liste_mob);
  if (liste_tower != NULL)
    liste_free_tower(&liste_tower);
  if (liste_tir != NULL)
    liste_free_tir(&liste_tir);

  if (sniper.tower != NULL)
    SDL_FreeSurface(sniper.tower);
  if (magic.tower != NULL)
    SDL_FreeSurface(magic.tower);
  if (creep.mob != NULL)
    SDL_FreeSurface(creep.mob);
  if (zombie.mob != NULL)
    SDL_FreeSurface(zombie.mob);
  if (ender.mob != NULL)
    SDL_FreeSurface(ender.mob);
  if (tir_magic.tir != NULL)
    SDL_FreeSurface(tir_magic.tir);
  if (creep.healthbar.vie != NULL)
    SDL_FreeSurface(creep.healthbar.vie);
  if (menu_tower != NULL)
    SDL_FreeSurface(menu_tower);
  if (sniper.range.range != NULL)
    SDL_FreeSurface(sniper.range.range);
  if (magic.range.range != NULL)
    SDL_FreeSurface(magic.range.range);
  SDL_Quit();
  
  return 0;

}
