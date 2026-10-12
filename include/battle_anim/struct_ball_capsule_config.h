#ifndef POKEPLATINUM_STRUCT_BALL_CAPSULE_CONFIG_H
#define POKEPLATINUM_STRUCT_BALL_CAPSULE_CONFIG_H

#include "pokemon.h"

typedef struct {
    int battlerType;
    int ballTypeOverride;
    Pokemon *mon;
} BallCapsuleConfig;

#endif // POKEPLATINUM_STRUCT_BALL_CAPSULE_CONFIG_H
