#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    u8 contestantID;
    u8 judgeContestantID;
    u8 animationDone;
    u8 isSameJudge;
    u8 timer;
    u8 animationDone2;
    ActingMessageParams messageParams;
    u8 actingMessagesID;
} ActingScoreGainTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H
