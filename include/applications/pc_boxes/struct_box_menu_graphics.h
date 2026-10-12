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
    BgConfig *bgConfig;
    u8 padding_04[4];
    const BoxApplication *boxApp;
    BoxGraphics *boxGraphics;
    MessageLoader *boxMessagesLoader;
    MessageLoader *systemMessagesLoader;
    Window *windows;
    u16 messageVisible;
    u16 menuVisible;
    int optionsFrame;
    void *charDataFile;
    NNSG2dCharacterData *charData;
    const StringTemplate *messageVariableBuffer;
    String *messageString;
    String *formattedString;
} BoxMenuGraphics;

#endif // POKEPLATINUM_STRUCT_BOX_MENU_GRAPHICS_H
