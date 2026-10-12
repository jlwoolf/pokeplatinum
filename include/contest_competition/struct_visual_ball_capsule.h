#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_H

#include "battle_anim/struct_ball_capsule_seal_effect_decl.h"
#include "battle_anim/struct_ball_capsule_config.h"

#include "pokemon.h"

typedef struct {
    BallCapsuleConfig config;
    BallCapsuleSealEffect *sealEffect;
    Pokemon *mon;
    u8 state;
    u8 done;
} VisualBallCapsule;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_H
