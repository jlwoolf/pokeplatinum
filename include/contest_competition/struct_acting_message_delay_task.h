#ifndef POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 timer;
    ActingMessageParams messageParams;
    u8 actingMessagesID;
    u8 delay;
    u8 messageFlag;
} ActingMessageDelayTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H
