#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"



/* ******************************************   MAIN   ********************************************** */


int main(int argc, char* argv[])
{
  SDL_Surface *screen = NULL, *menu_tower = NULL, *menu_jeu = NULL, *menu_pause = NULL,*menu_mort = NULL, *diamondbig = NULL, *diamondlittle = NULL, *bow = NULL, *sword = NULL, *firerate = NULL, *heart = NULL;
  SDL_Rect rcMenu_tower, rcMenujeu, rcMenupause, rcMenumort, rcDiamondbig, rcDiamondlittle, rcBow, rcSword, rcFirerate, rcHeart;
  SDL_Color Blanc = {255,255,255};

  TTF_Init();

  int colorkey, colorkeyN;
  int case1 = 1;
  int case2 = 1;
  int case3 = 1;
  int case4 = 1;

  int gameover;
  int pause;
  int print_pause;
  int menu;
  int fin;

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

  
  s_Text s_score;
  s_Text s_compteur;
  s_Text s_gameover;
  s_Text s_money;
  s_Text s_health;

  s_Text s_top1;
  s_Text s_top2;
  s_Text s_top3;
  s_Text s_top4;
  s_Text s_top5;

  s_Text s_ptop1;
  s_Text s_ptop2;
  s_Text s_ptop3;
  s_Text s_ptop4;
  s_Text s_ptop5;  
  

  liste_mob liste_mob = NULL;
  liste_tower liste_tower = NULL;
  liste_tir liste_tir = NULL;

  Map* map = NULL;
  Map* map_objet = NULL;

  int temps_jeu = 0;
  int temps_debut_pause = 0;
  int temps_menu = 0;
  int temps_score = 0;
  int dure_pause = 0;
  int num_mob = 0;
  int points = 0;
  int money = 300;
  int health = 20;
  int wave = 0;
  int nb_mobs = 0;
  int max_mobs = 0;
  int intervalle_mob = 0;
  int intervalle_wave = 0;
  int next_wave = wave +1;
  
  char tabscore[6] = "SCORE";
  char tabcompteur[11] = "0000000000";
  char tabgameover[12] = "GAME OVER !";
  char tabmoney[10] = "000000000";
  char tabhealth[3] = "00";

  char tabtop1[11] = {'0'};
  char tabtop2[11] = {'0'};
  char tabtop3[11] = {'0'};
  char tabtop4[11] = {'0'};
  char tabtop5[11] = {'0'};

  char tabptop1[3] = "1.";
  char tabptop2[3] = "2.";
  char tabptop3[3] = "3.";
  char tabptop4[3] = "4.";
  char tabptop5[3] = "5.";

  /* char des tours de sniper */
  char tabsniper_name[7] = "Sniper";
  char tabsniper_damages[4] = "2.0";
  char tabsniper_as[4] = "2.0";
  char tabsniper_cost[5] = "100";
  char tabsniper_range[5] = "90";


  /* char des tours de magie */
  char tabmagic_name[6] = "Magic";
  char tabmagic_damages[4] = "5.0";
  char tabmagic_as[4] = "1.0";
  char tabmagic_cost[5] = "200";
  char tabmagic_range[5] = "60";


  /* char des tours de feu */
  char tabfire_name[5] = "Fire";
  char tabfire_damages[5] = "0.08";
  char tabfire_as[5] = "50.0";
  char tabfire_cost[5] = "400";
  char tabfire_range[5] = "55";



  /* char des tours de slow */
  char tabslow_name[5] = "Slow";
  char tabslow_damages[4] = "0.0";
  char tabslow_as[4] = "0.0";
  char tabslow_cost[5] = "250";
  char tabslow_range[5] = "55";


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
  creep.frozen_mob = Load_image("Images/Mobs/sprite_creeper_slow.bmp");
  zombie.frozen_mob = Load_image("Images/Mobs/sprite_zombie_slow.bmp");
  ender.frozen_mob = Load_image("Images/Mobs/sprite_enderman_slow.bmp");
  spider.frozen_mob = Load_image("Images/Mobs/sprite_spider_slow.bmp");

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

  menu_tower = Load_image("Images/ATH/menu_tower.bmp");
  menu_jeu = Load_image("Images/menu.bmp");
  menu_pause = Load_image("Images/pause.bmp");
  menu_mort = Load_image("Images/mort.bmp");
  sword = Load_image("Images/ATH/sword.bmp");
  firerate = Load_image("Images/ATH/firerate.bmp");
  bow = Load_image("Images/ATH/bow.bmp");
  diamondlittle = Load_image("Images/ATH/diamondlittle.bmp");
  diamondbig = Load_image("Images/ATH/diamondbig.bmp");
  heart = Load_image("Images/ATH/heart.bmp");

  sniper1.menu.menu = Load_image("Images/ATH/menu_select.bmp");
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

  sniper1.up.up = Load_image("Images/ATH/upgrade.bmp");
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

  sniper1.sell.sell = Load_image("Images/ATH/sell.bmp");
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
  SDL_SetColorKey(creep.frozen_mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(zombie.frozen_mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(ender.frozen_mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(spider.frozen_mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

  SDL_SetColorKey(sword, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(firerate, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(bow, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(diamondlittle, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(diamondbig, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(heart, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);

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

  sniper1 = tower_init(sniper1, SNIPER_WIDTH, SNIPER_HEIGHT, TYPE_SNIPER,DISTANCE_SNIPER_TOWER, CADENCE_SNIPER_TOWER, PRIX_SNIPER);
  magic1 = tower_init(magic1, MAGIC_WIDTH, MAGIC_HEIGHT, TYPE_MAGIC, DISTANCE_MAGIC_TOWER, CADENCE_MAGIC_TOWER, PRIX_MAGIC);
  fire1 = tower_init(fire1, FIRE_WIDTH, FIRE_HEIGHT, TYPE_FIRE, DISTANCE_FIRE_TOWER, CADENCE_FIRE_TOWER, PRIX_FIRE);
  slow1 = tower_init(slow1, SLOW_WIDTH, SLOW_HEIGHT, TYPE_SLOW, DISTANCE_SLOW_TOWER,0, PRIX_SLOW);


  /* Initialize Text game*/
  s_score = text_init(23, MINECRAFT_POLICE, Blanc, s_score);
  s_compteur = text_init(23, MINECRAFT_POLICE, Blanc, s_compteur);
  s_money = text_init(23, MINECRAFT_POLICE, Blanc, s_money);
  s_health = text_init(23, MINECRAFT_POLICE, Blanc, s_health);

  sniper1.s_name = text_init(18, MINECRAFT_POLICE, Blanc, sniper1.s_name);
  sniper1.s_damages = text_init(15, IMP_POLICE, Blanc, sniper1.s_damages);
  sniper1.s_as = text_init(15, IMP_POLICE, Blanc, sniper1.s_as);
  sniper1.s_cost = text_init(15, IMP_POLICE, Blanc, sniper1.s_cost);
  sniper1.s_range = text_init(15, IMP_POLICE, Blanc, sniper1.s_range);
  sniper1.s_sell = text_init(15, IMP_POLICE, Blanc, sniper1.s_sell);
  sniper2.s_damages = sniper1.s_damages;
  sniper2.s_as = sniper1.s_as;
  sniper2.s_cost = sniper1.s_cost;
  sniper2.s_range = sniper1.s_range;
  sniper2.s_sell = sniper1.s_sell;
  sniper3.s_damages = sniper1.s_damages;
  sniper3.s_as = sniper1.s_as;
  sniper3.s_cost = sniper1.s_cost;
  sniper3.s_range = sniper1.s_range;
  sniper3.s_sell = sniper1.s_sell;


  magic1.s_name = text_init(18, MINECRAFT_POLICE, Blanc, magic1.s_name);
  magic1.s_damages = text_init(15, IMP_POLICE, Blanc, magic1.s_damages);
  magic1.s_as = text_init(15, IMP_POLICE, Blanc, magic1.s_as);
  magic1.s_cost = text_init(15, IMP_POLICE, Blanc, magic1.s_cost);
  magic1.s_sell = text_init(15, IMP_POLICE, Blanc, magic1.s_sell);
  magic1.s_range = text_init(15,IMP_POLICE , Blanc, magic1.s_range);
  magic2.s_damages = magic1.s_damages;
  magic2.s_as = magic1.s_as;
  magic2.s_cost = magic1.s_cost;
  magic2.s_range = magic1.s_range;
  magic2.s_sell = magic1.s_sell;
  magic3.s_damages = magic1.s_damages;
  magic3.s_as = magic1.s_as;
  magic3.s_cost = magic1.s_cost;
  magic3.s_range = magic1.s_range;
  magic3.s_sell = magic1.s_sell;

  fire1.s_name = text_init(18, MINECRAFT_POLICE, Blanc, fire1.s_name);
  fire1.s_damages = text_init(15, IMP_POLICE, Blanc, fire1.s_damages);
  fire1.s_as = text_init(15, IMP_POLICE, Blanc, fire1.s_as);
  fire1.s_cost = text_init(15, IMP_POLICE, Blanc, fire1.s_cost);
  fire1.s_sell = text_init(15, IMP_POLICE, Blanc, fire1.s_sell);
  fire1.s_range = text_init(15, IMP_POLICE, Blanc, fire1.s_range);
  fire2.s_damages = fire1.s_damages;
  fire2.s_as = fire1.s_as;
  fire2.s_cost = fire1.s_cost;
  fire2.s_range = fire1.s_range;
  fire2.s_sell = fire1.s_sell;
  fire3.s_damages = fire1.s_damages;
  fire3.s_as = fire1.s_as;
  fire3.s_cost = fire1.s_cost;
  fire3.s_range = fire1.s_range;
  fire3.s_sell = fire1.s_sell;

  slow1.s_name = text_init(18, MINECRAFT_POLICE, Blanc, slow1.s_name);
  slow1.s_damages = text_init(15, IMP_POLICE, Blanc, slow1.s_damages);
  slow1.s_as = text_init(15, IMP_POLICE, Blanc, slow1.s_as);
  slow1.s_cost = text_init(15, IMP_POLICE, Blanc, slow1.s_cost);
  slow1.s_sell = text_init(15, IMP_POLICE, Blanc, slow1.s_sell);
  slow1.s_range = text_init(15, IMP_POLICE, Blanc, slow1.s_range);
  slow2.s_damages = slow1.s_damages;
  slow2.s_as = slow1.s_as;
  slow2.s_cost = slow1.s_cost;
  slow2.s_range = slow1.s_range;
  slow2.s_sell = slow1.s_sell;
  slow3.s_damages = slow1.s_damages;
  slow3.s_as = slow1.s_as;
  slow3.s_cost = slow1.s_cost;
  slow3.s_range = slow1.s_range;
  slow3.s_sell = slow1.s_sell;

  gameover = 0;
  pause = 0;
  print_pause = 1;
  menu = 1;
  fin = 1;


  while(menu){
    update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, spider,sniper1, sniper2, sniper3, magic1, magic2, magic3, fire1, fire2, fire3, slow1, slow2, slow3, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover, &pause, &menu, &fin, &money, screen);
    

    rcMenujeu.x = 0;
    rcMenujeu.y = 0;
    SDL_BlitSurface(menu_jeu, NULL, screen, &rcMenujeu );

    temps_menu = temps_jeu;
    temps_jeu = SDL_GetTicks() - dure_pause + temps_debut_pause;
    
    
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_Delay(5);
  }

  



  /* boucle de jeu */
  
  while (!gameover)
    {
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);

      temps_jeu = SDL_GetTicks() + temps_debut_pause - dure_pause - temps_menu;


      while(pause){
	update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, spider,sniper1, sniper2, sniper3, magic1, magic2, magic3, fire1, fire2, fire3, slow1, slow2, slow3, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover, &pause, &menu, &fin, &money, screen);
		
	if(print_pause){ // pour que l'image ne s'affiche qu'une seul fois
	  rcMenupause.x = 0;
	  rcMenupause.y = 0;
	  SDL_SetAlpha(menu_pause, SDL_SRCALPHA, 70);
	  SDL_BlitSurface(menu_pause, NULL, screen, &rcMenupause );
	  print_pause = 0;
	}

	temps_debut_pause = temps_jeu;
	dure_pause = SDL_GetTicks();
	temps_menu = 0;
	
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(1);
      }
      print_pause = 1;
      
      /* look for an event */
      update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, spider,sniper1, sniper2, sniper3, magic1, magic2, magic3, fire1, fire2, fire3, slow1, slow2, slow3, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover, &pause, &menu, &fin, &money, screen);

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
      
      mob_affichage(liste_mob, map, screen, temps_jeu);

      /* draw tower select */
      Range_affichage(liste_tower, screen);
      menu_select_affichage(liste_tower, screen, sword, firerate, bow, diamondlittle);
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

      collision_tir_mob(&liste_tir, &liste_mob, &points, &money);
      tower_tir(&liste_tower, &liste_mob, &liste_tir, tir_magic, tir_sniper, tir_fire, screen, temps_jeu, sniper1);
      mob_slow(&liste_mob, &liste_tower, colorkey);
      collision_screen_mob(&liste_mob, &health, &gameover);


      printf("%d \n %d n \n",wave, next_wave);
      
      if(wave < next_wave){
	if(temps_jeu - intervalle_mob > 1000 && nb_mobs < max_mobs){
	  if(wave == 1){
	    mob_add(&num_mob, creep, &liste_mob);
	  }
	  if(wave == 2){
	    if(nb_mobs < max_mobs/2)
	      mob_add(&num_mob, spider, &liste_mob);
	    else
	      mob_add(&num_mob, creep, &liste_mob);
	  }
	  if(wave == 3){
	    if(nb_mobs < max_mobs/3)
	      mob_add(&num_mob, spider, &liste_mob);
	    else
	      mob_add(&num_mob, creep, &liste_mob);
	  }
	  if(wave == 4){
	    if(nb_mobs < max_mobs*2/3)
	      mob_add(&num_mob, creep, &liste_mob);
	    else
	      mob_add(&num_mob, zombie, &liste_mob);
	  }
	  if(wave == 5){
	    if(nb_mobs < max_mobs/4)
	      mob_add(&num_mob, spider, &liste_mob);
	    if(nb_mobs >= max_mobs/4 && nb_mobs < max_mobs*3/4)
	      mob_add(&num_mob, creep, &liste_mob);
	    if(nb_mobs >= max_mobs*3/4)
	      mob_add(&num_mob, zombie, &liste_mob);
	  }
	  if(wave == 6){
	    if(nb_mobs < max_mobs/2)
	      mob_add(&num_mob, creep, &liste_mob);
	    if(nb_mobs >= max_mobs/2 && nb_mobs < max_mobs*3/4)
	      mob_add(&num_mob, ender, &liste_mob);
	    if(nb_mobs >= max_mobs*3/4)
	      mob_add(&num_mob, zombie, &liste_mob);
	  }
	  if(wave == 7){
	    if(nb_mobs < max_mobs*2/5)
	      mob_add(&num_mob, spider, &liste_mob);
	    if(nb_mobs >= max_mobs*2/5 && nb_mobs < max_mobs*3/5)
	      mob_add(&num_mob, creep, &liste_mob);
	    if(nb_mobs >= max_mobs*3/5 && nb_mobs < max_mobs*4/5)
	      mob_add(&num_mob, ender, &liste_mob);
	    if(nb_mobs >= max_mobs*4/5)
	      mob_add(&num_mob, zombie, &liste_mob);
	  }
	  if(wave == 8){
	    if(nb_mobs < max_mobs*1/5)
	      mob_add(&num_mob, spider, &liste_mob);
	    if(nb_mobs >= max_mobs*1/5 && nb_mobs < max_mobs*3/5)
	      mob_add(&num_mob, creep, &liste_mob);
	    if(nb_mobs >= max_mobs*3/5 && nb_mobs < max_mobs*4/5)
	      mob_add(&num_mob, ender, &liste_mob);
	    if(nb_mobs >= max_mobs*4/5)
	      mob_add(&num_mob, zombie, &liste_mob);
	  }  
	  intervalle_mob = temps_jeu;
	  nb_mobs ++;
	}

	if(liste_is_empty_mob(liste_mob) && nb_mobs == max_mobs)
	  {
	    wave = wave +1;
	    intervalle_wave = temps_jeu;
	  }
      }
      	
      if(wave == next_wave && temps_jeu - intervalle_wave > 5000 ){
	nb_mobs = 0;
	if(wave == 1 || wave == 2)
	  max_mobs = 20;
	if(wave == 3 || wave == 4)
	  max_mobs = 30;
	if(wave == 5 || wave == 6)
	  max_mobs = 40;
	if(wave == 7 || wave == 8)
	  max_mobs = 50;
	if(wave > 8){
	  wave = 5;
	  // buff des monstres !!!
	}
	creep.pv_max = creep.pv_max*1.25;
	creep.pv = creep.pv_max;
	spider.pv_max = spider.pv_max*1.25;
	spider.pv = spider.pv_max;
	zombie.pv_max = zombie.pv_max*1.25;
	zombie.pv = zombie.pv_max;
	ender.pv_max = ender.pv_max*1.25;
	ender.pv = ender.pv_max;

	next_wave = wave +1;
      }
      

      
      /* Affichage score, money, health */

      rcDiamondbig.x = SCREEN_WIDTH - 100;
      rcDiamondbig.y = 30;
      SDL_BlitSurface(diamondbig, NULL, screen, &rcDiamondbig);

      rcHeart.x = SCREEN_WIDTH/2;
      rcHeart.y = 3;
      SDL_BlitSurface(heart, NULL, screen, &rcHeart);

      sprintf(tabcompteur,"%d", points);
      affichage_text(SCREEN_WIDTH -160, 10, tabscore, s_score, screen);
      affichage_text(SCREEN_WIDTH -62, 10, tabcompteur, s_compteur, screen);
      sprintf(tabmoney, "%d", money);
      affichage_text(SCREEN_WIDTH - 62, 40, tabmoney, s_money, screen);
      sprintf(tabhealth, "%d", health);
      affichage_text(SCREEN_WIDTH/2 + 30, 10, tabhealth, s_health, screen);

      /* Points en fonction du temps */
      if (temps_jeu - temps_score > 1000){
	points = points + 1;
	temps_score = temps_jeu;
      }
      
      /* Affichage specs tours */
      affichage_text(70, SCREEN_HEIGHT-74, tabsniper_name, sniper1.s_name, screen);
      affichage_text(90, SCREEN_HEIGHT-55, tabsniper_damages, sniper1.s_damages, screen);
      affichage_text(90, SCREEN_HEIGHT-35, tabsniper_as, sniper1.s_as, screen);
      affichage_text(145, SCREEN_HEIGHT-55, tabsniper_range, sniper1.s_range, screen);
      affichage_text(145, SCREEN_HEIGHT-35, tabsniper_cost, sniper1.s_cost, screen);

      affichage_text(238, SCREEN_HEIGHT-74, tabmagic_name, magic1.s_name, screen);
      affichage_text(258, SCREEN_HEIGHT-55, tabmagic_damages, magic1.s_damages, screen);
      affichage_text(258, SCREEN_HEIGHT-35, tabmagic_as, magic1.s_as, screen);
      affichage_text(313, SCREEN_HEIGHT-55, tabmagic_range, magic1.s_range, screen);
      affichage_text(313, SCREEN_HEIGHT-35, tabmagic_cost, magic1.s_cost, screen);

      affichage_text(406, SCREEN_HEIGHT-74, tabfire_name, fire1.s_name, screen);
      affichage_text(426, SCREEN_HEIGHT-55, tabfire_damages, fire1.s_damages, screen);
      affichage_text(426, SCREEN_HEIGHT-35, tabfire_as, fire1.s_as, screen);
      affichage_text(481, SCREEN_HEIGHT-55, tabfire_range, fire1.s_range, screen);
      affichage_text(481, SCREEN_HEIGHT-35, tabfire_cost, fire1.s_cost, screen);

      affichage_text(574, SCREEN_HEIGHT-74, tabslow_name, slow1.s_name, screen);
      affichage_text(594, SCREEN_HEIGHT-55, tabslow_damages, slow1.s_damages, screen);
      affichage_text(594, SCREEN_HEIGHT-35, tabslow_as, slow1.s_as, screen);
      affichage_text(644, SCREEN_HEIGHT-55, tabslow_range, slow1.s_range, screen);
      affichage_text(640, SCREEN_HEIGHT-35, tabslow_cost, slow1.s_cost, screen);
      
      /* affichage icones specs */
      rcSword.x = 70;
      rcSword.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(sword, NULL, screen, &rcSword );

      rcSword.x = 238;
      rcSword.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(sword, NULL, screen, &rcSword );

      rcSword.x = 406;
      rcSword.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(sword, NULL, screen, &rcSword );

      rcSword.x = 574;
      rcSword.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(sword, NULL, screen, &rcSword );

      rcFirerate.x = 70;
      rcFirerate.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(firerate, NULL, screen, &rcFirerate );

      rcFirerate.x = 238;
      rcFirerate.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(firerate, NULL, screen, &rcFirerate );

      rcFirerate.x = 406;
      rcFirerate.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(firerate, NULL, screen, &rcFirerate );

      rcFirerate.x = 574;
      rcFirerate.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(firerate, NULL, screen, &rcFirerate );

      rcBow.x = 125;
      rcBow.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(bow, NULL, screen, &rcBow );

      rcBow.x = 291;
      rcBow.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(bow, NULL, screen, &rcBow );

      rcBow.x = 461;
      rcBow.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(bow, NULL, screen, &rcBow );

      rcBow.x = 624;
      rcBow.y = SCREEN_HEIGHT-53;
      SDL_BlitSurface(bow, NULL, screen, &rcBow );

      rcDiamondlittle.x = 125;
      rcDiamondlittle.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcDiamondlittle );

      rcDiamondlittle.x = 291;
      rcDiamondlittle.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcDiamondlittle );

      rcDiamondlittle.x = 461;
      rcDiamondlittle.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcDiamondlittle );

      rcDiamondlittle.x = 624;
      rcDiamondlittle.y = SCREEN_HEIGHT-33;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcDiamondlittle );



      SDL_Flip(screen);

      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(5);
      
    }
   
  FreeMap(map);
  FreeMap(map_objet);


  /*  meilleurs score */
  int meilleurs_scores[5] = {0};
  
  top_score(meilleurs_scores, points);
  

  /* Intialize text gameover */
  s_score = text_init(35, 1, Blanc, s_score);
  s_compteur = text_init(35, 1, Blanc, s_compteur);
  s_gameover = text_init(70, 2, Blanc, s_gameover);
  s_top1 = text_init(35, 1, Blanc, s_top1);
  s_top2 = text_init(30, 1, Blanc, s_top2);
  s_top3 = text_init(25, 1, Blanc, s_top3);
  s_top4 = text_init(20, 1, Blanc, s_top4);
  s_top5 = text_init(15, 1, Blanc, s_top5);
  s_ptop1 = text_init(35, 1, Blanc, s_ptop1);
  s_ptop2 = text_init(30, 1, Blanc, s_ptop2);
  s_ptop3 = text_init(25, 1, Blanc, s_ptop3);
  s_ptop4 = text_init(20, 1, Blanc, s_ptop4);
  s_ptop5 = text_init(15, 1, Blanc, s_ptop5);
  sprintf(tabtop1, "%d", meilleurs_scores[0]);
  sprintf(tabtop2, "%d", meilleurs_scores[1]);
  sprintf(tabtop3, "%d", meilleurs_scores[2]);
  sprintf(tabtop4, "%d", meilleurs_scores[3]);
  sprintf(tabtop5, "%d", meilleurs_scores[4]);
  
  while(fin){


    update_events(key,&liste_mob, &liste_tower, creep, zombie, ender, spider,sniper1, sniper2, sniper3, magic1, magic2, magic3, fire1, fire2, fire3, slow1, slow2, slow3, map, map_objet, &num_mob, &case1, &case2, &case3, &case4, &gameover, &pause, &menu, &fin, &money, screen);
    
    rcMenumort.x = 0;
    rcMenumort.y = 0;
    SDL_BlitSurface(menu_mort, NULL, screen, &rcMenumort );
  
    /* affiche les textes */
    affichage_text(SCREEN_WIDTH/2 - 130, 120, tabscore, s_score, screen);
    affichage_text(SCREEN_WIDTH/2 + 70, 120, tabcompteur, s_compteur, screen);
    affichage_text(SCREEN_WIDTH/7, SCREEN_HEIGHT/20, tabgameover, s_gameover, screen);

    affichage_text(SCREEN_WIDTH/2 -220, 220, tabptop1, s_ptop1, screen); 
    affichage_text(SCREEN_WIDTH/2 -215, 280, tabptop2, s_ptop2, screen); 
    affichage_text(SCREEN_WIDTH/2 -210, 335, tabptop3, s_ptop3, screen); 
    affichage_text(SCREEN_WIDTH/2 -205, 385, tabptop4, s_ptop4, screen); 
    affichage_text(SCREEN_WIDTH/2 -200, 430, tabptop5, s_ptop5, screen); 
    
    affichage_text(SCREEN_WIDTH/2 -180, 220, tabtop1, s_top1, screen); 
    affichage_text(SCREEN_WIDTH/2 -175, 280, tabtop2, s_top2, screen); 
    affichage_text(SCREEN_WIDTH/2 -170, 335, tabtop3, s_top3, screen); 
    affichage_text(SCREEN_WIDTH/2 -165, 385, tabtop4, s_top4, screen); 
    affichage_text(SCREEN_WIDTH/2 -160, 430, tabtop5, s_top5, screen);   
    

    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_Delay(5);

  }
  /* ****************************************************************************************************************************** */
  /* ***********************************     Clean Up    ************************************************************************** */
  /* ****************************************************************************************************************************** */
 
  /* free TTF */
  if(s_score.police != NULL)
    TTF_CloseFont(s_score.police);
  if(s_compteur.police != NULL)
    TTF_CloseFont(s_compteur.police);
  if(s_gameover.police != NULL)
    TTF_CloseFont(s_gameover.police);
  if(s_top1.police != NULL)
    TTF_CloseFont(s_top1.police);
  if(s_top2.police != NULL)
    TTF_CloseFont(s_top2.police);
  if(s_top3.police != NULL)
    TTF_CloseFont(s_top3.police);
  if(s_top4.police != NULL)
    TTF_CloseFont(s_top4.police);
  if(s_top5.police != NULL)
    TTF_CloseFont(s_top5.police);
  if(s_ptop1.police != NULL)
    TTF_CloseFont(s_ptop1.police);
  if(s_ptop2.police != NULL)
    TTF_CloseFont(s_ptop2.police);
  if(s_ptop3.police != NULL)
    TTF_CloseFont(s_ptop3.police);
  if(s_ptop4.police != NULL)
    TTF_CloseFont(s_ptop4.police);
  if(s_ptop5.police != NULL)
    TTF_CloseFont(s_ptop5.police);
  if(s_money.police != NULL)
    TTF_CloseFont(s_money.police);
  if(s_health.police != NULL)
    TTF_CloseFont(s_health.police);

  if(sniper1.s_name.police != NULL)
    TTF_CloseFont(sniper1.s_name.police);
  if(sniper1.s_damages.police != NULL)
    TTF_CloseFont(sniper1.s_damages.police);
  if(sniper1.s_as.police != NULL)
    TTF_CloseFont(sniper1.s_as.police);
  if(sniper1.s_cost.police != NULL)
    TTF_CloseFont(sniper1.s_cost.police);
  if(sniper1.s_range.police != NULL)
    TTF_CloseFont(sniper1.s_range.police);
  if(sniper1.s_sell.police != NULL)
    TTF_CloseFont(sniper1.s_sell.police);

  if(magic1.s_name.police != NULL)
    TTF_CloseFont(magic1.s_name.police);
  if(magic1.s_damages.police != NULL)
    TTF_CloseFont(magic1.s_damages.police);
  if(magic1.s_as.police != NULL)
    TTF_CloseFont(magic1.s_as.police);
  if(magic1.s_cost.police != NULL)
    TTF_CloseFont(magic1.s_cost.police);
  if(magic1.s_range.police != NULL)
    TTF_CloseFont(magic1.s_range.police);
  if(magic1.s_sell.police != NULL)
    TTF_CloseFont(magic1.s_sell.police);

  if(fire1.s_name.police != NULL)
    TTF_CloseFont(fire1.s_name.police);
  if(fire1.s_damages.police != NULL)
    TTF_CloseFont(fire1.s_damages.police);
  if(fire1.s_as.police != NULL)
    TTF_CloseFont(fire1.s_as.police);
  if(fire1.s_cost.police != NULL)
    TTF_CloseFont(fire1.s_cost.police);
  if(fire1.s_range.police != NULL)
    TTF_CloseFont(fire1.s_range.police);
  if(fire1.s_sell.police != NULL)
    TTF_CloseFont(fire1.s_sell.police);

  if(slow1.s_name.police != NULL)
      TTF_CloseFont(slow1.s_name.police);
  if(slow1.s_damages.police != NULL)
    TTF_CloseFont(slow1.s_damages.police);
  if(slow1.s_as.police != NULL)
    TTF_CloseFont(slow1.s_as.police);
  if(slow1.s_cost.police != NULL)
    TTF_CloseFont(slow1.s_cost.police);
  if(slow1.s_range.police != NULL)
    TTF_CloseFont(slow1.s_range.police);
  if(slow1.s_sell.police != NULL)
    TTF_CloseFont(slow1.s_sell.police);

  TTF_Quit();




  /* free liste */
  if (liste_mob != NULL)
    liste_free_mob(&liste_mob);
  if (liste_tower != NULL)
    liste_free_tower(&liste_tower);
  if (liste_tir != NULL)
    liste_free_tir(&liste_tir);

  /* free ath */
  if (heart != NULL)
    SDL_FreeSurface(heart);
  if (diamondbig != NULL)
    SDL_FreeSurface(diamondbig);
  if (diamondlittle != NULL)
    SDL_FreeSurface(diamondlittle);
  if (sword != NULL)
    SDL_FreeSurface(sword);
  if (bow != NULL)
    SDL_FreeSurface(bow);
  if (firerate != NULL)
    SDL_FreeSurface(firerate);

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
  if (menu_tower != NULL)
    SDL_FreeSurface(menu_tower);
  if (menu_pause != NULL)
    SDL_FreeSurface(menu_pause);
  if (tir_magic.tir != NULL)
    SDL_FreeSurface(tir_magic.tir);

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
