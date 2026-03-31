#ifndef __FOR_DDG_H__
#define __FOR_DDG_H__

#include "LIB_stage.h"
#include "LIB_DDG.h"
#include "for_user.h"

DDG* init_ddg();
Chaser* init_chaser(int start_x, int start_y);
void update_ddg(DDG* ddg, Map m);
void update_chaser(Chaser* chaser, DDG* ddg, Map m);
void render_ddg(DDG* ddg);
void render_chaser(Chaser* chaser);
bool check_collision_with_chaser(DDG* ddg, Chaser* chaser);
bool col_wall(int nx, int ny, Map m);
bool col_marsh(int nx, int ny, Map m);
void update_ddg_after_attack(DDG* ddg, Stage * s, User * user);

#endif