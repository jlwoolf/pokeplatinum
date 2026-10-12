#ifndef POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H

#include "contest_competition/struct_contest_text_label.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *sprite;
    ContestTextLabel *textLabel;
    SysTask *task;
    s32 frame;
    u8 state;
} DanceSpriteTask;

#endif // POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H
