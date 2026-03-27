#include "LIB_DDG.h"
#include "LIB_stage.h"

static void initMap(Map* m) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            m -> tiles[i][j].x = j * tile_width;
            m->tiles[i][j].y = i * tile_width;
            m->tiles[i][j].w = tile_width;
            m->tiles[i][j].h = tile_width;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                m->tiles[i][j].type = 0; // 벽
            }
            else {
                m->tiles[i][j].type = 1; // 길
            }
        }
    }
}

// main에서 한번만 시작할 초기화 함수
void init_stage1(Stage* s) {
    s-> roadTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/road.png");
    must_init(s->roadTile, "roadTile image");
    s-> wallTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/wall.png");
    must_init(s->wallTile, "wallTile image");
    initMap(&s->map);
}

//상태 업데이트
static void update_stage1() {

}
static void renderMap(Stage* s) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            tile* t = &s->map.tiles[i][j];
            if (t -> type == 1) {
                // 길 타일 그리기
                al_draw_scaled_bitmap(s->wallTile, 0, 0,t-> w, t-> h,
                    t->x, t->y, t->w, t->h, 0);
            }
            else {
                // 벽 타일 그리기               
                al_draw_scaled_bitmap(s->roadTile, 0, 0, t->w, t->h,
                    t->x, t->y, t->w, t->h, 0);
            }
        }
    }
}

static void render_stage1(Stage* s) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    renderMap(s);
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