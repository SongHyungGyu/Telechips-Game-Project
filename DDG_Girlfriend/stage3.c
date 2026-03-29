#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"


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
    s->initMap = initStage3Map;
    //10마리의 지렁이 초기화
    s->wormNum = 10;
	s->worms = (worm**)malloc(sizeof(worm*) * s->wormNum);

	s->worms[0] = init_worm(50, 200, 0, 0, 600, 200, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[1] = init_worm(120, 600, 0, 0, 600, 200, VERTICAL, WORM_SPEED_STAGE3, -1);
    s->worms[2] = init_worm(50, 720, 50, 550, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, +1);
    s->worms[3] = init_worm(550, 780,50, 550, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, -1);
    s->worms[4] = init_worm(550, 300, 0, 0, 600, 300, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[5] = init_worm(610, 600, 0, 0, 600, 300, VERTICAL, WORM_SPEED_STAGE3, -1);
    s->worms[6] = init_worm(550, 100, 550, 950, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, +1);
    s->worms[7] = init_worm(950, 160, 550, 950, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, -1);
    s->worms[8] = init_worm(950, 300, 0, 0, 600, 300, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[9] = init_worm(1010, 600, 0, 0, 600, 300, VERTICAL, WORM_SPEED_STAGE3, -1);

    s->sx = sx3;
    s->sy = sy3;
    init_stage(s);
    return s;
}



static void render_stage3(Stage* s, DDG* ddg) {
    //���߿� �ٸ� ��ҵ鵵 ���� ��Ű�°� �߰��ɲ��� �������� �ȖM
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0); // ���� 1�常 ���
    //ddg 렌더
    render_ddg(ddg);
    //worm 렌더
    for (int i = 0; i < s->wormNum; i++) {
        render_worm(s->worms[i]);
    }
    al_flip_display();
}
static void update_stage3(DDG* ddg, Map m) {
    update_ddg(ddg, m);
}
static void update_stage3_by_time(DDG * ddg, Stage* s) {
    for (int i = 0; i < s->wormNum; i++) {
        update_worm(s->worms[i]);
    }
    if(col_worms(ddg, s->wormNum, s->worms)){   
        update_ddg_after_attack(ddg, s);
    }
}
void run_stage3(DDG* ddg, Stage* s, ALLEGRO_DISPLAY* display,
    ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_EVENT ev) {

    if ((ddg->x > ax3 - (TILE_SIZE / 2)) && (ddg->x < ax3 + (TILE_SIZE / 2)) &&
        (ddg->y > ay3 - (TILE_SIZE / 2)) && (ddg->y < ay3 + (TILE_SIZE / 2))) {
        mode = 7;
        return;
    }

    bool redraw = true;


    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage3_by_time(ddg, s);
        redraw = true; 
    }


    if (ev.type != ALLEGRO_EVENT_TIMER) {
        
        update_stage3(ddg, s->map);

        redraw = true;

    }

    if (redraw) {

        render_stage3(s, ddg);

        redraw = false;

    }
}