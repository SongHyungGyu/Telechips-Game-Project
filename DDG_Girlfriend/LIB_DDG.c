#include "LIB_DDG.h"
// °ø¿ë

void must_init(bool test, const char* description)
{
    if (test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

void init_system()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_font_addon(), "font addon");
}

SYSTEM init_game_system() {
    SYSTEM sys;

    sys.display = create_display();
    must_init(sys.display, "display");
    sys.queue = al_create_event_queue();
    must_init(sys.queue, "event queue");
    /*ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/
    sys.timer = al_create_timer(1.0 / 60.0);
    must_init(sys.timer, "timer");

    al_register_event_source(sys.queue, al_get_keyboard_event_source());
    al_register_event_source(sys.queue, al_get_display_event_source(sys.display));
    al_register_event_source(sys.queue, al_get_timer_event_source(sys.timer));

    al_start_timer(sys.timer);

    return sys;
}

ALLEGRO_DISPLAY* create_display()
{
    ALLEGRO_DISPLAY* display = al_create_display(DISP_W, DISP_H);
    must_init(display, "display");
    return display;
}

ALLEGRO_BITMAP* load_image(const char* path)
{
    ALLEGRO_BITMAP* img = al_load_bitmap(path);
    must_init(img, "image");
    return img;
}

void shutdown(ALLEGRO_BITMAP* img, ALLEGRO_DISPLAY* disp)
{
    al_destroy_bitmap(img);
    al_destroy_display(disp);
}

void keyboard_init() {
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= ~KEY_DOWN;
        break;
    }
}