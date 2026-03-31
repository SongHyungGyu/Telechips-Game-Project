#include "LIB_DDG.h"
#include "LIB_stage.h"

//디버깅용
static void printMap(Stage* s) {
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            printf("%d ", s->map.tiles[i][j].type);
        }
        printf("\n");
    }
}

void renderMap(Stage* s) {
    //printMap(s);
    for (int i = 0; i < tile_h_num; i++) {
        for (int j = 0; j < tile_w_num; j++) {
            tile* t = &s->map.tiles[i][j];
            ALLEGRO_BITMAP* target = (t->type == WALL) ? s->wallTile : 
				(t->type == MARSH) ? s->marshTile : s->roadTile;
            if (target != NULL) {
                al_draw_scaled_bitmap(target,
                    0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target),
                    t->x, t->y, t->w, t->h, 0);
            }
        }
    }
}

void init_stage(Stage* s) {
    s->roadTile = al_load_bitmap(PATH  "road.png");
    must_init(s->roadTile, "roadTile image");
    s->marshTile = al_load_bitmap(PATH "marsh.png");
    must_init(s->marshTile, "marshTile image");
    s->wallTile = al_load_bitmap(PATH "wall.png");
    must_init(s->wallTile, "wallTile image");

    s->initMap(&s->map);

    s->mapCache = al_create_bitmap(tile_w_num * TILE_SIZE, tile_h_num * TILE_SIZE);

    al_set_target_bitmap(s->mapCache);
    renderMap(s);
    al_set_target_backbuffer(al_get_current_display());
}

void set_stage1(DDG* ddg, Stage* s) {
	
    //각 stage 요소들도 초기화
    //매개변수로 Stage * s받으면 될듯
    //지렁이들...꽃...대포지렁이...
    //생명도 3으로 초기화
    //ddg 이미지도 각 스테이지의 시작 이미지로 초기화
    ddg->x = sx1;
    ddg->y = sy1;
    ddg->life = 3;
    play_time = 0;
    ddg->hit_time = 0;
    play_stream(s->bgm);
    mode = MODE_STAGE1;
}
void set_stage2(DDG* ddg, Stage* s) {
    ddg->x = sx2;
    ddg->y = sy2;
    ddg->life = 3;
    for (int i = 0; i < FLOWER_TOT2; i++) {
        s->flowers[i]->used = 0;
    }
    s->flower_cnt = FLOWER_TOT2;
    play_stream(s->bgm);
    mode = MODE_STAGE2;
}
void set_stage3(DDG* ddg, Stage* s) {
    ddg->x = sx3;
    ddg->y = sy3;
    ddg->life = 3;
    for (int i = 0; i < FLOWER_TOT3; i++) {
        s->flowers[i]->used = 0;
    }
    s->flower_cnt = FLOWER_TOT3;
    play_stream(s->bgm);
    mode = MODE_STAGE3;
}

void after_stage(Stage* s, GameMode toGo) {
    if (s->bgm) detach_stream(s->bgm);
    mode = toGo;
}

void render_play_time(SYSTEM* sys) {
    char c_play_time[20] = "";
    int seconds = play_time / 60;
    int minutes = seconds / 60;
    sprintf(c_play_time, "%02d:%02d", minutes, seconds % 60);

    al_draw_text(sys->font, al_map_rgb(255, 255, 255), DISP_W / 2, TILE_SIZE/2,
        ALLEGRO_ALIGN_CENTER, c_play_time);
}

void render_h(SYSTEM* sys, int play_time) {

    if ((play_time / 30) % 2 == 0) {
        ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

        al_draw_text(sys->font, white, 20, 20, ALLEGRO_ALIGN_LEFT, ">> ESC: Back to first <<");
    }
}

void render_ending()
{
    ALLEGRO_BITMAP* ending_img = al_load_bitmap("resource/img/ending.png");
    if (!ending_img) return;

    ALLEGRO_SAMPLE* ending_bgm = al_load_sample("resource/aud/ending.mp3");
    if (!ending_bgm) {
        al_destroy_bitmap(ending_img);
        return;
    }

    ALLEGRO_SAMPLE_ID bgm_id;
    al_play_sample(ending_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &bgm_id);

    double start_time = al_get_time();

    while (al_get_time() - start_time < 10.0)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(ending_img, 90, 0, 0);
        al_flip_display();

        al_rest(1.0 / 60.0);  // CPU 점유율 완화
    }
    al_stop_sample(&bgm_id);

    al_destroy_sample(ending_bgm);
    al_destroy_bitmap(ending_img);
}