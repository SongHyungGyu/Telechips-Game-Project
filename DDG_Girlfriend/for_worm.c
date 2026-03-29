#include "for_worm.h"
#include "LIB_stage.h"

worm* init_worm(int x, int y, int lx, int ly, int rx, int ry, int tx, int ty,
    int bx, int by, int type, int speed, int dir) {
    worm* w = (worm*)malloc(sizeof(worm));
    w->img = load_image(PATH "wall.png");
	w->w = al_get_bitmap_width(w->img);
	w->h = al_get_bitmap_height(w->img);
    w->x = x;
	w->y = y;
	w->lx = lx;
	w->ly = ly;
	w->rx = rx;
	w->ry = ry;
	w->tx = tx;
	w->tx = ty;
	w->bx = bx;
	w->by = by;
	w->type = type;
	w->speed = speed;
	w->dir = dir;
    return w;
}


void update_worm(worm* w) {
	printf("%d\n", w->x);
	printf("%d %d\n", w->lx, w->rx);
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
		w->x += w->speed * w->dir;

		if (w->x > w->tx) {
			w->x = w->tx;
			w->dir = -1;
		}
		else if (w->x < w->lx) {
			w->x = w->lx;
			w->dir = 1;
		}
	}
	else if(w->type == SQUARE) {
	}
}


void render_worm(worm* w) {
    // 지렁이 그리기
    al_draw_scaled_bitmap(w ->img, 0, 0, w-> w, w->h,
        w->x, w->y, WORM_SIZE, WORM_SIZE, 0);
}