#ifndef __FOR_WORM_H__
#define __FOR_WORM_H__

#include "LIB_stage.h"
#define WORM_SIZE 60

enum WormType {
	HORIZONTAL = 0,
	VERTICAL = 1,
	SQUARE = 2
};

worm* init_worm(int x, int y, int lx, int ly, int rx, int ry, int tx, int ty,
	int bx, int by, int type, int speed, int dir);
void render_worm(worm* w);
void update_worm(worm* w);

#endif