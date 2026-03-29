#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_flower.h"
#define FLOWER_TOT 3

static void initStage2Map(Map* m) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            m->tiles[i][j].x = j * TILE_SIZE;
            m->tiles[i][j].y = i * TILE_SIZE;
            m->tiles[i][j].w = TILE_SIZE;
            m->tiles[i][j].h = TILE_SIZE;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                m->tiles[i][j].type = WALL; // 벽
            }
            else if (j == 5 || j == 6 || j == 13 || j == 14) {
                m->tiles[i][j].type = MARSH; // 늪지대
            }
            else {
                m->tiles[i][j].type = ROAD; // 길
            }
        }
    }
}


Stage* init_stage2() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    //각 stage마다 맵 배열 다르고 시작 위치 달라서 얘네만 여기서 일케 함
    s->initMap = initStage2Map;
    s->sx = 0;
    s->sy = 0;
    
    s->flowers = (flower**)malloc(sizeof(flower*) * 3);
    s->flowers[0] = init_flower(300, 300);
    s->flowers[1] = init_flower(500, 500);
    s->flowers[2] = init_flower(700, 200);

    s->flower_cnt = FLOWER_TOT;
    //나머지 초기화는 똑같기 때문에 공용함수 사용
    init_stage(s);

    return s;
}
/*초기화*/

/*상태업데이트*/
static void update_stage2(DDG* ddg, Map m) {
    update_ddg(ddg, m);
}
static void update_stage2_by_time(Stage* s, DDG* ddg) {
    for (int i = 0; i < FLOWER_TOT; i++) {
        update_flower(s->flowers[i], ddg, s);
    }
}
/*상태업데이트*/

/*렌더링*/
static void render_stage2(Stage* s, DDG* ddg) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안뻄
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    //ddg 렌더
    render_ddg(ddg);
    for (int i = 0; i < FLOWER_TOT; i++) {
        render_flower(s->flowers[i]);
    }

    al_flip_display();
}
/*렌더링*/


/*stage2를 런하는 인터페이스*/
void run_stage2(DDG* ddg, Stage* s, ALLEGRO_DISPLAY* display,
    ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {

    if ((ddg->x > ax2 - (TILE_SIZE / 2)) && (ddg->x < ax2 + (TILE_SIZE / 2)) &&
        (ddg->y > ay2 - (TILE_SIZE / 2)) && (ddg->y < ay2 + (TILE_SIZE / 2))) {
        mode = 6;
        return;
    }

    bool redraw = true;


    if (ev.type == ALLEGRO_EVENT_TIMER) {
        update_stage2_by_time(s, ddg);

        //if (s->flower_cnt == 0) {
            //mode = 3;
        //}

        redraw = true;
    }

    if (ev.type != ALLEGRO_EVENT_TIMER) {

        update_stage2(ddg, s->map);

        redraw = true;

    }

    if (redraw) {

        render_stage2(s, ddg);

        redraw = false;

    }

}