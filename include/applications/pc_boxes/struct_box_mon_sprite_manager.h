#ifndef POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H
#define POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "narc.h"
#include "sprite.h"

typedef struct {
    void *animBank;
    NNSG2dAnimBankData *animBankData;
    void *cellBank;
    u8 padding_0C;
    NNSG2dCellDataBank *cellBankData;
    void *formCellBank;
    void *formAnimBank;
    NNSG2dCellDataBank *formCellBankData;
    NNSG2dAnimBankData *formAnimBankData;
    SpriteList *spriteList;
    u8 padding_28[24];
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
    NARC *iconNarc;
    u8 iconBuffer[640];
} BoxMonSpriteManager;

#endif // POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H
