#include "for_flower.h"
#include "LIB_stage.h"



flower* init_flower(int x, int y){
	flower* f = (flower*)malloc(sizeof(flower));
	
	f->img = load_image(PATH "flower.png");
	f->x = x;
	f->y = y;
	f->w = al_get_bitmap_width(f->img);
	f->h = al_get_bitmap_height(f->img);
	f->used = 0;

	return f;
}

//1은 꽃 2는 두더지
bool collide(int x1, int y1, int w1, int h1,
	int x2, int y2, int w2, int h2) {

	//각 중심 좌표 구하기 꽃의 중심좌표는 cx1, cy1, 두더지의 중심 좌표는 cx2, cy2
	int cx1 = x1 + w1 / 2;
	int cy1 = y1 + h1 / 2;

	int cx2 = x2 + w2 / 2;
	int cy2 = y2 + h2 / 2;

	//두 객체 중심 사이이의 거리 차이 dx, dy
	int dx = cx1 - cx2;
	int dy = cy1 - cy2;

	//두 객채 중심 사이 거리가 30(반지름)보다 작으면 충돌
	return (dx * dx + dy * dy) < 30 * 30; // 반지름 30
}

void update_flower(flower* f, DDG* ddg, Stage* s) {
	// 이미 먹은 꽃이면 반환함
	if (f->used) return;

	//이때까지 안먹었던 꽃 중 충돌이면 f->used = 1과 남은 꽃 개수를 하나 줄임
	if (collide(f->x, f->y, f->w, f->h,
		ddg->x, ddg->y, ddg->w, ddg->h)) {
		f->used = 1;   // 꽃 먹힘 처리
		s->flower_cnt--;
		printf("\nflower_current_cnt = %d\n", s->flower_cnt);
	}
}

void render_flower(flower* f) {
	if (f->used) return;
	al_draw_scaled_bitmap(f->img, 0, 0, f->w, f->h,
		f->x, f->y, FLOWER_SIZE, FLOWER_SIZE, 0);
}