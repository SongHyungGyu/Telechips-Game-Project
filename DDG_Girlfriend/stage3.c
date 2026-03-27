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

Stage* init_stage3() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    //각 stage마다 맵 배열 다르고 시작 위치 달라서 얘네만 여기서 일케 함
    s->initMap = initStage3Map;
    s->sx = 0;
    s->sy = 0;
    //나머지 초기화는 똑같기 때문에 공용함수 사용
    init_stage(s);
    return s;
}
static void update_stage3() {
}


static void render_stage3(Stage* s) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안뻄
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