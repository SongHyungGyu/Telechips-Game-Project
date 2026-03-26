#include "LIB_login.h"

run_login_page(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer) {
    ALLEGRO_BITMAP* first_page_image = load_image("resource/img/login_page.png");
    bool redraw = true;
    ALLEGRO_EVENT ev;

    char id[50] = "";
    int len = 0;

    while (1)
    {
        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
        if (ev.type == ALLEGRO_KEY_ENTER) return;
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN);
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