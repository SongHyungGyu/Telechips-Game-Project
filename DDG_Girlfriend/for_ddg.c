#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_worm.h"

// main에서 한번만 시작할 초기화 함수
DDG* init_ddg(){
	DDG* ddg = (DDG*)malloc(sizeof(DDG));
    ddg->img = (ALLEGRO_BITMAP*)malloc(sizeof(ALLEGRO_BITMAP*));

    ddg->img = load_image(PATH "ddg_down.png");
	ddg->x = TILE_SIZE * 1;
	ddg->y = TILE_SIZE * 1;
	ddg->life = 3;
	ddg->speed = 5;
	ddg->w = al_get_bitmap_width(ddg->img);
	ddg->h = al_get_bitmap_height(ddg->img);
	return ddg;
}

bool col_wall(int nx, int ny, Map m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    printf("nxtile : %d, nytile : %d, type : %d\n", nxtile, nytile, m.tiles[nytile][nxtile].type);
    if (m.tiles[nytile][nxtile].type == WALL) return true;
    return false;
}

bool col_marsh(int nx, int ny, Map m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    printf("nxtile : %d, nytile : %d, type : %d\n", nxtile, nytile, m.tiles[nytile][nxtile].type);
    if (m.tiles[nytile][nxtile].type == MARSH) return true;
    return false;
}

void update_ddg(DDG* ddg, Map m) {
    int nx, ny;
    printf("x : %d, y : %d\n", ddg->x, ddg->y);
    if (key[ALLEGRO_KEY_RIGHT]) {
        nx = ddg->x + ddg_size / 2 + ddg ->speed;
        ny = ddg->y + ddg_size / 2;
        if (!col_wall(nx, ny, m)) {
            if(col_marsh(nx, ny, m)) ddg->x += ddg->speed / 2;
            else ddg ->x += ddg->speed;
        }
        ddg->img = load_image(PATH "ddg_right.png");
    }
    if (key[ALLEGRO_KEY_LEFT]) {
        nx = ddg ->x + ddg_size / 2 - ddg ->speed;
        ny = ddg ->y + ddg_size / 2;
        if (!col_wall(nx, ny, m)) {
            if (col_marsh(nx, ny, m)) ddg->x -= ddg->speed/2;
            else ddg->x -= ddg->speed;;
        }
        ddg->img = load_image(PATH "ddg_left.png");
    }
    if (key[ALLEGRO_KEY_UP]) {
        nx = ddg ->x + ddg_size / 2;
        ny = ddg ->y + ddg_size / 2 - ddg ->speed;
        if (!col_wall(nx, ny, m)) {
            if (col_marsh(nx, ny, m)) ddg->y -= ddg->speed / 2;
            else ddg->y -= ddg->speed;
        }
        ddg->img = load_image(PATH "ddg_up.png");
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        nx = ddg ->x + ddg_size / 2;
        ny = ddg ->y + ddg_size / 2 + ddg ->speed;
        if (!col_wall(nx, ny, m)) {
            if(col_marsh(nx, ny, m)) ddg ->y += ddg->speed/2;
            else ddg->y += ddg->speed;
        }
        ddg->img = load_image(PATH "ddg_down.png");
    }
    ddg->w = al_get_bitmap_width(ddg->img);
    ddg->h = al_get_bitmap_height(ddg->img);
}

void render_ddg(DDG* ddg) {
     // 두더지 그리기
    al_draw_scaled_bitmap(ddg -> img, 0, 0, ddg ->w, ddg -> h,
        ddg -> x, ddg ->y, ddg_size, ddg_size, 0);
}

void update_ddg_after_attack(DDG* ddg, Stage * s){
    //생명에 따라 현재 스테이지의 시작위치로 돌아가거나
    //mode를 변경하며 스테이지1부터 시작
    if(ddg -> life > 1){
        ddg->x = s->sx;
        ddg->y = s->sy;
        --(ddg ->life); 
        //이미지도 start 이미지로 변경해야 하는데 start 
        //이미지도 스테이지마다 다르니 s에 저장해두면 좋을듯
    }else{
        //무조건 stage1으로 가면됨
        mode = 4;
    }

}