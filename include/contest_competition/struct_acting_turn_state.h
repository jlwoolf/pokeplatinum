#ifndef POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H
#define POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H

#include "contest_competition/struct_acting_performance.h"
#include "contest_competition/struct_acting_previous_move.h"

typedef struct {
    ActingPerformance unk_00[4];
    ActingPreviousMove unk_A0[4];
    s8 unk_B0[3];
    s8 unk_B3[3];
} ActingTurnState;

#endif // POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H
