
#ifndef __LIB_STAGE__
#define __LIB_STAGE__
#define tile_width 60
#define tile_w_num 20
#define tile_h_num 15

typedef struct {
    int x;
    int y;
    int w;
    int h;
	int type; //0: º®, 1: ±æ, 2: ´Ë
} tile;

typedef struct {
    tile tiles[tile_h_num][tile_w_num];
} Map;

typedef struct {
    Map map;

    ALLEGRO_BITMAP* roadTile;
    ALLEGRO_BITMAP* wallTile;
    ALLEGRO_BITMAP* marshTile; 

} Stage;
#endif