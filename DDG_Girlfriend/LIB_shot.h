#ifndef LIB_SHOT_H
#define LIB_SHOT_H
// #include "LIB_stage.h"
#include <stdbool.h>
#include <allegro5/allegro.h>

#define SHOTS_N 128

#define C_WORM_SHOT_W 8
#define C_WORM_SHOT_H 8

typedef struct SHOT
{
    int x, y;
    int dx, dy;
    int frame;
    bool used;
} SHOT;

typedef struct SHOT_SYSTEM
{
    ALLEGRO_BITMAP* img;
    SHOT shots[SHOTS_N];

} SHOT_SYSTEM;

bool shots_collide_player(
    SHOT_SYSTEM* s,
    int x,
    int y,
    int w,
    int h
);

SHOT_SYSTEM* init_shots(const char* img_path);

void shots_update(SHOT_SYSTEM* s);

void shots_draw(SHOT_SYSTEM* s);

bool shots_add(
    SHOT_SYSTEM* s,
    int x,
    int y,
    int dx,
    int dy
);

bool shots_collide_player(
    SHOT_SYSTEM* s,
    int x,
    int y,
    int w,
    int h
);
// bool col_c_worm_shots(DDG* ddg, Stage* s);
#endif