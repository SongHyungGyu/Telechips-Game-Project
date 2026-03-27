#if 1
#include "LIB_ddg.h"
#include "LIB_stage.h"
#include "LIB_first_page.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();

    Stage* stage1 = Stage1();
    Stage* stage2 = Stage2();
    Stage* stage3 = Stage3();

    init_stage(stage1);
    init_stage(stage2);
    init_stage(stage3);
 
    ALLEGRO_EVENT ev;
    int mode = 0;

    while (1) {
        al_wait_for_event(sys.queue, &ev);
        keyboard_update(&ev);
        if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev, &mode);
        if(mode == 1) run_stage1(stage1, sys.display, sys.queue, sys.timer, ev);
        if (mode == 2) run_stage2(stage2,sys.display, sys.queue, sys.timer, ev);
        if (mode == 3) run_stage3(stage3, sys.display, sys.queue, sys.timer, ev);
    }
    return 0;
}
#endif
