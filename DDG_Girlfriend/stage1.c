#include "LIB_stage.h"

void run_stage1(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev, bool* pstage1_init) {
    int ddg_w;
    int ddg_h;
    bool redraw;
    static int sx;
    static int sy;
    DDG ddg;
    ALLEGRO_BITMAP* ddg_image;
    if (*pstage1_init == false) {
        sx = 0;
        sy = 0;

        ddg_image = load_image("resource/img/ddg.png");

        ddg_w = al_get_bitmap_width(ddg_image);
        ddg_h = al_get_bitmap_height(ddg_image);

        ddg = (DDG){ ddg_image, sx, sy, 3, 5 };

        *pstage1_init = true;
        redraw = true;
        printf("초기화 완료\n");
    }
    /*al_wait_for_event(queue, &ev);*/
    // if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    /*if (ev.type == ALLEGRO_EVENT_KEY_DOWN) return;*/
    if (ev.type = ALLEGRO_KEY_DOWN) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            ddg.x += ddg.speed;
            redraw = true;
        }
    }

    if (redraw)
    {
        // printf("stage1\n");
        al_clear_to_color(al_map_rgb(255, 255, 255));
        
        al_set_target_backbuffer(display);
        al_draw_scaled_bitmap(ddg.img, 0, 0, ddg_w, ddg_h,
            ddg.x, ddg.y, ddg_size, ddg_size, 0);
        al_flip_display();

        redraw = false;
    }
}