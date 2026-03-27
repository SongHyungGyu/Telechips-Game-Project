#ifndef LIB_STAGE_H
#define LIB_STAGE_H

#include "LIB_ddg.h"
#define ddg_size 60
#define worm_size
#define c_worm_size
#define shot_size
#define flower_size
#define shot_speed

#define tile_w_num 20
#define tile_h_num 15

#define TILE_SIZE 60  

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//두더지
typedef struct {
	ALLEGRO_BITMAP* img;
	int x;
	int y;
	int life;
	int speed;
	int w;
	int h;
}DDG;

typedef struct {
	int x;
	int y;
	int speed;
}worm;
//shot의 출발 지점
typedef struct {
	int x;
	int y;
	int shot_timer;
}c_worm;
typedef struct {
	int x;
	int y;
	int speed;
	bool used;
}shot;
typedef struct flower {
	int x;
	int y;
	bool used;
}flower;
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
	int type; //0: 벽, 1: 길, 2: 늪
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
} Stage;

void renderMap(Stage* s);
void init_stage(Stage* s);

Stage* init_stage1();
//Stage* init_stage2();
//Stage* init_stage3();

void run_stage1(DDG* ddg, Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
//void run_stage2(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
//    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
//void run_stage3(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
//    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);

static bool col_wall(int nx, int ny);
#endif