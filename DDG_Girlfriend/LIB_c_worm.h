#ifndef LIB_C_WORM_H
#define LIB_C_WORM_H

#include "LIB_shot.h"

#define C_WORM_W 60
#define C_WORM_H 60

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

void destroy_c_worm(C_WORM* w);
void destroy_c_worms_array(C_WORM** worms, int count);

void update_c_worm(C_WORM* worm);

void render_c_worm(C_WORM* worm);

#endif