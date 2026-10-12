#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H

#include "sprite_system.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    SysTask *task;
    ManagedSprite *sprite;
    struct DanceCompetition_t *competition;
    u8 state;
    u8 contestantID;
    s8 unused_0E;
} DanceContestantSlotTask;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SLOT_TASK_H
