#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H

#include "contest_competition/struct_dance_move_data.h"

typedef struct {
    u8 name[32];
    u8 poseTimer;
    u8 moveArg1;
    u8 moveArg2;
    u8 moveArg3;
    DanceMoveData moveData;
} DanceContestant;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H
