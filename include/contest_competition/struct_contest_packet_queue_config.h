#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H

#include "contest_competition/struct_contest_packet_handler.h"

typedef struct {
    const struct ContestPacketHandler_t *unk_00;
    u16 unk_04;
    u8 playerContestantID;
    u8 isLinkContest;
    u8 unk_08;
} ContestPacketQueueConfig;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_CONFIG_H
