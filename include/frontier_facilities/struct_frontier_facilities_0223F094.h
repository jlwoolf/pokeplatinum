#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F094_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F094_H

#include "screen_scroll_manager.h"
#include "sys_task_manager.h"

// State for the screen-scroll SysTask wrapping a ScreenScrollManager.
typedef struct {
    ScreenScrollManager *screenScrollMgr;
    SysTask *unk_04;
    u32 unk_08;
} FrontierFacilitiesScreenScroll;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F094_H
