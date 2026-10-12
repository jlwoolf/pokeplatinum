#ifndef POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H

#include "contest_competition/struct_contest_text_label.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *unk_00;
    ContestTextLabel *unk_04;
    SysTask *unk_08;
    s32 unk_0C;
    u8 unk_10;
} DanceSpriteTask;

#endif // POKEPLATINUM_STRUCT_DANCE_SPRITE_TASK_H
