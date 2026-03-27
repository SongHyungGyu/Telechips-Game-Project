#include "LIB_stage.h"

#define tile_w_num 20
#define tile_h_num 15
static tile map[tile_h_num][tile_w_num];
ALLEGRO_BITMAP* roadTile;
ALLEGRO_BITMAP* wallTile;
ALLEGRO_BITMAP* ddg_image;
int ddg_w, ddg_h;
DDG ddg;
int sx1, sy1;
int angle;
int nx, ny;

static void initMap() {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            map[i][j].x = j * tile_width;
            map[i][j].y = i * tile_width;
            map[i][j].w = tile_width;
            map[i][j].h = tile_width;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                map[i][j].type = 0; // 벽
            }
            else {
                map[i][j].type = 1; // 길
            }
        }
    }
}

// main에서 한번만 시작할 초기화 함수
void init_stage1() {
    roadTile = al_load_bitmap("resource/img/road.png");
    must_init(roadTile, "roadTile image");
    wallTile = al_load_bitmap("resource/img/wall.png");
    must_init(wallTile, "wallTile image");
    initMap();
    ddg_image = load_image("resource/img/ddg_down.png");
    ddg_w = al_get_bitmap_width(ddg_image);
    ddg_h = al_get_bitmap_height(ddg_image);
    sx1 = 0, sy1 = 0;
    ddg = (DDG){ ddg_image, sx1, sy1, 3, 5 };
}
//상태 업데이트
static void update_stage1() {

}
static void renderMap(ALLEGRO_BITMAP* roadTile, ALLEGRO_BITMAP* wallTile) {
    //printf("renderMap\n");
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {

            if (map[i][j].type == 1) {
                // 길 타일 그리기
                al_draw_scaled_bitmap(wallTile, 0, 0, map[i][j].w, map[i][j].h,
                    map[i][j].x, map[i][j].y, map[i][j].w, map[i][j].h, 0);
            }
            else {
                // 벽 타일 그리기               
                al_draw_scaled_bitmap(roadTile, 0, 0, map[i][j].w, map[i][j].h,
                    map[i][j].x, map[i][j].y, map[i][j].w, map[i][j].h, 0);
            }
        }
    }
    // 두더지 그리기
    ddg_w = al_get_bitmap_width(ddg.img);
    ddg_h = al_get_bitmap_height(ddg.img);
    al_draw_scaled_bitmap(ddg.img, 0, 0, ddg_w, ddg_h,
        ddg.x, ddg.y, ddg_size, ddg_size, 0);
    //al_draw_scaled_rotated_bitmap(
    //    ddg.img,
    //    ddg_w / 2, ddg_h / 2,   // 중심 기준
    //    ddg.x + ddg_size / 2, ddg.y + ddg_size / 2,           // 위치
    //    //400, 400,
    //    (float)ddg_size / ddg_w,       // x 스케일
    //    (float)ddg_size / ddg_h,       // y 스케일
    //    angle,                  // 회전
    //    0
    //);
}
static void render_stage1() {
    // printf("stage1\n");
    al_clear_to_color(al_map_rgb(255, 255, 255));
    renderMap(roadTile, wallTile);

    /*al_set_target_backbuffer(display);*/
    /*al_draw_scaled_bitmap(ddg.img, 0, 0, ddg_w, ddg_h,
        ddg.x, ddg.y, ddg_size, ddg_size, 0);*/
    al_flip_display();

}
static bool col_wall(int nx, int ny) {
    int nxtile = nx / tile_h_num;
    int nytile = ny / tile_w_num;
    if (map[nxtile][nytile].type == 1) return true;
    return false;
}
void update_ddg() {
    if (key[ALLEGRO_KEY_RIGHT]) {
        nx = ddg.x + ddg.speed;
        ny = ddg.y;
        if (!col_wall(nx, ny)) {
            ddg.x = nx;
            ddg.img = load_image("resource/img/ddg_right.png");
        }
    }
    if (key[ALLEGRO_KEY_LEFT]) {
        nx = ddg.x - ddg.speed;
        ny = ddg.y;
        if (!col_wall(nx, ny)) {
            ddg.x = nx;
            ddg.img = load_image("resource/img/ddg_left.png");
        }
    }
    if (key[ALLEGRO_KEY_UP]) {
        nx = ddg.x;
        ny = ddg.y - ddg.speed;
        if (!col_wall(nx, ny)) {
            ddg.y = ny;
            ddg.img = load_image("resource/img/ddg_up.png");
        }
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        nx = ddg.x;
        ny = ddg.y + ddg.speed;
        if (!col_wall(nx, ny)) {
            ddg.y = ny;
            ddg.img = load_image("resource/img/ddg_down.png");
        }
    }
}
void run_stage1(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    bool redraw = true;

    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;

    if (ev.type != ALLEGRO_EVENT_TIMER) {
        update_ddg();
        redraw = true;
    }
    update_stage1();
    if (redraw){
        render_stage1();
        redraw = false;
    }
}