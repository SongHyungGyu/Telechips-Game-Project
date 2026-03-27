#ifndef __LIB_STAGE2__
#define __LIB_STAGE2__
// 스테이지 2 헤더 파일
#include "LIB_DDG.h"

void init_stage2(Stage* s);
void run_stage2(Stage* s , ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
	ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev);
#endif
#pragma once
