#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATE_H

typedef struct {
    u32 stirLevel;
    u32 revolutions;
    s32 angle;
    s32 speed;
    BOOL onTrack;
} PoffinCookingStirState;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATE_H
