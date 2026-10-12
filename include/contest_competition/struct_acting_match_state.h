#ifndef POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H
#define POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H

#include "constants/contests.h"

#include "contest_competition/struct_acting_turn_state.h"

typedef struct {
    u8 turn;
    u8 contestantOrder[4];
    u8 contestantCount;
    u16 moveIDs[CONTEST_NUM_PARTICIPANTS];
    u8 contestantIDs[CONTEST_NUM_PARTICIPANTS];
    s16 scores[CONTEST_NUM_PARTICIPANTS];
    s16 turnScores[4];
    s8 appealHistory[3];
    u16 previousMoveIDs[4];
    ActingTurnState turnState;
} ActingMatchState;

#endif // POKEPLATINUM_STRUCT_ACTING_MATCH_STATE_H
