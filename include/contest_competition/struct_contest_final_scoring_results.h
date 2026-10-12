#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H

#include "contest_competition/struct_final_scoring_message_args.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 winningContestantID;
    u8 unk_03[4];
    u8 unk_07;
    FinalScoringMessageArgs unk_08;
    u8 announcerMessagesID;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
} ContestFinalScoringResults;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H
