#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICIPANT_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICIPANT_H

#include "poffin_cooking/struct_poffin_cooking_touch_input.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"

typedef struct {
    PoffinCookingTouchInput touchInput;
    PoffinCookingBlendState blendState;
} PoffinCookingParticipant;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICIPANT_H
