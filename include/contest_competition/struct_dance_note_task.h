#ifndef POKEPLATINUM_STRUCT_DANCE_NOTE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_NOTE_TASK_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    SysTask *task;
    ManagedSprite *sprite;
    s32 x;
    s32 y;
    s32 velocityX;
    s32 velocityY;
    u16 frame;
} DanceNoteTask;

#endif // POKEPLATINUM_STRUCT_DANCE_NOTE_TASK_H
