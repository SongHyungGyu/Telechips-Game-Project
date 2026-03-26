#ifndef LIB_STAGE_H
#define LIB_STAGE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define TILE_SIZE 60  
  

typedef struct {
    int x, y;         // 화면상의 출력 좌표
    int type;         // 0: 길, 1: 벽 
} tile;


extern tile map[15][20];


void loadMap(int blueprint[15][20]);
void renderMap(ALLEGRO_BITMAP* roadTile, ALLEGRO_BITMAP* wallTile);

#endif