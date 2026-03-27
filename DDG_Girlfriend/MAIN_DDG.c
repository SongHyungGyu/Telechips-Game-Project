#if 1
#include "LIB_ddg.h"
#include "LIB_stage.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();

    ALLEGRO_EVENT ev;
    int mode = 1;
    init_stage1();

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        keyboard_update(&ev);
        if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev);
<<<<<<< HEAD
        /*run_login_page(sys.display, sys.queue, sys.timer);*/
        if(mode == 1) run_stage1(sys.display, sys.queue, sys.timer, ev);
=======
        if (mode == 1) run_stage1(sys.display, sys.queue, sys.timer, ev);
>>>>>>> origin/cys
    }

    return 0;
}
#endif