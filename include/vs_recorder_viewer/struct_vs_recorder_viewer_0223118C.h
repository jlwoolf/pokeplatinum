#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223118C_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223118C_H

#include "struct_decls/struct_02012744_decl.h"

#include "global_terminal/global_terminal_0222B008.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223118C_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233310.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223359C.h"

#include "bg_window.h"
#include "g3d_pipeline.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "pokemon_sprite.h"
#include "sprite_system.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"

typedef struct {
    NARC *narc;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    u8 padding_0C[4];
    BgConfig *bgConfig;
    PaletteData *palette;
    TouchScreenActions *touchScreenActions;
    TouchScreenRect touchRects[5];
    BOOL returnToMainMenu;
    MessageLoader *messageLoader;
    MessageLoader *secondaryMessageLoader;
    FontOAMManager *fontOAMManager;
    int fadeValue;
    int themeColor;
    u8 theme;
    u8 padding_49[3];
    G3DPipelineBuffers *g3dPipeline;
    PokemonSpriteManager *pokemonSpriteManager;
    VsRecorderViewerTransferContext transferContext;
    VsRecorderViewerListScrollBar scrollBar;
    VsRecorderViewerListWindow listWindow;
    u8 padding_4D8[24];
    VsRecorderViewerMenuSubContext subContext;
    BOOL drawing;
    BOOL drawSuspended;
} VsRecorderViewerMenuContext;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223118C_H
