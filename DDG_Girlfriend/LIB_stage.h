#ifndef LIB_STAGE_H
#define LIB_STAGE_H
#define tile_w_num 20
#define tile_h_num 15

#define TILE_SIZE 60  

#define C_WORM_N 10

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "LIB_c_worm.h"

typedef enum {
    WALL = 1,
    ROAD = 0,
    MARSH = 2
} TileType;

typedef struct {
    int x;
    int y;
    int w;
    int h;
	int type; //0: º®, 1: ±æ, 2: ´Ë
} tile;

typedef struct {
    tile tiles[tile_h_num][tile_w_num];
} Map;

typedef struct {
    Map map;
    ALLEGRO_BITMAP* mapCache;
    ALLEGRO_BITMAP* roadTile;
    ALLEGRO_BITMAP* wallTile;
    ALLEGRO_BITMAP* marshTile;
    void (*initMap)(Map* m);
    int sx, sy;

    C_WORM** c_worms;
    int c_worm_count;

} Stage;

Stage* Stage1();
Stage* Stage3();
void renderMap(Stage* s);
void init_stage(Stage* s);
void run_stage1(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
//void init_stage2(Stage* s);
//void run_stage2(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
//    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
void run_stage3(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
#endif