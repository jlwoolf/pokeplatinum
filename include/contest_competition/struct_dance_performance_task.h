#ifndef POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    DanceMoveState unk_10;
    u8 unk_45;
} DancePerformanceTask;

#endif // POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_TASK_H
