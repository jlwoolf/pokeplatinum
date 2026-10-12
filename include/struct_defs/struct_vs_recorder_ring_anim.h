#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_RING_ANIM_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_RING_ANIM_H

#include "struct_defs/struct_0208B878.h"

#include "sys_task_manager.h"

typedef struct {
    BOOL active;
    int frame;
    VsRecorderRing *ring;
    SysTask *task;
} VsRecorderRingAnim;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_RING_ANIM_H
