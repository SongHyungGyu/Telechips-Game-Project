#include "LIB_c_worm.h"
#include "LIB_ddg.h"

#define FIRE_DELAY 40


C_WORM* init_c_worm(int x, int y)
{
    C_WORM* worm = (C_WORM*)malloc(sizeof(C_WORM));

    worm->img = load_image(PATH "c_worm.png");
    worm->shots = init_shots(PATH "worm_shot.png");

    worm->w = al_get_bitmap_width(worm->img);
    worm->h = al_get_bitmap_height(worm->img);

    worm->x = x;
    worm->y = y;
  
    worm->shot_timer = 0;

    return worm;
}

static void fire_left(C_WORM* w)
{
    int sx = w->x;

    int sy =  w->y + w->h / 2;

    shots_add(w->shots, sx, sy,-3,0);
}

void update_c_worm(C_WORM* w)
{
    if (w->shot_timer > 0)
    {
        w->shot_timer--;
    }
    else
    {
        fire_left(w);
        w->shot_timer = FIRE_DELAY;
    }
    shots_update(w->shots);
}

void render_c_worm(C_WORM* w)
{
    al_draw_bitmap(w->img, w->x, w->y, 0 );

    shots_draw(w->shots);
}