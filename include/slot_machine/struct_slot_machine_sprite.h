#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_SPRITE_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_SPRITE_H

#include <nnsys.h>

#include "sprite.h"

typedef struct {
    int hasCharTransfer;
    Sprite *sprite;
    const NNSG2dImageProxy *imageProxy;
} SlotMachineSprite;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_SPRITE_H
