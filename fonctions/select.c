#include "../jeu.h"

//initialise la structure range
s_Range Range_init(s_Range r, int taillew, int tailleh) {
 
  r.rcSrc.x = 0;
  r.rcSrc.y = 0;
  r.rcSrc.w = taillew;
  r.rcSrc.h = tailleh;

  return r;
}

//initialise structure du menu
s_Menu menu_select_init(s_Menu menu, int taillew, int tailleh) {

  menu.rcSrc.x = 0;
  menu.rcSrc.y = 0;
  menu.rcSrc.w = taillew;
  menu.rcSrc.h = tailleh;

  return menu;
}

//initialise structure upgrade
s_Upgrade upgrade_init(s_Upgrade up, int taillew, int tailleh) {

  up.rcSrc.x = 0;
  up.rcSrc.y = 0;
  up.rcSrc.w = taillew;
  up.rcSrc.h = tailleh;

  return up;
}

//initialise structure sell  
s_Sell sell_init(s_Sell s, int taillew, int tailleh) {

  s.rcSrc.x = 0;
  s.rcSrc.y = 0;
  s.rcSrc.w = taillew;
  s.rcSrc.h = tailleh;

  return s;
}

//affichage des ranges de tours
void Range_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){

      t.range.coords.x = t.coords.x + t.rcSrc.w/2;
      t.range.coords.y = t.coords.y + 2*(t.rcSrc.h/3);


      t.range.rcSprite.x = (int) t.coords.x - (t.range.rcSrc.w - t.rcSrc.w)/2;
      t.range.rcSprite.y = (int) t.coords.y - (t.range.rcSrc.h - t.rcSrc.h)/2 + t.rcSrc.h/4;


      SDL_SetAlpha(t.range.range, SDL_SRCALPHA, 100);
      SDL_BlitSurface(t.range.range, &t.range.rcSrc, screen, &t.range.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}

//affichage du bouton upgrade
void upgrade_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.up.rcSprite.x = MENU_SELECT_WIDTH - UP_WIDTH - 7;
      t.up.rcSprite.y = 8;

      SDL_BlitSurface(t.up.up, &t.up.rcSrc, screen, &t.up.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}

//affichage du bouton sell
void sell_affichage(liste_tower L, SDL_Surface *screen) {

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.sell.rcSprite.x = MENU_SELECT_WIDTH - SELL_WIDTH - 7;
      t.sell.rcSprite.y = UP_HEIGHT + 12;

      SDL_BlitSurface(t.sell.sell, &t.sell.rcSrc, screen, &t.sell.rcSprite);
    }
    it->t = t;
    it = it->next;
  }
}

//affichage de prix d'upgrade/sell si on passe la souris sur le bouton
void up_sell_motion(liste_tower L, int event_motion_x, int event_motion_y, SDL_Surface *screen) {
  

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select && t.actif
       && event_motion_x >= t.sell.rcSprite.x
       && event_motion_x <= t.sell.rcSprite.x + SELL_WIDTH
       && event_motion_y >= t.sell.rcSprite.y
       && event_motion_y <= t.sell.rcSprite.y + SELL_HEIGHT) {

      t.print_sell = 1;   
    } else {
      t.print_sell = 0;
    }
    if(t.select && t.actif
       && event_motion_x >= t.up.rcSprite.x
       && event_motion_x <= t.up.rcSprite.x + UP_WIDTH
       && event_motion_y >= t.up.rcSprite.y
       && event_motion_y <= t.up.rcSprite.y + UP_HEIGHT) {

      t.print_up = 1;   
    } else {
      t.print_up = 0;
    }

    it->t = t;
    it = it->next;
  }
}

//affichage de petit menu select (en haut a gauche
void menu_select_affichage(liste_tower L, SDL_Surface *screen, SDL_Surface *sword, SDL_Surface *firerate,SDL_Surface *bow, SDL_Surface *diamondlittle){

  /* char des tours de sniper */
  char tabsniper_damages[4] = "2.0";
  char tabsniper_as[4] = "2.0";
  char tabsniper_range[5] = "90";
  char tabsniper_sell[5] = "50";

  char tabsniper2_damages[4] = "5.0";
  char tabsniper2_as[4] = "3.0";
  char tabsniper2_range[5] = "110";
  char tabsniper2_cost[5] = "200";
  char tabsniper2_sell[5] = "100";

  char tabsniper3_damages[5] = "12.0";
  char tabsniper3_as[4] = "4.5";
  char tabsniper3_range[5] = "130";
  char tabsniper3_cost[5] = "400";
  char tabsniper3_sell[5] = "200";

  /* char des tours de magie */
  char tabmagic_damages[4] = "5.0";
  char tabmagic_as[4] = "1.0";
  char tabmagic_range[5] = "60";
  char tabmagic_sell[5] = "100";

  char tabmagic2_damages[5] = "11.0";
  char tabmagic2_as[4] = "1.5";
  char tabmagic2_cost[5] = "400";
  char tabmagic2_range[5] = "70";
  char tabmagic2_sell[5] = "200";

  char tabmagic3_damages[5] = "27.0";
  char tabmagic3_as[5] = "2.25";
  char tabmagic3_cost[5] = "800";
  char tabmagic3_range[5] = "80";
  char tabmagic3_sell[5] = "400";

  /* char des tours de feu */
  char tabfire_damages[5] = "0.08";
  char tabfire_as[5] = "50.0";
  char tabfire_range[5] = "55";
  char tabfire_sell[5] = "200";

  char tabfire2_damages[5] = "0.3";
  char tabfire2_as[5] = "50.0";
  char tabfire2_cost[5] = "800";
  char tabfire2_range[5] = "60";
  char tabfire2_sell[5] = "400";

  char tabfire3_damages[5] = "0.8";
  char tabfire3_as[5] = "50.0";
  char tabfire3_cost[5] = "1600";
  char tabfire3_range[5] = "70";
  char tabfire3_sell[5] = "800";


  /* char des tours de slow */
  char tabslow_damages[4] = "0.0";
  char tabslow_as[4] = "0.0";
  char tabslow_range[5] = "55";
  char tabslow_sell[5] = "125";

  char tabslow2_damages[4] = "0.0";
  char tabslow2_as[4] = "0.0";
  char tabslow2_cost[5] = "500";
  char tabslow2_range[5] = "55";
  char tabslow2_sell[5] = "250";

  char tabslow3_damages[4] = "0.0";
  char tabslow3_as[4] = "0.0";
  char tabslow3_cost[5] = "1000";
  char tabslow3_range[5] = "55";
  char tabslow3_sell[5] = "500";

  SDL_Rect rcSprite;

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.menu.rcSprite.x = 0;
      t.menu.rcSprite.y = 0;

      SDL_BlitSurface(t.menu.menu, &t.menu.rcSrc, screen, &t.menu.rcSprite);

      rcSprite.x = 10;
      rcSprite.y = 7;
      SDL_BlitSurface(sword, NULL, screen, &rcSprite);
      rcSprite.y = 24;
      SDL_BlitSurface(firerate, NULL, screen, &rcSprite);
      rcSprite.y = 41;
      SDL_BlitSurface(bow, NULL, screen, &rcSprite);
      rcSprite.x = 113;
      if(t.type == TYPE_SLOW || t.type == TYPE_FIRE){
	if(t.niveau == 2)
	  rcSprite.x = 118;
      }
      if(t.print_sell) {
      rcSprite.y = 37;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcSprite);
      }
      if(t.print_up && t.niveau < 3) {
      rcSprite.y = 9;
      SDL_BlitSurface(diamondlittle, NULL, screen, &rcSprite);
      }

      if(t.niveau == 1){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 6, tabsniper_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabsniper_as, t.s_as, screen);
	  affichage_text(30, 38, tabsniper_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabsniper_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabsniper2_cost, t.s_cost, screen);
	  }
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 6, tabmagic_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabmagic_as, t.s_as, screen);
	  affichage_text(30, 38, tabmagic_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabmagic_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabmagic2_cost, t.s_cost, screen);
	  }
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 6, tabfire_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabfire_as, t.s_as, screen);
	  affichage_text(30, 38, tabfire_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabfire_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabfire2_cost, t.s_cost, screen);
	  }
	} else {
	  affichage_text(30, 6, tabslow_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabslow_as, t.s_as, screen);
	  affichage_text(30, 38, tabslow_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabslow_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabslow2_cost, t.s_cost, screen);
	  }
	}
      } else if(t.niveau == 2){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 6, tabsniper2_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabsniper2_as, t.s_as, screen);
	  affichage_text(30, 38, tabsniper2_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabsniper2_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabsniper3_cost, t.s_cost, screen);
	  }
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 6, tabmagic2_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabmagic2_as, t.s_as, screen);
	  affichage_text(30, 38, tabmagic2_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabmagic2_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabmagic3_cost, t.s_cost, screen);
	  }
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 6, tabfire2_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabfire2_as, t.s_as, screen);
	  affichage_text(30, 38, tabfire2_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabfire2_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabfire3_cost, t.s_cost, screen);
	  }
	} else {
	  affichage_text(30, 6, tabslow2_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabslow2_as, t.s_as, screen);
	  affichage_text(30, 38, tabslow2_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabslow2_sell, t.s_sell, screen);
	  }
	  if(t.print_up) {
	    affichage_text(90, 8, tabslow3_cost, t.s_cost, screen);
	  }
	}
      } else if(t.niveau == 3){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 6, tabsniper3_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabsniper3_as, t.s_as, screen);
	  affichage_text(30, 38, tabsniper3_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabsniper3_sell, t.s_sell, screen);
	  }
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 6, tabmagic3_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabmagic3_as, t.s_as, screen);
	  affichage_text(30, 38, tabmagic3_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabmagic3_sell, t.s_sell, screen);
	  }
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 6, tabfire3_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabfire3_as, t.s_as, screen);
	  affichage_text(30, 38, tabfire3_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabfire3_sell, t.s_sell, screen);
	  }
	} else {
	  affichage_text(30, 6, tabslow3_damages, t.s_damages, screen);
	  affichage_text(30, 22, tabslow3_as, t.s_as, screen);
	  affichage_text(30, 38, tabslow3_range, t.s_range, screen);
	  if(t.print_sell) {
	    affichage_text(90, 35, tabslow3_sell, t.s_sell, screen);
	  }
	}
      }
    }     
    it->t = t;
    it = it->next;
  }
}

