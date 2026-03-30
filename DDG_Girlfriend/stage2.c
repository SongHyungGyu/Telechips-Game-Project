#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"
#include "for_flower.h"
#include "LIB_hud.h"
#define FLOWER_TOT 3

static void initStage2Map(Map* m) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            m->tiles[i][j].x = j * TILE_SIZE;
            m->tiles[i][j].y = i * TILE_SIZE;
            m->tiles[i][j].w = TILE_SIZE;
            m->tiles[i][j].h = TILE_SIZE;
            if (i == 0 || i == tile_h_num - 1 || j == 0 || j == tile_w_num - 1) {
                m->tiles[i][j].type = WALL; // ��
            }
            else if (j == 5 || j == 6 || j == 13 || j == 14) {
                m->tiles[i][j].type = MARSH; // ������
            }
            else {
                m->tiles[i][j].type = ROAD; // ��
            }
        }
    }
}


Stage* init_stage2() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    s->initMap = initStage2Map;
    //4마리의 지렁이 초기화
    s->wormNum = 4;
	s->worms = (worm**)malloc(sizeof(worm*) * s->wormNum);

	s->worms[0] = init_worm(100, 100, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, +1);
    s->worms[1] = init_worm(1000, 300, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, -1);
    s->worms[2] = init_worm(100, 500, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, +1);
    s->worms[3] = init_worm(1000, 700, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, -1);


    s->sx = sx2;
    s->sy = sy2;
    
    s->flowers = (flower**)malloc(sizeof(flower*) * 3);
    s->flowers[0] = init_flower(300, 300);
    s->flowers[1] = init_flower(500, 500);
    s->flowers[2] = init_flower(700, 200);

    s->flower_cnt = FLOWER_TOT;
    init_stage(s);

    return s;
}

static void update_stage2(DDG* ddg, Map m) {
    update_ddg(ddg, m);
}
static void update_stage2_by_time(DDG * ddg, Stage* s) {
    for (int i = 0; i < FLOWER_TOT; i++) {
        update_flower(s->flowers[i], ddg, s);
    }
    for (int i = 0; i < s->wormNum; i++) {
        update_worm(s->worms[i]);
    }
    if(col_worms(ddg, s->wormNum, s->worms)){   
        update_ddg_after_attack(ddg, s);
    }
}

static void render_stage2(Stage* s, DDG * ddg, HEART* heart, SYSTEM* sys) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0);
    //ddg 렌더
    render_ddg(ddg);
    for (int i = 0; i < FLOWER_TOT; i++) {
        render_flower(s->flowers[i]);
    }

    //worm 렌더
    for (int i = 0; i < s->wormNum; i++) {
        render_worm(s->worms[i]);
    }
     // heart 렌더
	render_hud(heart, ddg);
    render_play_time(sys);

    al_flip_display();
}



void run_stage2(DDG* ddg, Stage * s, HEART* heart, SYSTEM* sys, ALLEGRO_EVENT ev){

    if ((ddg->x > ax2 - (TILE_SIZE / 2)) && (ddg->x < ax2 + (TILE_SIZE / 2)) &&
        (ddg->y > ay2 - (TILE_SIZE / 2)) && (ddg->y < ay2 + (TILE_SIZE / 2))) {
        mode = 6;
        return;
    }

    bool redraw = true;

      //타이머 이벤트인 경우에 실행
    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage2_by_time(ddg , s);
        update_stage2(ddg, s->map);
        //if (s->flower_cnt == 0) {
        //mode = 3;
        //}
        redraw = true;
		play_time++;
    }


    if (ev.type != ALLEGRO_EVENT_TIMER) {

        //update_stage2(ddg, s->map);

        //redraw = true;

    }

    if (redraw) {

        render_stage2(s, ddg, heart, sys);

        redraw = false;

    }

}