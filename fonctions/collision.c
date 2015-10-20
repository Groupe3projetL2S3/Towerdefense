#include "../jeu.h"




int collision_box_box(s_Hitbox box1, s_Hitbox box2) {
  if ((box2.x >= box1.w) /*D*/ 
      || (box2.w <= box1.x) /*G*/
      || (box2.y >= box1.h) /*B*/ 
      || (box2.h <= box1.y)) /*H*/
    
    return 0;
  else
    return 1;
}



void collision_tir_mob(liste_tir *T, liste_mob *M) {

  liste_tir new_liste_tir=NULL;
  liste_tir poubelle_tir = NULL;
  liste_mob new_liste_mob = NULL;
  liste_mob poubelle_mob = NULL;

  liste_tir tit = *T;
  liste_mob mit = *M;


  if (!liste_is_empty_tir(tit) && !liste_is_empty_mob(mit)) {
    
    while (mit != NULL) {
      
      s_Mob m = mit->m;
      tit = *T;
      
      while(tit != NULL) {
	
	s_Tir t = tit->t;
	
	
	if (collision_box_box(t.box, m.box) && t.cible.numero == m.numero) {
	  poubelle_tir = liste_cons_tir(t, poubelle_tir);
	  m.pv = m.pv-t.dommage;
	}
	else {
	  new_liste_tir = liste_cons_tir(t, new_liste_tir);
	}
	tit->t = t;
	tit = tit->next;
      }
      liste_free_tir(&poubelle_tir);
      liste_inverser_tir(&new_liste_tir);
      *T = new_liste_tir;
      new_liste_tir = NULL;
      liste_free_tir(&new_liste_tir);
      
      if (m.pv > 0) {
	new_liste_mob = liste_cons_mob(m, new_liste_mob);
      }
      else{
	poubelle_mob = liste_cons_mob(m, poubelle_mob);
      }
      
      mit->m = m;
      mit = mit->next;
    }
    
    liste_free_mob(&poubelle_mob);
    liste_inverser_mob(&new_liste_mob);
    *M = new_liste_mob;
    new_liste_mob = NULL;
    liste_free_mob(&new_liste_mob);


  }
}
      

      
  
