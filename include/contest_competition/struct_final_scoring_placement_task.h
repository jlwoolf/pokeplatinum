#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_PLACEMENT_TASK_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_PLACEMENT_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring.h"

typedef struct {
    ContestFinalScoring *finalScoring;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    s16 timer;
    s16 placements[4];
    s16 scores[4];
} FinalScoringPlacementTask;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_PLACEMENT_TASK_H
