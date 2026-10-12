#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_H

#include "struct_decls/struct_020F3DCC_decl.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0_sub1.h"

typedef struct {
    VsRecorderViewerMenuEntry mainEntries[5];
    VsRecorderViewerMenuEntry subEntries[5];
    const VsRecorderMenuEntry *entryConfigs[5];
    int mainEntryCount;
    u8 padding_1A8[4];
    int subEntryCount;
    int selectedIndex;
    u8 padding_1B4[8];
} VsRecorderViewerMenu;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_H
