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
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 flag;
    u16 turn;
    u8 moveIndex;
    u8 beatIndex;
    DanceMoveState moveState;
    DanceJudgeTask judgeTask;
    DancePerformanceResult performanceResults[CONTEST_NUM_PARTICIPANTS];
    DanceContestantTask *contestantTasks[4];
} DanceRoundState;

#endif // POKEPLATINUM_STRUCT_DANCE_ROUND_STATE_H
