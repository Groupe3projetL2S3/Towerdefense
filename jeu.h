#include "SDL.h"
#include <math.h> 
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/************************** Structs**********************************/

typedef struct
{
  SDL_Rect R;
  int type;
} TileProp;

typedef struct
{
  int tile_width, tile_height;
  int nbtilesX,nbtilesY;
  SDL_Surface* tileset;
  TileProp* tab_props;
  Uint16** monde;
  int nbtiles_largeur_monde,nbtiles_hauteur_monde;
} Map;

/**************************Headers**********************************/

Map* LoadMap(const char* Fichier);
int PrintMap(Map* map,SDL_Surface* screen);
int FreeMap(Map* map);

/******************************* SDL *********************************/

void update_events(char* keys);
void alternative_HandleEvent(char* key);



