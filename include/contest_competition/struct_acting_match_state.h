#ifndef POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H
#define POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H

#include "constants/contests.h"

#include "contest_competition/struct_acting_turn_state.h"

typedef struct {
    u8 unk_00;
    u8 unk_01[4];
    u8 unk_05;
    u16 moveIDs[CONTEST_NUM_PARTICIPANTS];
    u8 unk_0E[CONTEST_NUM_PARTICIPANTS];
    s16 unk_12[CONTEST_NUM_PARTICIPANTS];
    s16 unk_1A[4];
    s8 unk_22[3];
    u16 unk_26[4];
    ActingTurnState unk_30;
} ActingMatchState;

#endif // POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H
