#if 1
#include "LIB_ddg.h"

int main()
{
    init_system();

    SYSTEM sys = init_game_system();
    /*ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/

    // ALLEGRO_EVENT ev;

    run_first_page(sys.display, sys.queue, sys.timer);


    return 0;
}
#endif