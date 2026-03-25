#ifndef __LIB_DDG__
#define __LIB_DDG__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

// 공용 변수 및 함수
// test_LIB.c
#define DISP_W 1000
#define DISP_H 600
unsigned char key[ALLEGRO_KEY_MAX];
void must_init(bool test, const char* description);
void init_system();
ALLEGRO_DISPLAY* create_display();
ALLEGRO_BITMAP* load_image(const char* path);
void shutdown(ALLEGRO_BITMAP* img, ALLEGRO_DISPLAY* disp);
void keyboard_init();
typedef struct SYSTEM {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
}SYSTEM;
SYSTEM init_game_system();

// 첫번째 페이지 실행 함수
// first_page.c
void draw_scaled_crop(ALLEGRO_BITMAP* image);
void run_first_page(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer);

#endif