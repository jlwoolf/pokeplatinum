#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H

#include "contest_competition/struct_final_scoring_message_args.h"

typedef struct {
    u8 messageType;
    u8 unused_01;
    u8 winningContestantID;
    u8 placements[4];
    u8 competitionType;
    FinalScoringMessageArgs messageArgs;
    u8 announcerMessagesID;
    u8 messageState;
    u8 showCategories;
    u8 categoryState;
} ContestFinalScoringResults;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_RESULTS_H
