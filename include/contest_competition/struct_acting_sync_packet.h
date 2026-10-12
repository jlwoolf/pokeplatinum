#ifndef POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H
#define POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H

#include "contest_competition/struct_acting_performance_order.h"
#include "contest_competition/struct_acting_performance_messages.h"
#include "contest_competition/struct_acting_turn_state.h"

typedef struct {
    u8 contestantID;
    u8 contestantCount;
    u8 judgeContestantID;
    u8 isSameJudge;
    u8 judgeOrder[3][4];
    ActingTurnState turnState;
    ActingPerformanceMessages messages;
    ActingPerformanceOrder performanceOrder;
} ActingSyncPacket;

#endif // POKEPLATINUM_STRUCT_ACTING_SYNC_PACKET_H
