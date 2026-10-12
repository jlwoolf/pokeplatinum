#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_HANDLER_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_HANDLER_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"

typedef struct ContestPacketHandler_t {
    int (*unk_00)(ContestPacketQueue *param0, void *param1, int param2, void *param3);
    void (*unk_04)(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
    void (*unk_08)(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
} ContestPacketHandler;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_HANDLER_H
