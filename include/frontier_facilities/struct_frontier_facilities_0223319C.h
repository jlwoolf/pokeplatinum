#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H

#include "sys_task_manager.h"

// State for the object shake/oscillation SysTask: the task handle, two
// alternating offsets, and the interval/cycle counters.
typedef struct {
    SysTask *unk_00;
    s16 unk_04;
    s16 unk_06;
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    u8 unk_0B;
} FrontierFacilitiesShakeState;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H
