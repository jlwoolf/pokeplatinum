#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H

#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_packet.h"

#include "sys_task_manager.h"

typedef struct {
    SysTask *unk_00;
    DanceCompetition *unk_04;
    DancePacket unk_08;
    u8 unk_11;
    u8 unk_12;
} DanceContestantTask;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_TASK_H
