#include "SDL.h"
#include <math.h> 
#include <time.h>

#define TILE_SIZE 32

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CREEP_WIDTH 16
#define CREEP_HEIGHT 32

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


typedef struct
{
  float x;
  float y;
} s_Floatpos;

typedef struct
{
  s_Floatpos coords;
  s_Floatpos vit;
  int animation;
  int direction;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *mob;
} s_Mob;


/**************************Headers**********************************/

Map* LoadMap(const char* Fichier);
int PrintMap(Map* map,SDL_Surface* screen);
int FreeMap(Map* map);
s_Mob mob_spawn(s_Mob s_mob, int taillew, int tailleh);

/******************************* SDL *********************************/

void update_events(char* keys);
void alternative_HandleEvent(char* key);



