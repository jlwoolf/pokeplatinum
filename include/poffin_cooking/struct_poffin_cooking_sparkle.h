#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H

#include <nitro/fx/fx.h>

#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL active;
    BOOL motionDone;
    VecFx32 position;
    PoffinCookingMotionAnim motionX;
    PoffinCookingMotionAnim motionY;
    Sprite *sprite;
} PoffinCookingSparkle;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H
