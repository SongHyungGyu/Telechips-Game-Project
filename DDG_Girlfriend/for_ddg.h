#ifndef __FOR_DDG_H__
#define __FOR_DDG_H__

#include "LIB_stage.h"
#include "LIB_DDG.h"

DDG* init_ddg();
void update_ddg(DDG* ddg, Map m);
void render_ddg(DDG* ddg);
bool col_wall(int nx, int ny, Map m);
bool col_marsh(int nx, int ny, Map m);
void update_ddg_after_attack(DDG* ddg, Stage * s);

#endif