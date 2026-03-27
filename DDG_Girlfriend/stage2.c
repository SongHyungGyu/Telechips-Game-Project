#include "LIB_DDG.h"
#include "LIB_stage.h"

static tile stage2Map[tile_h_num][tile_w_num];
ALLEGRO_BITMAP* roadTile;
ALLEGRO_BITMAP* wallTile;
ALLEGRO_BITMAP* marshTile;

/*초기화*/
static void initStage2Map() {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            stage2Map[i][j].x = j * tile_width;
            stage2Map[i][j].y = i * tile_width;
            stage2Map[i][j].w = tile_width;
            stage2Map[i][j].h = tile_width;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                stage2Map[i][j].type = 0; // 벽
            }
            else if (j == 5 || j == 6 || j == 13 || j == 14) {
                stage2Map[i][j].type = 2; // 늪
            }
            else {
                stage2Map[i][j].type = 1; // 길
            }
        }
    }
}

// main에서 한번만 시작할 초기화 함수
void init_stage2() {
    roadTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/road.png");
    printf("roadTile\n");
    must_init(roadTile, "roadTile image");
    wallTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/wall.png");
    must_init(wallTile, "wallTile image");
    marshTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/marsh.png");
    must_init(marshTile, "marshTile image");
    initStage2Map();
}
/*초기화*/

/*상태업데이트*/
static void update_stage2() {

}
/*상태업데이트*/

/*렌더링*/
static void renderStage2Map(ALLEGRO_BITMAP* roadTile, ALLEGRO_BITMAP* wallTile) {
    //printf("renderMap\n");
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {

            if (stage2Map[i][j].type == 1) {
                // 길 타일 그리기
                al_draw_scaled_bitmap(wallTile, 0, 0, stage2Map[i][j].w, stage2Map[i][j].h,
                    stage2Map[i][j].x, stage2Map[i][j].y, stage2Map[i][j].w, stage2Map[i][j].h, 0);
            }
            else if (stage2Map[i][j].type == 2) {
                //늪 타일 그리기
                al_draw_scaled_bitmap(marshTile, 0, 0, stage2Map[i][j].w, stage2Map[i][j].h,
                    stage2Map[i][j].x, stage2Map[i][j].y, stage2Map[i][j].w, stage2Map[i][j].h, 0);
            }
            else {
                // 벽 타일 그리기               
                al_draw_scaled_bitmap(roadTile, 0, 0, stage2Map[i][j].w, stage2Map[i][j].h,
                    stage2Map[i][j].x, stage2Map[i][j].y, stage2Map[i][j].w, stage2Map[i][j].h, 0);
            }
        }
    }
}

static void render_stage2() {
    // printf("stage1\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    renderStage2Map(roadTile, wallTile);
    al_flip_display();

}
/*렌더링*/


/*stage2를 런하는 인터페이스*/
void run_stage2(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    bool redraw = true;

    /*al_wait_for_event(queue, &ev);*/
    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    /*if (ev.type == ALLEGRO_EVENT_KEY_DOWN) return;*/
    update_stage2();
    if (redraw)
    {
        render_stage2();
        redraw = false;
    }
}