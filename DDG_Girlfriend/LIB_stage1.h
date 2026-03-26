#ifndef __LIB_STAGE1__
#define __LIB_STAGE1__
// 스테이지 1 헤더 파일
#include "LIB_DDG.h"

void init_stage1();
void run_stage1(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, 
	ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
#endif
