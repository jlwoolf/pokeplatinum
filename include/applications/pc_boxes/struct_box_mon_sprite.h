#ifndef POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H
#define POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H

#include <nnsys.h>

#include "sprite.h"

typedef struct {
    Sprite *sprite;
    NNSG2dImageProxy imageProxy;
    u32 iconSpriteIndex;
    u16 paletteIndex;
    u16 markings;
    u16 heldItem;
    u8 padding_32[2];
} BoxMonSprite;

#endif // POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H
