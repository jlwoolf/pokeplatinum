#ifndef POKEPLATINUM_STRUCT_DANCE_ROUND_STATE_H
#define POKEPLATINUM_STRUCT_DANCE_ROUND_STATE_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_contestant_task.h"
#include "contest_competition/struct_dance_judge_task.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_dance_performance_result.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u16 unk_14;
    u8 unk_16;
    u8 unk_17;
    DanceMoveState unk_18;
    DanceJudgeTask unk_50;
    DancePerformanceResult unk_58[CONTEST_NUM_PARTICIPANTS];
    DanceContestantTask *unk_140[4];
} DanceRoundState;

#endif // POKEPLATINUM_STRUCT_DANCE_ROUND_STATE_H
