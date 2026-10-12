#ifndef POKEPLATINUM_CONTEST_COMM_TASKS_H
#define POKEPLATINUM_CONTEST_COMM_TASKS_H

#include "struct_defs/struct_020954F0.h"

#include "field_events/struct_contest_opponent_data.h"
#include "field_events/struct_contestant_summary.h"

#include "contest.h"
#include "pokemon.h"
#include "string_gf.h"

void ContestCommTask_RecvLeaderElection(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendLeaderElection(Contest *param0);
void ContestCommTask_RecvContestantMon(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendContestantMon(Contest *param0, int param1, const Pokemon *param2);
void ContestCommTask_RecvAllContestantMons(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendAllContestantMons(Contest *param0, Pokemon **param1);
void ContestCommTask_RecvOpponentData(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendOpponentData(Contest *param0, int param1, const ContestOpponentData *param2);
void ContestCommTask_RecvJudges(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendJudges(Contest *param0, int param1, const ContestJudge *param2);
void ContestCommTask_RecvTrainerName(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendTrainerName(Contest *param0, int param1, const String *param2);
void ContestCommTask_RecvChatotCry(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendChatotCry(Contest *param0, int param1, void *param2);
void ContestCommTask_RecvContestantSummary(int param0, int param1, void *param2, void *param3);
BOOL ContestCommTask_SendContestantSummary(Contest *param0, int param1, const ContestantSummary *param2);

#endif // POKEPLATINUM_CONTEST_COMM_TASKS_H
