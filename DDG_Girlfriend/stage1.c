#include "LIB_DDG.h"
#include "LIB_stage.h"

int ddg_w, ddg_h;
DDG ddg;
int sx1, sy1;
int angle;
int nx, ny;

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

//// main에서 한번만 시작할 초기화 함수
//void init_stage1() {
//    ddg_image = load_image("resource/img/ddg_down.png");
//    ddg_w = al_get_bitmap_width(ddg_image);
//    ddg_h = al_get_bitmap_height(ddg_image);
//    sx1 = 0, sy1 = 0;
//    ddg = (DDG){ ddg_image, sx1, sy1, 3, 5 };
//}
Stage* Stage1() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    s->initMap = initStage1Map;
    return s;
}

static void render_stage1(Stage* s) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안M
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //지도 이미 그려놓은거 출력
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    // 두더지 그리기
    ddg_w = al_get_bitmap_width(ddg.img);
    ddg_h = al_get_bitmap_height(ddg.img);
    al_draw_scaled_bitmap(ddg.img, 0, 0, ddg_w, ddg_h,
        ddg.x, ddg.y, ddg_size, ddg_size, 0);

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

//상태 업데이트
static void update_stage1() {
    update_ddg();
}

void run_stage1(Stage * s, ALLEGRO_DISPLAY * display, ALLEGRO_EVENT_QUEUE * queue, ALLEGRO_TIMER * timer, ALLEGRO_EVENT ev) {
            bool redraw = true;

            if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;

            if (ev.type != ALLEGRO_EVENT_TIMER) {
                update_stage1();
                redraw = true;
            }
            if (redraw) {
                render_stage1();
                redraw = false;
            }
}