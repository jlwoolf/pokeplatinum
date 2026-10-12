#ifndef POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H

#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    struct DanceCompetition_t *competition;
    SysTask *task;
    u16 beat;
    u8 state;
    u8 flag;
} DanceBeatTask;

#endif // POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H
