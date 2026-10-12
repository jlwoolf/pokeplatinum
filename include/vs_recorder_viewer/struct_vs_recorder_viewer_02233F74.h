#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233F74_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233F74_H

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_decls/struct_02030A80_decl.h"

#include "bg_window.h"
#include "sprite_system.h"

typedef struct {
    PlayerProfile *profile;
    BattleRecordingSummary *summary;
    u8 padding_08[4];
    ManagedSprite *sprites[12];
    Window windows[8];
} VsRecorderViewerSummaryPanel;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233F74_H
