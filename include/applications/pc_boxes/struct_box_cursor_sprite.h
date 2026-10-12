#ifndef POKEPLATINUM_STRUCT_BOX_CURSOR_SPRITE_H
#define POKEPLATINUM_STRUCT_BOX_CURSOR_SPRITE_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_view.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_party.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"
#include "applications/pc_boxes/struct_box_held_item_icons_decl.h"

#include "sprite.h"

typedef struct {
    SpriteList *unk_00;
    Sprite *unk_04;
    Sprite *unk_08;
    Sprite *unk_0C;
    Sprite *unk_10;
    void *unk_14;
    void *unk_18;
    NNSG2dCellDataBank *unk_1C;
    NNSG2dAnimBankData *unk_20;
    NNSG2dImageProxy unk_24;
    BoxMonSpriteManager *unk_48;
    BoxMonSprite unk_4C[30];
    struct {
        fx32 unk_00;
        fx32 unk_04;
    } unk_664[30];
    u32 unk_754;
    BoxView *unk_758;
    BoxParty *unk_75C;
    BoxHeldItemIcons *unk_760;
    s32 unk_764;
    s32 unk_768;
    s32 unk_76C;
    s32 unk_770;
    s32 unk_774;
    s32 unk_778;
    s32 unk_77C;
    s32 unk_780;
    u8 unk_784;
    u8 unk_785;
    u8 unk_786;
    u8 unk_787;
    u8 unk_788;
    s8 unk_789;
    s8 unk_78A;
    s8 unk_78B;
    u8 unk_78C;
    u8 unk_78D;
    u8 unk_78E;
    u8 padding_78F;
    const BoxApplication *unk_790;
    BoxGraphics *unk_794;
} BoxCursorSprite;

#endif // POKEPLATINUM_STRUCT_BOX_CURSOR_SPRITE_H
