#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"
#include "for_flower.h"
#include "for_user.h"

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
    s->stage = 2;
    s->initMap = initStage2Map;
    //4마리의 지렁이 초기화
    s->wormNum = 4;
	s->worms = (worm**)malloc(sizeof(worm*) * s->wormNum);

	s->worms[0] = init_worm(TILE_SIZE * 2.5, TILE_SIZE * 2.5, WORM_LX_STAGE2, WORM_RX_STAGE2, 
        0, 0, HORIZONTAL, WORM_SPEED_STAGE2, +1);
    s->worms[1] = init_worm(1000, 300, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, -1);
    s->worms[2] = init_worm(100, 500, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, +1);
    s->worms[3] = init_worm(1000, 700, WORM_LX_STAGE2, WORM_RX_STAGE2, 0, 0, HORIZONTAL, WORM_SPEED_STAGE2, -1);


    s->sx = sx2;
    s->sy = sy2;
    
    s->flowers = (flower**)malloc(sizeof(flower*) * 6);
    s->flowers[0] = init_flower(TILE_SIZE * 5, TILE_SIZE * 2);
    s->flowers[1] = init_flower(TILE_SIZE * 6, TILE_SIZE * 7);
    s->flowers[2] = init_flower(TILE_SIZE * 5, TILE_SIZE * 12);
    s->flowers[3] = init_flower(TILE_SIZE * 14, TILE_SIZE * 2);
    s->flowers[4] = init_flower(TILE_SIZE * 13, TILE_SIZE * 7);
    s->flowers[5] = init_flower(TILE_SIZE * 14, TILE_SIZE * 12);

    s->flower_cnt = FLOWER_TOT2;

    s->bgm = load_stream(AUDIOPATH "secondBGM.mp3");
    if (!s->bgm) printf("secondBGM load failed\n");

    s->ddg_girl = load_image(PATH "ddg_girl.png");
    init_stage(s);

    return s;
}

static void update_stage2_by_time(DDG * ddg, Stage* s, User * user) {
    for (int i = 0; i < FLOWER_TOT2; i++) {
        update_flower(s->flowers[i], ddg, s);
    }
    for (int i = 0; i < s->wormNum; i++) {
        update_worm(s->worms[i]);
    }
    if(col_worms(ddg, s->wormNum, s->worms)){   
        if (ddg->wormSound) {
            al_play_sample(ddg->wormSound, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        update_ddg_after_attack(ddg, s, user);
    }
    update_ddg(ddg, s->map);
}

static void render_stage2(Stage* s, DDG * ddg, SYSTEM* sys) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0);
    al_draw_scaled_bitmap(s->ddg_girl, 0, 0, 400, 400,
        ax2, ay2, TILE_SIZE, TILE_SIZE, 0);
    //ddg 렌더
    render_ddg(ddg);
    for (int i = 0; i < FLOWER_TOT2; i++) {
        render_flower(s->flowers[i]);
    }

    //worm 렌더
    for (int i = 0; i < s->wormNum; i++) {
        render_worm(s->worms[i]);
    }
    render_play_time(sys);
    render_h(sys, play_time);
    al_flip_display();
}



void run_stage2(User* user, DDG* ddg, Stage * s, SYSTEM* sys, ALLEGRO_EVENT ev){

    if ((ddg->x > ax2 - (TILE_SIZE / 2)) && (ddg->x < ax2 + (TILE_SIZE / 2)) &&
        (ddg->y > ay2 - (TILE_SIZE / 2)) && (ddg->y < ay2 + (TILE_SIZE / 2)) &&
        (s->flower_cnt == 0)) {
        set_User(user, NULL, 2, play_time / 60);
        if (s->bgm) detach_stream(s->bgm);
        mode = 6;
        return;
    }

    bool redraw = true;

      //타이머 이벤트인 경우에 실행
    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage2_by_time(ddg , s, user);
        redraw = true;
		play_time++;
    }


    if (ev.type != ALLEGRO_EVENT_TIMER) {

        //update_stage2(ddg, s->map);

        //redraw = true;

    }

    if (redraw) {

        render_stage2(s, ddg, sys);

        redraw = false;

    }

}