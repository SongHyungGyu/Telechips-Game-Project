#ifndef __FOR_FLOWER_H__
#define __FOR_FLOWER_H__

#include "LIB_stage.h"
#define FLOWER_SIZE 60

flower* init_flower(int x, int y);
void render_flower(flower* f);
void update_flower(flower* f, DDG* ddg, Stage* s);

#endif
