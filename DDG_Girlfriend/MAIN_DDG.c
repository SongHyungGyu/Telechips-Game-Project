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
   /* ALLEGRO_FONT* time_font = al_load_ttf_font("resource/font/Inkfree.ttf", 30, 0);*/

    ALLEGRO_EVENT ev;
    mode = 0;
	play_time = 0;

    while (1) {
        al_wait_for_event(sys->queue, &ev);
        keyboard_update(&ev);
        if(mode == 0) run_first_page(sys, ev);
        if (mode == 1) run_stage1(ddg, stage1, sys, ev);
        if (mode == 2) run_stage2(ddg, stage2, sys, ev);
        if (mode == 3) run_stage3(ddg, stage3, sys, ev);
        if (mode == 4) set_stage1(ddg);
        if (mode == 5) set_stage2(ddg, stage2);
        if (mode == 6) set_stage3(ddg, stage3);
    }
    return 0;
}
#endif
