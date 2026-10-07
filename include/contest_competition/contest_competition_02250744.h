#ifndef POKEPLATINUM_CONTEST_COMPETITION_02250744_H
#define POKEPLATINUM_CONTEST_COMPETITION_02250744_H

#include "contest_competition/struct_contest_competition_0224FCA0.h"
#include "contest_competition/struct_contest_competition_022507C4.h"
#include "contest_competition/struct_contest_competition_022508E4.h"

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

void contest_competition_02250744(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_022507C4(UnkStruct_contest_competition_022507C4 *param0);
void contest_competition_02250968(UnkStruct_contest_competition_0224FCA0 *param0, u32 announcerMessagesID, const UnkStruct_contest_competition_022508E4 *param2);
int contest_competition_0225099C(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_022509AC(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250A84(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250A88(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250AD8(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250B00(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250CEC(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250D24(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250D28(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250D8C(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250DB0(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250EFC(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250F68(UnkStruct_contest_competition_0224FCA0 *param0, NARC *param1);
void contest_competition_02250FBC(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02250FE4(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02251020(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_0225122C(UnkStruct_contest_competition_0224FCA0 *param0, NARC *param1);
void contest_competition_022512E0(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_0225131C(UnkStruct_contest_competition_0224FCA0 *param0, int param1, int param2);
void contest_competition_02251344(UnkStruct_contest_competition_0224FCA0 *param0, NARC *param1);
void contest_competition_022513C0(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_022513F4(UnkStruct_contest_competition_0224FCA0 *param0, int param1, int param2, int param3, int param4);
void contest_competition_02251544(UnkStruct_contest_competition_0224FCA0 *param0);
void contest_competition_02251598(UnkStruct_contest_competition_0224FCA0 *param0, int param1, u8 *param2);
void contest_competition_02251718(UnkStruct_contest_competition_0224FCA0 *param0, int contestantID, int param2, u8 *param3);
void contest_competition_02251930(Contest *param0, int param1, s16 param2[]);
void contest_competition_02251A1C(UnkStruct_contest_competition_0224FCA0 *param0);

#endif // POKEPLATINUM_CONTEST_COMPETITION_02250744_H
