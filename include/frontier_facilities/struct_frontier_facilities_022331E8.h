#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H

#include "sys_task_manager.h"

// State for the GX window reveal SysTask: the task handle, window bounds,
// delay and step counters.
typedef struct {
    SysTask *task;
    u8 windowX1;
    u8 windowY1;
    u8 windowX2;
    u8 windowY2;
    s16 delay;
    s8 showWindow;
    u8 unk_0B;
} FrontierFacilitiesWindowEffectState;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H
