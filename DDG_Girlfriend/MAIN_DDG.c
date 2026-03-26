#if 1
#include "LIB_ddg.h"
#include "LIB_stage.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();
    /*ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/

    ALLEGRO_BITMAP* road = al_load_bitmap("road.png");
    ALLEGRO_BITMAP* wall = al_load_bitmap("wall.png");


    init_stage3();

    ALLEGRO_EVENT ev;
    bool redraw = true;

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;

        // 그리기 (Redraw)
        if (redraw && al_is_event_queue_empty(sys.queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Stage 3 출력
            renderMap(road, wall);

            al_flip_display();
            redraw = false;
        }

       
    }
    shutdown(road, sys.display);
    al_destroy_bitmap(wall);

    return 0;
}
#endif