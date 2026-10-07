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
    NARC *unk_00;
    SpriteSystem *unk_04;
    SpriteManager *unk_08;
    u8 padding_0C[4];
    BgConfig *unk_10;
    PaletteData *unk_14;
    TouchScreenActions *unk_18;
    TouchScreenRect unk_1C[5];
    BOOL unk_30;
    MessageLoader *unk_34;
    MessageLoader *unk_38;
    FontOAMManager *unk_3C;
    int unk_40;
    int unk_44;
    u8 unk_48;
    u8 padding_49[3];
    G3DPipelineBuffers *unk_4C;
    PokemonSpriteManager *unk_50;
    VsRecorderViewerTransferContext unk_54;
    VsRecorderViewerListScrollBar unk_46C;
    VsRecorderViewerListWindow unk_48C;
    u8 padding_4D8[24];
    VsRecorderViewerMenuSubContext unk_4F0;
    BOOL unk_510;
    BOOL unk_514;
} VsRecorderViewerMenuContext;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223118C_H
