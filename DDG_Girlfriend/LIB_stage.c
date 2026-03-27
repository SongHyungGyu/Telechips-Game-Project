#include "LIB_DDG.h"
#include "LIB_stage.h"
void init_stage(Stage* s) {
    s->roadTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/road.png");
    must_init(s->roadTile, "roadTile image");
    s->marshTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/marsh.png");
    must_init(s->marshTile, "marshTile image");
    s->wallTile = al_load_bitmap("C:/Telechips4/GameProjectPractice/x64/Debug/wall.png");
    must_init(s->wallTile, "wallTile image");


    s->initMap(&s->map);

    s->mapCache = al_create_bitmap(tile_w_num * TILE_SIZE, tile_h_num * TILE_SIZE);
    al_set_target_bitmap(s->mapCache);  // "종이"에 그리기 모드
    renderMap(s);                     // 300장 그리기 (단 1회)
    al_set_target_backbuffer(al_get_current_display()); // 다시 화면에 그리기 모드
}

void renderMap(Stage* s) {
	printf("rendering map...\n");
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
