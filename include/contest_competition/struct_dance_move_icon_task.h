#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    SysTask *task;
    ManagedSprite *sprite;
    struct DanceCompetition_t *competition;
    DancePhotoSprite *photoSprite;
    u8 unused_10;
    u8 contestantID;
    u8 state;
    u8 index;
    s8 yOffset;
} DanceMoveIconTask;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_ICON_TASK_H
