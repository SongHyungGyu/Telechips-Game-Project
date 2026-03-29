#ifndef __LIB_HUD_H__
#define __LIB_HUD_H__

#include "LIB_stage.h"

HEART* hud_init();
void update_hud(HEART* heart);
void render_hud(HEART* heart, DDG* ddg);

#endif