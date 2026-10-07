#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_SCREEN_SCROLL_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_SCREEN_SCROLL_H

#include "screen_scroll_manager.h"
#include "sys_task_manager.h"

typedef struct {
    ScreenScrollManager *screenScrollMgr;
    SysTask *task;
    u32 frameCounter;
} SpearPillarScreenScroll;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_SCREEN_SCROLL_H
