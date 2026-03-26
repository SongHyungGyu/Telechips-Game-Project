#ifndef __LIB_STAGE__
#define __LIB_STAGE__

#include "LIB_ddg.h"
#define tile_width 60
#define ddg_size 60
#define worm_size
#define c_worm_size
#define shot_size
#define flower_size
#define shot_speed

//두더지
typedef struct ddg {
	ALLEGRO_BITMAP* img;
	int x;
	int y;
	int life;
	int speed;
}DDG;
typedef struct worm {
	int x;
	int y;
	int speed;
}worm;
//shot의 출발 지점
typedef struct c_worm {
	int x;
	int y;
	int shot_timer;
}c_worm;
typedef struct shot {
	int x;
	int y;
	int speed;
	bool used;
};
typedef struct flower {
	int x;
	int y;
	bool used;
};
void run_stage1(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev, bool stage1_init);

#endif