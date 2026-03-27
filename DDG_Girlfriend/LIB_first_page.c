// 첫번째 페이지 함수 실행부
#include "LIB_first_page.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


void draw_scaled_crop(ALLEGRO_BITMAP* image)
{
    float img_w = al_get_bitmap_width(image);
    float img_h = al_get_bitmap_height(image);

    float scale_x = (float)DISP_W / img_w;
    float scale_y = (float)DISP_H / img_h;

    float scale = (scale_x > scale_y) ? scale_x : scale_y;

    al_draw_scaled_bitmap(
        image,
        0, 0, img_w, img_h,
        0, 0, DISP_W, DISP_H,
        0
    );
}


void run_first_page(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev, int* mode) {
    static char user_name[20] = "";
    static int name_len = 0;
    static ALLEGRO_BITMAP* first_page_image = NULL;
    static ALLEGRO_FONT* font = NULL;
    static bool resources_loaded = false;

    if (!resources_loaded) {
        first_page_image = al_load_bitmap("resource/img/page.png");
        font = al_load_ttf_font("resource/font/Inkfree.ttf", 30, 0);

        resources_loaded = true;
    }

    bool redraw = false;

    if (ev.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && name_len > 0) {
            user_name[--name_len] = '\0';
        }
        else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            *mode = 1;
        }
        else if (ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126 && name_len < 19) {
            user_name[name_len++] = (char)ev.keyboard.unichar;
            user_name[name_len] = '\0';
        }
        redraw = true;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (first_page_image) {
            draw_scaled_crop(first_page_image);
        }

        if (font) {
            al_draw_text(font, al_map_rgb(0, 0, 0), 160, 203, 0 , user_name);
        }

        al_flip_display();
    }
}