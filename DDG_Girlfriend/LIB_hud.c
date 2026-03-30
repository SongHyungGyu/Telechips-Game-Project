#include "LIB_hud.h"

#define heart_size 40
#define	life_img_width 330
#define life_img_height 290

HEART* hud_init() {
	HEART* heart = (HEART*)malloc(sizeof(HEART));
	heart->img = load_image(PATH "heart.png");
	return heart;
}

void update_hud(HEART* heart) {

}

void render_hud(HEART* heart, DDG* ddg) {
	for (int i = 0; i < ddg->life; ++i) {
		al_draw_scaled_bitmap(heart->img, 460, 190, life_img_width, life_img_height,
			TILE_SIZE * 16 + heart_size * i, 10, heart_size, heart_size, 0);
	}
}