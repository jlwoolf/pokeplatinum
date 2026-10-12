#ifndef POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u8 unk_0C;
    u16 unk_0E;
    u8 unk_10;
    ActingMessageParams unk_12;
    u8 actingMessagesID;
} ActingMessageTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H
