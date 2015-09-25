#include "SDL.h"
#include <math.h> 
#include <time.h>
#include <assert.h>

#define TILE_SIZE 32

#define SCREEN_WIDTH 672
#define SCREEN_HEIGHT 480

#define CREEP_WIDTH 16
#define CREEP_HEIGHT 32

#define MAGIC_WIDTH 32
#define MAGIC_HEIGHT 48

#define TAB_MAX 1000

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
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *mob;
} s_Mob;

typedef struct
{
  s_Floatpos coords;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *tower;
} s_Tower;


/* Définition de la structure liste pour mobs*/
struct Liste_mob
{
  s_Mob m;
  struct Liste_mob * next;
};

/* Définition du type liste */ 
typedef struct Liste_mob Liste_mob;
typedef struct Liste_mob * liste_mob;

/* Définition de la structure liste pour towerss*/
struct Liste_tower
{
  s_Tower t;
  struct Liste_tower * next;
};

/* Définition du type liste */ 
typedef struct Liste_tower Liste_tower;
typedef struct Liste_tower * liste_tower;


/****************************Liste mob********************************/
/* constructeurs */
liste_mob liste_new_empty_mob();
liste_mob liste_cons_mob(s_Mob m, liste_mob L);

/* accesseurs */
int liste_is_empty_mob(liste_mob L);
s_Mob liste_head_mob(liste_mob L);
liste_mob liste_tail_mob(liste_mob L);

/* Libérer */
void liste_free_mob(liste_mob * L);


/****************************Liste tower********************************/
/* constructeurs */
liste_tower liste_new_empty_tower();
liste_tower liste_cons_tower(s_Tower t, liste_tower L);

/* accesseurs */
int liste_is_empty_tower(liste_tower L);
s_Tower liste_head_tower(liste_tower L);
liste_tower liste_tail_tower(liste_tower L);

/* Libérer */
void liste_free_tower(liste_tower * L);



/**************************Headers**********************************/

SDL_Surface* Load_image(const char* image);
Map* LoadMap(const char* Fichier);
int PrintMap(Map* map,SDL_Surface* screen);
int FreeMap(Map* map);
s_Mob mob_spawn(s_Mob s_mob, int taillew, int tailleh);
s_Mob mob_deplacement(s_Mob s_mob);
s_Mob mob_parcours(s_Mob s_mob, Map *map);
s_Mob mob_animation(s_Mob s_mob);
void mob_affichage(liste_mob L, s_Mob m, Map* map, SDL_Surface* screen);

s_Tower tower_init(s_Tower t, int taillew, int tailleh);
void tower_affichage(liste_tower L, s_Tower t, SDL_Surface *screen);


/******************************* SDL *********************************/

liste_mob update_events(char* keys, liste_mob L, s_Mob m);
liste_tower update_events_mouse(char* keys, liste_tower L, s_Tower t, Map *map);
void alternative_HandleEvent(char* key);



