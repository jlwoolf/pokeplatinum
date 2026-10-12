#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H

#include <nitro/fx/fx.h>

#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL state;
    BOOL motionDone;
    BOOL animDone;
    BOOL hasScale;
    BOOL followStir;
    VecFx32 position;
    VecFx32 scale;
    s32 angle;
    PoffinCookingMotionAnim motionX;
    PoffinCookingMotionAnim motionY;
    PoffinCookingMotionAnim motionScale;
    Sprite *sprite;
    int serial;
} PoffinCookingParticle;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H
