#ifndef POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H

#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    struct DanceCompetition_t *unk_00;
    SysTask *unk_04;
    u16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
} DanceBeatTask;

#endif // POKEPLATINUM_STRUCT_DANCE_BEAT_TASK_H
