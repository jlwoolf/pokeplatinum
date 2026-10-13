#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H

#include "sys_task_manager.h"

// State for the object shake/oscillation SysTask: the task handle, two
// alternating offsets, and the interval/cycle counters.
typedef struct {
    SysTask *task;
    s16 offsetY;
    s16 offsetX;
    s8 timer;
    s8 interval;
    s8 cyclesRemaining;
    u8 unk_0B;
} FrontierFacilitiesShakeState;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223319C_H
