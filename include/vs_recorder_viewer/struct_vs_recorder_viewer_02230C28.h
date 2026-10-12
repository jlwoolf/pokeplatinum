#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02230C28_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02230C28_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *sprites[2];
    SysTask *task;
    fx32 baseX;
    f32 scale;
    s16 xStep;
    s16 targetX;
    s8 direction;
    u8 phase;
    u8 padding_1A[2];
    int tick;
    int angle;
    int stepCount;
    int step;
    int state;
} VsRecorderViewerMenuAnimatedSprite;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02230C28_H
