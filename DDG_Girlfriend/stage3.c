#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "for_ddg.h"
#include "for_worm.h"
#include "LIB_shot.h"
#include "for_user.h"
#include "for_flower.h"
#include <allegro5/allegro_primitives.h>

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
	s->stage = 3;
    s->initMap = initStage3Map;
    //10마리의 지렁이 초기화
    s->wormNum = 10;
	s->worms = (worm**)malloc(sizeof(worm*) * s->wormNum);

	s->worms[0] = init_worm(TILE_SIZE, TILE_SIZE*4, 0, 0, TILE_SIZE*10, TILE_SIZE*4, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[1] = init_worm(TILE_SIZE*2+10, TILE_SIZE*10, 0, 0, TILE_SIZE*10, TILE_SIZE*4, VERTICAL, WORM_SPEED_STAGE3, -1);
    s->worms[2] = init_worm(TILE_SIZE, TILE_SIZE*12, TILE_SIZE, TILE_SIZE*9, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, +1);
    s->worms[3] = init_worm(TILE_SIZE*9, TILE_SIZE*13+10, TILE_SIZE, TILE_SIZE*9, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, -1);
    s->worms[4] = init_worm(TILE_SIZE*9, TILE_SIZE*5, 0, 0, TILE_SIZE*10, TILE_SIZE*5, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[5] = init_worm(TILE_SIZE*10, TILE_SIZE*10, 0, 0, TILE_SIZE*10, TILE_SIZE*5, VERTICAL, WORM_SPEED_STAGE3, -1);
    s->worms[6] = init_worm(TILE_SIZE*9, TILE_SIZE*2, TILE_SIZE*9, TILE_SIZE*16, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, +1);
    s->worms[7] = init_worm(TILE_SIZE*16, TILE_SIZE*3, TILE_SIZE*9, TILE_SIZE*16, 0, 0, HORIZONTAL, WORM_SPEED_STAGE3, -1);
    s->worms[8] = init_worm(TILE_SIZE*16, TILE_SIZE*5, 0, 0, TILE_SIZE*10, TILE_SIZE*5, VERTICAL, WORM_SPEED_STAGE3, +1);
    s->worms[9] = init_worm(TILE_SIZE*17, TILE_SIZE*10, 0, 0, TILE_SIZE*10, TILE_SIZE*5, VERTICAL, WORM_SPEED_STAGE3, -1);
    
    s->c_worm_count = 3;
    s->c_worms = (C_WORM**)malloc(sizeof(C_WORM*) * s->c_worm_count);

    s->c_worms[0] = init_c_worm(200, 150);
    s->c_worms[1] = init_c_worm(500, 300);
    s->c_worms[2] = init_c_worm(800, 450);

    s->flowers = (flower**)malloc(sizeof(flower*) * 4);
    s->flowers[0] = init_flower(TILE_SIZE * 1, TILE_SIZE * 13);
    s->flowers[1] = init_flower(TILE_SIZE * 10, TILE_SIZE * 13);
    s->flowers[2] = init_flower(TILE_SIZE * 9, TILE_SIZE * 2);
    s->flowers[3] = init_flower(TILE_SIZE * 17, TILE_SIZE * 2);
    s->flower_cnt = FLOWER_TOT3;

    s->sx = sx3;
    s->sy = sy3;

    s->bgm = load_stream(AUDIOPATH "thirdBGM.mp3");
    if (!s->bgm) printf("thirdBGM load failed\n");

    s->ddg_girl = load_image(PATH "ddg_girl.png");
    
    init_stage(s);
    
    return s;
}

static void render_stage3(Stage* s, DDG* ddg, SYSTEM* sys) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(s->mapCache, 0, 0, 0);
    al_draw_scaled_bitmap(s->ddg_girl, 0, 0, 400, 400,
        ax3, ay3, TILE_SIZE, TILE_SIZE, 0);
  
    for (int i = 0; i < s->c_worm_count; i++) {
        if (s->c_worms[i] != NULL) {
            render_c_worm(s->c_worms[i]);
        }
    }
    for (int i = 0; i < FLOWER_TOT3; i++) {
        render_flower(s->flowers[i]);
    }
    //ddg 렌더
    render_ddg(ddg);
    //worm 렌더
    for (int i = 0; i < s->wormNum; i++) {
        render_worm(s->worms[i]);
    }



    render_play_time(sys);
    render_h(sys, play_time);
    render_hud(ddg);
    al_flip_display();
}

bool col_c_worm_shots(DDG* ddg, Stage* s) {
    for (int i = 0; i < s->c_worm_count; i++) {
        if (s->c_worms[i] == NULL)
            continue;

        if (shots_collide_player(
            s->c_worms[i]->shots,
            ddg->x,
            ddg->y,
            ddg_size,
            ddg_size
        )) {
            return true;
        }
    }

    return false;
}

static void update_stage3_by_time(DDG * ddg, Stage* s, User * user) {
    for (int i = 0; i < s->wormNum; i++) {
        update_worm(s->worms[i]);
    }

    for (int i = 0; i < s->c_worm_count; i++) {
        if (s->c_worms[i] != NULL) {
            update_c_worm(s->c_worms[i]);
        }
    }

    for (int i = 0; i < FLOWER_TOT3; i++) {
        update_flower(s->flowers[i], ddg, s);
    }
    if(col_worms(ddg, s->wormNum, s->worms) || col_c_worm_shots(ddg, s)){
        if (ddg->wormSound) {
            al_play_sample(ddg->wormSound, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        update_ddg_after_attack(ddg, s , user);
    }
    update_ddg(ddg, s);
}

void run_stage3(User * user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev) {

    if ((ddg->x > ax3 - (TILE_SIZE / 2)) && (ddg->x < ax3 + (TILE_SIZE / 2)) &&
        (ddg->y > ay3 - (TILE_SIZE / 2)) && (ddg->y < ay3 + (TILE_SIZE / 2)) &&
        (s->flower_cnt == 0)) {
        set_User(user, NULL, 3, play_time / 60);
        save_User(user);
        after_stage(s, MODE_FIRST_PAGE);
        render_ending();
       
        return;
    }

    bool redraw = false;

    if (ev.type == ALLEGRO_EVENT_TIMER) { 
        update_stage3_by_time(ddg ,s ,user);
        redraw = true; 
        play_time++;
    }

    if (redraw) {

        render_stage3(s, ddg, sys);

        redraw = false;

    }
}


