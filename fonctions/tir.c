#include "../jeu.h"

s_Tir tir_init(s_Tir t, int taillew, int tailleh) {
 
  t.rcSrc.x = 0;
  t.rcSrc.y = 0;
  t.rcSrc.w = taillew;
  t.rcSrc.h = tailleh;
  t.cible.numero = 0;
  t.dommage = 0;
  t.animation = 0;
  return t;
}

s_Tir tir_animation(s_Tir tir){

  tir.animation = 0;

  if(tir.type == TYPE_SNIPER){
    float angle, alpha, op, adj;
    int i = 0, boucle = 1;

    if((((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) <= 0 
	&& ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) < 0)
       || (((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) >= 0 
	   && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) > 0)){
    
      op = fabs((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2));
      adj = fabs((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2));
    }
    if((((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) < 0 
	&& ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) >= 0)
       || (((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) > 0 
	   && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) <= 0)){
      
      adj = fabs((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2));
      op = fabs((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2));
    }

    if (adj != 0)
      alpha = op/adj;
    else
      alpha = op/0.01;

    angle = (atan(alpha)) *(180/M_PI);
    while(boucle){
      if(angle >= i && angle < i+5){
	boucle = 0;
      } 
      else {
	tir.animation += 1;
      }
      i += 5;
    }


    if(((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) <= 0 
       && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) < 0){
      tir.rcSrc.x = tir.rcSrc.w*tir.animation;
    }
    if(((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) < 0 
       && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) >= 0){
      tir.rcSrc.x = tir.rcSrc.w*tir.animation + tir.rcSrc.w*18;
    }
    if(((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) >= 0 
       && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) > 0){
      tir.rcSrc.x = tir.rcSrc.w*tir.animation + tir.rcSrc.w*36;
    }
    if(((tir.coords.y + tir.rcSrc.h/2) - (tir.cible.coords.y + tir.cible.rcSrc.h/2)) > 0 
       && ((tir.coords.x + tir.rcSrc.w/2) - (tir.cible.coords.x + tir.cible.rcSrc.w/2)) <= 0){
      tir.rcSrc.x = tir.rcSrc.w*tir.animation + tir.rcSrc.w*54;
    }

  }


  return tir;
}

void tir_affichage(liste_tir L,  SDL_Surface *screen, liste_mob M) {

  if (L == NULL)
    return;


  liste_tir it =  NULL;
  it = L;
  
  while (it != NULL) {
    s_Tir t = it->t;
    t = deplacement_tir(t);
    t = tir_animation(t);
    
    t.rcSprite.x = (int) t.coords.x;
    t.rcSprite.y = (int) t.coords.y;
    
    SDL_BlitSurface(t.tir, &t.rcSrc, screen, &t.rcSprite);
    
    it->t = t;
    it = it->next;
  }
 }


s_Tir tir_spawn(s_Tir t, s_Tower to) { 
  t.coords.x = to.coords.x + to.rcSprite.w/2;
  t.coords.y = to.coords.y + to.rcSprite.h/2;
  if (to.type == TYPE_SNIPER){
    t.dommage = 0; // a définir la puissance selon le type 
    t.type = to.type;
  }
  if (to.type == TYPE_MAGIC){
    t.dommage = 1; // a définir la puissance selon le type 
    t.type = to.type;
  }

  return t;
}

s_Tir direction_tir(s_Tir t, s_Mob mob) { //à faire appel quand il spawn
  float alpha;
  s_Mob m;


  m = mob;
  
  float xm = m.coords.x + CREEP_WIDTH/2;
  float ym = m.coords.y + CREEP_HEIGHT/2;
  float xt = t.coords.x + TIR_WIDTH/2;
  float yt = t.coords.y + TIR_HEIGHT/2;
  
  if (xm >= (xt) && ym <= (yt)){
    alpha = (xm-xt)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acosf(alpha);
    t.vit.x=cosf(alpha);
    t.vit.y=-sinf(alpha);
  }
  if (xm < (xt) && ym <= (yt)){
    alpha = (xt-xm)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acosf(alpha);
    t.vit.x=-cosf(alpha);
    t.vit.y=-sinf(alpha);
  }
  if (xm < (xt) && ym > (yt)){
    alpha = (xt-xm)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acosf(alpha);
    t.vit.x=-cosf(alpha);
    t.vit.y=sinf(alpha);
  }
  if (xm >= (xt) && ym > (yt)){
    alpha = (xm-xt)/((sqrt(pow((xm-xt),2)+pow((ym-yt),2))));
    alpha = acosf(alpha);
    t.vit.x=cosf(alpha);
    t.vit.y=sinf(alpha);
  }
  
  return t;
}


s_Tir deplacement_tir(s_Tir t) { //à faire appel dans affichage

  t.coords.x += t.vit.x*6;
  t.coords.y += t.vit.y*6;

  t.box.x = t.coords.x;
  t.box.y = t.coords.y;
  t.box.w = t.coords.x + t.rcSrc.w;
  t.box.h = t.coords.y + t.rcSrc.h;

  return t;
}


void disparition_tir(liste_tir *T, liste_mob M) {

  liste_tir new_liste_tir=NULL;
  liste_tir poubelle_tir = NULL;

  liste_tir it = *T;
      
  while(it != NULL) {
    
    s_Tir t = it->t;
	
    if (liste_is_empty_mob(M) || t.cible.numero == 0) {
      poubelle_tir = liste_cons_tir(t, poubelle_tir);
    }
    else {
      new_liste_tir = liste_cons_tir(t, new_liste_tir);
    }
    

  
    it->t = t;
    it = it->next;
  }
  liste_free_tir(&poubelle_tir);
  *T = new_liste_tir;
  new_liste_tir = NULL;
  liste_free_tir(&new_liste_tir);     
  
}

void cible(liste_tir *L, liste_mob M){

  liste_tir it = *L;
  liste_tir new_liste_tir = NULL;
  liste_mob mit = M;
  int cible_valide = 0;

  if (!liste_is_empty_tir(it) && !liste_is_empty_mob(mit)){
    
    
    while (it != NULL) {
      s_Tir t = it->t;
      
      
      while(mit != NULL){
	
	s_Mob m = mit->m;
	
	if(m.numero == t.cible.numero){
	  t = direction_tir(t, m);
	  cible_valide = 1;
	}
	
	
	mit->m = m;
	mit = mit->next;
	
      }
      if(cible_valide == 0){
	t.cible.numero = 0;
      }
      new_liste_tir = liste_cons_tir(t, new_liste_tir);

      it->t = t;
      it = it->next;
      
    }
    *L = new_liste_tir;

  }
}
