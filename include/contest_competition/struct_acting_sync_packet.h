#ifndef POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H
#define POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H

#include "contest_competition/struct_acting_performance_order.h"
#include "contest_competition/struct_acting_performance_messages.h"
#include "contest_competition/struct_acting_turn_state.h"

typedef struct {
    u8 contestantID;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04[3][4];
    ActingTurnState unk_10;
    ActingPerformanceMessages unk_C6;
    ActingPerformanceOrder unk_D6_val1;
} ActingSyncPacket;

#endif // POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H
