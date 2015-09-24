#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

#define TAB_MAX 1000

SDL_Surface* Load_image(const char* image) {
  SDL_Surface* res;
  SDL_Surface* temp = SDL_LoadBMP(image);
  res = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return res;
}

//Fonctions de LoadMap
void LoadMap_tiles(FILE* Fichier,Map* map) //Sous fonction qui charge les tiles dans un tableau
{
  int nbtile, i, j;
  char tab[TAB_MAX];  
  char tab1[TAB_MAX]; // Tableaux pour stocker lignes Fichier 
  fscanf(Fichier, "%s", tab); // #images_tiles
  fscanf(Fichier, "%s", tab); // nom image bmp
  map->tileset = Load_image(tab); //On charge l'image indiquée dans le txt
  fscanf(Fichier, "%d %d", &map->nbtilesX, &map->nbtilesY);
  map->tile_width = map->tileset->w / map->nbtilesX; //on obtient la largeur d'un tile
  map->tile_height = map->tileset->h / map->nbtilesY; //on obtient la hauteur d'un tile
  map->tab_props = malloc(map->nbtilesX * map->nbtilesY * sizeof(TileProp));
  for(j = 0, nbtile = 0; j < map->nbtilesY; j++)
    {
      for(i = 0; i < map->nbtilesX; i++, nbtile++)
	{
	  map->tab_props[nbtile].R.w = map->tile_width;
	  map->tab_props[nbtile].R.h = map->tile_height;
	  map->tab_props[nbtile].R.x = i * map->tile_width;
	  map->tab_props[nbtile].R.y = j * map->tile_height;
	  fscanf(Fichier,"%s %s",tab,tab1);
	  map->tab_props[nbtile].type = 0;
	  if (strcmp(tab1,"terrain")==0)
	    map->tab_props[nbtile].type = 1;
	}
    }
}



void LoadMap_structure(FILE* Fichier,Map* map) //Charge les tiles dans le tableau final
{
  int i,j;
  char tab[TAB_MAX];  
  fscanf(Fichier, "%s", tab); // On change de partie du Fichier (#monde)
  fscanf(Fichier, "%d %d", &map->nbtiles_largeur_monde, &map->nbtiles_hauteur_monde); //largeur et hauteur du tableau monde
  map->monde = malloc(map->nbtiles_largeur_monde * sizeof(Uint16*));
  for(i = 0; i < map->nbtiles_largeur_monde; i++)
    map->monde[i] = malloc(map->nbtiles_hauteur_monde * sizeof(Uint16));
  for(j = 0; j < map->nbtiles_hauteur_monde; j++)
    {
      for(i = 0; i < map->nbtiles_largeur_monde; i++)
	{
	  int tmp;
	  fscanf(Fichier, "%d", &tmp);
	  if (tmp >= map->nbtilesX * map->nbtilesY)
	    {
	      printf("Il n'y a pas autant de tiles !\n");
	      SDL_Quit();
	    }
	  map->monde[i][j] = tmp;
	}
    }
}



Map* LoadMap(const char* monde) //affecte le Fichier txt à la map
{
  FILE* Fichier;
  Map* map;
  Fichier = fopen(monde,"r");
  if (!Fichier)
    {
      printf("Fichier %s introuvable !! \n",monde);
      SDL_Quit();
    }
  map = malloc(sizeof(Map));
  LoadMap_tiles(Fichier,map);
  LoadMap_structure(Fichier,map);
  fclose(Fichier);
  return map;
}


int PrintMap(Map* map,SDL_Surface* screen) //affiche la map
{
  int i,j;
  SDL_Rect Rect_dest;
  int numero_tile;
  for(i = 0; i < map->nbtiles_largeur_monde; i++)
    {
      for(j = 0; j < map->nbtiles_hauteur_monde; j++)
	{
	  Rect_dest.x = i * map->tile_width;
	  Rect_dest.y = j * map->tile_height;
	  numero_tile = map->monde[i][j];
	  SDL_BlitSurface(map->tileset, &(map->tab_props[numero_tile].R), screen, &Rect_dest);
	}
    }
  return 0;
}

int FreeMap(Map* map)
{
  int i;
  SDL_FreeSurface(map->tileset);
  for(i = 0; i < map->nbtiles_hauteur_monde; i++)
    free(map->monde[i]);
  free(map->monde);
  free(map->tab_props);
  free(map);
  return 0;
}


s_Mob mob_spawn(s_Mob s_mob, int taillew, int tailleh) { //gère l'apparition du vaisseau
  /* set vaisseau speed */
  s_mob.vit.x = 0.2;
  s_mob.vit.y = 0.0;

  /* set sprite position */
  s_mob.coords.x = -30;
  s_mob.coords.y = 120;
  
  /* set sprite animation frame */
  s_mob.rcSrc.x = 0;
  s_mob.rcSrc.y = 0;
  s_mob.rcSrc.w = taillew;
  s_mob.rcSrc.h = tailleh;

  s_mob.animation = 0;
  
  return s_mob;
}
s_Mob mob_deplacement(s_Mob s_mob) { 


  s_mob.coords.x = s_mob.coords.x + s_mob.vit.x;
  s_mob.coords.y = s_mob.coords.y + s_mob.vit.y;
  
  
  return s_mob;
}

s_Mob mob_parcours(s_Mob s_mob, Map *map){
  
  int x, y, marge, haut, bas, gauche, droite;
  
 
  x = (int) (s_mob.coords.x + CREEP_WIDTH/2 ) / TILE_SIZE;
  y = (int) (s_mob.coords.y +  CREEP_HEIGHT/2) / TILE_SIZE;
      
  
  if (s_mob.coords.x > TILE_SIZE){
    haut = map->monde[x][y-1];
    gauche = map->monde[x-1][y];
    bas = map->monde[x][y+1];
    droite = map->monde[x+1][y];

    float creep_speed = 0.4;
    marge = 8;

   if (map->tab_props[gauche].type == 0 && s_mob.vit.y > 0 && s_mob.coords.y >= y*TILE_SIZE - marge) {
      s_mob.vit.x = -creep_speed;
      s_mob.vit.y = 0;

    }
    if (map->tab_props[gauche].type == 0 && s_mob.vit.y < 0 && s_mob.coords.y <= y*TILE_SIZE - marge) {
      s_mob.vit.x = -creep_speed;
      s_mob.vit.y = 0;
    }
    if (map->tab_props[bas].type == 0 && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = creep_speed;

    }
    if (map->tab_props[bas].type == 0 && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = creep_speed;

    }
    if (map->tab_props[haut].type == 0 && s_mob.vit.x > 0 && s_mob.coords.x >= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -creep_speed;

    }
    if (map->tab_props[haut].type == 0 && s_mob.vit.x < 0 && s_mob.coords.x <= x*TILE_SIZE + marge){
      s_mob.vit.x = 0;
      s_mob.vit.y = -creep_speed;

    }

    if (map->tab_props[droite].type == 0 && s_mob.vit.y > 0 && s_mob.coords.y >= (y*TILE_SIZE - marge)) {
      s_mob.vit.x = creep_speed;
      s_mob.vit.y = 0;

    }
    if (map->tab_props[droite].type == 0 && s_mob.vit.y < 0 && s_mob.coords.y <= (y*TILE_SIZE - marge)) {
      s_mob.vit.x = creep_speed;
      s_mob.vit.y = 0;

    }
 


  }
  return s_mob;
}

s_Mob mob_animation(s_Mob s_mob) {

  s_mob.animation += 1;
  if (s_mob.animation >= 45) 
    s_mob.animation = 0;

  s_mob.rcSrc.x = (s_mob.animation/15)* s_mob.rcSrc.w;

  return s_mob;
}


/******************************          Programme          *******************************/

/* varaible pour les phases de jeux */

int gameover;


/* SDL Function */
void update_events(char* keys)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      gameover = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
	
      case SDLK_q:
      case SDLK_ESCAPE:
	gameover = 1;
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;
    }
  }
}



/* ******************************************   MAIN   ********************************************** */




int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp;
  int colorkey;
  s_Mob creep;

  Map* map, *map_objet;
  /* set the title bar */
  SDL_WM_SetCaption("Tower Defense", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);
  
  int xmin, ymin;
  /* **********************   LOAD IMAGE ******************* */
  map = LoadMap("monde.txt");
  map_objet = LoadMap("objet.txt");
  
  creep.mob = Load_image("sprite_creeper.bmp");
  

  /* ********************   colorkey ******************* */



  /* Pour le ROSE */
  colorkey =  SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(map_objet->tileset, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  SDL_SetColorKey(creep.mob, SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey);
  char key[SDLK_LAST] = {0};
  gameover = 0;
  
  
  /* ******************** boucle principale ******************* */
  
  
  creep = mob_spawn(creep, CREEP_WIDTH, CREEP_HEIGHT);

  /* message pump */
  while (!gameover)
    {
      
      
      /* initialize SDL */
      SDL_Init(SDL_INIT_VIDEO);
      
      
      /* look for an event */
      update_events(key);
      
      
 
      
      
      PrintMap(map,screen);
      PrintMap(map_objet,screen);

     /* draw the creeper */
      creep = mob_deplacement(creep);
      creep = mob_animation(creep);

      creep.rcSprite.x = (int) creep.coords.x;
      creep.rcSprite.y = (int) creep.coords.y;
      SDL_BlitSurface(creep.mob, &creep.rcSrc, screen, &creep.rcSprite);

      SDL_Flip(screen);
      
      creep = mob_parcours(creep,map);
      /* test */
      xmin = (int) creep.coords.x / 32;
      ymin = (int) creep.coords.y / 32;

      //printf(" %d %d \n", xmin, ymin);


      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(5);
      
      
    }
  
  FreeMap(map);
  
  
  /* ****************************************************************************************************************************** */
  /* ***********************************     Clean Up    ************************************************************************** */
  /* ****************************************************************************************************************************** */
  
  SDL_FreeSurface(creep.mob);
  SDL_Quit();
  
  return 0;

}
