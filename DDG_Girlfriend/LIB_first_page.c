// 첫번째 페이지 함수 실행부
#include "LIB_first_page.h"

void draw_scaled_crop(ALLEGRO_BITMAP* image)
{
    float img_w = al_get_bitmap_width(image);
    float img_h = al_get_bitmap_height(image);

    float scale_x = (float)DISP_W / img_w;
    float scale_y = (float)DISP_H / img_h;

    // x축 y축 중에 큰 값 넣기
    float scale = (scale_x > scale_y) ? scale_x : scale_y;

    float crop_w = DISP_W / scale;
    float crop_h = DISP_H / scale;

    float crop_x = (img_w - crop_w) / 2;
    float crop_y = (img_h - crop_h) / 2;

    al_draw_scaled_bitmap(
        image,
        crop_x, crop_y, crop_w, crop_h,
        0, 0, DISP_W, DISP_H,
        0
    );
}

void run_first_page(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer) {
    ALLEGRO_BITMAP* first_page_image = load_image("resource/img/first_page.png");
    bool redraw = true;
    ALLEGRO_EVENT ev;

    char id[50] = "";
    int len = 0;

    while (1)
    {
        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) return;
        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // 디스플레이 출력전 크기 맞추고 출력
            al_set_target_backbuffer(display);
            draw_scaled_crop(first_page_image);
            // 백버퍼에서 프론트버퍼로 복사
            al_flip_display();
            redraw = false;
        }
    }
}