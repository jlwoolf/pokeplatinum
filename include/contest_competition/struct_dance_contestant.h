#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H

#include "contest_competition/struct_dance_move_data.h"

typedef struct {
    u8 unk_00[32];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    DanceMoveData unk_24;
} DanceContestant;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_H
