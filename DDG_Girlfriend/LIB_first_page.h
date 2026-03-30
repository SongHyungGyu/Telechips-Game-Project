#ifndef __LIB_FIRST_PAGE__
#define __LIB_FIRST_PAGE__
// 첫번째 페이지 헤더 파일
#include "LIB_DDG.h"
#include "for_user.h"

void draw_scaled_crop(ALLEGRO_BITMAP* image);
void run_first_page(User* user, SYSTEM* sys, ALLEGRO_EVENT ev);

#endif