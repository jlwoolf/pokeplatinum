#ifndef POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_ARGS_H
#define POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_ARGS_H

typedef struct {
    u32 flags;
    u16 actingAnimationMoveID;
    u8 isContestant;
    u8 hasFriendship;
    u8 friendship;
} ActingMoveAnimArgs;

#endif // POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_ARGS_H
