#ifndef POKEPLATINUM_STRUCT_BOX_VIEW_H
#define POKEPLATINUM_STRUCT_BOX_VIEW_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"

typedef struct {
    u8 boxID;
    u8 wallpaperTileBase;
    u8 wallpaperBuffer;
    u8 prevWallpaperBuffer;
    u32 scrollStepCount;
    s32 offsetStart;
    s32 bgXOffset;
    s32 offsetStep;
    s32 offsetEnd;
    u8 padding_18[24];
    u32 reloadBoxID;
    u32 reloadBuffer;
    fx32 monStartPositions[2][6];
    fx32 monTargetPositions[2][6];
    u32 boxChanging;
    BOOL boxChangeDone;
    u16 boxCursorPosition;
    u8 state;
    u8 reloadTaskActive;
    u8 monState;
    u8 padding_A5[3];
    BoxMonSprite monSprites[2][30];
    u8 iconCharData[30][640];
    u16 iconSpriteIndices[30];
    u16 species[30];
    u8 padding_5850[4];
    int leftBoxX;
    int rightBoxX;
    int compareXOffset;
    u16 blendedPalette[9][16];
    BoxMonSpriteManager *monSpriteManager;
    BgConfig *bgConfig;
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
} BoxView;

#endif // POKEPLATINUM_STRUCT_BOX_VIEW_H
