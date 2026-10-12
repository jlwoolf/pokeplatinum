#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_BURST_EFFECT_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_BURST_EFFECT_H

#include "poffin_cooking/struct_poffin_cooking_scale_anim.h"

#include "software_sprite.h"

typedef struct {
    SoftwareSpriteChars *chars[6];
    SoftwareSpritePalette *palettes[8];
    SoftwareSprite *sprites[8];
    PoffinCookingScaleAnim scaleAnim;
    int scaleState;
    int scaleDirection;
    int active;
} PoffinCookingBurstEffect;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_BURST_EFFECT_H
