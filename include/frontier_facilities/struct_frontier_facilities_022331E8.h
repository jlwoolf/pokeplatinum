#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H

#include "sys_task_manager.h"

// State for the GX window reveal SysTask: the task handle, window bounds,
// delay and step counters.
typedef struct {
    SysTask *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s8 unk_0A;
    u8 unk_0B;
} FrontierFacilitiesWindowEffectState;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_022331E8_H
