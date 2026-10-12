#ifndef POKEPLATINUM_STRUCT_DANCE_SCORE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_SCORE_TASK_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    SysTask *task;
    ManagedSprite *sprite;
    s32 unused_08;
    s32 unused_0C;
    s32 unused_10;
    s32 unused_14;
    u16 unused_18;
} DanceScoreTask;

#endif // POKEPLATINUM_STRUCT_DANCE_SCORE_TASK_H
