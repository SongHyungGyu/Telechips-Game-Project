#include "LIB_first_page.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

bool has_seen_explanation = false;


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


void run_first_page(User * user, SYSTEM* sys, ALLEGRO_EVENT ev) {
    static char user_name[20] = "";
    static int name_len = 0;
    static ALLEGRO_BITMAP* first_page_image = NULL;
    static ALLEGRO_FONT* rankingFont = NULL;
    static bool resources_loaded = false;

    if (!resources_loaded) {
        first_page_image = al_load_bitmap(PATH "page.png");
		rankingFont = al_load_ttf_font("resource/font/Inkfree.ttf", 20, 0);
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
            if (name_len > 0 && name_len <= 20) {
                set_User(user, user_name, 0, 0);
                user_name[0] = '\0';
                name_len = 0;


                if (!has_seen_explanation) {
                    mode = 7;                   
                    has_seen_explanation = true; // 2. 이제 봤다고 표시 (true로 변경)
                }
                else {
                    mode = 4;                   // 3. 이미 본 적이 있다면 바로 스테이지 1 세팅(mode 4)으로 이동
                }
            }

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

        if (sys->font) {
            al_draw_text(sys->font, al_map_rgb(0, 0, 0), 160, 203, 0 , user_name);
            draw_top_Users(rankingFont);
        }

        al_flip_display();
    }
}

void run_explanation_page(ALLEGRO_EVENT ev) {
    
    static ALLEGRO_BITMAP* expl_image = NULL;
    static bool resources_loaded = false;

    if (!resources_loaded) {
        expl_image = al_load_bitmap(PATH "explanation_bg.png"); // 설명 배경 이미지
        resources_loaded = true;
    }

    bool redraw = false;

    if (ev.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            mode = 4;
        }
    }

    if (redraw ) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (expl_image) {
            draw_scaled_crop(expl_image);
            
        }

        al_flip_display();
    }
}