#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    SysTask *unk_00;
    ManagedSprite *unk_04;
    struct DanceCompetition_t *unk_08;
    DancePhotoSprite *unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    s8 unk_14;
} DanceMoveIconTask;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H
