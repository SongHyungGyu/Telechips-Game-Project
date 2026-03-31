#if 1
#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "LIB_first_page.h"
#include "for_ddg.h"
#include "for_user.h"
int main()
{
    
    init_system();
    keyboard_init();

    SYSTEM* sys = init_game_system();
    User* user = init_User();
    DDG* ddg = init_ddg();

    Stage* stage1 = init_stage1();
    Stage* stage2 = init_stage2();
    Stage* stage3 = init_stage3();

    ALLEGRO_EVENT ev;

    bool running = true;

    mode = MODE_FIRST_PAGE;
    //mode = 6;
	play_time = 0;

    while (running) {
        al_wait_for_event(sys->queue, &ev);
        keyboard_update(&ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (mode == MODE_STAGE1) after_stage(stage1, MODE_FIRST_PAGE);
                if (mode == MODE_STAGE2) after_stage(stage2, MODE_FIRST_PAGE);
                if (mode == MODE_STAGE3) after_stage(stage3, MODE_FIRST_PAGE);
            }
        }

        if(mode == MODE_FIRST_PAGE) run_first_page(user, sys, ev);
        if (mode == MODE_STAGE1) run_stage1(user, ddg, stage1, sys, ev);
        if (mode == MODE_STAGE2) run_stage2(user, ddg, stage2, sys, ev);
        if (mode == MODE_STAGE3) run_stage3(user, ddg, stage3, sys, ev);
        if (mode == MODE_SET_STAGE1) set_stage1(ddg, stage1);
        if (mode == MODE_SET_STAGE2) set_stage2(ddg, stage2);
        if (mode == MODE_SET_STAGE3) set_stage3(ddg, stage3);
        if (mode == MODE_EXPLAIN) run_explanation_page(ev);
    }

    destroy_stage(stage1);
    destroy_stage(stage2);
    destroy_stage(stage3);

    destroy_ddg(ddg);

    destroy_User(user);

    if (sys->font) al_destroy_font(sys->font);
    if (sys->queue) al_destroy_event_queue(sys->queue);
    if (sys->timer) al_destroy_timer(sys->timer);
    if (sys->display) al_destroy_display(sys->display);
    
    free(sys);

    return 0;
}
#endif
