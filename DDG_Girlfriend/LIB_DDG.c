#include "LIB_DDG.h"
// ����

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
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");;
}

SYSTEM* init_game_system() {
	SYSTEM* sys = (SYSTEM*)malloc(sizeof(SYSTEM));

    sys->display = create_display();
    must_init(sys->display, "display");
    sys->queue = al_create_event_queue();
    must_init(sys->queue, "event queue");

    sys->font = al_load_ttf_font("resource/font/Inkfree.ttf", 30, 0);
    must_init(sys->font, "font");

    sys->timer = al_create_timer(1.0 / 60.0);
    must_init(sys->timer, "timer");

    al_register_event_source(sys->queue, al_get_keyboard_event_source());
    al_register_event_source(sys->queue, al_get_display_event_source(sys->display));
    al_register_event_source(sys->queue, al_get_timer_event_source(sys->timer));

    al_start_timer(sys->timer);

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

ALLEGRO_SAMPLE* load_aud(const char* path)
{
    ALLEGRO_SAMPLE* aud = al_load_sample(path);
    //printf("%s\n", path);
    //must_init(aud, "audio");
    return aud;
}


ALLEGRO_AUDIO_STREAM* load_stream(const char* path)
{
    ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream(path, 4, 2048);
    //printf("%
    // s\n", path);
    //must_init(aud, "audio");
    return stream;
}

void play_stream(ALLEGRO_AUDIO_STREAM* stream)
{
    if (!stream) return;
    al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP);
    al_seek_audio_stream_secs(stream, 0.0);
    al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());
}

void detach_stream(ALLEGRO_AUDIO_STREAM* stream)
{
    al_detach_audio_stream(stream);
}
void destroy_stream(ALLEGRO_AUDIO_STREAM* stream)
{
    al_destroy_audio_stream(stream);
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