#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"
#include "LIB_hud.h"

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


Stage* init_stage1() {
    Stage* s = (Stage*)malloc(sizeof(Stage));
    //각 stage마다 맵 배열 다르고 시작 위치 달라서 얘네만 여기서 일케 함
    s->initMap = initStage1Map;

    //4마리의 지렁이 초기화
	s->worms = (worm**)malloc(sizeof(worm*) * 4);

	s->worms[0] = init_worm(100, 100, 100, 100, 1000, 100, 0, 0, 0, 0, HORIZONTAL, 5, +1);
    s->worms[1] = init_worm(1000, 300, 100, 300, 1000, 300, 0, 0, 0, 0, HORIZONTAL, 5, -1);
    s->worms[2] = init_worm(100, 500, 100, 500, 1000, 500, 0, 0, 0, 0, HORIZONTAL, 5, +1);
    s->worms[3] = init_worm(1000, 700, 100, 700, 1000, 700, 0, 0, 0, 0, HORIZONTAL, 5, -1);

    s->sx = 0;
    s ->sy = 0;

    //나머지 초기화는 똑같기 때문에 공용함수 사용
    init_stage(s);
    return s;
}

static void render_stage1(Stage* s, DDG * ddg, HEART* heart, SYSTEM* sys) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안M
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //지도 이미 그려놓은거 출력
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    //ddg 렌더
    render_ddg(ddg);
	//worm 렌더
    for (int i = 0; i < 4; i++) {
        render_worm(s->worms[i]);
    }
    // heart 렌더
	render_hud(heart, ddg);
    render_play_time(sys);
   
    al_flip_display();
}



//상태 업데이트
static void update_stage1( DDG * ddg, Map m) {
   update_ddg(ddg ,m);
}
static void update_stage1_by_time(Stage* s) {
    for (int i = 0; i < 4; i++) {
        update_worm(s->worms[i]);
    }
}

void run_stage1(DDG* ddg, Stage * s, HEART* heart, SYSTEM* sys, ALLEGRO_EVENT ev) {
    
    // 도착 지점
    if ((ddg->x > ax1 - (TILE_SIZE/2)) && (ddg->x < ax1 + (TILE_SIZE / 2)) &&
        (ddg->y > ay1 - (TILE_SIZE / 2)) && (ddg->y < ay1 + (TILE_SIZE / 2))) {
        mode = 5;
        return;
    }

    bool redraw = true;
    
            
    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage1_by_time(s);
        update_stage1(ddg, s->map);
        redraw = true;
		play_time++;
    }

            
    if (ev.type != ALLEGRO_EVENT_TIMER) {
                
        //update_stage1(ddg, s->map);
  
        //redraw = true;
            
    }
            
    if (redraw) {
                
        render_stage1(s, ddg, heart, sys);
                
        redraw = false;
            
    }
}