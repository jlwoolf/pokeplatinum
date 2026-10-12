#ifndef POKEPLATINUM_CONTEST_COMPETITION_0224E930_H
#define POKEPLATINUM_CONTEST_COMPETITION_0224E930_H

#include "contest_competition/struct_dance_contestant_task.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_performance_result.h"
#include "contest_competition/struct_dance_move_definition.h"

void contest_competition_0224E930(DancePerformanceResult *param0, int contestantID, int param2, u32 param3, int param4);
void contest_competition_0224E958(DancePerformanceResult *param0);
void contest_competition_0224E990(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3);
void contest_competition_0224ED8C(int param0, DanceCompetition *param1, DancePerformanceResult *param2, u32 param3, u32 param4, u32 param5, const DanceMoveDefinition *param6, DanceContestantTask *param7);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0224E930_H
