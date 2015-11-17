#include "../jeu.h"

//initialisation de la structure healhbar
s_Healthbar healthbar_init(s_Healthbar h, int taillew, int tailleh) {
  
  h.rcSrc.x = 0;
  h.rcSrc.y = 0;
  h.rcSrc.w = taillew;
  h.rcSrc.h = tailleh;

  return h;
}

//animation de la barre de vie des mobs
s_Healthbar healthbar_animation(s_Healthbar h, s_Mob mob) {
  
  float tmp1 = 0, tmp2 = 0, vie = 100.0;
  tmp1 = mob.pv_max;
  tmp2 = mob.pv;

  vie = ((tmp2/tmp1)*100);

  
  if (vie >= 95){
    h.rcSrc.x = 0;
  }
  if (vie >= 90 && vie < 95){
    h.rcSrc.x = 20;
  }
  if (vie >= 85 && vie < 90){
    h.rcSrc.x = 40;
  }
  if (vie >= 80 && vie < 85){
    h.rcSrc.x = 60;
  }
  if (vie >= 75 && vie < 80){
    h.rcSrc.x = 80;
  }
 if (vie >= 70 && vie < 75){
    h.rcSrc.x = 100;
  }
 if (vie >= 65 && vie < 70){
    h.rcSrc.x = 120;
  }
 if (vie >= 60 && vie < 65){
    h.rcSrc.x = 140;
  }
 if (vie >= 55 && vie < 60){
    h.rcSrc.x = 160;
  }
 if (vie >= 50 && vie < 55){
    h.rcSrc.x = 180;
  }
 if (vie >= 45 && vie < 50){
    h.rcSrc.x = 200;
  }
 if (vie >= 40 && vie < 45){
    h.rcSrc.x = 220;
  }
 if (vie >= 35 && vie < 40){
    h.rcSrc.x = 240;
  }
if (vie >= 30 && vie < 35){
    h.rcSrc.x = 260;
  }
if (vie >= 25 && vie < 30){
    h.rcSrc.x = 280;
  }
if (vie >= 20 && vie < 25){
    h.rcSrc.x = 300;
  }
if (vie >= 15 && vie < 20){
    h.rcSrc.x = 320;
  }
if (vie >= 10 && vie < 15){
    h.rcSrc.x = 340;
  }
if (vie >= 5 && vie < 10){
    h.rcSrc.x = 360;
  }
if (vie >= 0 && vie < 5){
    h.rcSrc.x = 380;
  }

  return h;
}


//affichage de la barre de vie des mobs
void healthbar_affichage(liste_mob L, SDL_Surface *screen) {
  
  liste_mob it = L;
  while (it != NULL) {
    s_Mob m = it->m;
	
    
    m.healthbar.rcSprite.x = (int) m.coords.x + m.rcSrc.w/2 - m.healthbar.rcSrc.w/2;
    m.healthbar.rcSprite.y = (int) m.coords.y - m.healthbar.rcSrc.h;

    m.healthbar = healthbar_animation(m.healthbar, m);

    SDL_SetAlpha(m.healthbar.vie, SDL_SRCALPHA, 190);
    SDL_BlitSurface(m.healthbar.vie, &m.healthbar.rcSrc, screen, &m.healthbar.rcSprite);

    it->m = m;
    it = it->next;
  }
}
