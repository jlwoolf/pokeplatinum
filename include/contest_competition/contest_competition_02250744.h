#ifndef POKEPLATINUM_CONTEST_COMPETITION_02250744_H
#define POKEPLATINUM_CONTEST_COMPETITION_02250744_H

#include "contest_competition/struct_contest_final_scoring.h"
#include "contest_competition/struct_contest_final_scoring_scene.h"
#include "contest_competition/struct_final_scoring_message_args.h"

#include "contest.h"
#include "narc.h"

enum ContestAnnouncerMessagesIDs {
    CONTEST_ANNOUNCER_MESSAGE_NONE,
    CONTEST_ANNOUNCER_MESSAGE_JUDGING_COMPLETED,
    CONTEST_ANNOUNCER_MESSAGE_VISUAL_COMPETITION_RESULTS,
    CONTEST_ANNOUNCER_MESSAGE_DANCE_COMPETITION_RESULTS,
    CONTEST_ANNOUNCER_MESSAGE_ACTING_COMPETITION_RESULTS,
    CONTEST_ANNOUNCER_MESSAGE_WINNER_IS,
    CONTEST_ANNOUNCER_MESSAGE_INDIVIDUAL_CATEGORIES
};

void contest_competition_02250744(ContestFinalScoring *param0);
void contest_competition_022507C4(ContestFinalScoringScene *param0);
void contest_competition_02250968(ContestFinalScoring *param0, u32 announcerMessagesID, const FinalScoringMessageArgs *param2);
int contest_competition_0225099C(ContestFinalScoring *param0);
void contest_competition_022509AC(ContestFinalScoring *param0);
void contest_competition_02250A84(ContestFinalScoring *param0);
void contest_competition_02250A88(ContestFinalScoring *param0);
void contest_competition_02250AD8(ContestFinalScoring *param0);
void contest_competition_02250B00(ContestFinalScoring *param0);
void contest_competition_02250CEC(ContestFinalScoring *param0);
void contest_competition_02250D24(ContestFinalScoring *param0);
void contest_competition_02250D28(ContestFinalScoring *param0);
void contest_competition_02250D8C(ContestFinalScoring *param0);
void contest_competition_02250DB0(ContestFinalScoring *param0);
void contest_competition_02250EFC(ContestFinalScoring *param0);
void contest_competition_02250F68(ContestFinalScoring *param0, NARC *param1);
void contest_competition_02250FBC(ContestFinalScoring *param0);
void contest_competition_02250FE4(ContestFinalScoring *param0);
void contest_competition_02251020(ContestFinalScoring *param0);
void contest_competition_0225122C(ContestFinalScoring *param0, NARC *param1);
void contest_competition_022512E0(ContestFinalScoring *param0);
void contest_competition_0225131C(ContestFinalScoring *param0, int param1, int param2);
void contest_competition_02251344(ContestFinalScoring *param0, NARC *param1);
void contest_competition_022513C0(ContestFinalScoring *param0);
void contest_competition_022513F4(ContestFinalScoring *param0, int param1, int param2, int param3, int param4);
void contest_competition_02251544(ContestFinalScoring *param0);
void contest_competition_02251598(ContestFinalScoring *param0, int param1, u8 *param2);
void contest_competition_02251718(ContestFinalScoring *param0, int contestantID, int param2, u8 *param3);
void contest_competition_02251930(Contest *param0, int param1, s16 param2[]);
void contest_competition_02251A1C(ContestFinalScoring *param0);

#endif // POKEPLATINUM_CONTEST_COMPETITION_02250744_H
