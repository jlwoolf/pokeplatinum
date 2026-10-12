#ifndef POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 contestantID;
    u8 unk_12;
    ActingMessageParams unk_14;
    u8 actingMessagesID;
    u8 unk_1B;
    u8 unk_1C;
} ActingMessageDelayTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MESSAGE_DELAY_TASK_H
