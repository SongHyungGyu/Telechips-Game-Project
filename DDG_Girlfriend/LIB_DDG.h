#ifndef __LIB_DDG__
#define __LIB_DDG__
// ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



#define DISP_W 1200
#define DISP_H 900

#define AUDIOPATH "resource/aud/"
#define PATH "resource/img/"

int mode;
int play_time;

unsigned char key[ALLEGRO_KEY_MAX];
void must_init(bool test, const char* description);
void init_system();
ALLEGRO_DISPLAY* create_display();
ALLEGRO_BITMAP* load_image(const char* path);
ALLEGRO_SAMPLE* load_aud(const char* path);
void shutdown(ALLEGRO_BITMAP* img, ALLEGRO_DISPLAY* disp);
typedef struct SYSTEM {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font;
}SYSTEM;
SYSTEM* init_game_system();
void draw_scaled_crop(ALLEGRO_BITMAP* image);

ALLEGRO_AUDIO_STREAM* load_stream(const char* path);
void play_stream(ALLEGRO_AUDIO_STREAM* stream);
void detach_stream(ALLEGRO_AUDIO_STREAM* stream);
void destroy_stream(ALLEGRO_AUDIO_STREAM* stream);

#define KEY_SEEN     1
#define KEY_DOWN     2
unsigned char key[ALLEGRO_KEY_MAX];
void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);
#endif