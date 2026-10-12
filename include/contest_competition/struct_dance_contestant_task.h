#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H

#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_packet.h"

#include "sys_task_manager.h"

typedef struct {
    SysTask *task;
    DanceCompetition *competition;
    DancePacket packet;
    u8 state;
    u8 flag;
} DanceContestantTask;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H
