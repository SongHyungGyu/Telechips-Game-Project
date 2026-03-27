#include "LIB_ddg.h"
#include "LIB_stage.h"

// main에서 한번만 시작할 초기화 함수
DDG* init_ddg(){
	DDG* ddg = (DDG*)malloc(sizeof(DDG));


    ddg->img = load_image("C:/Telechips4/GameProjectPractice/x64/Debug/road.png");
	//ddg->img = load_image("resource/img/ddg_down.png");
	ddg->x = 0;
	ddg->y = 0;
	ddg->life = 3;
	ddg->speed = 5;
	ddg->w = al_get_bitmap_width(ddg->img);
	ddg->h = al_get_bitmap_height(ddg->img);
	return ddg;
}


static bool col_wall(int nx, int ny) {
    int nxtile = nx / tile_h_num;
    int nytile = ny / tile_w_num;
    //if (map[nxtile][nytile].type == 1)
    //    return true;
    return false;
}


void update_ddg(DDG* ddg) {
    int nx, ny;
    if (key[ALLEGRO_KEY_RIGHT]) {
        nx = ddg ->x + ddg ->speed;
        ny = ddg ->y;
        if (!col_wall(nx, ny)) {
            ddg ->x = nx;
            ddg ->img = load_image("resource/img/ddg_right.png");
			ddg->w = al_get_bitmap_width(ddg->img);
			ddg->h = al_get_bitmap_height(ddg->img);
        }
    }
    if (key[ALLEGRO_KEY_LEFT]) {
        nx = ddg ->x - ddg ->speed;
        ny = ddg ->y;
        if (!col_wall(nx, ny)) {
            ddg ->x = nx;
            ddg ->img = load_image("resource/img/ddg_left.png");
            ddg->w = al_get_bitmap_width(ddg->img);
            ddg->h = al_get_bitmap_height(ddg->img);
        }
    }
    if (key[ALLEGRO_KEY_UP]) {
        nx = ddg ->x;
        ny = ddg ->y - ddg ->speed;
        if (!col_wall(nx, ny)) {
            ddg ->y = ny;
            ddg ->img = load_image("resource/img/ddg_up.png");
            ddg->w = al_get_bitmap_width(ddg->img);
            ddg->h = al_get_bitmap_height(ddg->img);
        }
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        nx = ddg ->x;
        ny = ddg ->y + ddg ->speed;
        if (!col_wall(nx, ny)) {
            ddg ->y = ny;
            ddg ->img = load_image("resource/img/ddg_down.png");
            ddg->w = al_get_bitmap_width(ddg->img);
            ddg->h = al_get_bitmap_height(ddg->img);
        }
    }
}


void render_ddg(DDG* ddg) {
    // 두더지 그리기
    al_draw_scaled_bitmap(ddg -> img, 0, 0, ddg ->w, ddg -> h,
        ddg -> x, ddg ->y, ddg_size, ddg_size, 0);
}