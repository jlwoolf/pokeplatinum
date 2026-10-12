#ifndef POKEPLATINUM_CONTEST_COMPETITION_0223F7E4_H
#define POKEPLATINUM_CONTEST_COMPETITION_0223F7E4_H

#include "contest_competition/struct_acting_move_menu_decl.h"
#include "contest_competition/struct_acting_competition_scene.h"
#include "contest_competition/struct_acting_match_state.h"

#include "bg_window.h"
#include "contest.h"

void contest_competition_0223F80C(BgConfig *param0);
void contest_competition_0223F864(BgConfig *param0);
void *contest_competition_0223F88C(Contest *param0, ActingCompetitionScene *param1, ActingMatchState *param2);
void contest_competition_0223F960(ActingMoveMenu *param0);
void contest_competition_0223F9C4(ActingMoveMenu *param0, int param1, int param2, void *param3);
int contest_competition_0223FAF8(ActingMoveMenu *param0);
BOOL contest_competition_0223FBC0(ActingMoveMenu *param0);
void contest_competition_02240A80(ActingMoveMenu *param0, u16 param1[]);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0223F7E4_H
