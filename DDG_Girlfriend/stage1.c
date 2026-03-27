#include "LIB_DDG.h"
#include "LIB_stage.h"

static void initStage1Map(Map* m) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            m->tiles[i][j].x = j * TILE_SIZE;
            m->tiles[i][j].y = i * TILE_SIZE;
            m->tiles[i][j].w = TILE_SIZE;
            m->tiles[i][j].h = TILE_SIZE;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                m->tiles[i][j].type = WALL; // 벽
            }
            else {
                m->tiles[i][j].type = ROAD; // 길
            }
        }
    }
}

Stage* Stage1() {
	Stage* s = (Stage*)malloc(sizeof(Stage));
    s->initMap = initStage1Map;
    return s;
}


//상태 업데이트
static void update_stage1() {

}

static void render_stage1(Stage* s) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안뻄
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    al_flip_display();
  
}

void run_stage1(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    bool redraw = true;

    /*al_wait_for_event(queue, &ev);*/
    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    /*if (ev.type == ALLEGRO_EVENT_KEY_DOWN) return;*/
    update_stage1();
    if (redraw)
    {
        render_stage1(s);
        redraw = false;
    }
}