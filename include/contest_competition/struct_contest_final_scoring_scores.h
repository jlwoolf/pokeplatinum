#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H

#include "constants/contests.h"

#include "struct_defs/struct_02095C48_sub1_sub1.h"

typedef struct {
    ContestantResult results[CONTEST_NUM_PARTICIPANTS];
    u8 placementOrder[CONTEST_NUM_PARTICIPANTS];
    u8 unused_34;
    u8 finalPlacements[4];
    s16 visualScores[4];
    s16 danceScores[4];
    s16 actingScores[4];
    s16 totalScores[4];
    s16 visualPercents[4];
    s16 dancePercents[4];
    s16 actingPercents[4];
    s16 unused_72[4];
    s16 finalScores[4];
    s16 visualPoints[4];
    s16 dancePoints[4];
    s16 actingPoints[4];
} ContestFinalScoringScores;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H
