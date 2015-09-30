#include "jeu.h"

/*************************** Implémentation liste mob *********************/
/* constructeurs */

liste_mob liste_new_empty_mob() {
  return NULL;
}


liste_mob liste_cons_mob(s_Mob m, liste_mob L) {
  liste_mob nouveau = (liste_mob) malloc(sizeof(Liste_mob));
  nouveau->m = m; 
  nouveau->next = L;
  return nouveau;
}


/* accesseurs */

int liste_is_empty_mob(liste_mob L) {
  if (L == NULL) {
    return 1;
  }
  return 0;
}

s_Mob liste_head_mob(liste_mob L) {
  assert (liste_is_empty_mob(L)==0);
  return (L->m);
}

liste_mob liste_tail_mob(liste_mob L) {
  assert (liste_is_empty_mob(L)==0);
  return (L->next);
}


/* free  */

void liste_free_mob(liste_mob * L) {
  liste_mob tmp;
  while (!liste_is_empty_mob(*L)) {
    tmp = *L;
    *L = liste_tail_mob(*L);
    free(tmp);
  }
}




/*************************** Implémentation liste Towers *********************/
/* constructeurs */

liste_tower liste_new_empty_tower() {
  return NULL;
}


liste_tower liste_cons_tower(s_Tower t, liste_tower L) {
  liste_tower nouveau = (liste_tower) malloc(sizeof(Liste_tower));
  nouveau->t = t; 
  nouveau->next = L;
  return nouveau;
}


/* accesseurs */

int liste_is_empty_tower(liste_tower L) {
  if (L == NULL) {
    return 1;
  }
  return 0;
}

s_Tower liste_head_tower(liste_tower L) {
  assert (liste_is_empty_tower(L)==0);
  return (L->t);
}

liste_tower liste_tail_tower(liste_tower L) {
  assert (liste_is_empty_tower(L)==0);
  return (L->next);
}


/* free  */

void liste_free_tower(liste_tower * L) {
  liste_tower tmp;
  while (!liste_is_empty_tower(*L)) {
    tmp = *L;
    *L = liste_tail_tower(*L);
    free(tmp);
  }
}


/*************************** Implémentation liste tir *********************/
/* constructeurs */

liste_tir liste_new_empty_tir() {
  return NULL;
}


liste_tir liste_cons_tir(s_Tir t, liste_tir L) {
  liste_tir nouveau = (liste_tir) malloc(sizeof(Liste_tir));
  nouveau->t = t; 
  nouveau->next = L;
  return nouveau;
}


/* accesseurs */

int liste_is_empty_tir(liste_tir L) {
  if (L == NULL) {
    return 1;
  }
  return 0;
}

s_Tir liste_head_tir(liste_tir L) {
  assert (liste_is_empty_tir(L)==0);
  return (L->t);
}

liste_tir liste_tail_tir(liste_tir L) {
  assert (liste_is_empty_tir(L)==0);
  return (L->next);
}


/* free  */

void liste_free_tir(liste_tir * L) {
  liste_tir tmp;
  while (!liste_is_empty_tir(*L)) {
    tmp = *L;
    *L = liste_tail_tir(*L);
    free(tmp);
  }
}
