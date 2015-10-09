#include "SDL.h"
#include "SDL_ttf.h"

#include <math.h> 
#include <time.h>
#include <assert.h>

#define ERROR -1
#define CHEMIN 0
#define TERRAIN 1
#define OBSTACLE 2
#define TILE_SIZE 32

#define SCREEN_WIDTH 672
#define SCREEN_HEIGHT 512

#define CREEP_WIDTH 16
#define CREEP_HEIGHT 32
#define CREEP_SPEED 0.8

#define ZOMBIE_WIDTH 16
#define ZOMBIE_HEIGHT 32
#define ZOMBIE_SPEED 0.6

#define MAGIC_WIDTH 32
#define MAGIC_HEIGHT 48

#define TIR_WIDTH 16
#define TIR_HEIGHT 16

#define HB_WIDTH 20
#define HB_HEIGHT 5

#define DISTANCE_MAGIC_TOWER 70

#define TAB_MAX 1000

/************************** Structs**********************************/

typedef struct
{
  SDL_Rect R;
  int type;
} TileProp;


typedef struct 
{
  float x;
  float y;
  float w;
  float h;
} s_Hitbox;


typedef struct
{
  float x;
  float y;
} s_Floatpos;


typedef struct
{
  s_Floatpos coords;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *vie;
} s_Healthbar;


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
  s_Floatpos coords;
  s_Floatpos vit;
  s_Hitbox box;
  s_Healthbar healthbar;
  int animation;
  int numero;
  int pv_max;
  int pv;
  float priorite;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *mob;
} s_Mob;

typedef struct
{
  s_Floatpos coords;
  int temps;
  int type;
  int actif;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *tower;
} s_Tower;


typedef struct
{
  s_Floatpos coords;
  s_Floatpos vit;
  s_Hitbox box;
  int dommage;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *tir;
  s_Mob cible;
} s_Tir;




/* Définition de la structure liste pour mobs*/
struct Liste_mob
{
  s_Mob m;
  struct Liste_mob * next;
};

/* Définition du type liste_mob */ 
typedef struct Liste_mob Liste_mob;
typedef struct Liste_mob * liste_mob;

/* Définition de la structure liste pour towers*/
struct Liste_tower
{
  s_Tower t;
  struct Liste_tower * next;
};

/* Définition du type liste_tower */ 
typedef struct Liste_tower Liste_tower;
typedef struct Liste_tower * liste_tower;

/* Définition de la structure liste pour les tirs*/
struct Liste_tir
{
  s_Tir t;
  struct Liste_tir * next;
};

/* Définition du type liste_tir */ 
typedef struct Liste_tir Liste_tir;
typedef struct Liste_tir * liste_tir;


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


/****************************Liste tir********************************/
/* constructeurs */
liste_tir liste_new_empty_tir();
liste_tir liste_cons_tir(s_Tir t, liste_tir L);

/* accesseurs */
int liste_is_empty_tir(liste_tir L);
s_Tir liste_head_tir(liste_tir L);
liste_tir liste_tail_tir(liste_tir L);

/* Libérer */
void liste_free_tir(liste_tir * L);


/**************************Headers**********************************/

SDL_Surface* Load_image(const char* image);
Map* LoadMap(const char* Fichier);
int PrintMap(Map* map,SDL_Surface* screen);
int FreeMap(Map* map);
float SeekSpawn(Map *map);

s_Mob mob_spawn(s_Mob s_mob, Map *map, int taillew, int tailleh, float vit);
s_Mob mob_deplacement(s_Mob s_mob);
s_Mob mob_parcours(s_Mob s_mob, Map *map);
s_Mob mob_animation(s_Mob s_mob);
void mob_affichage(liste_mob L, Map* map, SDL_Surface* screen);


s_Tower tower_init(s_Tower t, int taillew, int tailleh);
void tower_affichage(liste_tower L, SDL_Surface *screen);
void tower_tir (liste_tower *L, liste_mob *M, liste_tir *T, s_Tir tir, SDL_Surface *screen, int temps_jeu, s_Tower s_tower);
void tower_menu(s_Tower tower, liste_tower *T,  int event_button_x, int event_button_y, int case1, Map *map, Map *map_o);

s_Tir tir_init(s_Tir t, int taillew, int tailleh);
void tir_affichage(liste_tir L, s_Tir t, SDL_Surface *screen, liste_mob M);
s_Tir tir_spawn(s_Tir t, s_Tower to);
s_Tir direction_tir(s_Tir t, s_Mob mob);
s_Tir deplacement_tir(s_Tir t);
void disparition_tir(liste_tir *T,liste_mob L );
void cible(liste_tir *L, liste_mob M);

s_Healthbar healthbar_init(s_Healthbar h, int taillew, int tailleh);
s_Healthbar healthbar_animation(s_Healthbar h, s_Mob mob);
void healthbar_affichage(liste_mob L, SDL_Surface *screen);

void collision_tir_mob(liste_tir *T, liste_mob *M);
int collision_box_box(s_Hitbox box1, s_Hitbox box2);

/******************************* SDL *********************************/

void update_events(char* keys, liste_mob *L,liste_tower *T, s_Mob mob, s_Mob mob2, s_Tower tower, Map *map, Map *map_o, int *i);





