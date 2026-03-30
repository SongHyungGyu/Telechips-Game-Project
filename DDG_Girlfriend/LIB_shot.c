#include "LIB_shot.h"
#include "LIB_DDG.h" 


static bool collide(
    int ax1, int ay1,
    int ax2, int ay2,
    int bx1, int by1,
    int bx2, int by2)
{
    if (ax1 > bx2) return false;
    if (ax2 < bx1) return false;
    if (ay1 > by2) return false;
    if (ay2 < by1) return false;

    return true;
}


SHOT_SYSTEM* init_shots(const char* img_path)
{
    SHOT_SYSTEM* s =
        (SHOT_SYSTEM*)malloc(sizeof(SHOT_SYSTEM));

    s->img = load_image(img_path);

    for (int i = 0; i < SHOTS_N; i++)
        s->shots[i].used = false;

    return s;
}


bool shots_add(SHOT_SYSTEM* s,int x,int y,int dx,int dy)
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (s->shots[i].used)
            continue;

        s->shots[i].x = x - (C_WORM_SHOT_W / 2);

        s->shots[i].y = y - (C_WORM_SHOT_H / 2);

        s->shots[i].dx = dx;
        s->shots[i].dy = dy;

        s->shots[i].frame = 0;
        s->shots[i].used = true;

        return true;
    }

    return false;
}


void shots_update(SHOT_SYSTEM* s)
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!s->shots[i].used)
            continue;

        s->shots[i].x += s->shots[i].dx;
        s->shots[i].y += s->shots[i].dy;

        if ( // �Ѿ� �������
            s->shots[i].x < -C_WORM_SHOT_W ||
            s->shots[i].x > DISP_W ||
            s->shots[i].y < -C_WORM_SHOT_H ||
            s->shots[i].y > DISP_H
            )
        {
            s->shots[i].used = false;
            continue;
        }

        s->shots[i].frame++;
    }
}


bool shots_collide_player(
    SHOT_SYSTEM* s,
    int x,
    int y,
    int w,
    int h
)
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!s->shots[i].used)
            continue;

        if (collide(
            x,
            y,
            x + w,
            y + h,

            s->shots[i].x,
            s->shots[i].y,

            s->shots[i].x + C_WORM_SHOT_W,
            s->shots[i].y + C_WORM_SHOT_H
        ))
        {
            s->shots[i].used = false;
            return true;
        }
    }

    return false;
}


void shots_draw(SHOT_SYSTEM* s)
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!s->shots[i].used)
            continue;

        al_draw_scaled_bitmap(

            s->img,

            0,
            0,

            al_get_bitmap_width(s->img),
            al_get_bitmap_height(s->img),

            s->shots[i].x,
            s->shots[i].y,

            C_WORM_SHOT_W,
            C_WORM_SHOT_H,

            0
        );
    }
}