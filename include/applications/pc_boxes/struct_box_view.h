#ifndef POKEPLATINUM_STRUCT_BOX_VIEW_H
#define POKEPLATINUM_STRUCT_BOX_VIEW_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"

typedef struct {
    u8 boxID;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 padding_18[24];
    u32 unk_30;
    u32 unk_34;
    fx32 unk_38[2][6];
    fx32 unk_68[2][6];
    u32 unk_98;
    BOOL unk_9C;
    u16 unk_A0;
    u8 unk_A2;
    u8 unk_A3;
    u8 unk_A4;
    u8 padding_A5[3];
    BoxMonSprite unk_A8[2][30];
    u8 unk_CD8[30][640];
    u16 unk_57D8[30];
    u16 unk_5814[30];
    u8 padding_5850[4];
    int unk_5854;
    int unk_5858;
    int unk_585C;
    u16 unk_5860[9][16];
    BoxMonSpriteManager *unk_58F0;
    BgConfig *unk_58F4;
    const BoxApplication *unk_58F8;
    BoxGraphics *unk_58FC;
} BoxView;

#endif // POKEPLATINUM_STRUCT_BOX_VIEW_H
