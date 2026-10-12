#ifndef POKEPLATINUM_STRUCT_ACTING_PREVIOUS_MOVE_H
#define POKEPLATINUM_STRUCT_ACTING_PREVIOUS_MOVE_H

typedef struct {
    u32 moveID : 16;
    u32 contestMoveEffect : 8;
    u32 : 8;
} ActingPreviousMove;

#endif // POKEPLATINUM_STRUCT_ACTING_PREVIOUS_MOVE_H
