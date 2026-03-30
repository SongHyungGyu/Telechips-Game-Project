#ifndef __FOR_WORM_H__
#define __FOR_WORM_H__

#include "LIB_stage.h"
#define WORM_SIZE 50

#define WORM_SPEED_STAGE1 5
#define WORM_LX_STAGE1 100
#define WORM_RX_STAGE1 1000

#define WORM_SPEED_STAGE2 10
#define WORM_LX_STAGE2 100
#define WORM_RX_STAGE2 1000

#define WORM_SPEED_STAGE3 3

enum WormType {
	HORIZONTAL = 0,
	VERTICAL = 1,
	SQUARE = 2
};

worm* init_worm(int x, int y, int lx, int rx, int ty, int by, int type, int speed, int dir);
void render_worm(worm* w);
void update_worm(worm* w);
bool col_worms(DDG * ddg, int wormNum, worm ** worms);
#endif