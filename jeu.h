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
#define CREEP_SPEED 0.7
#define CREEP_PV 60
#define CREEP_TYPE 1

#define ZOMBIE_WIDTH 16
#define ZOMBIE_HEIGHT 32
#define ZOMBIE_SPEED 0.3
#define ZOMBIE_PV 200
#define ZOMBIE_TYPE 2

#define ENDER_WIDTH 16
#define ENDER_HEIGHT 40
#define ENDER_SPEED 0.5
#define ENDER_PV 100
#define ENDER_TYPE 3

#define MAGIC_WIDTH 32
#define MAGIC_HEIGHT 48
#define SNIPER_WIDTH 32
#define SNIPER_HEIGHT 48
#define FIRE_WIDTH 32
#define FIRE_HEIGHT 48
#define SLOW_WIDTH 32
#define SLOW_HEIGHT 48

#define TIR_WIDTH 16
#define TIR_HEIGHT 16

#define HB_WIDTH 20
#define HB_HEIGHT 5

#define UP_WIDTH 32
#define UP_HEIGHT 32

#define SELL_WIDTH 32
#define SELL_HEIGHT 32

#define DISTANCE_SNIPER_TOWER 70
#define TYPE_SNIPER 1

#define DISTANCE_MAGIC_TOWER 70
#define TYPE_MAGIC 2

#define DISTANCE_FIRE_TOWER 70
#define TYPE_FIRE 3

#define DISTANCE_SLOW_TOWER 70
#define TYPE_SLOW 4

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
  s_Floatpos coords;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *range;
  int range_max;
} s_Range;

typedef struct
{
  s_Floatpos coords;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *sell;
} s_Sell;

typedef struct
{
  s_Floatpos coords;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *up;
} s_Upgrade;

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
  int type;
  int pv_max;
  int pv;
  int slow;
  int lvl_slow;
  float priorite;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  SDL_Surface *mob;
} s_Mob;

typedef struct
{
  s_Floatpos coords;
  s_Range range;
  s_Sell sell;
  s_Upgrade up;
  int temps;
  int type;
  int actif;
  int select;
  int niveau;
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
  int animation;
  int type;
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
void liste_inverser_mob(liste_mob * L);

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
void liste_inverser_tower(liste_tower * L);

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
void liste_inverser_tir(liste_tir * L);

/* Libérer */
void liste_free_tir(liste_tir * L);


/**************************Headers**********************************/

SDL_Surface* Load_image(const char* image);
Map* LoadMap(const char* Fichier);
int PrintMap(Map* map,SDL_Surface* screen);
int FreeMap(Map* map);
float SeekSpawn(Map *map);

s_Mob mob_spawn(s_Mob s_mob, Map *map, int taillew, int tailleh, float vit, int map_pv, int type);
s_Mob mob_deplacement(s_Mob s_mob);
s_Mob mob_parcours(s_Mob s_mob, Map *map);
s_Mob mob_animation(s_Mob s_mob);
void mob_affichage(liste_mob L, Map* map, SDL_Surface* screen);
void mob_add(int *i, s_Mob mob, liste_mob *L);
void mob_slow(liste_mob *M, liste_tower *T, int colorkey);

s_Tower tower_init(s_Tower t, int taillew, int tailleh, int type, int distance);
void tower_affichage(liste_tower L, SDL_Surface *screen);
void tower_tir (liste_tower *L, liste_mob *M, liste_tir *T, s_Tir tir_magic, s_Tir tir_sniper, s_Tir tir_fire, SDL_Surface *screen, int temps_jeu, s_Tower s_tower);
void tower_menu(s_Tower sniper, s_Tower magic, s_Tower fire, s_Tower slow, liste_tower *T,  int event_button_x, int event_button_y, Map *map, Map *map_o, int *case1, int *case2, int *case3, int *case4);
void tower_motion(liste_tower *T, int event_motion_x, int event_motion_y);
void tower_select(liste_tower *T,  int event_button_x, int event_button_y);
int tower_posay(liste_tower *T, int event_button_x, int event_button_y);
void tower_add(liste_tower *T, s_Tower tower, int *case1, int *case2, int *case3, int *case4, int event_button_x, int event_button_y);
s_Tower towerup_init(s_Tower t, s_Tower t_up);
void tower_gestion(liste_tower *T, s_Tower sniper2, s_Tower sniper3, s_Tower magic2, s_Tower magic3, s_Tower fire2, s_Tower fire3, s_Tower slow2, s_Tower slow3, int event_button_x, int event_button_y);

s_Tir tir_init(s_Tir t, int taillew, int tailleh);
void tir_affichage(liste_tir L, SDL_Surface *screen, liste_mob M);
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

s_Range Range_init(s_Range r, int taillew, int tailleh);
void Range_affichage(liste_tower L, SDL_Surface *screen);

s_Upgrade upgrade_init(s_Upgrade up, int taillew, int tailleh);
void upgrade_affichage(liste_tower L, SDL_Surface *screen);

s_Sell sell_init(s_Sell s, int taillew, int tailleh);
void sell_affichage(liste_tower L, SDL_Surface *screen);
/******************************* SDL *********************************/

void update_events(char* keys, liste_mob *L,liste_tower *T, s_Mob mob, s_Mob mob2, s_Mob mob3, s_Tower sniper1, s_Tower sniper2, s_Tower sniper3, s_Tower magic1, s_Tower magic2, s_Tower magic3, s_Tower fire1, s_Tower fire2, s_Tower fire3, s_Tower slow1, s_Tower slow2, s_Tower slow3, Map *map, Map *map_o, int *i, int *case1, int *case2, int *case3, int *case4, int *gameover);





