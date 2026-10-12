#ifndef POKEPLATINUM_STRUCT_BOX_SELECTION_POPUP_H
#define POKEPLATINUM_STRUCT_BOX_SELECTION_POPUP_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "bg_window.h"
#include "font_special_chars.h"
#include "message.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task_manager.h"

typedef struct {
    BoxGraphics *boxGraphics;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    const BoxApplication *boxApp;
    Window *windows;
    void *charDataFile;
    NNSG2dCharacterData *charData;
    void *cellBank;
    NNSG2dCellDataBank *cellBankData;
    u8 padding_24[8];
    void *screenDataFile1;
    NNSG2dScreenData *screenData1;
    void *screenDataFile2;
    NNSG2dScreenData *screenData2;
    Bitmap boxIconBitmap;
    FontSpecialCharsContext *fontContext;
    Sprite *boxIconSprites[18];
    Sprite *monIconSprite;
    u32 boxMonCounts[18];
    SysTask *task;
    s32 boxSelectionBoxID;
    u16 paletteBuffer[8][48];
    u8 iconBuffer[18][1024];
    u8 iconLoaded[18];
    u8 padding_4BF6[2];
    MessageLoader *itemDescriptionLoader;
    String *string;
} BoxSelectionPopup;

#endif // POKEPLATINUM_STRUCT_BOX_SELECTION_POPUP_H
