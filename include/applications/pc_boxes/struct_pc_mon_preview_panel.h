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
    BOOL unk_00;
    Window *unk_04;
    BgConfig *unk_08;
    SpriteList *unk_0C;
    const BoxApplication *unk_10;
    BoxGraphics *unk_14;
    FontSpecialCharsContext *unk_18;
    FontSpecialCharsContext *unk_1C;
    PokemonSpriteManager *unk_20;
    PokemonSprite *unk_24;
    void *unk_28;
    NNSG2dCellDataBank *unk_2C;
    Sprite *unk_30;
    void *unk_34;
    NNSG2dCellDataBank *unk_38;
    Sprite *unk_3C[2];
    String *unk_44;
    String *unk_48;
    SysTask *unk_4C;
    u8 padding_50[4];
} PCMonPreviewPanel;

#endif // POKEPLATINUM_STRUCT_PC_MON_PREVIEW_PANEL_H
