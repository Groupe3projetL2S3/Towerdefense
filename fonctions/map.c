#include "../jeu.h"

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
	  map->tab_props[nbtile].type = CHEMIN;
	  if (strcmp(tab1,"terrain")==0)
	    map->tab_props[nbtile].type = TERRAIN;
	  if (strcmp(tab1,"obstacle")==0)
	    map->tab_props[nbtile].type = OBSTACLE;
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

float SeekSpawn(Map *map) {
  int i;
  float res = 0.0;
  float marge = 40.0;
  for (i = 0; i < map->nbtiles_hauteur_monde; i++) {
    if (map->tab_props[map->monde[0][i]].type == CHEMIN) {
      res = ((i+1)*TILE_SIZE - marge);
    }
  }
return res;
}
