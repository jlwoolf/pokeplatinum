#ifndef POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    u16 messageID;
    u8 timer;
    ActingMessageParams messageParams;
    u8 actingMessagesID;
} ActingMessageTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MESSAGE_TASK_H
