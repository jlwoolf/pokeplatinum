#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H

struct ContestPacketHandler_t;

typedef struct {
    const struct ContestPacketHandler_t *handlers;
    u16 handlerCount;
    u8 playerContestantID;
    u8 isLinkContest;
    u8 selfContestantID;
    u32 usedSlots;
    u8 sendBuffer[512];
    u8 receiveBuffers[4][512];
    u8 packetPending;
    u8 receiveReady[4];
    u8 receivedCount;
} ContestPacketQueue;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H
