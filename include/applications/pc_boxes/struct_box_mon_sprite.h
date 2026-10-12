#ifndef POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H
#define POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H

#include <nnsys.h>

#include "sprite.h"

typedef struct {
    Sprite *unk_00;
    NNSG2dImageProxy unk_04;
    u32 unk_28;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u8 padding_32[2];
} BoxMonSprite;

#endif // POKEPLATINUM_STRUCT_BOX_MON_SPRITE_H
