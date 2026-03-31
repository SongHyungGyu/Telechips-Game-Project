#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"
#include "for_user.h"
#include <math.h>

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
	s->stage = 1;
    //각 stage마다 맵 배열 다르고 시작 위치 달라서 얘네만 여기서 일케 함
    s->initMap = initStage1Map;

    s->chaser = init_chaser(800, 800);

    //4마리의 지렁이 초기화
    s->wormNum = 4;
	s->worms = (worm**)malloc(sizeof(worm*) * s->wormNum);

	s->worms[0] = init_worm(TILE_SIZE * 2.5, TILE_SIZE * 2.5, WORM_LX_STAGE1, WORM_RX_STAGE1, 
        0, 0, HORIZONTAL, WORM_SPEED_STAGE1, +1);
    s->worms[1] = init_worm(1000, 300, WORM_LX_STAGE1, WORM_RX_STAGE1, 
        0, 0, HORIZONTAL, WORM_SPEED_STAGE1, -1);
    s->worms[2] = init_worm(100, 500, WORM_LX_STAGE1, WORM_RX_STAGE1, 
        0, 0, HORIZONTAL, WORM_SPEED_STAGE1, +1);
    s->worms[3] = init_worm(1000, 700, WORM_LX_STAGE1, WORM_RX_STAGE1, 
        0, 0, HORIZONTAL, WORM_SPEED_STAGE1, -1);

    s->sx = sx1;
    s ->sy = sy1;

    s->ddg_girl = load_image(PATH "ddg_girl.png");

    s->bgm = load_stream(AUDIOPATH "firstBGM.mp3");
    if (!s->bgm) printf("firstBGM load failed\n");

    //나머지 초기화는 똑같기 때문에 공용함수 사용
    init_stage(s);
    return s;
}

static void render_stage1(Stage* s, DDG * ddg, SYSTEM* sys) {
    //나중에 다른 요소들도 렌더 시키는거 추가될꺼라 공용으로 안M
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //지도 이미 그려놓은거 출력
    al_draw_bitmap(s->mapCache, 0, 0, 0); // 종이 1장만 출력
    //
    al_draw_scaled_bitmap(s -> ddg_girl, 0, 0, 400, 400,
    ax1, ay1, TILE_SIZE, TILE_SIZE, 0);
    //ddg 렌더
    render_ddg(ddg);
	//worm 렌더
    for (int i = 0; i < s->wormNum; i++) {
        render_worm(s->worms[i]);
    }

    render_chaser(s->chaser);
    render_play_time(sys);
    render_h(sys, play_time);
    render_hud(ddg);
    al_flip_display();
}



static void update_stage1_by_time(DDG* ddg, Stage* s, User* user) {
    for (int i = 0; i < s->wormNum; i++) {
        update_worm(s->worms[i]);
    }
    if(col_worms(ddg, s->wormNum, s->worms)){   
        if (ddg->wormSound) {
            al_play_sample(ddg->wormSound, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        update_ddg_after_attack(ddg, s, user);
    }
    
    
    if (check_collision_with_chaser(ddg, s->chaser)) {
        update_ddg_after_attack(ddg, s, user);
        // 플레이어가 시작점으로 갔으니 추적자도 원래 위치로 돌려보냄
        s->chaser->x = 800;
        s->chaser->y = 800;
    }
    update_chaser(s->chaser, ddg, s->map);
    update_ddg(ddg, s);
}

void run_stage1(User * user, DDG* ddg, Stage * s, SYSTEM* sys, ALLEGRO_EVENT ev) {
    
    // 도착 지점
    if ((ddg->x > ax1 - (TILE_SIZE/2)) && (ddg->x < ax1 + (TILE_SIZE / 2)) &&
        (ddg->y > ay1 - (TILE_SIZE / 2)) && (ddg->y < ay1 + (TILE_SIZE / 2))) {
        set_User(user, NULL, 1, play_time / 60);
        after_stage(s, MODE_SET_STAGE2);
        return;
    }

    bool redraw = false;
    
    //타이머 이벤트인 경우에 실행
    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage1_by_time(ddg , s , user);
        redraw = true;
		play_time++;
    }
            
    if (redraw) {
                
        render_stage1(s, ddg, sys);
                
        redraw = false;
            
    }
}