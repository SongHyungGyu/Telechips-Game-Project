#include "LIB_DDG.h"
#include "LIB_stage.h"
#define tile_w_num 20
#define tile_h_num 15
static tile map[tile_h_num][tile_w_num];
ALLEGRO_BITMAP* roadTile;
ALLEGRO_BITMAP* wallTile;

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
    roadTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/road.png");
    must_init(roadTile, "roadTile image");
    wallTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/wall.png");
    must_init(wallTile, "wallTile image");
    initMap();
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
}

static void render_stage1() {
    // printf("stage1\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    renderMap(roadTile, wallTile);
    al_flip_display();
  
}

void run_stage1(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    bool redraw = true;

    /*al_wait_for_event(queue, &ev);*/
    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    /*if (ev.type == ALLEGRO_EVENT_KEY_DOWN) return;*/
    update_stage1();
    if (redraw)
    {
        render_stage1();
        redraw = false;
    }
}