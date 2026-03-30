#ifndef __LIB_FIRST_PAGE__
#define __LIB_FIRST_PAGE__
// 첫번째 페이지 헤더 파일
#include "LIB_DDG.h"
#include "for_user.h"

void draw_scaled_crop(ALLEGRO_BITMAP* image);
void run_first_page(User * user, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);

#endif