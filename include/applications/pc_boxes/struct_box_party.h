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
    BoxGraphics *boxGraphics;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    const BoxApplication *boxApp;
    BoxView *boxView;
    void *screenDataFile;
    NNSG2dScreenData *screenData;
    void *monPath;
    fx32 pathStepX;
    fx32 pathStepY;
    u8 monIndex;
    u8 shiftMonCount;
    u8 pathStep;
    u8 windowOffset;
    BOOL taskActive;
    u32 tileOffset;
    int xOffset;
    BoxMonSpriteManager *monSpriteManager;
    BoxMonSprite monSprites[6];
    u8 state;
    u8 padding_175[3];
} BoxParty;

#endif // POKEPLATINUM_STRUCT_BOX_PARTY_H
