#include "LIB_stage3.h"
#include "LIB_stage.h"


static int stage3_blueprint[tile_h_num][tile_w_num] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static void initStage3Map(Map* m) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            m->tiles[i][j].x = j * TILE_SIZE;
            m->tiles[i][j].y = i * TILE_SIZE;
            m->tiles[i][j].w = TILE_SIZE;
            m->tiles[i][j].h = TILE_SIZE;
            m->tiles[i][j].type = stage3_blueprint[i][j];
        }
    }
}

Stage* Stage3() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    s->initMap = initStage3Map;
    return s;
}

static void update_stage3() {
}


static void render_stage3(Stage* s) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    al_flip_display();
}


void run_stage3(Stage* s, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    static bool redraw = false;
    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    update_stage3();
    if (redraw) {
        render_stage3(s);
        redraw = false;
    }
}