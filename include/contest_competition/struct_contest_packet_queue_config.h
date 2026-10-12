#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H

#include "contest_competition/struct_contest_packet_handler.h"

typedef struct {
    const struct ContestPacketHandler_t *handlers;
    u16 handlerCount;
    u8 playerContestantID;
    u8 isLinkContest;
    u8 selfContestantID;
} ContestPacketQueueConfig;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H
