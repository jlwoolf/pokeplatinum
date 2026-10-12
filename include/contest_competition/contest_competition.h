#ifndef POKEPLATINUM_CONTEST_COMPETITION_H
#define POKEPLATINUM_CONTEST_COMPETITION_H

#include "contest_competition/struct_acting_competition.h"

#include "overlay_manager.h"

int ActingCompetition_Init(ApplicationManager *appMan, int *param1);
int ActingCompetition_Main(ApplicationManager *appMan, int *param1);
int ActingCompetition_Exit(ApplicationManager *appMan, int *param1);
void contest_competition_0223BB14(ActingCompetition *param0, int param1, int param2);

#endif // POKEPLATINUM_CONTEST_COMPETITION_H
