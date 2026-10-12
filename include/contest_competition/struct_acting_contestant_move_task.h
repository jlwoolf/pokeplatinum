#ifndef POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    s32 moveID;
    s32 timer;
    u8 state;
    u8 contestantID;
    u8 messageState;
    s16 contestMoveEffect;
} ActingContestantMoveTask;

#endif // POKEPLATINUM_STRUCT_ACTING_CONTESTANT_MOVE_TASK_H
