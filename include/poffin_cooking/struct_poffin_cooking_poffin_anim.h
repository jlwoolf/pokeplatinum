#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H

#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"

#include "sprite.h"

typedef struct {
    BOOL active;
    BOOL animating;
    Sprite *poffinSprites[4];
    Sprite *burstSprites[4];
    PoffinCookingSpriteSet spriteSets[4];
    int count;
    PoffinCookingMotionAnim motionX[4];
    PoffinCookingMotionAnim motionY[4];
    int states[4];
    int delays[4];
    int nextIndex;
} PoffinCookingPoffinAnim;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_POFFIN_ANIM_H
