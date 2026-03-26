#include "LIB_stage3.h"
#include "LIB_stage.h"

#define tile_w_num 20
#define tile_h_num 15

static tile map[tile_h_num][tile_w_num];
static ALLEGRO_BITMAP* roadTile;
static ALLEGRO_BITMAP* wallTile;
//static ALLEGRO_BITMAP* mapCache = NULL; // 지도를 저장할 "종이"

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

static void initMap() {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            map[i][j].x = j * tile_width;
            map[i][j].y = i * tile_width;
            map[i][j].w = tile_width;
            map[i][j].h = tile_width;
            map[i][j].type = stage3_blueprint[i][j];
        }
    }
}

void init_stage3() {
    roadTile = al_load_bitmap("road.png");
    must_init(roadTile, "roadTile image");
    wallTile = al_load_bitmap("wall.png");
    must_init(wallTile, "wallTile image");
    initMap();

    /*
    mapCache = al_create_bitmap(tile_w_num * tile_width, tile_h_num * tile_width);
    al_set_target_bitmap(mapCache);  // "종이"에 그리기 모드
    renderMap();                     // 300장 그리기 (단 1회)
    al_set_target_backbuffer(al_get_current_display()); // 다시 화면에 그리기 모드
    */
}

static void update_stage3() {
}

static void renderMap() {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            ALLEGRO_BITMAP* target = (map[i][j].type == 1) ? wallTile : roadTile;
            if (target != NULL) {
                al_draw_scaled_bitmap(target,
                    0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target),
                    map[i][j].x, map[i][j].y, map[i][j].w, map[i][j].h, 0);
            }
        }
    }
}

static void render_stage3() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    renderMap();
    al_flip_display();
}

/*
static void render_stage3() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(mapCache, 0, 0, 0); // 종이 1장만 출력
    al_flip_display();
}
*/

void run_stage3(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue,
    ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {
    static bool redraw = false;
    if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;
    update_stage3();
    if (redraw) {
        render_stage3();
        redraw = false;
    }
}