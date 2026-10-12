#ifndef POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H
#define POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H

#include "contest_competition/struct_acting_message_params.h"

typedef struct {
    ActingMessageParams messageParams;
    ActingMessageParams messageParams2;
    u8 actingMessagesID;
    u8 actingMessagesID2;
    u8 delay;
    u8 messageFlag;
} ActingPerformanceMessages;

#endif // POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_MESSAGES_H
