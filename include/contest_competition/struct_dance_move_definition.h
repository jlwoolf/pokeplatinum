#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H

#include "contest_competition/struct_dance_move_scores.h"

typedef struct {
    u16 moveID;
    u16 unused_02;
    u8 duration;
    u8 beatCount;
    u8 unused_06;
    u8 unused_07;
    DanceMoveScores scores;
} DanceMoveDefinition;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H
