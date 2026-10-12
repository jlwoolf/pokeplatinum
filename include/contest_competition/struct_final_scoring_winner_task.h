#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_WINNER_TASK_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_WINNER_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring.h"

typedef struct {
    ContestFinalScoring *finalScoring;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 winningContestantID;
    u8 animationDone;
    u8 animationDone2;
    s16 timer;
} FinalScoringWinnerTask;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_WINNER_TASK_H
