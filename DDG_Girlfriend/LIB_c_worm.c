#include "LIB_c_worm.h"
#include "LIB_DDG.h"
#include "LIB_shot.h"

#define FIRE_DELAY 100


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

void destroy_c_worm(C_WORM* w)
{
    if (w == NULL) return;

    if (w->img)
    {
        al_destroy_bitmap(w->img);
    }

    if (w->shots)
    {
        destroy_shots(w->shots);
    }

    free(w);
}

void destroy_c_worms_array(C_WORM** worms, int count)
{
    if (worms == NULL) return;

    for (int i = 0; i < count; i++)
    {
        if (worms[i])
        {
            destroy_c_worm(worms[i]);
        }
    }

    free(worms);
}

static void fire_left(C_WORM* w)
{
    int sx = w->x;

    int sy = w->y + C_WORM_H / 2 - C_WORM_SHOT_H / 2;

    shots_add(w->shots, sx, sy, -3, 0);
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
    al_draw_scaled_bitmap(w->img, 0, 0, w->w, w->h,
        w->x, w->y, C_WORM_W, C_WORM_H, 0);
    shots_draw(w->shots);
}