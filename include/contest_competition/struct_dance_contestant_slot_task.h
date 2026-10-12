#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H

#include "sprite_system.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    SysTask *unk_00;
    ManagedSprite *unk_04;
    struct DanceCompetition_t *unk_08;
    u8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
} DanceContestantSlotTask;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H
