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
    SpriteList *spriteList;
    Sprite *monSprite;
    Sprite *shadowSprite;
    Sprite *leftArrowSprite;
    Sprite *rightArrowSprite;
    void *cellBank;
    void *animBank;
    NNSG2dCellDataBank *cellBankData;
    NNSG2dAnimBankData *animBankData;
    NNSG2dImageProxy imageProxy;
    BoxMonSpriteManager *monSpriteManager;
    BoxMonSprite heldMons[30];
    struct {
        fx32 x;
        fx32 y;
    } heldMonOffsets[30];
    u32 heldMonCount;
    BoxView *boxView;
    BoxParty *boxParty;
    BoxHeldItemIcons *heldItemIcons;
    s32 x;
    s32 y;
    s32 targetX;
    s32 targetY;
    s32 fxX;
    s32 fxY;
    s32 velocityX;
    s32 velocityY;
    u8 state;
    u8 cursorLocation;
    u8 destCursorLocation;
    u8 moveSteps;
    u8 animFinished;
    s8 boxCol;
    s8 boxRow;
    s8 partyPos;
    u8 isHoldingMon;
    u8 isHoldingItem;
    u8 shadowEnabled;
    u8 padding_78F;
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
} BoxCursorSprite;

#endif // POKEPLATINUM_STRUCT_BOX_CURSOR_SPRITE_H
