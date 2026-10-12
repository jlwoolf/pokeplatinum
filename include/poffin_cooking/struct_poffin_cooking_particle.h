#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H

#include <nitro/fx/fx.h>

#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL unk_00;
    BOOL unk_04;
    BOOL unk_08;
    BOOL unk_0C;
    BOOL unk_10;
    VecFx32 unk_14;
    VecFx32 unk_20;
    s32 unk_2C;
    PoffinCookingMotionAnim unk_30;
    PoffinCookingMotionAnim unk_48;
    PoffinCookingMotionAnim unk_60;
    Sprite *unk_78;
    int unk_7C;
} PoffinCookingParticle;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_H
