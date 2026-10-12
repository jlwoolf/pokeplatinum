#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_dance_contestant_info.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantIDs[4];
    DanceContestantInfo contestantInfo[4];
    DanceMoveState moveState;
} DanceMoveTask;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_TASK_H
