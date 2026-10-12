#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_SCORE_REVEAL_TASK_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_SCORE_REVEAL_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring.h"

typedef struct {
    ContestFinalScoring *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11[4];
    u8 unk_15;
    s16 unk_16;
} FinalScoringScoreRevealTask;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_SCORE_REVEAL_TASK_H
