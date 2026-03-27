#if 1
#include "LIB_ddg.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();

    ALLEGRO_EVENT ev;
    int mode = 0;

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev);
        if (mode == 1) run_stage1(sys.display, sys.queue, sys.timer, ev);
    }

    return 0;
}
#endif