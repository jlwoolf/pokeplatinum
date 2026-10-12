#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H

#include <nitro/fx/fx.h>

#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL unk_00;
    BOOL unk_04;
    VecFx32 unk_08;
    PoffinCookingMotionAnim unk_14;
    PoffinCookingMotionAnim unk_2C;
    Sprite *unk_44;
} PoffinCookingSparkle;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_H
