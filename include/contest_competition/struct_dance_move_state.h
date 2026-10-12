#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H

#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_move_definition.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02[CONTEST_NUM_PARTICIPANTS];
    u32 unk_08;
    u32 unk_0C;
    u16 unk_10;
    u32 unk_14[CONTEST_NUM_PARTICIPANTS];
    DanceMoveDefinition unk_24;
    DanceMessageArgs unk_30;
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
} DanceMoveState;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H
