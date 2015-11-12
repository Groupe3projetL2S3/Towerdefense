#include "../jeu.h"

s_Range Range_init(s_Range r, int taillew, int tailleh) {
 
  r.rcSrc.x = 0;
  r.rcSrc.y = 0;
  r.rcSrc.w = taillew;
  r.rcSrc.h = tailleh;

  return r;
}

s_Menu menu_select_init(s_Menu menu, int taillew, int tailleh) {

  menu.rcSrc.x = 0;
  menu.rcSrc.y = 0;
  menu.rcSrc.w = taillew;
  menu.rcSrc.h = tailleh;

  return menu;
}

s_Upgrade upgrade_init(s_Upgrade up, int taillew, int tailleh) {

  up.rcSrc.x = 0;
  up.rcSrc.y = 0;
  up.rcSrc.w = taillew;
  up.rcSrc.h = tailleh;

  return up;
}
  
s_Sell sell_init(s_Sell s, int taillew, int tailleh) {

  s.rcSrc.x = 0;
  s.rcSrc.y = 0;
  s.rcSrc.w = taillew;
  s.rcSrc.h = tailleh;

  return s;
}

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

void menu_select_affichage(liste_tower L, SDL_Surface *screen) {

  /* char des tours de sniper */
  char tabsniper_name[7] = "Sniper";
  char tabsniper_damages[4] = "1.0";
  char tabsniper_as[4] = "3.5";
  char tabsniper_cost[4] = "100";
  char tabsniper_range[4] = "90";
  char tabsniper_sell[4] = "50";

  char tabsniper2_damages[4] = "1.0";
  char tabsniper2_as[4] = "3.5";
  char tabsniper2_range[4] = "110";
  char tabsniper2_cost[4] = "200";
  char tabsniper2_sell[4] = "100";

  char tabsniper3_damages[4] = "1.0";
  char tabsniper3_as[4] = "3.5";
  char tabsniper3_range[4] = "130";
  char tabsniper3_cost[4] = "300";
  char tabsniper3_sell[4] = "150";

  /* char des tours de magie */
  char tabmagic_name[6] = "Magic";
  char tabmagic_damages[4] = "5.0";
  char tabmagic_as[4] = "2.5";
  char tabmagic_cost[4] = "100";
  char tabmagic_range[4] = "60";
  char tabmagic_sell[4] = "50";

  char tabmagic2_damages[4] = "5.0";
  char tabmagic2_as[4] = "2.5";
  char tabmagic2_cost[4] = "200";
  char tabmagic2_range[4] = "70";
  char tabmagic2_sell2[4] = "100";

  char tabmagic3_damages[4] = "5.0";
  char tabmagic3_as[4] = "2.5";
  char tabmagic3_cost[4] = "300";
  char tabmagic3_range[4] = "80";
  char tabmagic3_sell2[4] = "150";

  /* char des tours de feu */
  char tabfire_name[5] = "Fire";
  char tabfire_damages[4] = "0.1";
  char tabfire_as[4] = "2.0";
  char tabfire_cost[4] = "100";
  char tabfire_range[4] = "55";
  char tabfire_sell[4] = "50";

  char tabfire2_damages[4] = "0.1";
  char tabfire2_as[4] = "2.0";
  char tabfire2_cost[4] = "200";
  char tabfire2_range[4] = "60";
  char tabfire2_sell[4] = "100";

  char tabfire3_damages[4] = "0.1";
  char tabfire3_as[4] = "2.0";
  char tabfire3_cost[4] = "300";
  char tabfire3_range[4] = "70";
  char tabfire3_sell[4] = "150";


  /* char des tours de slow */
  char tabslow_name[5] = "Slow";
  char tabslow_damages[4] = "0.0";
  char tabslow_as[4] = "2.0";
  char tabslow_cost[4] = "100";
  char tabslow_range[4] = "55";
  char tabslow_sell[4] = "50";

  char tabslow2_damages[4] = "0.0";
  char tabslow2_as[4] = "3.0";
  char tabslow2_cost[4] = "200";
  char tabslow2_range[4] = "55";
  char tabslow2_sell[4] = "100";

  char tabslow3_damages[4] = "0.0";
  char tabslow3_as[4] = "4.0";
  char tabslow3_cost[4] = "300";
  char tabslow3_range[4] = "55";
  char tabslow3_sell[4] = "150";

  liste_tower it = L;
  while (it != NULL) {
    s_Tower t = it->t;
	
    if(t.select){
      t.menu.rcSprite.x = 0;
      t.menu.rcSprite.y = 0;

      SDL_BlitSurface(t.menu.menu, &t.menu.rcSrc, screen, &t.menu.rcSprite);


      if(t.niveau == 1){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 12, tabsniper_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabsniper_as, t.s_as, screen);
	  affichage_text(30, 41, tabsniper_range, t.s_range, screen);
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 12, tabmagic_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabmagic_as, t.s_as, screen);
	  affichage_text(30, 41, tabmagic_range, t.s_range, screen);
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 12, tabfire_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabfire_as, t.s_as, screen);
	  affichage_text(30, 41, tabfire_range, t.s_range, screen);
	} else {
	  affichage_text(30, 12, tabslow_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabslow_as, t.s_as, screen);
	  affichage_text(30, 41, tabslow_range, t.s_range, screen);
	}
      } else if(t.niveau == 2){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 12, tabsniper2_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabsniper2_as, t.s_as, screen);
	  affichage_text(30, 41, tabsniper2_range, t.s_range, screen);
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 12, tabmagic2_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabmagic2_as, t.s_as, screen);
	  affichage_text(30, 41, tabmagic2_range, t.s_range, screen);
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 12, tabfire2_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabfire2_as, t.s_as, screen);
	  affichage_text(30, 41, tabfire2_range, t.s_range, screen);
	} else {
	  affichage_text(30, 12, tabslow2_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabslow2_as, t.s_as, screen);
	  affichage_text(30, 41, tabslow2_range, t.s_range, screen);
	}
      } else if(t.niveau == 3){
	if(t.type == TYPE_SNIPER){ 
	  affichage_text(30, 12, tabsniper3_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabsniper3_as, t.s_as, screen);
	  affichage_text(30, 41, tabsniper3_range, t.s_range, screen);
	} else if(t.type == TYPE_MAGIC){
	  affichage_text(30, 12, tabmagic3_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabmagic3_as, t.s_as, screen);
	  affichage_text(30, 41, tabmagic3_range, t.s_range, screen);
	} else if(t.type == TYPE_FIRE){  
	  affichage_text(30, 12, tabfire3_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabfire3_as, t.s_as, screen);
	  affichage_text(30, 41, tabfire3_range, t.s_range, screen);
	} else {
	  affichage_text(30, 12, tabslow3_damages, t.s_damages, screen);
	  affichage_text(30, 27, tabslow3_as, t.s_as, screen);
	  affichage_text(30, 41, tabslow3_range, t.s_range, screen);
	}
      }
    }     
    it->t = t;
    it = it->next;
  }
}

