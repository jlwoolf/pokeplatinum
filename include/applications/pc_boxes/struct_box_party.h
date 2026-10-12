#ifndef POKEPLATINUM_STRUCT_BOX_PARTY_H
#define POKEPLATINUM_STRUCT_BOX_PARTY_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_view.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"
#include "sprite.h"

typedef struct {
    BoxGraphics *unk_00;
    BgConfig *unk_04;
    SpriteList *unk_08;
    const BoxApplication *unk_0C;
    BoxView *unk_10;
    void *unk_14;
    NNSG2dScreenData *unk_18;
    void *unk_1C;
    fx32 unk_20;
    fx32 unk_24;
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 unk_2B;
    BOOL unk_2C;
    u32 unk_30;
    int unk_34;
    BoxMonSpriteManager *unk_38;
    BoxMonSprite unk_3C[6];
    u8 unk_174;
    u8 padding_175[3];
} BoxParty;

#endif // POKEPLATINUM_STRUCT_BOX_PARTY_H
