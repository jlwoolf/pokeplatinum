#ifndef POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    s32 unk_0C;
    s32 unk_10;
    u8 unk_14;
    u8 contestantID;
    u8 unk_16;
    s16 unk_18;
} ActingContestantMoveTask;

#endif // POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H
