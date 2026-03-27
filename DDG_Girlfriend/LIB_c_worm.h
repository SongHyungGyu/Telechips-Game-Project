#ifndef LIB_C_WORM_H
#define LIB_C_WORM_H

#include "LIB_shot.h"

#define C_WORM_W 32
#define C_WORM_H 32

typedef struct C_WORM
{
    ALLEGRO_BITMAP* img;

    int x;
    int y;

    int w;
    int h;

    int shot_timer;

    SHOT_SYSTEM* shots;

} C_WORM;


C_WORM* init_c_worm(int x, int y);

void update_c_worm(C_WORM* worm);

void render_c_worm(C_WORM* worm);

#endif