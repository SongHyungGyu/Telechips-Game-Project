#if 1
#include "LIB_ddg.h"
#include "LIB_stage.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();
    /*ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/

    ALLEGRO_EVENT ev;
    int mode = 1;
    init_stage1();

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        keyboard_update(&ev);
        if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev);
        /*run_login_page(sys.display, sys.queue, sys.timer);*/
        if(mode == 1) run_stage1(sys.display, sys.queue, sys.timer, ev);
    }

    return 0;
}
#endif