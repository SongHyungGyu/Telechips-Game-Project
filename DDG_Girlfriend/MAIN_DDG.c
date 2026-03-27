#if 1
#include "LIB_ddg.h"
#include "LIB_stage.h"
#include "LIB_first_page.h"
#include "LIB_stage1.h"
#include "LIB_stage2.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();

    Stage stage1;
    //Stage stage2;

    init_stage1(&stage1);
   /* init_stage2(&stage2);*/
    ALLEGRO_EVENT ev;
    int mode = 1;

    while (1) {
        al_wait_for_event(sys.queue, &ev);
       // if(mode == 0) run_first_page(sys.display, sys.queue, sys.timer, ev);
		if (mode == 1) run_stage1(&stage1, sys.display, sys.queue, sys.timer, ev);
        //else if (mode == 2) run_stage2(&stage2, sys.display, sys.queue, sys.timer, ev);
    }
    shutdown(road, sys.display);
    al_destroy_bitmap(wall);

    return 0;
}
#endif