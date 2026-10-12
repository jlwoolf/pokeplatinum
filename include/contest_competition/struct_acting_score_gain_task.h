#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u8 unk_0C;
    u8 contestantID;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    ActingMessageParams unk_14;
    u8 actingMessagesID;
} ActingScoreGainTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_GAIN_TASK_H
