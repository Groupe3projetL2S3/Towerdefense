#include "../jeu.h"


//initialise la structure text
s_Text text_init(int taille_police,int type_police, SDL_Color couleur,s_Text t){


  t.temps = 0;
  t.affiche = 1;
  TTF_Font *police = NULL;
  if(type_police == IMP_POLICE){
    police = TTF_OpenFont("font/impact.ttf", taille_police);
  }
  if(type_police == MINECRAFT_POLICE){
    police = TTF_OpenFont("font/Minecraft.ttf", taille_police);
  }
  if(!police) {
    printf("erreur chargement police \n");
    exit(-1);
  }
  t.police = police;
  t.color = couleur;
  if(!t.police) {
    printf("erreur assignation police \n");
    exit(-1);
  }
  return t;
}

//affichage des textes
void affichage_text(int x, int y, char *tab, s_Text t,SDL_Surface *screen){ //affichage du texte

  t.text = TTF_RenderText_Solid(t.police,tab,t.color);
  t.rctext.x = x;
  t.rctext.y = y;
  if (t.affiche)
    SDL_BlitSurface(t.text,NULL,screen,&t.rctext);
 
}

//gestion des meilleurs scores
void top_score(int *meilleurs_scores, int points) {

  FILE *fichier = NULL;
  
  fichier = fopen("autres/meilleurs_scores.txt", "r");
  
  if (fichier != NULL) {
    fscanf(fichier, "%d %d %d %d %d", &meilleurs_scores[0], &meilleurs_scores[1], &meilleurs_scores[2], &meilleurs_scores[3], &meilleurs_scores[4]);    
    fclose(fichier);
    
    fichier = fopen("autres/meilleurs_scores.txt", "w+");
    if (points >= meilleurs_scores[0]) {
      
      meilleurs_scores[4] = meilleurs_scores[3];
      meilleurs_scores[3] = meilleurs_scores[2];
      meilleurs_scores[2] = meilleurs_scores[1];
      meilleurs_scores[1] = meilleurs_scores[0];
      meilleurs_scores[0] = points;
    }
    if (meilleurs_scores[0] > points && points >= meilleurs_scores[1]) {
      
      meilleurs_scores[4] = meilleurs_scores[3];
      meilleurs_scores[3] = meilleurs_scores[2];
      meilleurs_scores[2] = meilleurs_scores[1];
      meilleurs_scores[1] = points;
    }
    if (meilleurs_scores[1] > points && points >= meilleurs_scores[2]) {
      
      meilleurs_scores[4] = meilleurs_scores[3];
      meilleurs_scores[3] = meilleurs_scores[2];
      meilleurs_scores[2] = points;
    }
    if (meilleurs_scores[2] > points && points >= meilleurs_scores[3]) {
      
      meilleurs_scores[4] = meilleurs_scores[3];
      meilleurs_scores[3] = points;
    }
    if (meilleurs_scores[3] > points && points >= meilleurs_scores[4]) {
      
      meilleurs_scores[4] = points;
    }
    
    fprintf(fichier, "%d %d %d %d %d", meilleurs_scores[0], meilleurs_scores[1], meilleurs_scores[2], meilleurs_scores[3], meilleurs_scores[4]);
    fclose(fichier);
  }
}
