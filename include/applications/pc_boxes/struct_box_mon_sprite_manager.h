#ifndef POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H
#define POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "narc.h"
#include "sprite.h"

typedef struct {
    void *unk_00;
    NNSG2dAnimBankData *unk_04;
    void *unk_08;
    u8 padding_0C;
    NNSG2dCellDataBank *unk_10;
    void *unk_14;
    void *unk_18;
    NNSG2dCellDataBank *unk_1C;
    NNSG2dAnimBankData *unk_20;
    SpriteList *unk_24;
    u8 padding_28[24];
    const BoxApplication *unk_40;
    BoxGraphics *unk_44;
    NARC *unk_48;
    u8 unk_4C[640];
} BoxMonSpriteManager;

#endif // POKEPLATINUM_STRUCT_BOX_MON_SPRITE_MANAGER_H
