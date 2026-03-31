#if 1
#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "LIB_first_page.h"
#include "for_ddg.h"
#include "for_user.h"
int main()
{
    
    init_system();

    SYSTEM* sys = init_game_system();
    User* user = init_User();
    DDG* ddg = init_ddg();
    Stage* stage1 = init_stage1();
    Stage* stage2 = init_stage2();
    Stage* stage3 = init_stage3();

    ALLEGRO_EVENT ev;
    mode = MODE_FIRST_PAGE;
	play_time = 0;

    while (1) {
        al_wait_for_event(sys->queue, &ev);
        keyboard_update(&ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                mode = MODE_FIRST_PAGE;
            }
        }

        if(mode == MODE_FIRST_PAGE) run_first_page(user, sys, ev);
        if (mode == MODE_STAGE1) run_stage1(user, ddg, stage1, sys, ev);
        if (mode == MODE_STAGE2) run_stage2(user, ddg, stage2, sys, ev);
        if (mode == MODE_STAGE3) run_stage3(user, ddg, stage3, sys, ev);
        if (mode == MODE_SET_STAGE1) set_stage1(ddg);
        if (mode == MODE_SET_STAGE2) set_stage2(ddg, stage2);
        if (mode == MODE_SET_STAGE3) set_stage3(ddg, stage3);
    }
    return 0;
}
#endif
