#ifndef POKEPLATINUM_STRUCT_PC_MON_PREVIEW_PANEL_H
#define POKEPLATINUM_STRUCT_PC_MON_PREVIEW_PANEL_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "bg_window.h"
#include "font_special_chars.h"
#include "pokemon_sprite.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task_manager.h"

typedef struct {
    BOOL isLoaded;
    Window *windows;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
    FontSpecialCharsContext *dexNumFont;
    FontSpecialCharsContext *levelFont;
    PokemonSpriteManager *pokemonSpriteManager;
    PokemonSprite *monSprite;
    void *cellBank;
    NNSG2dCellDataBank *cellBankData;
    Sprite *infoSprite;
    void *typeIconBank;
    NNSG2dCellDataBank *typeIconCellBank;
    Sprite *typeIconSprites[2];
    String *maleString;
    String *femaleString;
    SysTask *task;
    u8 padding_50[4];
} PCMonPreviewPanel;

#endif // POKEPLATINUM_STRUCT_PC_MON_PREVIEW_PANEL_H
