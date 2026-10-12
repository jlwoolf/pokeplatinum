#ifndef POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H
#define POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H

#include "contest_competition/struct_acting_message_params.h"

typedef struct {
    ActingMessageParams unk_00;
    ActingMessageParams unk_06;
    u8 actingMessagesID;
    u8 actingMessagesID2;
    u8 unk_0E;
    u8 unk_0F;
} ActingPerformanceMessages;

#endif // POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H
