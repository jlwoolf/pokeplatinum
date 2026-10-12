#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SCORE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SCORE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    DanceMoveState moveState;
    u32 score;
    u8 state;
} DanceContestantScoreTask;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SCORE_TASK_H
