#include "LIB_stage.h"

tile map[15][20];


void loadMap(int blueprint[15][20]) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 20; j++) {
            map[i][j].x = j * TILE_SIZE;
            map[i][j].y = i * TILE_SIZE;
            map[i][j].type = blueprint[i][j];
        }
    }
}

void renderMap(ALLEGRO_BITMAP* roadTile, ALLEGRO_BITMAP* wallTile) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 20; j++) {
            ALLEGRO_BITMAP* target;

            if (map[i][j].type == 1) {
                target = wallTile;
            }
            else {
                target = roadTile;
            }

            if (target != NULL) {
                al_draw_scaled_bitmap(target,
                    0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target), 
                    map[i][j].x, map[i][j].y, TILE_SIZE, TILE_SIZE, 
                    0);
            }
        }
    }
}