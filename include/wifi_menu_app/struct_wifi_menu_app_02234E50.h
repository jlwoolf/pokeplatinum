#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_02234E50_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_02234E50_H

#include <nnsys.h>

#include "struct_decls/font_oam.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "string_template.h"
#include "touch_screen_actions.h"

typedef struct {
    StringTemplate *template;
    void *screenDataBuffer;
    NNSG2dScreenData *screenData;
    void *pageScreenDataBuffers[7];
    NNSG2dScreenData *pageScreenData[7];
    void *headerScreenDataBuffer;
    NNSG2dScreenData *headerScreenData;
    TouchScreenActions *actions;
    u8 friendListState[32];
    u8 rowIndex;
    u8 selection;
    u8 selectionFrame;
    u8 state;
    s8 detailPage;
    u8 listDirty;
    u8 animTimer;
    u8 prevSelection;
    BOOL fullRedraw;
    Window nameWindows[8];
    Window statusWindows[8][2];
    Window detailWindow;
    SpriteResource *resources[4];
    Sprite *buttonSprites[3];
    CharTransferAllocation charAllocation;
    FontOAM *fontOAM;
    u32 buttonMode;
    u32 pressedButton;
    u32 buttonInput;
    TouchScreenActions *buttonActions;
} WiFiMenuAppTouchScreen;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_02234E50_H
