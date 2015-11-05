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
  s_Mob spider;

  s_Tower sniper1;
  s_Tower sniper2;
  s_Tower sniper3;
  s_Tower magic1;
  s_Tower magic2;
  s_Tower magic3;
  s_Tower fire1;
  s_Tower fire2;
  s_Tower fire3;
  s_Tower slow1;
  s_Tower slow2;
  s_Tower slow3;

  s_Tir tir_sniper;
  s_Tir tir_magic;
  s_Tir tir_fire;

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
  
  creep.mob = Load_image("Images/Mobs/sprite_creeper.bmp");
  zombie.mob = Load_image("Images/Mobs/sprite_zombie.bmp");
  ender.mob = Load_image("Images/Mobs/sprite_enderman.bmp");
  spider.mob = Load_image("Images/Mobs/sprite_spider.bmp");

  sniper1.tower = Load_image("Images/Tower/tower_sniper1.bmp");
  sniper2.tower = Load_image("Images/Tower/tower_sniper2.bmp");
  sniper3.tower = Load_image("Images/Tower/tower_sniper3.bmp");
  magic1.tower = Load_image("Images/Tower/tower_magic1.bmp");
  magic2.tower = Load_image("Images/Tower/tower_magic2.bmp");
  magic3.tower = Load_image("Images/Tower/tower_magic3.bmp");
  fire1.tower = Load_image("Images/Tower/tower_fire1.bmp");
  fire2.tower = Load_image("Images/Tower/tower_fire2.bmp");
  fire3.tower = Load_image("Images/Tower/tower_fire3.bmp");
  slow1.tower = Load_image("Images/Tower/tower_slow1.bmp");
  slow2.tower = Load_image("Images/Tower/tower_slow2.bmp");
  slow3.tower = Load_image("Images/Tower/tower_slow3.bmp");

  tir_magic.tir = Load_image("Images/tir_magic.bmp");
  tir_sniper.tir = Load_image("Images/sprite_fleche.bmp");
  tir_fire.tir = Load_image("Images/tir.bmp");

  creep.healthbar.vie = Load_image("Images/Bighealthbar.bmp");
  zombie.healthbar.vie = creep.healthbar.vie;
  ender.healthbar.vie = creep.healthbar.vie;
  spider.healthbar.vie = creep.healthbar.vie;

  menu_tower = Load_image("Images/menu_tower.bmp");

  sniper1.menu.menu = Load_image("Images/menu_select.bmp");
  sniper2.menu.menu = sniper1.menu.menu;
  sniper3.menu.menu = sniper1.menu.menu;
  magic1.menu.menu = sniper1.menu.menu;
  magic2.menu.menu = sniper1.menu.menu;
  magic3.menu.menu = sniper1.menu.menu;
  fire1.menu.menu = sniper1.menu.menu;
  fire2.menu.menu = sniper1.menu.menu;
  fire3.menu.menu = sniper1.menu.menu;
  slow1.menu.menu = sniper1.menu.menu;
  slow2.menu.menu = sniper1.menu.menu;
  slow3.menu.menu = sniper1.menu.menu;

  sniper1.up.up = Load_image("Images/upgrade.bmp");
  sniper2.up.up = sniper1.up.up;
  sniper3.up.up = sniper1.up.up;
  magic1.up.up = sniper1.up.up;
  magic2.up.up = sniper1.up.up;
  magic3.up.up = sniper1.up.up;
  fire1.up.up = sniper1.up.up;
  fire2.up.up = sniper1.up.up;
  fire3.up.up = sniper1.up.up;
  slow1.up.up = sniper1.up.up;
  slow2.up.up = sniper1.up.up;
  slow3.up.up = sniper1.up.up;

  sniper1.sell.sell = Load_image("Images/sell.bmp");
  sniper2.sell.sell = sniper1.sell.sell;
  sniper3.sell.sell = sniper1.sell.sell;
  magic1.sell.sell = sniper1.sell.sell;
  magic2.sell.sell = sniper1.sell.sell;
  magic3.sell.sell = sniper1.sell.sell;
  fire1.sell.sell = sniper1.sell.sell;
  fire2.sell.sell = sniper1.sell.sell;
  fire3.sell.sell = sniper1.sell.sell;
  slow1.sell.sell = sniper1.sell.sell;
  slow2.sell.sell = sniper1.sell.sell;
  slow3.sell.sell = sniper1.sell.sell;

  sniper1.range.range = Load_image("Images/Range/range_90.bmp");
  sniper2.range.range = Load_image("Images/Range/range_110.bmp");
  sniper3.range.range = Load_image("Images/Range/range_130.bmp");
  magic1.range.range = Load_image("Images/Range/range_60.bmp");
  magic2.range.range = Load_image("Images/Range/range_70.bmp");
  magic3.range.range = Load_image("Images/Range/range_80.bmp");
  fire1.range.range = Load_image("Images/Range/range_55.bmp");
  fire2.range.range = magic1.range.range;
  fire3.range.range = magic2.range.range;
  slow1.range.range = fire1.range.range;
  slow2.range.range = slow1.range.range;
  slow3.range.range = slow1.range.range;
  /* ********************   colorkey ******************* */

  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);
  colorkeyN =  SDL_MapRGB(screen->format, 0, 0, 0);

  SDL_SetColorKey(map_objet->tileset, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(creep.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(zombie.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(ender.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(spider.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

  SDL_SetColorKey(sniper1.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(sniper2.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(sniper3.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic1.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic2.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic3.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(fire1.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(fire2.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(fire3.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(slow1.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(slow2.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(slow3.tower, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

  SDL_SetColorKey(tir_magic.tir, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(tir_sniper.tir, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(tir_fire.tir, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkeyN);

  SDL_SetColorKey(sniper1.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(sniper2.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(sniper3.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic1.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic2.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(magic3.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(fire1.range.range, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

  char key[SDLK_LAST] = {0};

  
  /* ******************** boucle principale ******************* */
  
  
  creep = mob_spawn(creep, map, CREEP_WIDTH, CREEP_HEIGHT, CREEP_SPEED, CREEP_PV, CREEP_TYPE);
  zombie = mob_spawn(zombie, map, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, ZOMBIE_SPEED, ZOMBIE_PV, ZOMBIE_TYPE);
  ender = mob_spawn(ender, map, ENDER_WIDTH, ENDER_HEIGHT, ENDER_SPEED, ENDER_PV, ENDER_TYPE);
  spider = mob_spawn(spider, map, SPIDER_WIDTH, SPIDER_HEIGHT, SPIDER_SPEED, SPIDER_PV, SPIDER_TYPE);

  tir_magic = tir_init(tir_magic, TIR_WIDTH, TIR_HEIGHT);
  tir_sniper = tir_init(tir_sniper, TIR_WIDTH, TIR_HEIGHT);
  tir_fire = tir_init(tir_fire, TIR_WIDTH, TIR_HEIGHT);

  creep.healthbar = healthbar_init(creep.healthbar, HB_WIDTH, HB_HEIGHT);
  zombie.healthbar = healthbar_init(zombie.healthbar, HB_WIDTH, HB_HEIGHT);
  ender.healthbar = healthbar_init(ender.healthbar, HB_WIDTH, HB_HEIGHT);
  spider.healthbar = healthbar_init(spider.healthbar, HB_WIDTH, HB_HEIGHT);

  sniper1.range = Range_init(sniper1.range, DISTANCE_SNIPER_TOWER*2 , DISTANCE_SNIPER_TOWER*2 );
  sniper2.range = Range_init(sniper2.range, DISTANCE_SNIPER_TOWER*2 , DISTANCE_SNIPER_TOWER*2 );
  sniper3.range = Range_init(sniper3.range, DISTANCE_SNIPER_TOWER*2 , DISTANCE_SNIPER_TOWER*2 ); 
  magic1.range = Range_init(magic1.range, DISTANCE_MAGIC_TOWER*2 , DISTANCE_MAGIC_TOWER*2 );
  magic2.range = Range_init(magic2.range, DISTANCE_MAGIC_TOWER*2 , DISTANCE_MAGIC_TOWER*2 );
  magic3.range = Range_init(magic3.range, DISTANCE_MAGIC_TOWER*2 , DISTANCE_MAGIC_TOWER*2 );
  fire1.range = Range_init(fire1.range, DISTANCE_FIRE_TOWER*2 , DISTANCE_FIRE_TOWER*2 );
  fire2.range = Range_init(fire2.range, DISTANCE_FIRE_TOWER*2 , DISTANCE_FIRE_TOWER*2 );
  fire3.range = Range_init(fire3.range, DISTANCE_FIRE_TOWER*2 , DISTANCE_FIRE_TOWER*2 );
  slow1.range = Range_init(slow1.range, DISTANCE_SLOW_TOWER*2 , DISTANCE_SLOW_TOWER*2 );
  slow2.range = Range_init(slow2.range, DISTANCE_SLOW_TOWER*2 , DISTANCE_SLOW_TOWER*2 );
  slow3.range = Range_init(slow3.range, DISTANCE_SLOW_TOWER*2 , DISTANCE_SLOW_TOWER*2 );

  sniper1.menu = menu_select_init(sniper1.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  sniper2.menu = menu_select_init(sniper2.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  sniper3.menu = menu_select_init(sniper3.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  magic1.menu = menu_select_init(magic1.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  magic2.menu = menu_select_init(magic2.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  magic3.menu = menu_select_init(magic3.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  fire1.menu = menu_select_init(fire1.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  fire2.menu = menu_select_init(fire2.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  fire3.menu = menu_select_init(fire3.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  slow1.menu = menu_select_init(slow1.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  slow2.menu = menu_select_init(slow2.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);
  slow3.menu = menu_select_init(slow3.menu, MENU_SELECT_WIDTH, MENU_SELECT_HEIGHT);

  sniper1.up = upgrade_init(sniper1.up, UP_WIDTH, UP_HEIGHT);
  sniper2.up = upgrade_init(sniper2.up, UP_WIDTH, UP_HEIGHT);
  sniper3.up = upgrade_init(sniper3.up, UP_WIDTH, UP_HEIGHT);
  magic1.up = upgrade_init(magic1.up, UP_WIDTH, UP_HEIGHT);
  magic2.up = upgrade_init(magic2.up, UP_WIDTH, UP_HEIGHT);
  magic3.up = upgrade_init(magic3.up, UP_WIDTH, UP_HEIGHT);
  fire1.up = upgrade_init(fire1.up, UP_WIDTH, UP_HEIGHT);
  fire2.up = upgrade_init(fire2.up, UP_WIDTH, UP_HEIGHT);
  fire3.up = upgrade_init(fire3.up, UP_WIDTH, UP_HEIGHT);
  slow1.up = upgrade_init(slow1.up, UP_WIDTH, UP_HEIGHT);
  slow2.up = upgrade_init(slow2.up, UP_WIDTH, UP_HEIGHT);
  slow3.up = upgrade_init(slow3.up, UP_WIDTH, UP_HEIGHT);

  sniper1.sell = sell_init(sniper1.sell, SELL_WIDTH, SELL_HEIGHT);
  sniper2.sell = sell_init(sniper2.sell, SELL_WIDTH, SELL_HEIGHT);
  sniper3.sell = sell_init(sniper3.sell, SELL_WIDTH, SELL_HEIGHT);
  magic1.sell = sell_init(magic1.sell, SELL_WIDTH, SELL_HEIGHT);
  magic2.sell = sell_init(magic2.sell, SELL_WIDTH, SELL_HEIGHT);
  magic3.sell = sell_init(magic3.sell, SELL_WIDTH, SELL_HEIGHT);
  fire1.sell = sell_init(fire1.sell, SELL_WIDTH, SELL_HEIGHT);
  fire2.sell = sell_init(fire2.sell, SELL_WIDTH, SELL_HEIGHT);
  fire3.sell = sell_init(fire3.sell, SELL_WIDTH, SELL_HEIGHT);
  slow1.sell = sell_init(slow1.sell, SELL_WIDTH, SELL_HEIGHT);
  slow2.sell = sell_init(slow2.sell, SELL_WIDTH, SELL_HEIGHT);
  slow3.sell = sell_init(slow3.sell, SELL_WIDTH, SELL_HEIGHT);

  sniper1 = tower_init(sniper1, SNIPER_WIDTH, SNIPER_HEIGHT, TYPE_SNIPER,DISTANCE_SNIPER_TOWER, CADENCE_SNIPER_TOWER);
  magic1 = tower_init(magic1, MAGIC_WIDTH, MAGIC_HEIGHT, TYPE_MAGIC, DISTANCE_MAGIC_TOWER, CADENCE_MAGIC_TOWER);
  fire1 = tower_init(fire1, FIRE_WIDTH, FIRE_HEIGHT, TYPE_FIRE, DISTANCE_FIRE_TOWER, CADENCE_FIRE_TOWER);
  slow1 = tower_init(slow1, SLOW_WIDTH, SLOW_HEIGHT, TYPE_SLOW, DISTANCE_SLOW_TOWER,0);


  /* boucle de jeu */
  gameover = 0;
  while (!gameover)
    {
      
      temps_jeu = SDL_GetTicks();
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);
      
      /* look for an event */
      update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, spider,sniper1, sniper2, sniper3, magic1, magic2, magic3, fire1, fire2, fire3, slow1, slow2, slow3, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover);

      /* draw the map */
      PrintMap(map,screen);
      PrintMap(map_objet,screen);

      rcMenu_tower.x = 0;
      rcMenu_tower.y = 416;
      SDL_BlitSurface(menu_tower, NULL, screen, &rcMenu_tower );
      

      sniper1.rcSprite.x = 21;
      sniper1.rcSprite.y = 439;
      SDL_BlitSurface(sniper1.tower, NULL, screen, &sniper1.rcSprite );

      magic1.rcSprite.x = 189;
      magic1.rcSprite.y = 439;
      SDL_BlitSurface(magic1.tower, NULL, screen, &magic1.rcSprite );
	
      fire1.rcSprite.x = 357;
      fire1.rcSprite.y = 439;
      SDL_BlitSurface(fire1.tower, NULL, screen, &fire1.rcSprite );

      slow1.rcSprite.x = 525;
      slow1.rcSprite.y = 439;
      SDL_BlitSurface(slow1.tower, NULL, screen, &slow1.rcSprite );


      /* draw mobs */
      mob_affichage(liste_mob, map, screen);

      /* draw tower select */
      Range_affichage(liste_tower, screen);
      menu_select_affichage(liste_tower, screen);
      upgrade_affichage(liste_tower, screen);
      sell_affichage(liste_tower, screen);
      
      /* draw towers */     
      tower_affichage(liste_tower ,screen);

      /* draw shoots */
      cible(&liste_tir, liste_mob);
      tir_affichage(liste_tir, screen, liste_mob);
      disparition_tir(&liste_tir, liste_mob);

      /* draw healthbar */
      healthbar_affichage(liste_mob, screen);

      /* fonction */
      collision_tir_mob(&liste_tir, &liste_mob);
      tower_tir(&liste_tower, &liste_mob, &liste_tir, tir_magic, tir_sniper, tir_fire, screen, temps_jeu, sniper1);
      mob_slow(&liste_mob, &liste_tower, colorkey);
      
      SDL_Flip(screen);

      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(1);
      
      
    }
  
  FreeMap(map);
  FreeMap(map_objet);
  
  /* ****************************************************************************************************************************** */
  /* ***********************************     Clean Up    ************************************************************************** */
  /* ****************************************************************************************************************************** */
  /* free liste */
  if (liste_mob != NULL)
    liste_free_mob(&liste_mob);
  if (liste_tower != NULL)
    liste_free_tower(&liste_tower);
  if (liste_tir != NULL)
    liste_free_tir(&liste_tir);

  /* free tower */

  if (sniper1.tower != NULL)
    SDL_FreeSurface(sniper1.tower);
  if (sniper2.tower != NULL)
    SDL_FreeSurface(sniper2.tower);
  if (sniper3.tower != NULL)
    SDL_FreeSurface(sniper3.tower);
  if (magic1.tower != NULL)
    SDL_FreeSurface(magic1.tower);
  if (magic2.tower != NULL)
    SDL_FreeSurface(magic2.tower);
  if (magic3.tower != NULL)
    SDL_FreeSurface(magic3.tower);

  /* free mob */

  if (creep.mob != NULL)
    SDL_FreeSurface(creep.mob);
  if (zombie.mob != NULL)
    SDL_FreeSurface(zombie.mob);
  if (ender.mob != NULL)
    SDL_FreeSurface(ender.mob);
  if (spider.mob != NULL)
    SDL_FreeSurface(spider.mob);

  if (creep.healthbar.vie != NULL)
    SDL_FreeSurface(creep.healthbar.vie);

  /* free autres */

  if (tir_magic.tir != NULL)
    SDL_FreeSurface(tir_magic.tir);

  if (menu_tower != NULL)
    SDL_FreeSurface(menu_tower);

  if (sniper1.range.range != NULL)
    SDL_FreeSurface(sniper1.range.range);
  if (sniper2.range.range != NULL)
    SDL_FreeSurface(sniper2.range.range);
  if (sniper3.range.range != NULL)
    SDL_FreeSurface(sniper3.range.range);
  if (magic1.range.range != NULL)
    SDL_FreeSurface(magic1.range.range);
  if (magic2.range.range != NULL)
    SDL_FreeSurface(magic2.range.range);
  if (magic3.range.range != NULL)
    SDL_FreeSurface(magic3.range.range);
  if (fire1.range.range != NULL)
    SDL_FreeSurface(fire1.range.range);

  if (sniper1.up.up != NULL)
    SDL_FreeSurface(sniper1.up.up);

  if (sniper1.sell.sell != NULL)
    SDL_FreeSurface(sniper1.sell.sell);

  SDL_Quit();
  
  return 0;

}
