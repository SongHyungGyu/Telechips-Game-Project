#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_worm.h"
#include "for_user.h"
#include <math.h>

#define heart_size 40
#define	life_img_width 330
#define life_img_height 290

// main에서 한번만 시작할 초기화 함수
DDG* init_ddg(){
	DDG* ddg = (DDG*)malloc(sizeof(DDG));

    ddg->img = load_image(PATH "ddg.png");
    ddg-> wormSound = load_aud(AUDIOPATH "wormSound.wav");
	if (!ddg->wormSound) printf("wormSound load failed\n");
    ddg-> flowerSound= load_aud(AUDIOPATH "flowerSound.wav");
    if (!ddg->flowerSound) printf("flowerSound load failed\n");

	ddg->x = TILE_SIZE * 1;
	ddg->y = TILE_SIZE * 1;
	ddg->life = 3;
	ddg->speed = 5;
	ddg->w = 0;
	ddg->h = 0;
    ddg->heart_img = load_image(PATH "heart.png");
	return ddg;
}

Chaser* init_chaser(int start_x, int start_y) {

    Chaser* chaser = (Chaser*)malloc(sizeof(Chaser));
    chaser->x = start_x;
    chaser->y = start_y;
    chaser->speed = 2; // 플레이어보다 느린 속도
    chaser->img = load_image(PATH "fox.png"); // 적 이미지 로드
    return chaser;

}

bool col_wall(int nx, int ny, Map* m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    if (m -> tiles[nytile][nxtile].type == WALL) return true;
    return false;
}

bool col_marsh(int nx, int ny, Map * m) {
    int nxtile = nx / TILE_SIZE;
    int nytile = ny / TILE_SIZE;
    if (m -> tiles[nytile][nxtile].type == MARSH) return true;
    return false;
}

void update_ddg(DDG* ddg, Stage* s) {
    int cx = ddg->x + ddg_size / 2;
    int cy = ddg->y + ddg_size / 2;
    int nx, ny;
    if (key[ALLEGRO_KEY_RIGHT]) {
        nx = cx + ddg ->speed;
        ny = cy;
        if (!col_wall(nx + ddg_size / 2, ny, &s->map)) {
            if(col_marsh(nx, ny, &s->map)) ddg->x += ddg->speed / 2;
            else ddg ->x += ddg->speed;
        }
        ddg->w = 200;
    }
    if (key[ALLEGRO_KEY_LEFT]) {
        nx = cx - ddg ->speed;
        ny = cy;
        if (!col_wall(nx - ddg_size / 2, ny, &s->map)) {
            if (col_marsh(nx, ny, &s->map)) ddg->x -= ddg->speed/2;
            else ddg->x -= ddg->speed;;
        }
        ddg->w = 100;
    }
    if (key[ALLEGRO_KEY_UP]) {
        nx = cx;
        ny = cy - ddg ->speed;
        if (!col_wall(nx, ny- ddg_size / 2, &s->map)) {
            if (col_marsh(nx, ny, &s->map)) ddg->y -= ddg->speed / 2;
            else ddg->y -= ddg->speed;
        }
        ddg->w = 300;
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        nx = cx;
        ny = cy + ddg ->speed;
        if (!col_wall(nx, ny+ ddg_size / 2, &s->map)) {
            if(col_marsh(nx, ny, &s->map)) ddg ->y += ddg->speed/2;
            else ddg->y += ddg->speed;
        }
        ddg->w = 0;
    }
}

void update_chaser(Chaser* chaser, DDG* ddg, Map* m) {
    int nx = chaser->x;
    int ny = chaser->y;

    // 중심점 계산 (충돌 판정을 더 정확하게 하기 위함)
    int cx = chaser->x + ddg_size / 2;
    int cy = chaser->y + ddg_size / 2;

    // 1. X축 이동 방향 결정 (플레이어 쪽으로)
    if (chaser->x < ddg->x) nx = cx + chaser->speed;
    else if (chaser->x > ddg->x) nx = cx - chaser->speed;

    // X축 벽 충돌 확인 후 이동 적용
    if (!col_wall(nx, cy, m)) {
        if (chaser->x < ddg->x) chaser->x += chaser->speed;
        else if (chaser->x > ddg->x) chaser->x -= chaser->speed;
    }

    // 2. Y축 이동 방향 결정
    if (chaser->y < ddg->y) ny = cy + chaser->speed;
    else if (chaser->y > ddg->y) ny = cy - chaser->speed;

    // Y축 벽 충돌 확인 후 이동 적용
    if (!col_wall(cx, ny, m)) {
        if (chaser->y < ddg->y) chaser->y += chaser->speed;
        else if (chaser->y > ddg->y) chaser->y -= chaser->speed;
    }
}
bool check_collision_with_chaser(DDG* ddg, Chaser* chaser) {
    int hitbox_range = ddg_size / 2;

    if (abs(ddg->x - chaser->x) < hitbox_range &&
        abs(ddg->y - chaser->y) < hitbox_range) {
        return true;
    }
    return false;
}



void render_ddg(DDG* ddg) {
    int draw = 1;

    if (play_time - ddg->hit_time < 60) {
        if ((play_time / 10) % 2 != 0) {
            draw = 0;  // 이 프레임은 안 그림
        }
    }
    if (draw) {
        al_draw_scaled_bitmap(ddg->img, ddg->w, 0, 100, 100,
            ddg->x, ddg->y, ddg_size, ddg_size, 0);
    }
}

void render_hud(DDG* ddg) {
    for (int i = 0; i < ddg->life; ++i) {
        al_draw_scaled_bitmap(ddg->heart_img, 460, 190, life_img_width, life_img_height,
            TILE_SIZE * 16 + i * heart_size, 10, heart_size, heart_size, 0);
    }
}
void render_chaser(Chaser* chaser) {
    

    if (chaser == NULL || chaser->img == NULL) {
        return;
    }

    float img_w = al_get_bitmap_width(chaser->img);
    float img_h = al_get_bitmap_height(chaser->img);

    al_draw_scaled_bitmap(chaser->img,
        0, 0, img_w, img_h,
        chaser->x, chaser->y, ddg_size, ddg_size, 0);
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
    }else   {    // 로그인 페이지로 가면됨
        if (s-> stage > 1) save_User(user);
        after_stage(s, MODE_FIRST_PAGE);
    }
    ddg->hit_time = play_time;
}



