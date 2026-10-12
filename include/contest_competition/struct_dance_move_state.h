#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H

#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_move_definition.h"

typedef struct {
    u8 state;
    u8 moveIndex;
    u8 contestantIDs[CONTEST_NUM_PARTICIPANTS];
    u32 duration;
    u32 beatInterval;
    u16 beat;
    u32 moveIDs[CONTEST_NUM_PARTICIPANTS];
    DanceMoveDefinition moveDefinition;
    DanceMessageArgs messageArgs;
    u8 messageID;
    u8 delay;
    u8 flag;
} DanceMoveState;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_STATE_H
