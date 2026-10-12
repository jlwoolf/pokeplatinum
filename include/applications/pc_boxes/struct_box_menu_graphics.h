#ifndef POKEPLATINUM_STRUCT_BOX_MENU_GRAPHICS_H
#define POKEPLATINUM_STRUCT_BOX_MENU_GRAPHICS_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"

#include "bg_window.h"
#include "message.h"
#include "string_gf.h"
#include "string_template.h"

typedef struct {
    BgConfig *unk_00;
    u8 padding_04[4];
    const BoxApplication *unk_08;
    BoxGraphics *unk_0C;
    MessageLoader *unk_10;
    MessageLoader *unk_14;
    Window *unk_18;
    u16 unk_1C;
    u16 unk_1E;
    int unk_20;
    void *unk_24;
    NNSG2dCharacterData *unk_28;
    const StringTemplate *unk_2C;
    String *unk_30;
    String *unk_34;
} BoxMenuGraphics;

#endif // POKEPLATINUM_STRUCT_BOX_MENU_GRAPHICS_H
