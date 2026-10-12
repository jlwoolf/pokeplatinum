#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H

#include "constants/contests.h"

#include "struct_defs/struct_02095C48_sub1_sub1.h"

typedef struct {
    ContestantResult unk_00[CONTEST_NUM_PARTICIPANTS];
    u8 unk_30[CONTEST_NUM_PARTICIPANTS];
    u8 unk_34;
    u8 unk_35[4];
    s16 unk_3A[4];
    s16 unk_42[4];
    s16 unk_4A[4];
    s16 unk_52[4];
    s16 unk_5A[4];
    s16 unk_62[4];
    s16 unk_6A[4];
    s16 unk_72[4];
    s16 unk_7A[4];
    s16 unk_82[4];
    s16 unk_8A[4];
    s16 unk_92[4];
} ContestFinalScoringScores;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCORES_H
