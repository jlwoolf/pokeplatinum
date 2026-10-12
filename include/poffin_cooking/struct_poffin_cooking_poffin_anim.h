#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H

#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL unk_00;
    BOOL unk_04;
    Sprite *unk_08[4];
    Sprite *unk_18[4];
    PoffinCookingSpriteSet unk_28[4];
    int unk_108;
    PoffinCookingMotionAnim unk_10C[4];
    PoffinCookingMotionAnim unk_16C[4];
    int unk_1CC[4];
    int unk_1DC[4];
    int unk_1EC;
} PoffinCookingPoffinAnim;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H
