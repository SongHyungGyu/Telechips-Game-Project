#ifndef LIB_STAGE_H
#define LIB_STAGE_H
#include "LIB_c_worm.h" 
#include "LIB_DDG.h"
#include "for_user.h"
#define ddg_size 60
#define c_worm_size
#define shot_size
#define flower_size
#define shot_speed

#define tile_w_num 20
#define tile_h_num 15

// 타일 크기
#define TILE_SIZE 60  

#define C_WORM_N 10

// 시작 위치
#define sx1 60
#define sy1 60
#define sx2 60
#define sy2 780
#define sx3 60
#define sy3 60
// 도착 위치
#define ax1 300
#define ay1 300
#define ax2 400
#define ay2 400
#define ax3 500
#define ay3 500

#define FLOWER_TOT2 3

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
	ALLEGRO_BITMAP* heart_img;
}DDG;


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
	ALLEGRO_BITMAP* img;
	int x;
	int y;
	int w;
	int h;
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
	ALLEGRO_BITMAP* img;
	int w;
	int h;
	int x;
	int y;
	int lx;
	int rx;
	int ty; 
	int by; 
	int type; //수직 지렁이, 수평 지렁이, 네모 지렁이 구분
	int dir;// +1: 오른쪽, 아래쪽, -1: 왼쪽, 위쪽
	int speed;
}worm;

typedef struct {
	int stage;
    Map map;
    ALLEGRO_BITMAP* mapCache;
    ALLEGRO_BITMAP* roadTile;
    ALLEGRO_BITMAP* wallTile;
    ALLEGRO_BITMAP* marshTile;
    void (*initMap)(Map* m);
    int sx, sy;

    C_WORM** c_worms;
    int c_worm_count;

	int wormNum;
	worm** worms; 
	flower** flowers;
	int flower_cnt;
	ALLEGRO_BITMAP* ddg_girl;
} Stage;

void renderMap(Stage* s);
void init_stage(Stage* s);

Stage* init_stage1();
Stage* init_stage2();
Stage* init_stage3();

void run_stage1(User * user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);
void run_stage2(User* user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);
void run_stage3(User* user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);

void set_stage1(DDG* ddg);
void set_stage2(DDG* ddg, Stage* s);
void set_stage3(DDG* ddg);

void render_play_time(SYSTEM* sys);
#endif