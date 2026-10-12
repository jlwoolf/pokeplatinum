#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H

#include "contest_competition/struct_dance_move_scores.h"

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    DanceMoveScores unk_08;
} DanceMoveDefinition;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_DEFINITION_H
