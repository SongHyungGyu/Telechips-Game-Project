#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_worm.h"
#include "for_user.h"

#define heart_size 40
#define	life_img_width 330
#define life_img_height 290

// main에서 한번만 시작할 초기화 함수
DDG* init_ddg(){
	DDG* ddg = (DDG*)malloc(sizeof(DDG));
    //ddg->img = (ALLEGRO_BITMAP*)malloc(sizeof(ALLEGRO_BITMAP*));

    ddg->img = load_image(PATH "ddg.png");
	ddg->x = TILE_SIZE * 1;
	ddg->y = TILE_SIZE * 1;
	ddg->life = 3;
	ddg->speed = 5;
	ddg->w = 0;
	ddg->h = 0;
    ddg->heart_img = load_image(PATH "heart.png");
	return ddg;
}

bool col_wall(int nx, int ny, Map m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    //printf("nxtile : %d, nytile : %d, type : %d\n", nxtile, nytile, m.tiles[nytile][nxtile].type);
    if (m.tiles[nytile][nxtile].type == WALL) return true;
    return false;
}

bool col_marsh(int nx, int ny, Map m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    //printf("nxtile : %d, nytile : %d, type : %d\n", nxtile, nytile, m.tiles[nytile][nxtile].type);
    if (m.tiles[nytile][nxtile].type == MARSH) return true;
    return false;
}

void update_ddg(DDG* ddg, Map m) {
    int cx = ddg->x + ddg_size / 2;
    int cy = ddg->y + ddg_size / 2;
    int nx, ny;
    //printf("x : %d, y : %d\n", ddg->x, ddg->y);
    if (key[ALLEGRO_KEY_RIGHT]) {
        nx = cx + ddg ->speed;
        ny = cy;
        if (!col_wall(nx + ddg_size / 2, ny, m)) {
            if(col_marsh(nx, ny, m)) ddg->x += ddg->speed / 2;
            else ddg ->x += ddg->speed;
        }
        ddg->w = 200;
    }
    if (key[ALLEGRO_KEY_LEFT]) {
        nx = cx - ddg ->speed;
        ny = cy;
        if (!col_wall(nx - ddg_size / 2, ny, m)) {
            if (col_marsh(nx, ny, m)) ddg->x -= ddg->speed/2;
            else ddg->x -= ddg->speed;;
        }
        ddg->w = 100;
    }
    if (key[ALLEGRO_KEY_UP]) {
        nx = cx;
        ny = cy - ddg ->speed;
        if (!col_wall(nx, ny- ddg_size / 2, m)) {
            if (col_marsh(nx, ny, m)) ddg->y -= ddg->speed / 2;
            else ddg->y -= ddg->speed;
        }
        ddg->w = 300;
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        nx = cx;
        ny = cy + ddg ->speed;
        if (!col_wall(nx, ny+ ddg_size / 2, m)) {
            if(col_marsh(nx, ny, m)) ddg ->y += ddg->speed/2;
            else ddg->y += ddg->speed;
        }
        ddg->w = 0;
    }
}

void render_ddg(DDG* ddg) {
    // �δ��� �׸���
    al_draw_scaled_bitmap(ddg -> img, ddg->w, 0, 100, 100,
        ddg -> x, ddg ->y, ddg_size, ddg_size, 0);
    for (int i = 0; i < ddg->life; ++i) {
        al_draw_scaled_bitmap(ddg->heart_img, 460, 190, life_img_width, life_img_height,
            TILE_SIZE * 16 + heart_size * i, 10, heart_size, heart_size, 0);
    }
}

void update_ddg_after_attack(DDG* ddg, Stage * s, User * user){
    //생명에 따라 현재 스테이지의 시작위치로 돌아가거나
    //mode를 변경하며 스테이지1부터 시작
    if(ddg -> life > 1){
        ddg->x = s->sx;
        ddg->y = s->sy;
        --(ddg ->life); 
        //이미지도 start 이미지로 변경해야 하는데 start 
        //이미지도 스테이지마다 다르니 s에 저장해두면 좋을듯
    }else{
        // 로그인 페이지로 가면됨
        if (s-> stage > 1) save_User(user);
        mode = 0;
    }
}



