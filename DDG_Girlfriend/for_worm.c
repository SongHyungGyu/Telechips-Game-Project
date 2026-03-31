#include "for_worm.h"
#include "LIB_stage.h"

worm* init_worm(int x, int y, int lx, int rx, int ty,int by, int type, int speed, int dir) {
    worm* w = (worm*)malloc(sizeof(worm));
    w->img = load_image(PATH "realWorm.png");
	w->w = al_get_bitmap_width(w->img);
	w->h = al_get_bitmap_height(w->img);
    w->x = x;
	w->y = y;
	w->lx = lx;
	w->rx = rx;
	w->ty = ty;
	w->by = by;
	w->type = type;
	w->speed = speed;
	w->dir = dir;
    return w;
}

void destroy_worm(worm* w) {
	if (w == NULL) return;

	// 1. 지렁이 이미지 해제
	if (w->img) {
		al_destroy_bitmap(w->img);
	}
	// 2. 지렁이 구조체 메모리 해제
	free(w);
}

void destroy_worms_array(worm** worms, int count) {
	if (worms == NULL) return;

	for (int i = 0; i < count; i++) {
		if (worms[i]) {
			destroy_worm(worms[i]); // 개별 지렁이 해제 호출
		}
	}
	free(worms); // 지렁이 포인터 배열 자체를 해제
}


void update_worm(worm* w) {
	if (w->type == HORIZONTAL) {
		w->x += w->speed * w->dir;

		if (w->x > w->rx) {
			w->x = w->rx;
			w->dir = -1;
		}
		else if (w->x < w->lx) {
			w->x = w->lx;
			w->dir = 1;
		}
	}
	else if(w->type == VERTICAL) {
		w->y += w->speed * w->dir;

		if (w->y > w->ty) {
			w->y = w->ty;
			w->dir = -1;
		}
		else if (w->y < w->by) {
			w->y = w->by;
			w->dir = 1;
		}
	}
	else if(w->type == SQUARE) {
	}
}


void render_worm(worm* w) {
    al_draw_scaled_bitmap(w ->img, 0, 0, w-> w, w->h,
        w->x, w->y, WORM_SIZE, WORM_SIZE, 0);
}

bool col_worm(DDG* ddg, worm * w) {
	//충돌하지 않는 경우
	//A의 왼쪽 경계가 B의 오른쪽 경계보다 오른쪽이거나
	//A의 오른쪽 경계가 B의 왼쪽 경계보다 왼쪽이거나
	//A의 위쪽 경계가 B의 아랫쪽 경계보다 아래거나
	//A의 아래쪽 경계가 B의 위쪽 경계보다 위면 
	//겹치지 않는거임
	//그 경우를 제외하곤 겹침 판정
	//ddg랑 worm으로 굳이 안하고 A, B로 하고 공용으로 빼도 될듯함
	//다만 기준 좌표가 왼쪽 위인게 정확해야 함
	int ddg_l = ddg -> x;
	int ddg_r = ddg -> x + ddg_size;
	int ddg_t = ddg -> y;
	int ddg_b = ddg -> y + ddg_size;

	int worm_l = w->x;
	int worm_r = w->x + WORM_SIZE;
	int worm_t = w->y;
	int worm_b = w->y + WORM_SIZE;
	if( ddg_l >  worm_r || ddg_r < worm_l || ddg_t > worm_b || ddg_b < worm_t)
		return false;
	return true;

}

bool col_worms(DDG* ddg,int wormNum, worm ** worms){
	for(int i = 0; i< wormNum; ++i){
		if(col_worm(ddg , worms[i]))
			return true;
	}
	return false;
}
