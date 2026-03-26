#if 1
#include "LIB_ddg.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();
    /*ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/

    ALLEGRO_EVENT ev;
    int mode = 0;

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev);
        /*run_login_page(sys.display, sys.queue, sys.timer);*/
    }

    return 0;
}
#endif