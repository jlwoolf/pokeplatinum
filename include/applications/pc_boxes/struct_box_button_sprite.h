#ifndef POKEPLATINUM_STRUCT_BOX_BUTTON_SPRITE_H
#define POKEPLATINUM_STRUCT_BOX_BUTTON_SPRITE_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "sprite.h"

typedef struct {
    SpriteList *spriteList;
    Sprite *sprite;
    void *cellBank;
    void *animBank;
    NNSG2dCellDataBank *cellBankData;
    NNSG2dAnimBankData *animBankData;
    NNSG2dImageProxy imageProxy;
    SpriteList *buttonSpriteList;
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
} BoxButtonSprite;

#endif // POKEPLATINUM_STRUCT_BOX_BUTTON_SPRITE_H
