#ifndef POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H
#define POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H

#include "contest_competition/struct_acting_performance.h"
#include "contest_competition/struct_acting_previous_move.h"

typedef struct {
    ActingPerformance performances[4];
    ActingPreviousMove previousMoves[4];
    s8 voltage[3];
    s8 voltageDisplay[3];
} ActingTurnState;

#endif // POKEPLATINUM_STRUCT_ACTING_TURN_STATE_H
