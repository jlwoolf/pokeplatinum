#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB2_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB2_H

#include "bg_window.h"
#include "narc.h"
#include "palette.h"
#include "sprite_system.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"

typedef struct {
    NARC *narc;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    PaletteData *palette;
    TouchScreenActions *touchScreenActions;
    TouchScreenRect touchRects[24];
    BOOL cursorHidden;
} VsRecorderViewerIdEntryGraphics;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB2_H
